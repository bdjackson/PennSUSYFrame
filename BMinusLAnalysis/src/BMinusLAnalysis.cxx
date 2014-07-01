#include "BMinusLAnalysis/include/BMinusLAnalysis.h"
#include "BMinusLAnalysis/include/BMinusLUtils.h"
#include "BMinusLAnalysis/include/BMinusLHistogramHandlers.h"
#include "PennSusyFrameCore/include/PennSusyFrameCore.h"

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
PennSusyFrame::BMinusLAnalysis::BMinusLAnalysis(TTree* tree) : PennSusyFrame::PennSusyFrameCore(tree)
                                                             , m_out_hist_file_name("BMinusL.hists.root")
                                                             , m_crit_cut_grl(false)
                                                             , m_crit_cut_incomplete_event(false)
                                                             , m_crit_cut_lar_error(false)
                                                             , m_crit_cut_tile_error(false)
                                                             , m_crit_cut_tile_hot_spot(false)
                                                             , m_crit_cut_tile_trip(false)
                                                             , m_crit_cut_bad_jet_veto(false)
                                                             , m_crit_cut_calo_problem_jet(false)
                                                             , m_crit_cut_primary_vertex(false)
                                                             , m_crit_cut_bad_mu_veto(false)
                                                             , m_crit_cut_cosmic_mu_veto(false)
                                                             , m_crit_cut_hfor(false)
                                                             , m_crit_cut_mc_overlap(false)
                                                             , m_crit_cut_ge_2_lep(false)
                                                             , m_crit_cut_2_lep(false)
                                                             , m_crit_cut_signal_lep(false)
                                                             , m_crit_cut_b_jets(false)
                                                             , m_crit_cut_z_veto(false)
                                                             , m_crit_cut_met(false)
                                                             , m_met_min(-1)
                                                             , m_met_max(-1)
                                                             , m_min_el_pt_baseline(20.e3)
                                                             , m_max_el_pt_baseline(-1)
                                                             , m_min_mu_pt_baseline(20.e3)
                                                             , m_max_mu_pt_baseline(-1)
                                                             , m_min_b_jet_pt_baseline(20.e3)
                                                             , m_max_b_jet_pt_baseline(-1)
{
}

// -----------------------------------------------------------------------------
PennSusyFrame::BMinusLAnalysis::~BMinusLAnalysis()
{
  size_t term_1 = m_bminusl_histogram_handler.size();
  for (size_t it_1 = 0; it_1 != term_1; ++it_1) {
    if ( m_bminusl_histogram_handler.at(it_1) ) {
      delete m_bminusl_histogram_handler.at(it_1);
      m_bminusl_histogram_handler.at(it_1) = 0;
    }
  }
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLAnalysis::prepareTools()
{
  PennSusyFrameCore::prepareTools();

  std::string base_dir = getenv("BASE_WORK_DIR");
  if (m_is_data) {
    // TODO make this configurable
    m_grl.init( base_dir
              + "/data/data12_8TeV.periodAllYear_DetStatus-v58-pro14-01_DQDefects-00-00-33_PHYS_StandardGRL_All_Good.xml"
              );
  }
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLAnalysis::prepareSelection()
{
  PennSusyFrameCore::prepareSelection();

  std::cout << "preparing selection\n";

  // EL_BASELINE
  m_electron_selectors.at(EL_BASELINE).setElectronQuality(EL_QUALITY_MEDPP);
  // m_electron_selectors.at(EL_BASELINE).setPtCut(20.e3, -1);
  m_electron_selectors.at(EL_BASELINE).setPtCut(m_min_el_pt_baseline, m_max_el_pt_baseline);
  m_electron_selectors.at(EL_BASELINE).setEtaCut(-1, 2.47);

  // EL_SIGNAL
  m_electron_selectors.at(EL_SIGNAL).setElectronQuality(EL_QUALITY_TIGHTPP);
  m_electron_selectors.at(EL_SIGNAL).setD0SignificanceCut(-1, 3);
  m_electron_selectors.at(EL_SIGNAL).setZ0SignThetaCut(-1, 0.4);
  m_electron_selectors.at(EL_SIGNAL).setPtIsoCut(-1, 0.13);
  m_electron_selectors.at(EL_SIGNAL).setEtIsoCut(-1, 0.21);

  // MU_BASELINE
  // m_muon_selectors.at(MU_BASELINE).setPtCut(20.e3, -1);
  m_muon_selectors.at(MU_BASELINE).setPtCut(m_min_mu_pt_baseline, m_max_mu_pt_baseline);
  m_muon_selectors.at(MU_BASELINE).setEtaCut(-1, 2.5);
  m_muon_selectors.at(MU_BASELINE).setBLayerHitsCut(1, -1);
  m_muon_selectors.at(MU_BASELINE).setPixelHitsCut(1, -1);
  m_muon_selectors.at(MU_BASELINE).setSctHitsCut(5, -1);
  m_muon_selectors.at(MU_BASELINE).setSiHolesCut(-1, 2);
  m_muon_selectors.at(MU_BASELINE).setTrtEtaCut(0.1, 1.9);
  m_muon_selectors.at(MU_BASELINE).setTrtHitsCut(6, -1);
  m_muon_selectors.at(MU_BASELINE).setTrtOlFractionCut(-1, 0.9);

  // MU_SIGNAL
  m_muon_selectors.at(MU_SIGNAL).setEtaCut(-1, 2.4);
  m_muon_selectors.at(MU_SIGNAL).setD0SignificanceCut(-1, 3.);
  m_muon_selectors.at(MU_SIGNAL).setZ0SignThetaCut(-1, 1.);
  m_muon_selectors.at(MU_SIGNAL).setPtIsoCut(-1, 0.11);
  m_muon_selectors.at(MU_SIGNAL).setEtIsoCut(-1, 0.19);

  // JET_B
  m_jet_selectors.at(JET_B).setPtCut(m_min_b_jet_pt_baseline, m_max_b_jet_pt_baseline);
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLAnalysis::beginRun()
{
  PennSusyFrameCore::beginRun();

  // prepare selection
  prepareSelection();

  m_histogram_handlers.resize(BMINUSL_HIST_N);

  for (unsigned int hist_level = 0; hist_level != BMINUSL_HIST_N; ++hist_level) {
    m_histogram_handlers.at(hist_level).push_back( new PennSusyFrame::EventLevelHists(      PennSusyFrame::BMINUSL_HIST_LEVEL_STRINGS[hist_level]) );
    m_histogram_handlers.at(hist_level).push_back( new PennSusyFrame::LeptonKinematicsHists(PennSusyFrame::BMINUSL_HIST_LEVEL_STRINGS[hist_level]) );
    m_histogram_handlers.at(hist_level).push_back( new PennSusyFrame::JetKinematicsHists(   PennSusyFrame::BMINUSL_HIST_LEVEL_STRINGS[hist_level]) );
    m_histogram_handlers.at(hist_level).push_back( new PennSusyFrame::MetHists(             PennSusyFrame::BMINUSL_HIST_LEVEL_STRINGS[hist_level]) );

    m_bminusl_histogram_handler.push_back(new PennSusyFrame::BMinusLHists(PennSusyFrame::BMINUSL_HIST_LEVEL_STRINGS[hist_level]));
  }
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLAnalysis::processEvent()
{
  m_event_weight = 1.;

  m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_ALL);
  m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_ALL, m_event_weight);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // set mc event weight
  // TODO validate MC event weight
  m_event_weight *= m_event_quantities.getMcEventWeight();
  m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_MC_EVENT_WEIGHT);
  m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_MC_EVENT_WEIGHT, m_event_weight);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // set pile up weight
  // TODO validate pile up weight
  m_event_weight *= m_event_quantities.getPileUpSF();
  m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_PILEUP_WEIGHT);
  m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_PILEUP_WEIGHT, m_event_weight);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // set cross section weight
  // TODO validate cross section weight
  m_event_weight *= m_xsec_weight;
  m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_XSEC_WEIGHT);
  m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_XSEC_WEIGHT, m_event_weight);

  // -----------------------------------------------------------------------------
  m_event.setPhaseSpace(getPhaseSpace());

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // GRL cut
  // TODO validate grl cut
  // only check grl cut on data
  bool pass_grl = (!m_is_data || m_grl.passEvent(m_event));
  m_pass_event = (m_pass_event && pass_grl);
  if (m_crit_cut_grl && !pass_grl) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_GRL);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_GRL, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // incomplete event cut
  // TODO validate incomplete event cut
  bool pass_incomplete_event = PennSusyFrame::passIncompleteEvent(m_event);
  m_pass_event = (m_pass_event && pass_incomplete_event);
  if (m_crit_cut_incomplete_event && !pass_incomplete_event) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_INCOMPLETE_EVENT);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_INCOMPLETE_EVENT, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // LAr error cut
  // TODO validate LAr error cut
  bool pass_lar_error = PennSusyFrame::passLarError(m_event);
  m_pass_event = (m_pass_event && pass_lar_error);
  if (m_crit_cut_lar_error && !pass_lar_error) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_LAR_ERROR);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_LAR_ERROR, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // tile error cut
  // TODO validate tile error cut
  bool pass_tile_error = PennSusyFrame::passTileError(m_event);
  m_pass_event = (m_pass_event && pass_tile_error);
  if (m_crit_cut_tile_error && !pass_tile_error) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_TILE_ERROR);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_TILE_ERROR, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // tile hot spot cut
  // TODO validate tile hot spot cut
  bool pass_tile_hot_spot = PennSusyFrame::TileHotSpotTool::passTileHotSpot(m_event, m_jets);
  m_pass_event = (m_pass_event && pass_tile_hot_spot);
  if (m_crit_cut_tile_hot_spot && !pass_tile_hot_spot) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_TILE_HOT_SPOT);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_TILE_HOT_SPOT, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // tile trip cut
  // TODO validate tile trip cut
  bool pass_tile_trip = m_tile_trip_tool.passTileTrip(m_event);
  m_pass_event = (m_pass_event && pass_tile_trip);
  if (m_crit_cut_tile_trip && !pass_tile_trip) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_TILE_TRIP);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_TILE_TRIP, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // bad jet veto
  bool pass_bad_jet_veto = (m_jets.num(JET_BAD) == 0);
  m_pass_event = (m_pass_event && pass_bad_jet_veto);
  if (m_crit_cut_bad_jet_veto && !pass_bad_jet_veto) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_BAD_JET_VETO);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_BAD_JET_VETO, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // calo problem jet cut
  bool pass_calo_problem_jet = (m_jets.num(JET_CALO_PROBLEM) == 0);
  m_pass_event = (m_pass_event && pass_calo_problem_jet);
  if (m_crit_cut_calo_problem_jet && !pass_calo_problem_jet) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_CALO_PROBLEM_JET);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_CALO_PROBLEM_JET, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // primary vertex cut
  bool pass_primary_vertex = PennSusyFrame::passPrimaryVertex(m_vertices);
  m_pass_event = (m_pass_event && pass_primary_vertex);
  if (m_crit_cut_primary_vertex && !pass_primary_vertex) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_PRIMARY_VERTEX);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_PRIMARY_VERTEX, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // bad muon cut
  bool pass_bad_mu_veto = (m_muons.num(MU_BAD) == 0);
  m_pass_event = (m_pass_event && pass_bad_mu_veto);
  if (m_crit_cut_bad_mu_veto && !pass_bad_mu_veto) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_BAD_MUON);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_BAD_MUON, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // cosmic muon veto
  bool pass_cosmic_mu_veto = (m_muons.num(MU_COSMIC) == 0);
  m_pass_event = (m_pass_event && pass_cosmic_mu_veto);
  if (m_crit_cut_cosmic_mu_veto && !pass_cosmic_mu_veto) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_COSMIC_MUON_VETO);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_COSMIC_MUON_VETO, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // HFOR cut
  // TODO validate HFOR cut
  bool pass_hfor = m_hfor_tool.passHFOR(m_mc_truth);
  m_pass_event = (m_pass_event && pass_hfor);
  if (m_crit_cut_hfor && !pass_hfor) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_HFOR);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_HFOR, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // mc overlap cut
  // TODO validate mc overlap cut
  bool pass_mc_overlap = (  PennSusyFrame::passSherpaWWOverlapRemoval(m_event, m_mc_truth)
                         && PennSusyFrame::passZOverlapRemoval(m_mc_truth)
                         );
  m_pass_event = (m_pass_event && pass_mc_overlap);
  if (m_crit_cut_mc_overlap && !pass_mc_overlap) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_MC_OVERLAP);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_MC_OVERLAP, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // fill histograms for BL_PAIRING hist level
  if (m_pass_event) {
    fillHistHandles( PennSusyFrame::BMINUSL_HIST_BASIC_CLEANING
                   , 0
                   , 0
                   , m_event_weight
                   );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // get number of good leptons
  int num_good_leptons = m_electrons.num(EL_GOOD) + m_muons.num(MU_GOOD);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // >= 2 baseline leptons cut
  bool pass_ge_2_lep = (num_good_leptons >= 2);
  m_pass_event = (m_pass_event && pass_ge_2_lep);
  if (m_crit_cut_ge_2_lep && !pass_ge_2_lep) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_GE_2_BASELINE_LEPTONS);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_GE_2_BASELINE_LEPTONS, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // == 2 baseline leptons cut
  bool pass_2_lep = (num_good_leptons == 2);
  m_pass_event = (m_pass_event && pass_2_lep);
  if (m_crit_cut_2_lep && !pass_2_lep) return;
  if (m_pass_event) {
    {
      m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_EQ_2_BASELINE_LEPTONS);
      m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_EQ_2_BASELINE_LEPTONS, m_event_weight);
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // get number of signal leptons
  int num_signal_leptons = m_electrons.num(EL_SIGNAL) + m_muons.num(MU_SIGNAL);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // == 2 signal lepton cut
  bool pass_signal_lep = (num_signal_leptons == 2);
  m_pass_event = (m_pass_event && pass_signal_lep);
  if (m_crit_cut_signal_lep && !pass_signal_lep) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_EQ_2_SIGNAL_LEPTON);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_EQ_2_SIGNAL_LEPTON, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // lepton scale factor
  // TODO validate lepton sf
  m_event_weight *= m_event_quantities.getLeptonSF();
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_LEP_SF);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_LEP_SF, m_event_weight);

    m_raw_cutflow_tracker.fillHist(m_event.getPhaseSpace(), BMINUSL_CUT_LEP_SF);
    m_cutflow_tracker.fillHist(    m_event.getPhaseSpace(), BMINUSL_CUT_LEP_SF, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // get number of b jets
  int num_b_jets = m_jets.num(JET_B);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // check number of b jets >= 2
  bool pass_ge_2_b_jet = (num_b_jets >= 2);
  m_pass_event = (m_pass_event && pass_ge_2_b_jet);
  if (m_crit_cut_b_jets && ! pass_ge_2_b_jet) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_GE_2_B_JET);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_GE_2_B_JET, m_event_weight);

    m_raw_cutflow_tracker.fillHist(m_event.getPhaseSpace(), BMINUSL_CUT_GE_2_B_JET);
    m_cutflow_tracker.fillHist(    m_event.getPhaseSpace(), BMINUSL_CUT_GE_2_B_JET, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // check number of b jets == 2
  bool pass_eq_2_b_jet = (num_b_jets == 2);
  m_pass_event = (m_pass_event && pass_eq_2_b_jet);
  if (m_crit_cut_b_jets && ! pass_eq_2_b_jet) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_EQ_2_B_JET);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_EQ_2_B_JET, m_event_weight);

    m_raw_cutflow_tracker.fillHist(m_event.getPhaseSpace(), BMINUSL_CUT_EQ_2_B_JET);
    m_cutflow_tracker.fillHist(    m_event.getPhaseSpace(), BMINUSL_CUT_EQ_2_B_JET, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // b tag sf
  // TODO validate b tag SF
  m_event_weight *= m_event_quantities.getBTagSF();
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_B_TAG_SF);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_B_TAG_SF, m_event_weight);

    m_raw_cutflow_tracker.fillHist(m_event.getPhaseSpace(), BMINUSL_CUT_B_TAG_SF);
    m_cutflow_tracker.fillHist(    m_event.getPhaseSpace(), BMINUSL_CUT_B_TAG_SF, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // do b-l pairing
  PennSusyFrame::blPair bl_0;
  PennSusyFrame::blPair bl_1;

  bool pass_bl_pairing = PennSusyFrame::doBLPairing( m_event
                                                   , m_electrons.getCollection(EL_GOOD)
                                                   , m_muons.getCollection(MU_GOOD)
                                                   , m_jets.getCollection(JET_B)
                                                   , bl_0
                                                   , bl_1
                                                   );
  m_pass_event = (m_pass_event && pass_bl_pairing);
  if (m_crit_cut_bl_pairing && !pass_bl_pairing) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_BL_PAIRING);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_BL_PAIRING, m_event_weight);

    m_raw_cutflow_tracker.fillHist(m_event.getPhaseSpace(), BMINUSL_CUT_BL_PAIRING);
    m_cutflow_tracker.fillHist(    m_event.getPhaseSpace(), BMINUSL_CUT_BL_PAIRING, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // fill histograms for BL_PAIRING hist level
  if (m_pass_event) {
    fillHistHandles( PennSusyFrame::BMINUSL_HIST_BL_PAIRING
                   , &bl_0
                   , &bl_1
                   , m_event_weight
                   );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // do z veto fo SFOS lepton pairs
  bool pass_z_veto = true;
  if (  m_event.getFlavorChannel() == FLAVOR_EE
     || m_event.getFlavorChannel() == FLAVOR_MM
     ) {
    pass_z_veto = ( fabs(m_event_quantities.getMll() - 91.e3) > 10.e3 );
  }
  m_pass_event = (m_pass_event && pass_z_veto);
  if (m_crit_cut_z_veto && !pass_z_veto) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_ZVETO);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_ZVETO, m_event_weight);

    m_raw_cutflow_tracker.fillHist(m_event.getPhaseSpace(), BMINUSL_CUT_ZVETO);
    m_cutflow_tracker.fillHist(    m_event.getPhaseSpace(), BMINUSL_CUT_ZVETO, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // fill histograms for ZVETO hist level
  if (m_pass_event) {
    fillHistHandles( PennSusyFrame::BMINUSL_HIST_ZVETO
                   , &bl_0
                   , &bl_1
                   , m_event_weight
                   );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Apply met cut
  bool pass_met = ( PennSusyFrame::passCut( m_met.getMetEt()
                                          , m_met_min
                                          , m_met_max
                                          )
                  );
  m_pass_event = (m_pass_event && pass_met);
  if (m_crit_cut_met && !pass_met) return;
  if (m_pass_event) {
    m_raw_cutflow_tracker.fillHist(FLAVOR_NONE, BMINUSL_CUT_MET);
    m_cutflow_tracker.fillHist(    FLAVOR_NONE, BMINUSL_CUT_MET, m_event_weight);

    m_raw_cutflow_tracker.fillHist(m_event.getPhaseSpace(), BMINUSL_CUT_MET);
    m_cutflow_tracker.fillHist(    m_event.getPhaseSpace(), BMINUSL_CUT_MET, m_event_weight);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // fill histograms for MET hist level
  if (m_pass_event) {
    fillHistHandles( PennSusyFrame::BMINUSL_HIST_MET
                   , &bl_0
                   , &bl_1
                   , m_event_weight
                   );
  }
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    // fill histograms for GE_4_OBJECTS hist level
  fillHistHandles( PennSusyFrame::BMINUSL_HIST_GE_4_OBJECTS
		   , &bl_0
		   , &bl_1
		   , m_event_weight
		   );

}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLAnalysis::finalizeEvent()
{
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLAnalysis::finalizeRun()
{
  std::cout << "BMinusLAnalysis::finalizeRun()\n";
  std::cout << "creating output histogram file\n";
  TFile out_hist_file(m_out_hist_file_name.c_str(), "RECREATE");

  m_d3pd_reader->writeNumEvents();

  // TDirectory* hist_dir = out_hist_file.mkdir("hists");

  std::cout << "about to write histograms to file\n";
  for ( unsigned int hist_level = 0
      ; hist_level != BMINUSL_HIST_N
      ; ++hist_level
      ) {
    TDirectory* hist_dir_cut_level = out_hist_file.mkdir(PennSusyFrame::BMINUSL_HIST_LEVEL_STRINGS[hist_level].c_str());

    size_t num_hists = m_histogram_handlers.at(hist_level).size();
    for (size_t hist_it = 0; hist_it != num_hists; ++hist_it) {
      std::cout << "\twriting histogram handler " << hist_it << " to file\n";
      m_histogram_handlers.at(hist_level).at(hist_it)->write(hist_dir_cut_level);
    }

    m_bminusl_histogram_handler.at(hist_level)->write(hist_dir_cut_level);
  }
  std::cout << "done writing histograms to file\n";

  out_hist_file.Close();
  std::cout << "file is closed!\n";

  m_raw_cutflow_tracker.printToScreen();
  m_cutflow_tracker.printToScreen();
}

// -----------------------------------------------------------------------------
PHASE_SPACE PennSusyFrame::BMinusLAnalysis::getPhaseSpace()
{
  if (m_event.getFlavorChannel() == FLAVOR_EE) return PHASE_EE;
  if (m_event.getFlavorChannel() == FLAVOR_MM) return PHASE_MM;
  if (m_event.getFlavorChannel() == FLAVOR_EM) {
    float pt_e = m_electrons.getCollection(EL_GOOD)->at(0)->getPt();
    float pt_m = m_muons.getCollection(    MU_GOOD)->at(0)->getPt();
    if (pt_e >= pt_m) return PHASE_EM;
    return PHASE_ME;
  }

  return PHASE_NONE;
}

// -----------------------------------------------------------------------------
void PennSusyFrame::BMinusLAnalysis::fillHistHandles( PennSusyFrame::BMINUSL_HIST_LEVELS hist_level
                                                    , const PennSusyFrame::blPair* bl_0
                                                    , const PennSusyFrame::blPair* bl_1
                                                    , float weight
                                                    )
{
  size_t num_hists = m_histogram_handlers.at(hist_level).size();
  for (size_t hist_it = 0; hist_it != num_hists; ++hist_it) {
    m_histogram_handlers.at(hist_level).at(hist_it)->Fill( m_event
                                                         , m_event_quantities
                                                         , m_electrons.getCollection(EL_GOOD)
                                                         , m_muons.getCollection(MU_GOOD)
                                                         , m_jets.getCollection(JET_GOOD)
                                                         , m_met
                                                         , weight
                                                         );
  }
  if (bl_0 && bl_1) {
    m_bminusl_histogram_handler.at(hist_level)->FillSpecial( m_event
                                                           , m_jets.getCollection(JET_B)
                                                           , *bl_0
                                                           , *bl_1
                                                           , m_mc_truth
                                                           , weight
                                                           );
  }
}
