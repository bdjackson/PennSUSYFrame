#include "CalculateFakeRates/include/CalculateFakeRates.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#include <TCanvas.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2.h>
#include <TROOT.h>
#include <TStyle.h>

#include "NtupleLooper/include/NtupleLooper.h"

#include "SusyAnalysisTools/include/EventDescription.h"
#include "SusyAnalysisTools/include/SRHelper.h"
#include "SusyAnalysisTools/include/SusyEnums.h"
#include "SusyAnalysisTools/include/ElectronDescription.h"
#include "SusyAnalysisTools/include/MuonDescription.h"

// -----------------------------------------------------------------------------
CalculateFakeRates::CalculateFakeRates( TTree *tree
                                      , double num_events) : NtupleLooper(tree, num_events)
                                                           , m_el_re(NULL)
                                                           , m_el_re_numer(NULL)
                                                           , m_el_re_denom(NULL)
                                                           , m_mu_re(NULL)
                                                           , m_mu_re_numer(NULL)
                                                           , m_mu_re_denom(NULL)
                                                           , m_el_fr(NULL)
                                                           , m_el_fr_numer(NULL)
                                                           , m_el_fr_denom(NULL)
                                                           , m_mu_fr(NULL)
                                                           , m_mu_fr_numer(NULL)
                                                           , m_mu_fr_denom(NULL)
{
  double pt_bins[7] = {0., 15., 30., 55., 100., 250., 500.};

  m_el_re_numer = new TH1D("el_re_numer", "electron re numerator"  , 6, pt_bins);
  m_el_re_denom = new TH1D("el_re_denom", "electron re denominator", 6, pt_bins);

  m_mu_re_numer = new TH1D("mu_re_numer", "muon re numerator"      , 6, pt_bins);
  m_mu_re_denom = new TH1D("mu_re_denom", "muon re denominator"    , 6, pt_bins);

  m_el_fr_numer = new TH1D("el_fr_numer", "electron fr numerator"  , 6, pt_bins);
  m_el_fr_denom = new TH1D("el_fr_denom", "electron fr denominator", 6, pt_bins);

  m_mu_fr_numer = new TH1D("mu_fr_numer", "muon fr numerator"      , 6, pt_bins);
  m_mu_fr_denom = new TH1D("mu_fr_denom", "muon fr denominator"    , 6, pt_bins);
}

// -----------------------------------------------------------------------------
CalculateFakeRates::~CalculateFakeRates()
{
  // delete m_el_re_numer;
  // delete m_el_re_denom;

  // delete m_mu_re_numer;
  // delete m_mu_re_denom;

  // delete m_el_fr_numer;
  // delete m_el_fr_denom;

  // delete m_mu_fr_numer;
  // delete m_mu_fr_denom;
}

// -----------------------------------------------------------------------------
void CalculateFakeRates::processEvent()
{
  SusyAnalysisTools::EventDescription evt_desc  = m_event_desc;
  double weight = 1.;


  // apply mc event weight
  weight *= m_mc_event_weight;

  // GRL
  if (evt_desc.getPassGrl() == false) return;

  // incomplete event
  if (evt_desc.getPassIncompleteEvent() == false) return;

  // lar error
  if (evt_desc.getPassLarError() == false) return;

  // tile error
  if (evt_desc.getPassTileError() == false) return;

  // tile hot spot
  if (evt_desc.getPassTileHotSpot() == false) return;

  // tile trip
  if (evt_desc.getPassTileTrip() == false) return;

  // bad jets
  if (evt_desc.getPassBadJets() == false) return;

  // calo problem jets
  if (evt_desc.getPassCaloProblemJets() == false) return;

  // primary vertex
  if (evt_desc.getPassPrimaryVertex() == false) return;

  // bad muons
  if (evt_desc.getPassBadMuons() == false) return;

  // cosmic muons
  if (evt_desc.getPassCosmicMuons() == false) return;

  // HFOR
  if (evt_desc.getPassHFOR() == false) return;


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  size_t num_el = m_el_desc->size();
  size_t num_mu = m_mu_desc->size();

  for (size_t el_it = 0; el_it != num_el; ++el_it) {
    SusyAnalysisTools::ElectronDescription el_desc(m_el_desc->at(el_it));
    bool is_truth_matched = el_desc.getPassPromptLepton();
    bool is_baseline      = el_desc.getPassGood();
    // bool is_signal        = el_desc.getPassSignal();
    bool is_signal        = isSignalElectron(el_it, el_desc);
    float el_pt = m_el_pt->at(el_it)/1000.;

    if (el_pt >= 500.) el_pt = 499.;

    if (is_truth_matched) {
      if (is_baseline) {
        m_el_re_denom->Fill(el_pt);
      }
      if (is_baseline && is_signal) {
        m_el_re_numer->Fill(el_pt);
      }
    }
    else {
      if (is_baseline) {
        m_el_fr_denom->Fill(el_pt);
      }
      if (is_baseline && is_signal) {
        m_el_fr_numer->Fill(el_pt);
      }
    }
  }

  for (size_t mu_it = 0; mu_it != num_mu; ++mu_it) {
    SusyAnalysisTools::MuonDescription mu_desc(m_mu_desc->at(mu_it));
    bool is_truth_matched = mu_desc.getPassPromptLepton();
    bool is_baseline      = mu_desc.getPassGood();
    // bool is_signal        = mu_desc.getPassSignal();
    bool is_signal        = isSignalMuon(mu_it, mu_desc);
    float mu_pt = m_mu_pt->at(mu_it)/1000.;

    if (mu_pt >= 500.) mu_pt = 499.;

    if (is_truth_matched) {
      if (is_baseline) {
        m_mu_re_denom->Fill(mu_pt);
      }
      if (is_baseline && is_signal) {
        m_mu_re_numer->Fill(mu_pt);
      }
    }
    else {
      if (is_baseline) {
        m_mu_fr_denom->Fill(mu_pt);
      }
      if (is_baseline && is_signal) {
        // std::cout << "Found fake muon  -- event: " << m_event_number << " -- num el: " << num_el << " -- num mu: " << num_mu << "\n";
        // std::cout << "\tpt:       " << m_mu_pt->at(mu_it)       << "\n";
        // std::cout << "\tptcone30: " << m_mu_ptcone30->at(mu_it) << "\n";
        // std::cout << "\tetcone30: " << m_mu_etcone30->at(mu_it) << "\n";
        // std::cout << "\td0_sig:   " << m_mu_d0_sig->at(mu_it)   << "\n";
        // std::cout << "\tz0:       " << m_mu_z0->at(mu_it)       << "\n";
        m_mu_fr_numer->Fill(mu_pt);
      }
    }
  }

  // ---------------------------------------------------------------------------
  // >= 2 good leptons
  // if (evt_desc.getPassGE2GoodLeptons() == false) return;

  // == 2 good leptons
  // if (evt_desc.getPass2GoodLeptons() == false) return;

  // mll
  // if (evt_desc.getPassMll() == false) return;

  // 2 signal leptons
  // if (evt_desc.getPass2SignalLeptons() == false) return;

  // // flavor selection
  // bool pass_flavor = false;
  // if (phase == PHASE_EE && evt_desc.getFlavorChannel() == FLAVOR_EE)
  //   pass_flavor = true;
  // if (phase == PHASE_MM && evt_desc.getFlavorChannel() == FLAVOR_MM)
  //   pass_flavor = true;
  // if (phase == PHASE_EM && evt_desc.getFlavorChannel() == FLAVOR_EM)
  //   pass_flavor = true;
  // if (phase == PHASE_ME && evt_desc.getFlavorChannel() == FLAVOR_EM)
  //   pass_flavor = true;
  //
  // if (pass_flavor == false) return;
  // fillHist(phase, weight_type, bin_num++, weight);

  // // apply lepton weight
  // weight *= m_lepton_weight;

  // // apply trigger weight
  // weight *= m_trigger_weight;

  // // phase space selection
  // if (evt_desc.getPhaseSpace() != phase) return;
  // fillHist(phase, weight_type, bin_num++, weight);

  // // Trigger
  // bool pass_trigger = false;
  // if (phase == PHASE_EE && evt_desc.isEETrigger()) pass_trigger = true;
  // if (phase == PHASE_MM && evt_desc.isMMTrigger()) pass_trigger = true;
  // if (phase == PHASE_EM && evt_desc.isEMTrigger()) pass_trigger = true;
  // if (phase == PHASE_ME && evt_desc.isMETrigger()) pass_trigger = true;
  // if (pass_trigger == false) return;
  // fillHist(phase, weight_type, bin_num++, weight);

  // // Trigger matching
  // if (evt_desc.getPassTriggerMatch() == false) return;

  // // Flag prompt lepton events
  // if (evt_desc.getTruthPrompt())
  //   fillHist(phase, weight_type, bin_num, weight);
  // ++bin_num;

  // // Flag OS events
  // if (evt_desc.getSignChannel() == SIGN_OS)
  //   fillHist(phase, weight_type, bin_num, weight);

  // // Flag SS events
  // if (evt_desc.getSignChannel() == SIGN_SS)
  //   fillHist(phase, weight_type, bin_num, weight);
}

// -----------------------------------------------------------------------------
void CalculateFakeRates::printToScreen()
{
  unsigned int line_width   = 100;
  unsigned int label_field  = 30;
  unsigned int weight_field = (line_width - label_field - 4 - 2*3 )/2;
  unsigned int precision    = weight_field-2;
  if (4+label_field+2*weight_field != line_width) {
    label_field += (line_width - label_field - 4 - 2*3 )%2;
  }
  std::string break_label = "";
  std::string break_weight = "";
  for (unsigned int i = 0; i != label_field ; ++i) break_label  += "-";
  for (unsigned int i = 0; i != weight_field; ++i) break_weight += "-";

  std::string single_line;
  for (unsigned int i = 0; i != line_width; ++i) single_line += '=';
  single_line = single_line + "\n";

  m_el_re = static_cast<TH1D*>(m_el_re_numer->Clone("m_el_re"));
  m_el_re->Divide(m_el_re_denom);

  m_mu_re = static_cast<TH1D*>(m_mu_re_numer->Clone("m_mu_re"));
  m_mu_re->Divide(m_mu_re_denom);

  m_el_fr = static_cast<TH1D*>(m_el_fr_numer->Clone("m_el_fr"));
  m_el_fr->Divide(m_el_fr_denom);

  m_mu_fr = static_cast<TH1D*>(m_mu_fr_numer->Clone("m_mu_fr"));
  m_mu_fr->Divide(m_mu_fr_denom);

  size_t num_pt_bins = m_el_re_numer->GetXaxis()->GetNbins();
  std::stringstream ss_pt_bins;     ss_pt_bins     << "pt:         ";
  std::stringstream ss_el_re_numer; ss_el_re_numer << "el re numer:";
  std::stringstream ss_el_re_denom; ss_el_re_denom << "el re denom:";
  std::stringstream ss_el_re;       ss_el_re       << "el re:      ";
  std::stringstream ss_el_fr_numer; ss_el_fr_numer << "el fr numer:";
  std::stringstream ss_el_fr_denom; ss_el_fr_denom << "el fr denom:";
  std::stringstream ss_el_fr;       ss_el_fr       << "el fr:      ";
  std::stringstream ss_mu_re_numer; ss_mu_re_numer << "mu re numer:";
  std::stringstream ss_mu_re_denom; ss_mu_re_denom << "mu re denom:";
  std::stringstream ss_mu_re;       ss_mu_re       << "mu re:      ";
  std::stringstream ss_mu_fr_numer; ss_mu_fr_numer << "mu fr numer:";
  std::stringstream ss_mu_fr_denom; ss_mu_fr_denom << "mu fr denom:";
  std::stringstream ss_mu_fr;       ss_mu_fr       << "mu fr:      ";
  for (size_t pt_it = 0; pt_it != num_pt_bins; ++pt_it) {
    ss_pt_bins     << "\t|\t" << m_el_re_numer->GetXaxis()->GetBinLowEdge(pt_it + 1) << " - " << m_el_re_numer->GetXaxis()->GetBinUpEdge(pt_it+1);
    ss_el_re_numer << "\t|\t" << m_el_re_numer->GetBinContent(pt_it + 1);
    ss_el_re_denom << "\t|\t" << m_el_re_denom->GetBinContent(pt_it + 1);
    ss_el_re       << "\t|\t" << m_el_re->GetBinContent(      pt_it + 1);
    ss_el_fr_numer << "\t|\t" << m_el_fr_numer->GetBinContent(pt_it + 1);
    ss_el_fr_denom << "\t|\t" << m_el_fr_denom->GetBinContent(pt_it + 1);
    ss_el_fr       << "\t|\t" << m_el_fr->GetBinContent(      pt_it + 1);
    ss_mu_re_numer << "\t|\t" << m_mu_re_numer->GetBinContent(pt_it + 1);
    ss_mu_re_denom << "\t|\t" << m_mu_re_denom->GetBinContent(pt_it + 1);
    ss_mu_re        << "\t|\t" << m_mu_re->GetBinContent(      pt_it + 1);
    ss_mu_fr_numer << "\t|\t" << m_mu_fr_numer->GetBinContent(pt_it + 1);
    ss_mu_fr_denom << "\t|\t" << m_mu_fr_denom->GetBinContent(pt_it + 1);
    ss_mu_fr       << "\t|\t" << m_mu_fr->GetBinContent(      pt_it + 1);
  }
  ss_pt_bins     << "\t|\tinclusive\n";
  ss_el_re_numer << "\t|\t" << m_el_re_numer->Integral() << "\n";
  ss_el_re_denom << "\t|\t" << m_el_re_denom->Integral() << "\n";
  ss_el_re       << "\t|\t" << m_el_re->Integral()       << "\n";
  ss_el_fr_numer << "\t|\t" << m_el_fr_numer->Integral() << "\n";
  ss_el_fr_denom << "\t|\t" << m_el_fr_denom->Integral() << "\n";
  ss_el_fr       << "\t|\t" << m_el_fr->Integral()       << "\n";
  ss_mu_re_numer << "\t|\t" << m_mu_re_numer->Integral() << "\n";
  ss_mu_re_denom << "\t|\t" << m_mu_re_denom->Integral() << "\n";
  ss_mu_re       << "\t|\t" << m_mu_re->Integral()       << "\n";
  ss_mu_fr_numer << "\t|\t" << m_mu_fr_numer->Integral() << "\n";
  ss_mu_fr_denom << "\t|\t" << m_mu_fr_denom->Integral() << "\n";
  ss_mu_fr       << "\t|\t" << m_mu_fr->Integral()       << "\n";

  std::cout << '\n';
  std::cout << single_line;
  std::cout << single_line;
  std::cout << ss_pt_bins.str();
  std::cout << single_line;
  std::cout << ss_el_re_numer.str();
  std::cout << ss_el_re_denom.str();
  std::cout << ss_el_re.str();
  std::cout << single_line;
  std::cout << ss_el_fr_numer.str();
  std::cout << ss_el_fr_denom.str();
  std::cout << ss_el_fr.str();
  std::cout << single_line;
  std::cout << ss_pt_bins.str();
  std::cout << single_line;
  std::cout << ss_mu_re_numer.str();
  std::cout << ss_mu_re_denom.str();
  std::cout << ss_mu_re.str();
  std::cout << single_line;
  std::cout << ss_mu_fr_numer.str();
  std::cout << ss_mu_fr_denom.str();
  std::cout << ss_mu_fr.str();
}

// -----------------------------------------------------------------------------
void CalculateFakeRates::printToFile(std::string out_file_name)
{
  TFile f(out_file_name.c_str(), "RECREATE");
  f.cd();

  m_el_re->Write();
  m_el_re_numer->Write();
  m_el_re_denom->Write();

  m_mu_re->Write();
  m_mu_re_numer->Write();
  m_mu_re_denom->Write();

  m_el_fr->Write();
  m_el_fr_numer->Write();
  m_el_fr_denom->Write();

  m_mu_fr->Write();
  m_mu_fr_numer->Write();
  m_mu_fr_denom->Write();
}