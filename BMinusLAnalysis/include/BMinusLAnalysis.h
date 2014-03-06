#ifndef BMINUSLANALYSIS_H
#define BMINUSLANALYSIS_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "PennSusyFrameCore/include/PennSusyFrameCore.h"
#include "PennSusyFrameCore/include/EventSelectors.h"
#include "HistogramHandlers/include/HistogramHandlers.h"
#include "BMinusLAnalysis/include/BMinusLCutFlowTracker.h"
#include "BMinusLAnalysis/include/BMinusLHistogramHandlers.h"

// =============================================================================
namespace PennSusyFrame
{
  enum BMINUSL_HIST_LEVELS { BMINUSL_HIST_BL_PAIRING
                           , BMINUSL_HIST_ZVETO
                           , BMINUSL_HIST_MET
                           , BMINUSL_HIST_N
                           };

  const std::string BMINUSL_HIST_LEVEL_STRINGS[] = { "BMINUSL_BL_PAIRING"
                                                   , "BMINUSL_ZVETO"
                                                   , "BMINUSL_MET"
                                                   };

  // ===========================================================================
  class BMinusLAnalysis : public PennSusyFrame::PennSusyFrameCore
  {
    public :
      BMinusLAnalysis(TTree *tree=0);
      virtual ~BMinusLAnalysis();

      virtual void prepareTools();

      virtual void prepareSelection();

      virtual void beginRun();
      virtual void processEvent();
      virtual void finalizeEvent();
      virtual void finalizeRun();

      PHASE_SPACE getPhaseSpace();

      void setOutHistFileName(std::string val) { m_out_hist_file_name = val; }

      void setCritCutGrl(            bool val) { m_crit_cut_grl = val;              }
      void setCritCutIncompleteEvent(bool val) { m_crit_cut_incomplete_event = val; }
      void setCritCutLarError(       bool val) { m_crit_cut_lar_error = val;        }
      void setCritCutTileError(      bool val) { m_crit_cut_tile_error = val;       }
      void setCritCutTileHotSpot(    bool val) { m_crit_cut_tile_hot_spot = val;    }
      void setCritCutTileTrip(       bool val) { m_crit_cut_tile_trip = val;        }
      void setCritCutBadJetVeto(     bool val) { m_crit_cut_bad_jet_veto = val;     }
      void setCritCutCaloProblemJet( bool val) { m_crit_cut_calo_problem_jet = val; }
      void setCritCutPrimaryVertex(  bool val) { m_crit_cut_primary_vertex = val;   }
      void setCritCutBadMuonVeto(    bool val) { m_crit_cut_bad_mu_veto = val;      }
      void setCritCutCosmicMuonVeto( bool val) { m_crit_cut_cosmic_mu_veto = val;   }
      void setCritCutHFOR(           bool val) { m_crit_cut_hfor = val;             }
      void setCritCutMcOverlap(      bool val) { m_crit_cut_mc_overlap = val;       }
      void setCritCutGe2Lepton(      bool val) { m_crit_cut_ge_2_lep = val;         }
      void setCritCut2Lepton(        bool val) { m_crit_cut_2_lep = val;            }
      void setCritCut2SignalLepton(  bool val) { m_crit_cut_signal_lep = val;       }
      void setCritCut2BJets(         bool val) { m_crit_cut_b_jets = val;           }
      void setCritCutBLPairing(      bool val) { m_crit_cut_bl_pairing = val;       }
      void setCritCutZVeto(          bool val) { m_crit_cut_z_veto = val;           }
      void setCritCutMet(            bool val) { m_crit_cut_met = val;              }

      void setMetCut(float min, float max) { m_met_min = min ; m_met_max = max; }

    protected:
      void fillHistHandles( BMINUSL_HIST_LEVELS
                          , const PennSusyFrame::blPair&
                          , const PennSusyFrame::blPair&
                          , float weight
                          );
      std::string m_out_hist_file_name;

      PennSusyFrame::LeptonKinematicsHists m_lep_hists;

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
      bool m_crit_cut_b_jets;
      bool m_crit_cut_bl_pairing;
      bool m_crit_cut_z_veto;
      bool m_crit_cut_met;

      PennSusyFrame::GrlTool m_grl;
      PennSusyFrame::TileTripTool m_tile_trip_tool;
      PennSusyFrame::HFORTool m_hfor_tool;

      BMinusLCutFlowTracker m_raw_cutflow_tracker;
      BMinusLCutFlowTracker m_cutflow_tracker;

      std::vector<PennSusyFrame::BMinusLHists*> m_bminusl_histogram_handler;

      double m_met_min;
      double m_met_max;

    private:
  };
}

#endif
