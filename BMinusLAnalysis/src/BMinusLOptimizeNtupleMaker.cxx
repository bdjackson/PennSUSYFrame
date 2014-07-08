#include "BMinusLAnalysis/include/BMinusLOptimizeNtupleMaker.h"
#include "BMinusLAnalysis/include/BMinusLUtils.h"
#include "PennSusyFrameCore/include/PennSusyFrameCore.h"

#include "TFile.h"
#include "TTree.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <dirent.h>
#include <math.h>
#include <algorithm>

#include "PennSusyFrameCore/include/ObjectContainers.h"
#include "PennSusyFrameCore/include/Calculators.h"
#include "PennSusyFrameCore/include/D3PDReader.h"
#include "PennSusyFrameCore/include/SelectorHelpers.h"

// -----------------------------------------------------------------------------
PennSusyFrame::BMinusLOptimizeNtupleMaker::BMinusLOptimizeNtupleMaker(TTree* tree) : PennSusyFrame::BMinusLAnalysis(tree)
                                                                                   , m_out_ntuple_file_name("BMinusL.ntup.root")
                                                                                   , m_output_file(0)
                                                                                   , m_output_tree(0)
{
}

// -----------------------------------------------------------------------------
PennSusyFrame::BMinusLOptimizeNtupleMaker::~BMinusLOptimizeNtupleMaker()
{
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLOptimizeNtupleMaker::beginRun()
{
  PennSusyFrameCore::beginRun();

  // prepare selection
  prepareSelection();

  configureOutput(m_out_ntuple_file_name, "optimize");
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLOptimizeNtupleMaker::initializeEvent()
{
  PennSusyFrame::BMinusLAnalysis::initializeEvent();
  clearVariables();
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLOptimizeNtupleMaker::finalizeEvent()
{
  if (  m_pass_grl
     && m_pass_incomplete_event
     && m_pass_lar_error
     && m_pass_tile_error
     && m_pass_tile_hot_spot
     && m_pass_tile_trip
     && m_pass_bad_jet_veto
     && m_pass_calo_problem_jet
     && m_pass_primary_vertex
     && m_pass_bad_mu_veto
     && m_pass_cosmic_mu_veto
     && m_pass_hfor
     && m_pass_mc_overlap
     && m_pass_ge_2_lep
     && m_pass_2_lep
     && m_pass_signal_lep
     && m_pass_ge_2_b_jet
     // && m_pass_eq_2_b_jet
     && m_pass_bl_pairing
     && m_pass_z_veto
     ) {
    // std::cout << "finalizeEvent():"
    //           << "\n\tevent: "             << m_event.getEventNumber()
    //           << "\n\tweight: "            << m_event_weight
    //           << "\n\t\tmc event weight: " << m_mc_event_weight
    //           << "\n\t\tpile up sf: "      << m_pile_up_sf
    //           << "\n\t\tx-sec weight: "    << m_xsec_weight
    //           << "\n\t\tlepton sf: "       << m_lepton_sf
    //           << "\n\t\tb-tag sf: "        << m_btag_sf
    //           << "\n\tmbl 0: mbl_0: "      << m_bl_0->getMbl()
    //           << "\n\tmbl 0: mbl_0: "      << m_bl_1->getMbl()
    //           << "\n\tht baseline: "       << m_event_quantities.getHtBaseline()
    //           << "\n\tmet et: "            << m_met.getMetEt()
    //           << "\n\tmet sig: "           << m_met.getMetSigBaseline()
    //           << "\n";

    fillNtuple( m_bl_0
              , m_bl_1
              , m_event_weight
              );
  }
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLOptimizeNtupleMaker::finalizeRun()
{
  m_output_file->Write();
  m_output_file->Close();
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLOptimizeNtupleMaker::clearVariables()
{
  m_weight = 1.;

  m_mbl_0 = 0 ;
  m_mbl_1 = 0 ;

  m_ptbl_0 = 0 ;
  m_ptbl_1 = 0 ;

  m_mbbll  = 0 ;
  m_ptbbll = 0 ;

  m_mll = 0 ;

  m_met_et  = 0 ;
  m_met_rel = 0 ;

  m_ht_all      = 0 ;
  m_ht_baseline = 0 ;
  m_ht_good     = 0 ;
  m_ht_signal   = 0 ;

  m_pt_l_0 = 0 ;
  m_pt_l_1 = 0 ;
  m_pt_b_0 = 0 ;
  m_pt_b_1 = 0 ;

  m_dphi_bl_0 = 0 ;
  m_dphi_bl_1 = 0 ;
  m_deta_bl_0 = 0 ;
  m_deta_bl_1 = 0 ;
  m_dr_bl_0 = 0 ;
  m_dr_bl_1 = 0 ;

  m_dphi_ll = 0 ;
  m_deta_ll = 0 ;
  m_dr_ll = 0 ;

  m_dphi_bb = 0 ;
  m_deta_bb = 0 ;
  m_dr_bb = 0 ;
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLOptimizeNtupleMaker::configureOutput( std::string out_file_name
                                                               , std::string out_tree_name
                                                               )
{
  m_output_file = new TFile(out_file_name.c_str(), "RECREATE");
  m_output_tree = new TTree(out_tree_name.c_str(), out_tree_name.c_str());

  // connect branches for output
  m_output_tree->Branch( "weight" , &m_weight);

  m_output_tree->Branch( "mbl_0" , &m_mbl_0);
  m_output_tree->Branch( "mbl_1" , &m_mbl_1);
  m_output_tree->Branch( "mbbll" , &m_mbbll);

  m_output_tree->Branch( "ptbl_0" , &m_ptbl_0);
  m_output_tree->Branch( "ptbl_1" , &m_ptbl_1);
  m_output_tree->Branch( "ptbbll" , &m_ptbbll);

  m_output_tree->Branch( "mll"  , &m_mll);
  m_output_tree->Branch( "ptll" , &m_ptll);

  m_output_tree->Branch( "met_et"  , &m_met_et);
  m_output_tree->Branch( "met_rel" , &m_met_rel);

  m_output_tree->Branch( "ht_all"      , &m_ht_all);
  m_output_tree->Branch( "ht_baseline" , &m_ht_baseline);
  m_output_tree->Branch( "ht_good"     , &m_ht_good);
  m_output_tree->Branch( "ht_signal"   , &m_ht_signal);

  m_output_tree->Branch( "pt_l_0" , &m_pt_l_0);
  m_output_tree->Branch( "pt_l_1" , &m_pt_l_1);
  m_output_tree->Branch( "pt_b_0" , &m_pt_b_0);
  m_output_tree->Branch( "pt_b_1" , &m_pt_b_1);

  m_output_tree->Branch( "dphi_bl_0" , &m_dphi_bl_0);
  m_output_tree->Branch( "dphi_bl_1" , &m_dphi_bl_1);
  m_output_tree->Branch( "deta_bl_0" , &m_deta_bl_0);
  m_output_tree->Branch( "deta_bl_1" , &m_deta_bl_1);
  m_output_tree->Branch( "dr_bl_0"   , &m_dr_bl_0);
  m_output_tree->Branch( "dr_bl_1"   , &m_dr_bl_1);

  m_output_tree->Branch( "dphi_ll" , &m_dphi_ll);
  m_output_tree->Branch( "deta_ll" , &m_deta_ll);
  m_output_tree->Branch( "dr_ll"   , &m_dr_ll);

  m_output_tree->Branch( "dphi_bb" , &m_dphi_bb);
  m_output_tree->Branch( "deta_bb" , &m_deta_bb);
  m_output_tree->Branch( "dr_bb"   , &m_dr_bb);
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLOptimizeNtupleMaker::fillNtuple( const PennSusyFrame::blPair* bl_0
                                                          , const PennSusyFrame::blPair* bl_1
                                                          , float weight
                                                          )
{
  m_weight = weight;

  m_mbl_0 = bl_0->getMbl()/1.e3;
  m_mbl_1 = bl_1->getMbl()/1.e3;

  m_ptbl_0 = bl_0->getPtbl()/1.e3;
  m_ptbl_1 = bl_1->getPtbl()/1.e3;

  m_mbbll  = PennSusyFrame::calcMbbll( *bl_0, *bl_1)/1.e3;
  m_ptbbll = PennSusyFrame::calcPtbbll(*bl_0, *bl_1)/1.e3;

  m_mll  = m_event_quantities.getMll()/1.e3;
  m_ptll = m_event_quantities.getPtll()/1.e3;

  m_met_et  = m_met.getMetEt() /1.e3;
  m_met_rel = m_met.getMetRel()/1.e3;

  m_ht_all      = m_event_quantities.getHtAll()/1.e3;
  m_ht_baseline = m_event_quantities.getHtBaseline()/1.e3;
  m_ht_good     = m_event_quantities.getHtGood()/1.e3;
  m_ht_signal   = m_event_quantities.getHtSignal()/1.e3;

  m_pt_l_0 = bl_0->getLepton()->getPt();
  m_pt_l_1 = bl_1->getLepton()->getPt();
  m_pt_b_0 = bl_0->getJet()->getPt();
  m_pt_b_1 = bl_1->getJet()->getPt();

  m_dphi_bl_0 = bl_0->getDphi();
  m_dphi_bl_1 = bl_1->getDphi();

  m_deta_bl_0 = bl_0->getDeta();
  m_deta_bl_1 = bl_1->getDeta();

  m_dr_bl_0 = bl_0->getDr();
  m_dr_bl_1 = bl_1->getDr();

  float phi_l_0   = bl_0->getLepton()->getPhi();
  float phi_l_1   = bl_1->getLepton()->getPhi();

  float eta_l_0   = bl_0->getLepton()->getEta();
  float eta_l_1   = bl_1->getLepton()->getEta();

  m_dphi_ll = PennSusyFrame::calcDphi(phi_l_0, phi_l_1);
  m_deta_ll = fabs(eta_l_0 - eta_l_1);
  m_dr_ll = sqrt(m_dphi_ll*m_dphi_ll + m_deta_ll*m_deta_ll);

  float phi_b_0   = bl_0->getJet()->getPhi();
  float phi_b_1   = bl_1->getJet()->getPhi();

  float eta_b_0   = bl_0->getJet()->getEta();
  float eta_b_1   = bl_1->getJet()->getEta();

  m_dphi_bb = PennSusyFrame::calcDphi(phi_b_0, phi_b_1);
  m_deta_bb = fabs(eta_b_0 - eta_b_1);
  m_dr_bb   = sqrt(m_dphi_bb*m_dphi_bb + m_deta_bb*m_deta_bb);

  // fill output tree
  m_output_tree->Fill();
}