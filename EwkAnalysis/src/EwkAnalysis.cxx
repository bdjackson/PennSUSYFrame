#include "EwkAnalysis/include/EwkAnalysis.h"
#include "PennSusyFrameCore/include/PennSusyFrameCore.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <dirent.h>
#include <math.h>
#include <algorithm>

#include "PennSusyFrameCore/include/ObjectContainers.h"
#include "PennSusyFrameCore/include/Calculators.h"

// -----------------------------------------------------------------------------
PennSusyFrame::EwkAnalysis::EwkAnalysis(TTree* tree) : PennSusyFrame::PennSusyFrameCore(tree)
{
  std::string base_dir = getenv("ROOTCOREDIR");
  if (m_is_data) {
    // TODO make this configurable
    m_grl.init( base_dir
              + "data/data12_8TeV.periodAllYear_DetStatus-v58-pro14-01_DQDefects-00-00-33_PHYS_StandardGRL_All_Good.xml"
              );
  }
}

// -----------------------------------------------------------------------------
PennSusyFrame::EwkAnalysis::~EwkAnalysis()
{}

// -----------------------------------------------------------------------------
void PennSusyFrame::EwkAnalysis::processEvent()
{
  bool pass_event = true;
  m_event_weight = 1.;

  // GRL cut
  bool pass_grl = m_grl.passEvent(m_event);
  pass_event = (pass_event && pass_grl);
  if (m_crit_cut_grl && !pass_grl) return;

  // incomplete event cut
  // TODO implement incomplete event cut
  bool pass_incomplete_event = true;
  pass_event = (pass_event && pass_incomplete_event);
  if (m_crit_cut_incomplete_event && !pass_incomplete_event) return;

  // LAr error cut
  // TODO implement LAr error cut
  bool pass_lar_error = true;
  pass_event = (pass_event && pass_lar_error);
  if (m_crit_cut_lar_error && !pass_lar_error) return;

  // tile error cut
  // TODO implement tile error cut
  bool pass_tile_error = true;
  pass_event = (pass_event && pass_tile_error);
  if (m_crit_cut_tile_error && !pass_tile_error) return;

  // tile hot spot cut
  // TODO implement tile hot spot cut
  bool pass_tile_hot_spot = true;
  pass_event = (pass_event && pass_tile_hot_spot);
  if (m_crit_cut_tile_hot_spot && !pass_tile_hot_spot) return;

  // tile trip cut
  // TODO implement tile trip cut
  bool pass_tile_trip = true;
  pass_event = (pass_event && pass_tile_trip);
  if (m_crit_cut_tile_trip && !pass_tile_trip) return;

  // bad jet veto
  // TODO validate bad jet veto
  bool pass_bad_jet_veto = (m_jets.num(JET_BAD) == 0);
  pass_event = (pass_event && pass_bad_jet_veto);
  if (m_crit_cut_bad_jet_veto && !pass_bad_jet_veto) return;

  // calo problem jet cut
  // TODO validate calo problem jet cut
  bool pass_calo_problem_jet = (m_jets.num(JET_CALO_PROBLEM) == 0);
  pass_event = (pass_event && pass_calo_problem_jet);
  if (m_crit_cut_calo_problem_jet && !pass_calo_problem_jet) return;

  // primary vertex cut
  // TODO implement primary vertex cut
  bool pass_primary_vertex = true;
  pass_event = (pass_event && pass_primary_vertex);
  if (m_crit_cut_primary_vertex && !pass_primary_vertex) return;

  // bad muon cut
  // TODO validate bad muon cut
  bool pass_bad_mu_veto = (m_muons.num(MU_BAD) == 0);
  pass_event = (pass_event && pass_bad_mu_veto);
  if (m_crit_cut_bad_mu_veto && !pass_bad_mu_veto) return;

  // cosmic muon veto
  // TODO validate cosmic muon veto
  bool pass_cosmic_mu_veto = (m_muons.num(MU_COSMIC) == 0);
  pass_event = (pass_event && pass_cosmic_mu_veto);
  if (m_crit_cut_cosmic_mu_veto && !pass_cosmic_mu_veto) return;

  // HFOR cut
  // TODO implement HFOR cut
  bool pass_hfor = true;
  pass_event = (pass_event && pass_hfor);
  if (m_crit_cut_hfor && !pass_hfor) return;

  // mc overlap cut
  // TODO implement mc overlap cut
  bool pass_mc_overlap = true;
  pass_event = (pass_event && pass_mc_overlap);
  if (m_crit_cut_mc_overlap && !pass_mc_overlap) return;

  // get number of good leptons
  int num_good_leptons = m_electrons.num(EL_GOOD) + m_muons.num(MU_GOOD);

  // >= 2 baseline leptons cut
  // TODO validate >= 2 baseline leptons cut
  bool pass_ge_2_lep = (num_good_leptons >= 2);
  pass_event = (pass_event && pass_ge_2_lep);
  if (m_crit_cut_ge_2_lep && !pass_ge_2_lep) return;

  // == 2 baseline leptons cut
  // TODO validate == 2 baseline leptons cut
  bool pass_2_lep = (num_good_leptons == 2);
  pass_event = (pass_event && pass_2_lep);
  if (m_crit_cut_2_lep && !pass_2_lep) return;

  // tau veto
  // TODO validate tau veto
  bool pass_tau_veto = (m_taus.num(TAU_SIGNAL) == 0);
  pass_event = (pass_event && pass_tau_veto);
  if (m_crit_cut_tau_veto && !pass_tau_veto) return;

  // mll SFOS cut
  // TODO implement mll SFOS cut
  bool pass_mll_sfos = true;
  pass_event = (pass_event && pass_mll_sfos);
  if (m_crit_cut_mll_sfos && !pass_mll_sfos) return;

  // get number of signal leptons
  int num_signal_leptons = m_electrons.num(EL_SIGNAL) + m_muons.num(MU_SIGNAL);

  // == 2 signal lepton cut
  // TODO validate == 2 signal lepton cut
  bool pass_signal_lep = (num_signal_leptons == 2);
  pass_event = (pass_event && pass_signal_lep);
  if (m_crit_cut_signal_lep && !pass_signal_lep) return;

  // phase space cut
  // TODO implement phase space cut
  bool pass_phase_space = true;
  pass_event = (pass_event && pass_phase_space);
  if (m_crit_cut_phase_space && !pass_phase_space) return;

  // trigger cut
  // TODO implement trigger cut
  bool pass_trigger = true;
  pass_event = (pass_event && pass_trigger);
  if (m_crit_cut_trigger && !pass_trigger) return;

  // trigger matching
  // TODO implement trigger matching
  bool pass_trigger_match = true;
  pass_event = (pass_event && pass_trigger_match);
  if (m_crit_cut_trigger_match && !pass_trigger_match) return;

  // check for prompt leptons
  // TODO implement check for prompt leptons
  bool pass_prompt_leptons = true;
  pass_event = (pass_event && pass_prompt_leptons);
  if (m_crit_cut_prompt_leptons && !pass_prompt_leptons) return;

  // check for stream overlap
  // TODO implement check for stream overlap
  bool pass_stream_overlap = true;
  pass_event = (pass_event && pass_stream_overlap);
  if (m_crit_cut_stream_overlap && !pass_stream_overlap) return;

}

// -----------------------------------------------------------------------------
void PennSusyFrame::EwkAnalysis::finalizeEvent()
{

}
