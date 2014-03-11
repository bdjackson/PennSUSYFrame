#include "include/PlotNtupleMaker.h"

#include <iostream>
#include <sstream>
#include <map>
#include <vector>

#include <TROOT.h>
#include <TCut.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
// #include "TVectorD.h"

#include "NtupleLooper/include/NtupleLooper.h"

#include "Selection/include/EventSelection.h"
#include "Selection/include/WeightHandler.h"

#include "SusyAnalysisTools/include/EventDescription.h"
#include "SusyAnalysisTools/include/SRHelper.h"
#include "SusyAnalysisTools/include/SusyEnums.h"

// -----------------------------------------------------------------------------
PlotNtupleMaker::PlotNtupleMaker( TTree *tree
                                , double events
                                , std::string out_file_name
                                )
                                : NtupleHelper::NtupleLooper(tree, events)
                                , m_out_file(NULL)
                                , m_entry_num(0)
{
  m_out_file = new TFile(out_file_name.c_str(), "recreate");
}

// -----------------------------------------------------------------------------
PlotNtupleMaker::~PlotNtupleMaker()
{
  // do nothing
}

// -----------------------------------------------------------------------------
void PlotNtupleMaker::addCut( std::string key
                            , Selection::EventSelection& selecton
                            )
{
  std::cout << "adding cut: " << key << "\n";

  m_keys.push_back(key);
  m_selection[key] = selecton;
}

// -----------------------------------------------------------------------------
void PlotNtupleMaker::Loop()
{
  std::vector<std::string>::iterator key_it = m_keys.begin();
  std::vector<std::string>::iterator key_term = m_keys.end();
  for (; key_it != key_term; ++key_it) {
    std::cout << "filter tree - key: " << *key_it << "\n";
    filterTree(*key_it);
  }

  m_out_file->cd();
  std::cout << "writing num_events\n";
  TH1D num_events("num_events", "num_events", 1, -0.5, 0.5);
  num_events.Fill(0., m_num_events);
  // TVectorD num_events(1);
  // num_events[0] = m_num_events;
  num_events.Write("num_events");
}

// -----------------------------------------------------------------------------
void PlotNtupleMaker::processEvent()
{
  // do nothing
}

// -----------------------------------------------------------------------------
void PlotNtupleMaker::writeToFile()
{
  // loop though cut directories
  std::vector<std::string>::iterator key_it = m_keys.begin();
  std::vector<std::string>::iterator key_term = m_keys.end();
  for (; key_it != key_term; ++key_it) {
    m_out_file->cd();
    // TDirectory* d = m_out_file->GetDirectory((*key_it).c_str());
    // if (d == NULL) d = m_out_file->mkdir((*key_it).c_str());
    //
    // d->cd();
  }
}

// -----------------------------------------------------------------------------
void PlotNtupleMaker::writeToFile(std::string key, TTree* tree_to_write)
{
  m_out_file->cd();
  tree_to_write->Write(key.c_str());
}

// -----------------------------------------------------------------------------
void PlotNtupleMaker::filterTree(std::string key)
{
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
  TCut full_selection = (  cut_pass_event
                        && cut_pass_sr
                        && additional_cuts
                        );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Copy fChain into temp tree with selection applied
  std::cout << "key: " << key <<"\n";
  std::cout << "\tfull selection: " << full_selection << "\n";
  TTree* tmp_tree = fChain->CopyTree(full_selection);

  writeToFile(key, tmp_tree);
}