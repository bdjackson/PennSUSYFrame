#ifndef BMINUSLANALYSIS_H
#define BMINUSLANALYSIS_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <fstream>

#include "PennSusyFrameCore/include/PennSusyFrameCore.h"
#include "PennSusyFrameCore/include/EventSelectors.h"
#include "HistogramHandlers/include/HistogramHandlers.h"
#include "BMinusLAnalysis/include/BMinusLCutFlowTracker.h"
#include "BMinusLAnalysis/include/BMinusLHistogramHandlers.h"
#include "BMinusLAnalysis/include/BMinusLTriggerScaleFactor.h"

// =============================================================================
namespace PennSusyFrame
{
  enum BMINUSL_HIST_LEVELS { BMINUSL_HIST_BL_PAIRING
                           , BMINUSL_HIST_Z_VETO
                           , BMINUSL_HIST_GE_4_OBJECTS
                           , BMINUSL_HIST_NO_WEIGHTS

                           , BMINUSL_HIST_ZREGION_MBL_200

                           , BMINUSL_HIST_PARTIAL_SR_HT_1100_Z_VETO

                           , BMINUSL_HIST_SR_HT_1100_MBL_400_MINUS_HT
                           , BMINUSL_HIST_SR_HT_1100_MBL_600_MINUS_HT

                           , BMINUSL_HIST_SR_HT_1100_MBL_400_MINUS_MBL_ASYM
                           , BMINUSL_HIST_SR_HT_1100_MBL_600_MINUS_MBL_ASYM

                           , BMINUSL_HIST_SR_HT_1100_MBL_400_MINUS_Z_VETO
                           , BMINUSL_HIST_SR_HT_1100_MBL_600_MINUS_Z_VETO

                           , BMINUSL_HIST_SR_HT_1100_MINUS_MBL

                           , BMINUSL_HIST_SR_HT_1100_MBL_200
                           , BMINUSL_HIST_SR_HT_1100_MBL_400
                           , BMINUSL_HIST_SR_HT_1100_MBL_600

                           , BMINUSL_HIST_CR_TOP_MBL_200_MINUS_HT
                           , BMINUSL_HIST_CR_TOP_MBL_200_MINUS_MBL_ASYM
                           , BMINUSL_HIST_CR_TOP_MBL_200_MINUS_MET_SIG
                           , BMINUSL_HIST_CR_TOP_MBL_200

                           , BMINUSL_HIST_CR_Z_MBL_200_MINUS_HT
                           , BMINUSL_HIST_CR_Z_MBL_200_MINUS_MBL_ASYM
                           , BMINUSL_HIST_CR_Z_MBL_200_MINUS_MET_SIG
                           , BMINUSL_HIST_CR_Z_MBL_200

                           , BMINUSL_HIST_VR_TOP_MBL_200_1
                           , BMINUSL_HIST_VR_TOP_MBL_200_2
                           , BMINUSL_HIST_VR_TOP_MBL_200_3
                           , BMINUSL_HIST_VR_TOP_MBL_200_4
                           , BMINUSL_HIST_VR_Z_MBL_200

                           , BMINUSL_HIST_N
                           };

  const std::string BMINUSL_HIST_LEVEL_STRINGS[] = { "BMINUSL_BL_PAIRING"
                                                   , "BMINUSL_ZVETO"
                                                   , "BMINUSL_GE_4_OBJECTS"
                                                   , "BMINUSL_NO_WEIGHTS"

                                                   , "BMINUSL_ZREGION_MBL_200"

                                                   , "BMINUSL_PARTIAL_SR_HT_1100_Z_VETO"

                                                   , "BMINUSL_SR_HT_1100_MBL_400_MINUS_HT"
                                                   , "BMINUSL_SR_HT_1100_MBL_600_MINUS_HT"

                                                   , "BMINUSL_SR_HT_1100_MBL_400_MINUS_MBL_ASYM"
                                                   , "BMINUSL_SR_HT_1100_MBL_600_MINUS_MBL_ASYM"

                                                   , "BMINUSL_SR_HT_1100_MBL_400_MINUS_Z_VETO"
                                                   , "BMINUSL_SR_HT_1100_MBL_600_MINUS_Z_VETO"

                                                   , "BMINUSL_SR_HT_1100_MINUS_MBL"

                                                   , "BMINUSL_SR_HT_1100_MBL_200"
                                                   , "BMINUSL_SR_HT_1100_MBL_400"
                                                   , "BMINUSL_SR_HT_1100_MBL_600"

                                                   , "BMINUSL_CR_TOP_MBL_200_MINUS_HT"
                                                   , "BMINUSL_CR_TOP_MBL_200_MINUS_MBL_ASYM"
                                                   , "BMINUSL_CR_TOP_MBL_200_MINUS_MET_SIG"
                                                   , "BMINUSL_CR_TOP_MBL_200"

                                                   , "BMINUSL_CR_Z_MBL_200_MINUS_HT"
                                                   , "BMINUSL_CR_Z_MBL_200_MINUS_MBL_ASYM"
                                                   , "BMINUSL_CR_Z_MBL_200_MINUS_MET_SIG"
                                                   , "BMINUSL_CR_Z_MBL_200"

                                                   , "BMINUSL_VR_TOP_1_MBL_200"
                                                   , "BMINUSL_VR_TOP_2_MBL_200"
                                                   , "BMINUSL_VR_TOP_3_MBL_200"
                                                   , "BMINUSL_VR_TOP_4_MBL_200"
                                                   , "BMINUSL_VR_Z_MBL_200"

                                                   , "BMINUSL_N"
                                                   };

  // ---------------------------------------------------------------------------
  class blPair;

  // ===========================================================================
  class BMinusLAnalysis : public PennSusyFrame::PennSusyFrameCore
  {
    public :
      BMinusLAnalysis(TTree *tree=0);
      virtual ~BMinusLAnalysis();

      virtual void prepareTools();

      virtual void prepareSelection();

      virtual void beginRun();
      virtual void initializeEvent();
      virtual void processEvent();
      virtual void finalizeEvent();
      virtual void finalizeRun();

      void fillTrackers(BMINUSL_CUTS);
      PHASE_SPACE getPhaseSpace();
      bool passPhaseSpace();
      bool passTriggerMatch();

      void setOutHistFileName(std::string val) { m_out_hist_file_name = val; }

      void setDoZKFactor(bool val) { m_do_z_k_factor = val; }
      void setDoDetailedBLHists(bool val = true) { m_do_detailed_bl_hists = val; }

      void setCritCutGrl(            bool val) { m_crit_cut_grl              = val; }
      void setCritCutIncompleteEvent(bool val) { m_crit_cut_incomplete_event = val; }
      void setCritCutLarError(       bool val) { m_crit_cut_lar_error        = val; }
      void setCritCutTileError(      bool val) { m_crit_cut_tile_error       = val; }
      void setCritCutTileHotSpot(    bool val) { m_crit_cut_tile_hot_spot    = val; }
      void setCritCutTileTrip(       bool val) { m_crit_cut_tile_trip        = val; }
      void setCritCutBadJetVeto(     bool val) { m_crit_cut_bad_jet_veto     = val; }
      void setCritCutCaloProblemJet( bool val) { m_crit_cut_calo_problem_jet = val; }
      void setCritCutPrimaryVertex(  bool val) { m_crit_cut_primary_vertex   = val; }
      void setCritCutBadMuonVeto(    bool val) { m_crit_cut_bad_mu_veto      = val; }
      void setCritCutCosmicMuonVeto( bool val) { m_crit_cut_cosmic_mu_veto   = val; }
      void setCritCutHFOR(           bool val) { m_crit_cut_hfor             = val; }
      void setCritCutMcOverlap(      bool val) { m_crit_cut_mc_overlap       = val; }
      void setCritCutGe2Lepton(      bool val) { m_crit_cut_ge_2_lep         = val; }
      void setCritCut2Lepton(        bool val) { m_crit_cut_2_lep            = val; }
      void setCritCut2SignalLepton(  bool val) { m_crit_cut_signal_lep       = val; }
      void setCritCutOSLeptons(      bool val) { m_crit_cut_os_lep           = val; }
      void setCritCut2BJets(         bool val) { m_crit_cut_b_jets           = val; }
      void setCritCutBLPairing(      bool val) { m_crit_cut_bl_pairing       = val; }
      void setCritCutZVeto(          bool val) { m_crit_cut_z_veto           = val; }
      void setCritCutMet(            bool val) { m_crit_cut_met              = val; }

      void setMetCut(   float min, float max) { m_met_min               = min ; m_met_max               = max; }
      void setElPtCut(  float min, float max) { m_min_el_pt_baseline    = min ; m_max_el_pt_baseline    = max; }
      void setMuPtCut(  float min, float max) { m_min_mu_pt_baseline    = min ; m_max_mu_pt_baseline    = max; }
      void setBJetPtCut(float min, float max) { m_min_b_jet_pt_baseline = min ; m_max_b_jet_pt_baseline = max; }

    protected:
      virtual void constructObjects();
      virtual void getSelectedObjects();

      void fillHistHandles( BMINUSL_HIST_LEVELS
                          , const PennSusyFrame::blPair*
                          , const PennSusyFrame::blPair*
                          , float weight
                          );

      std::string m_out_hist_file_name;

      bool m_do_z_k_factor;
      bool m_do_detailed_bl_hists;

      bool m_crit_cut_grl;
      bool m_crit_cut_incomplete_event;
      bool m_crit_cut_lar_error;
      bool m_crit_cut_tile_error;
      bool m_crit_cut_tile_hot_spot;
      bool m_crit_cut_tile_trip;
      bool m_crit_cut_bad_jet_veto;
      bool m_crit_cut_calo_problem_jet;
      bool m_crit_cut_primary_vertex;
      bool m_crit_cut_bad_mu_veto;
      bool m_crit_cut_cosmic_mu_veto;
      bool m_crit_cut_hfor;
      bool m_crit_cut_mc_overlap;
      bool m_crit_cut_ge_2_lep;
      bool m_crit_cut_2_lep;
      bool m_crit_cut_signal_lep;
      bool m_crit_cut_os_lep;
      bool m_crit_cut_b_jets;
      bool m_crit_cut_bl_pairing;
      bool m_crit_cut_z_veto;
      bool m_crit_cut_met;

      bool m_no_weights;

      PennSusyFrame::GrlTool m_grl;
      PennSusyFrame::TileTripTool m_tile_trip_tool;
      PennSusyFrame::HFORTool m_hfor_tool;

      BMinusLTriggerScaleFactor m_bminusl_trigger_sf_tool;

      BMinusLCutFlowTracker m_raw_cutflow_tracker;
      BMinusLCutFlowTracker m_cutflow_tracker;

      std::vector<PennSusyFrame::BMinusLHists*> m_bminusl_histogram_handler;
      std::vector<PennSusyFrame::JetMultiplicityHists*> m_jet_multiplicity_histogram_handler;
      std::vector<PennSusyFrame::ParentHists*>  m_parent_histogram_handler;
      std::vector<PennSusyFrame::BMinusLDetailedHists*> m_bminusl_detailed_histogram_handler;

      PennSusyFrame::blPair* m_bl_0;
      PennSusyFrame::blPair* m_bl_1;

      double m_mc_event_weight;
      double m_pile_up_sf;
      double m_lepton_sf;
      double m_trigger_sf;
      double m_btag_sf;
      double m_ttbar_pt_weight;
      double m_fudge_k_factor_weight;

      bool m_pass_grl;
      bool m_pass_incomplete_event;
      bool m_pass_lar_error;
      bool m_pass_tile_error;
      bool m_pass_tile_hot_spot;
      bool m_pass_tile_trip;
      bool m_pass_bad_jet_veto;
      bool m_pass_calo_problem_jet;
      bool m_pass_primary_vertex;
      bool m_pass_bad_mu_veto;
      bool m_pass_cosmic_mu_veto;
      bool m_pass_hfor;
      bool m_pass_mc_overlap;
      bool m_pass_ge_2_lep;
      bool m_pass_2_lep;
      bool m_pass_signal_lep;
      bool m_pass_os;
      bool m_pass_trigger;
      bool m_pass_phase;
      bool m_pass_trigger_match;
      bool m_pass_ge_2_b_jet;
      bool m_pass_eq_2_b_jet;
      bool m_pass_bl_pairing;
      bool m_pass_z_veto;
      bool m_pass_wide_z_veto;
      bool m_pass_met;

      double m_met_min;
      double m_met_max;

      double m_min_el_pt_baseline;
      double m_max_el_pt_baseline;

      double m_min_mu_pt_baseline;
      double m_max_mu_pt_baseline;

      double m_min_b_jet_pt_baseline;
      double m_max_b_jet_pt_baseline;
  };
}

#endif
