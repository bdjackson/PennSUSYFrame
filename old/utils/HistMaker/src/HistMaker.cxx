#include "include/HistMaker.h"

// -----------------------------------------------------------------------------
HistMaker::HistMaker( TTree *tree
                    , double num_events
                    , std::string out_file_name
                    )
                    : NtupleHelper::NtupleLooper(tree, num_events)
                    , m_out_file(NULL)
                    , m_entry_num(0)
{
  m_out_file = new TFile(out_file_name.c_str(), "UPDATE");
}

// -----------------------------------------------------------------------------
HistMaker::~HistMaker()
{
  m_out_file->Close();
}

// -----------------------------------------------------------------------------
void HistMaker::addCut( std::string key
                      , Selection::EventSelection& selecton
                      , Selection::WeightHandler& weight
                      )
{
  std::cout << "adding cut: " << key << "\n";

  m_keys.push_back(key);
  m_selection[key] = selecton;
  m_weight[key] = weight;
}

// -----------------------------------------------------------------------------
void HistMaker::addHist(const HistInfo& hist_info)
{
  std::cout << "adding hist: " << hist_info.getName() << "\n";

  m_hist_info.push_back(hist_info);
}

// -----------------------------------------------------------------------------
void HistMaker::Loop()
{
  std::vector<std::string>::iterator key_it = m_keys.begin();
  std::vector<std::string>::iterator key_term = m_keys.end();
  for (; key_it != key_term; ++key_it) {
    fillHists(*key_it);
  }
}

// -----------------------------------------------------------------------------
void HistMaker::processEvent()
{
  std::vector<std::string>::iterator key_it = m_keys.begin();
  std::vector<std::string>::iterator key_term = m_keys.end();
  for (; key_it != key_term; ++key_it) {
    if (m_selection[*key_it].passEvent(m_event_desc, m_sr_helper))
      fillHists(*key_it);
  }
}

// -----------------------------------------------------------------------------
void HistMaker::writeToFile()
{
  // loop though cut directories
  std::vector<std::string>::iterator key_it = m_keys.begin();
  std::vector<std::string>::iterator key_term = m_keys.end();
  for (; key_it != key_term; ++key_it) {
    m_out_file->cd();
    TDirectory* d = m_out_file->GetDirectory((*key_it).c_str());
    if (d == NULL) d = m_out_file->mkdir((*key_it).c_str());

    d->cd();

    size_t num_hists = m_hist_info.size();
    for (size_t hist_it = 0; hist_it != num_hists; ++hist_it) {
      TH1* tmp_hist = m_hist.at(*key_it).at(hist_it);
      std::string hist_name = m_hist_info.at(hist_it).getName();
      tmp_hist->Write(hist_name.c_str());
    }
  }
}

// -----------------------------------------------------------------------------
void HistMaker::fillHists(std::string key)
{
  // Get weights for this selection and event
  TCut evt_weight = m_weight[key].getWeightString().c_str();

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // get the selection cuts for this event
  ull_t pass_event = m_selection[key].getPassEventWord()->toInt();
  ull_t pass_sr    = m_selection[key].getPassSRWord()->toInt();

  std::stringstream ss_pass_event;
  ss_pass_event << "((event_desc & " << pass_event
                << ") == " << pass_event << ") ";
  TCut cut_pass_event = ss_pass_event.str().c_str();

  std::stringstream ss_pass_sr;
  ss_pass_sr << "((sr_helper & " << pass_sr
             << ") == " << pass_sr << ") ";
  TCut cut_pass_sr = ss_pass_sr.str().c_str();

  TCut additional_cuts = m_selection[key].getAdditionalCutString().c_str();

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  TCut full_selection = evt_weight * (  cut_pass_event
                                     && cut_pass_sr
                                     && additional_cuts
                                     );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  std::vector<HistInfo>::iterator hist_it = m_hist_info.begin();
  std::vector<HistInfo>::iterator hist_term = m_hist_info.end();
  for (; hist_it != hist_term; ++hist_it) {
    TH1* tmp_hist = hist_it->genHist(key);

    std::string var_exp = ( hist_it->getVarExp() + " >> "
                          + hist_it->getName() + "__" + key
                          );

    TCut hist_selection = full_selection;
    if (hist_it->getHistCut() != "") {
      hist_selection = hist_selection && ( TCut(hist_it->getHistCut().c_str()) );
    }
    std::cout << "var_exp: " << var_exp << "\n";
    std::cout << "full_selection: " << full_selection << "\n";
    std::cout << "hist_selection: " << hist_selection << "\n";
    fChain->Draw(var_exp.c_str(), hist_selection, "goff");

    m_hist[key].push_back(tmp_hist);
  }
}