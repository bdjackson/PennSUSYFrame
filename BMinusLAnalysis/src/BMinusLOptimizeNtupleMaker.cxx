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
  BMinusLAnalysis::prepareSelection();

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
     && m_pass_signal_lep
     && m_pass_os
     && m_pass_trigger
     && m_pass_phase
     && m_pass_ge_2_b_jet
     && m_pass_bl_pairing
     ) {
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

  m_btag_sf_b_up_frac   = 1;
  m_btag_sf_b_down_frac = 1;
  m_btag_sf_c_up_frac   = 1;
  m_btag_sf_c_down_frac = 1;
  m_btag_sf_l_up_frac   = 1;
  m_btag_sf_l_down_frac = 1;

  m_is_signal = false;

  m_flavor_channel = FLAVOR_NONE;

  m_is_ee = false;
  m_is_mm = false;
  m_is_em = false;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  m_is_sr_1     = false;
  m_is_sr_2     = false;

  m_is_sr_ht_1100_mbl_200 = false;
  m_is_sr_ht_1100_mbl_400 = false;
  m_is_sr_ht_1100_mbl_600 = false;
  m_is_sr_ht_1100_mbl_800 = false;

  m_is_sr_ht_1000_mbl_200 = false;
  m_is_sr_ht_1000_mbl_400 = false;
  m_is_sr_ht_1000_mbl_600 = false;
  m_is_sr_ht_1000_mbl_800 = false;

  m_is_sr_ht_900_mbl_200 = false;
  m_is_sr_ht_900_mbl_400 = false;
  m_is_sr_ht_900_mbl_600 = false;
  m_is_sr_ht_900_mbl_800 = false;

  m_is_sr_ht_800_mbl_200 = false;
  m_is_sr_ht_800_mbl_400 = false;
  m_is_sr_ht_800_mbl_600 = false;
  m_is_sr_ht_800_mbl_800 = false;

  m_is_sr_ht_700_mbl_200 = false;
  m_is_sr_ht_700_mbl_400 = false;
  m_is_sr_ht_700_mbl_600 = false;
  m_is_sr_ht_700_mbl_800 = false;

  m_is_sr_ht_600_mbl_200 = false;
  m_is_sr_ht_600_mbl_400 = false;
  m_is_sr_ht_600_mbl_600 = false;
  m_is_sr_ht_600_mbl_800 = false;

  m_is_sr_ht_500_mbl_200 = false;
  m_is_sr_ht_500_mbl_400 = false;
  m_is_sr_ht_500_mbl_600 = false;
  m_is_sr_ht_500_mbl_800 = false;

  m_is_cr_top   = false;
  m_is_cr_z     = false;

  m_is_cr_top_mbl_200 = false;
  m_is_cr_z_mbl_200 = false;

  m_is_vr_top_1 = false;
  m_is_vr_top_2 = false;
  m_is_vr_top_3 = false;
  m_is_vr_z     = false;

  m_is_vr_top_mbl_200_1 = false;
  m_is_vr_top_mbl_200_2 = false;
  m_is_vr_top_mbl_200_3 = false;
  m_is_vr_z_mbl_200     = false;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  m_mbl_0    = 0;
  m_mbl_1    = 0;
  m_mbl_asym = 0;
  m_mbbll    = 0;

  m_ptbl_0    = 0;
  m_ptbl_1    = 0;
  m_ptbl_asym = 0;
  m_ptbbll    = 0;

  m_mll = 0;

  m_met_et  = 0;
  m_met_rel = 0;
  m_met_sig_signal = 0;

  m_ht_all      = 0;
  m_ht_baseline = 0;
  m_ht_good     = 0;
  m_ht_signal   = 0;

  m_pt_l_0 = 0;
  m_pt_l_1 = 0;
  m_pt_b_0 = 0;
  m_pt_b_1 = 0;

  m_dphi_bl_0 = 0;
  m_dphi_bl_1 = 0;
  m_deta_bl_0 = 0;
  m_deta_bl_1 = 0;
  m_dr_bl_0 = 0;
  m_dr_bl_1 = 0;

  m_dphi_ll = 0;
  m_deta_ll = 0;
  m_dr_ll = 0;

  m_dphi_bb = 0;
  m_deta_bb = 0;
  m_dr_bb = 0;
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

  m_output_tree->Branch( "btag_sf_b_up_frac"   , &m_btag_sf_b_up_frac  );
  m_output_tree->Branch( "btag_sf_b_down_frac" , &m_btag_sf_b_down_frac);
  m_output_tree->Branch( "btag_sf_c_up_frac"   , &m_btag_sf_c_up_frac  );
  m_output_tree->Branch( "btag_sf_c_down_frac" , &m_btag_sf_c_down_frac);
  m_output_tree->Branch( "btag_sf_l_up_frac"   , &m_btag_sf_l_up_frac  );
  m_output_tree->Branch( "btag_sf_l_down_frac" , &m_btag_sf_l_down_frac);

  m_output_tree->Branch( "is_signal" , &m_is_signal);

  m_output_tree->Branch( "flavor_channel" , &m_flavor_channel);

  m_output_tree->Branch( "is_ee" , &m_is_ee);
  m_output_tree->Branch( "is_mm" , &m_is_mm);
  m_output_tree->Branch( "is_em" , &m_is_em);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  m_output_tree->Branch( "is_sr_1"    , &m_is_sr_1    );
  m_output_tree->Branch( "is_sr_2"    , &m_is_sr_2    );

  m_output_tree->Branch( "is_sr_ht_1100_mbl_200", &m_is_sr_ht_1100_mbl_200);
  m_output_tree->Branch( "is_sr_ht_1100_mbl_400", &m_is_sr_ht_1100_mbl_400);
  m_output_tree->Branch( "is_sr_ht_1100_mbl_600", &m_is_sr_ht_1100_mbl_600);
  m_output_tree->Branch( "is_sr_ht_1100_mbl_800", &m_is_sr_ht_1100_mbl_800);

  m_output_tree->Branch( "is_sr_ht_1000_mbl_200", &m_is_sr_ht_1000_mbl_200);
  m_output_tree->Branch( "is_sr_ht_1000_mbl_400", &m_is_sr_ht_1000_mbl_400);
  m_output_tree->Branch( "is_sr_ht_1000_mbl_600", &m_is_sr_ht_1000_mbl_600);
  m_output_tree->Branch( "is_sr_ht_1000_mbl_800", &m_is_sr_ht_1000_mbl_800);

  m_output_tree->Branch( "is_sr_ht_900_mbl_200", &m_is_sr_ht_900_mbl_200);
  m_output_tree->Branch( "is_sr_ht_900_mbl_400", &m_is_sr_ht_900_mbl_400);
  m_output_tree->Branch( "is_sr_ht_900_mbl_600", &m_is_sr_ht_900_mbl_600);
  m_output_tree->Branch( "is_sr_ht_900_mbl_800", &m_is_sr_ht_900_mbl_800);

  m_output_tree->Branch( "is_sr_ht_800_mbl_200", &m_is_sr_ht_800_mbl_200);
  m_output_tree->Branch( "is_sr_ht_800_mbl_400", &m_is_sr_ht_800_mbl_400);
  m_output_tree->Branch( "is_sr_ht_800_mbl_600", &m_is_sr_ht_800_mbl_600);
  m_output_tree->Branch( "is_sr_ht_800_mbl_800", &m_is_sr_ht_800_mbl_800);

  m_output_tree->Branch( "is_sr_ht_700_mbl_200", &m_is_sr_ht_700_mbl_200);
  m_output_tree->Branch( "is_sr_ht_700_mbl_400", &m_is_sr_ht_700_mbl_400);
  m_output_tree->Branch( "is_sr_ht_700_mbl_600", &m_is_sr_ht_700_mbl_600);
  m_output_tree->Branch( "is_sr_ht_700_mbl_800", &m_is_sr_ht_700_mbl_800);

  m_output_tree->Branch( "is_sr_ht_600_mbl_200", &m_is_sr_ht_600_mbl_200);
  m_output_tree->Branch( "is_sr_ht_600_mbl_400", &m_is_sr_ht_600_mbl_400);
  m_output_tree->Branch( "is_sr_ht_600_mbl_600", &m_is_sr_ht_600_mbl_600);
  m_output_tree->Branch( "is_sr_ht_600_mbl_800", &m_is_sr_ht_600_mbl_800);

  m_output_tree->Branch( "is_sr_ht_500_mbl_200", &m_is_sr_ht_500_mbl_200);
  m_output_tree->Branch( "is_sr_ht_500_mbl_400", &m_is_sr_ht_500_mbl_400);
  m_output_tree->Branch( "is_sr_ht_500_mbl_600", &m_is_sr_ht_500_mbl_600);
  m_output_tree->Branch( "is_sr_ht_500_mbl_800", &m_is_sr_ht_500_mbl_800);

  m_output_tree->Branch( "is_cr_top"  , &m_is_cr_top  );
  m_output_tree->Branch( "is_cr_z"    , &m_is_cr_z    );

  m_output_tree->Branch( "is_cr_top_mbl_200", &m_is_cr_top_mbl_200);
  m_output_tree->Branch( "is_cr_z_mbl_200", &m_is_cr_z_mbl_200);

  m_output_tree->Branch( "is_vr_top_1", &m_is_vr_top_1);
  m_output_tree->Branch( "is_vr_top_2", &m_is_vr_top_2);
  m_output_tree->Branch( "is_vr_top_3", &m_is_vr_top_3);
  m_output_tree->Branch( "is_vr_z"    , &m_is_vr_z    );

  m_output_tree->Branch( "is_vr_top_mbl_200_1", &m_is_vr_top_mbl_200_1);
  m_output_tree->Branch( "is_vr_top_mbl_200_2", &m_is_vr_top_mbl_200_2);
  m_output_tree->Branch( "is_vr_top_mbl_200_3", &m_is_vr_top_mbl_200_3);
  m_output_tree->Branch( "is_vr_z_mbl_200", &m_is_vr_z_mbl_200);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  m_output_tree->Branch( "mbl_0"    , &m_mbl_0);
  m_output_tree->Branch( "mbl_1"    , &m_mbl_1);
  m_output_tree->Branch( "mbl_asym" , &m_mbl_asym);
  m_output_tree->Branch( "mbbll"    , &m_mbbll);

  m_output_tree->Branch( "ptbl_0"    , &m_ptbl_0);
  m_output_tree->Branch( "ptbl_1"    , &m_ptbl_1);
  m_output_tree->Branch( "ptbl_asym" , &m_ptbl_asym);
  m_output_tree->Branch( "ptbbll"    , &m_ptbbll);

  m_output_tree->Branch( "mll"  , &m_mll);
  m_output_tree->Branch( "ptll" , &m_ptll);

  m_output_tree->Branch( "met_et"         , &m_met_et);
  m_output_tree->Branch( "met_rel"        , &m_met_rel);
  m_output_tree->Branch( "met_sig_signal" , &m_met_sig_signal);

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

  m_btag_sf_b_up_frac   = m_event_quantities.getBTagSFBUp()  /m_event_quantities.getBTagSF();
  m_btag_sf_b_down_frac = m_event_quantities.getBTagSFBDown()/m_event_quantities.getBTagSF();
  m_btag_sf_c_up_frac   = m_event_quantities.getBTagSFCUp()  /m_event_quantities.getBTagSF();
  m_btag_sf_c_down_frac = m_event_quantities.getBTagSFCDown()/m_event_quantities.getBTagSF();
  m_btag_sf_l_up_frac   = m_event_quantities.getBTagSFLUp()  /m_event_quantities.getBTagSF();
  m_btag_sf_l_down_frac = m_event_quantities.getBTagSFLDown()/m_event_quantities.getBTagSF();

  // TODO we don't relaly want to do this every event. leave for now while looking for cleaner way to implement the branching fraction scaling, but if this is the permanent solution :-(, make this cleaner.
  if (!m_is_data) {
    unsigned int channel_number = m_mc_truth.getChannelNumber();
    m_is_signal = (  channel_number >= 202632
                  && channel_number <= 202641
                  );
  }

  m_flavor_channel = m_event.getFlavorChannel();

  m_is_ee = (m_event.getFlavorChannel() == FLAVOR_EE);
  m_is_mm = (m_event.getFlavorChannel() == FLAVOR_MM);
  m_is_em = (m_event.getFlavorChannel() == FLAVOR_EM);

  m_mbl_0   = bl_0->getMbl()/1.e3;
  m_mbl_1   = bl_1->getMbl()/1.e3;
  m_mbl_asym = (m_mbl_0 - m_mbl_1) / (m_mbl_0 + m_mbl_1);
  m_mbbll  = PennSusyFrame::calcMbbll( *bl_0, *bl_1)/1.e3;

  m_ptbl_0 = bl_0->getPtbl()/1.e3;
  m_ptbl_1 = bl_1->getPtbl()/1.e3;
  m_ptbl_asym = (bl_0->getPtbl() - bl_1->getPtbl()) / (bl_0->getPtbl() + bl_1->getPtbl());
  m_ptbbll = PennSusyFrame::calcPtbbll(*bl_0, *bl_1)/1.e3;

  m_mll  = m_event_quantities.getMll()/1.e3;
  m_ptll = m_event_quantities.getPtll()/1.e3;

  m_ht_all      = m_event_quantities.getHtAll()/1.e3;
  m_ht_baseline = m_event_quantities.getHtBaseline()/1.e3;
  m_ht_good     = m_event_quantities.getHtGood()/1.e3;
  m_ht_signal   = m_event_quantities.getHtSignal()/1.e3;

  m_met_et         = m_met.getMetEt() /1.e3;
  m_met_rel        = m_met.getMetRel()/1.e3;
  m_met_sig_signal = m_met_et/sqrt(m_ht_signal);

  m_pt_l_0 = bl_0->getLepton()->getPt()/1.e3;
  m_pt_l_1 = bl_1->getLepton()->getPt()/1.e3;
  m_pt_b_0 = bl_0->getJet()->getPt()/1.e3;
  m_pt_b_1 = bl_1->getJet()->getPt()/1.e3;

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

  bool ht_ge_1100    = (m_ht_signal      >= 1100.0);
  bool ht_ge_1000    = (m_ht_signal      >= 1000.0);
  bool ht_ge_900     = (m_ht_signal      >= 900.0 );
  bool ht_ge_800     = (m_ht_signal      >= 800.0 );
  bool ht_ge_700     = (m_ht_signal      >= 700.0 );
  bool ht_ge_600     = (m_ht_signal      >= 600.0 );
  bool ht_ge_500     = (m_ht_signal      >= 500.0 );

  bool mbl_le_2      = (m_mbl_asym       <= 0.20  );
  bool met_sig_ge_4  = (m_met_sig_signal >= 4.    );

  bool bl_mass_0_ge_200 = (m_mbl_0 > 200);
  bool bl_mass_0_ge_400 = (m_mbl_0 > 400);
  bool bl_mass_0_ge_600 = (m_mbl_0 > 600);
  bool bl_mass_0_ge_800 = (m_mbl_0 > 800);

  // don't include SR in data if we are blinded
  if ( !m_is_data || !m_is_blind) {
    m_is_sr_1 = (m_pass_z_veto && mbl_le_2 && ht_ge_1100);
    m_is_sr_2 = (m_pass_z_veto && mbl_le_2 && ht_ge_500 && !ht_ge_1100);

    if (m_pass_z_veto && mbl_le_2 && ht_ge_1100) {
      m_is_sr_ht_1100_mbl_200 = bl_mass_0_ge_200;
      m_is_sr_ht_1100_mbl_400 = bl_mass_0_ge_400;
      m_is_sr_ht_1100_mbl_600 = bl_mass_0_ge_600;
      m_is_sr_ht_1100_mbl_800 = bl_mass_0_ge_800;
    }
    if (m_pass_z_veto && mbl_le_2 && ht_ge_1000) {
      m_is_sr_ht_1000_mbl_200 = bl_mass_0_ge_200;
      m_is_sr_ht_1000_mbl_400 = bl_mass_0_ge_400;
      m_is_sr_ht_1000_mbl_600 = bl_mass_0_ge_600;
      m_is_sr_ht_1000_mbl_800 = bl_mass_0_ge_800;
    }
    if (m_pass_z_veto && mbl_le_2 && ht_ge_900) {
      m_is_sr_ht_900_mbl_200 = bl_mass_0_ge_200;
      m_is_sr_ht_900_mbl_400 = bl_mass_0_ge_400;
      m_is_sr_ht_900_mbl_600 = bl_mass_0_ge_600;
      m_is_sr_ht_900_mbl_800 = bl_mass_0_ge_800;
    }
    if (m_pass_z_veto && mbl_le_2 && ht_ge_800) {
      m_is_sr_ht_800_mbl_200 = bl_mass_0_ge_200;
      m_is_sr_ht_800_mbl_400 = bl_mass_0_ge_400;
      m_is_sr_ht_800_mbl_600 = bl_mass_0_ge_600;
      m_is_sr_ht_800_mbl_800 = bl_mass_0_ge_800;
    }
    if (m_pass_z_veto && mbl_le_2 && ht_ge_700) {
      m_is_sr_ht_700_mbl_200 = bl_mass_0_ge_200;
      m_is_sr_ht_700_mbl_400 = bl_mass_0_ge_400;
      m_is_sr_ht_700_mbl_600 = bl_mass_0_ge_600;
      m_is_sr_ht_700_mbl_800 = bl_mass_0_ge_800;
    }
    if (m_pass_z_veto && mbl_le_2 && ht_ge_600) {
      m_is_sr_ht_600_mbl_200 = bl_mass_0_ge_200;
      m_is_sr_ht_600_mbl_400 = bl_mass_0_ge_400;
      m_is_sr_ht_600_mbl_600 = bl_mass_0_ge_600;
      m_is_sr_ht_600_mbl_800 = bl_mass_0_ge_800;
    }
    if (m_pass_z_veto && mbl_le_2 && ht_ge_500) {
      m_is_sr_ht_500_mbl_200 = bl_mass_0_ge_200;
      m_is_sr_ht_500_mbl_400 = bl_mass_0_ge_400;
      m_is_sr_ht_500_mbl_600 = bl_mass_0_ge_600;
      m_is_sr_ht_500_mbl_800 = bl_mass_0_ge_800;
    }
  }

  m_is_cr_top = (m_pass_z_veto && !ht_ge_500 && mbl_le_2 && met_sig_ge_4);
  m_is_cr_z   = (!m_pass_z_veto && !ht_ge_500 && mbl_le_2 && !met_sig_ge_4);

  m_is_cr_top_mbl_200 = (m_pass_z_veto && !ht_ge_500 && mbl_le_2 &&
                         met_sig_ge_4 && bl_mass_0_ge_200);
  m_is_cr_z_mbl_200 = (!m_pass_z_veto && !ht_ge_500 && mbl_le_2 &&
                       !met_sig_ge_4 && bl_mass_0_ge_200);

  m_is_vr_top_1 = (m_pass_z_veto  && !ht_ge_500 && mbl_le_2 && !met_sig_ge_4);
  m_is_vr_top_2 = (m_pass_z_veto  && !ht_ge_500 && !mbl_le_2);
  m_is_vr_top_3 = (m_pass_z_veto  && ht_ge_500  && met_sig_ge_4 && !mbl_le_2);
  m_is_vr_z     = (!m_pass_z_veto && ht_ge_500  && mbl_le_2);

  m_is_vr_top_mbl_200_1 = (m_pass_z_veto  && !ht_ge_500 && mbl_le_2 &&
                           !met_sig_ge_4 && bl_mass_0_ge_200);
  m_is_vr_top_mbl_200_2 = (m_pass_z_veto  && !ht_ge_500 && !mbl_le_2 &&
                           bl_mass_0_ge_200);
  m_is_vr_top_mbl_200_3 = (m_pass_z_veto  && ht_ge_500 && met_sig_ge_4 &&
                           !mbl_le_2 && bl_mass_0_ge_200);
  m_is_vr_z_mbl_200 = (!m_pass_z_veto && ht_ge_500 && mbl_le_2 &&
                       bl_mass_0_ge_200);

  // fill output tree
  m_output_tree->Fill();
}
