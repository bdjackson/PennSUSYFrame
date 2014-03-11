// Dear emacs, this is -*- c++ -*-
#ifndef SusyAnalysisTools_EventDescription_h
#define SusyAnalysisTools_EventDescription_h

#include "SusyEnums.h"

// ============================================================================
namespace SusyAnalysisTools
{
  // ==========================================================================
  class EventDescription
  {
    // ------------------------------------------------------------------------
    public:
      EventDescription();
      EventDescription(ull_t);
      ~EventDescription();

      ull_t toInt() const;

      void clear();
      void set (const EventDescription&);
      void set (const ull_t&);
      EventDescription& operator=(const EventDescription&);
      EventDescription& operator=(const ull_t&);

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      // Setter functions
      void setIsData(bool);
      void setPassGrl(bool);
      void setPassIncompleteEvent(bool);
      void setPassLarError(bool);
      void setPassTileError(bool);
      void setPassTileHotSpot(bool);
      void setPassBadJets(bool);
      void setPassCaloProblemJets(bool);
      void setPassPrimaryVertex(bool);
      void setPassBadMuons(bool);
      void setPassCosmicMuons(bool);
      void setPassHFOR(bool);
      void setPassMCOverlap(bool);
      void setPassGE2GoodLeptons(bool);
      void setPass2GoodLeptons(bool);
      void setPassMll(bool);
      void setPass2SignalLeptons(bool);
      void setPassTriggerMatch(bool);
      void setFlavorChannel(FLAVOR_CHANNEL);
      void setPhaseSpace(PHASE_SPACE);
      void setPhaseSpace(TRIG_PHASE);
      void setEETrigger(bool);
      void setMMTrigger(bool);
      void setEMTrigger(bool);
      void setMETrigger(bool);
      void setSignChannel(SIGN_CHANNEL);

      void setTruthMatched(bool);
      void setTruthPrompt(bool);
      void setCFCandidate(bool);
      void setTruthSignChannel(SIGN_CHANNEL);

      void setPassTileTrip(bool);
      void setPassTauVeto(bool);

      void setSRSS(bool);

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      // Getter functions
      bool getIsData() const;
      bool getPassGrl() const;
      bool getPassIncompleteEvent() const;
      bool getPassLarError() const;
      bool getPassTileError() const;
      bool getPassTileHotSpot() const;
      bool getPassBadJets() const;
      bool getPassCaloProblemJets() const;
      bool getPassPrimaryVertex() const;
      bool getPassBadMuons() const;
      bool getPassCosmicMuons() const;
      bool getPassHFOR() const;
      bool getPassMCOverlap() const;
      bool getPassGE2GoodLeptons() const;
      bool getPass2GoodLeptons() const;
      bool getPassMll() const;
      bool getPass2SignalLeptons() const;
      bool getPassTriggerMatch() const;
      FLAVOR_CHANNEL  getFlavorChannel() const;
      PHASE_SPACE     getPhaseSpace() const;
      bool isEETrigger() const;
      bool isMMTrigger() const;
      bool isEMTrigger() const;
      bool isMETrigger() const;
      SIGN_CHANNEL    getSignChannel() const;

      bool getTruthMatched() const;
      bool getTruthPrompt() const;
      bool getCFCandidate() const;
      SIGN_CHANNEL getTruthSignChannel() const;

      bool getPassTileTrip() const;
      bool getPassTauVeto() const;

      bool getPassSRSS() const;

      bool pass(   const EventDescription& test) const;
      bool reverse(const EventDescription& test) const;

    // -------------------------------------------------------------------------
    private:
      static const unsigned int SIZE_BOOL    = 1;
      static const unsigned int SIZE_FLAVOR  = 3;
      static const unsigned int SIZE_PHASE   = 4;
      static const unsigned int SIZE_SIGN    = 2;

      static const unsigned int ADD_IS_DATA            = 0;
      static const unsigned int ADD_GRL                = 1;
      static const unsigned int ADD_INCOMPLETE_EVENT   = 2;
      static const unsigned int ADD_LAR_ERROR          = 3;
      static const unsigned int ADD_TILE_ERROR         = 4;
      static const unsigned int ADD_TILE_HOT_SPOT      = 5;
      static const unsigned int ADD_BAD_JETS           = 6;
      static const unsigned int ADD_CALO_PROBLEM_JETS  = 7;
      static const unsigned int ADD_PRIMARY_VERTEX     = 8;
      static const unsigned int ADD_BAD_MUONS          = 9;
      static const unsigned int ADD_COSMIC_MUONS       = 10;
      static const unsigned int ADD_HFOR               = 11;
      static const unsigned int ADD_MC_OVERLAP         = 12;
      static const unsigned int ADD_GE_2_GOOD_LEPTON   = 13;
      static const unsigned int ADD_2_GOOD_LEPTON      = 14;
      static const unsigned int ADD_2_SIGNAL_LEPTON    = 15;
      static const unsigned int ADD_MLL                = 16;
      static const unsigned int ADD_FLAVOR_CHANNEL     = 17;
      static const unsigned int ADD_PHASE_SPACE        = 20;
      static const unsigned int ADD_TRIGGER_EE         = 24;
      static const unsigned int ADD_TRIGGER_MM         = 25;
      static const unsigned int ADD_TRIGGER_EM         = 26;
      static const unsigned int ADD_TRIGGER_ME         = 27;
      static const unsigned int ADD_TRIGGER_MATCH      = 28;
      static const unsigned int ADD_SIGN_CHANNEL       = 29;
      static const unsigned int ADD_TRUTH_SIGN_CHANNEL = 31;
      static const unsigned int ADD_TRUTH_MATCHED      = 33;
      static const unsigned int ADD_TRUTH_PROMPT       = 34;
      static const unsigned int ADD_TRUTH_CF_CAND      = 35;
      static const unsigned int ADD_TILE_TRIP          = 36;
      static const unsigned int ADD_TAU_VETO           = 37;

      static const unsigned int ADD_SR_SS              = 41;


      bool            m_is_data;
      bool            m_pass_grl;
      bool            m_pass_incomplete_event;
      bool            m_pass_lar_error;
      bool            m_pass_tile_error;
      bool            m_pass_tile_hot_spot;
      bool            m_pass_bad_jets;
      bool            m_pass_calo_problem_jets;
      bool            m_pass_primary_vertex;
      bool            m_pass_bad_muons;
      bool            m_pass_cosmic_muons;
      bool            m_pass_hfor;
      bool            m_pass_mc_overlap;
      bool            m_pass_ge_2_good_leptons;
      bool            m_pass_2_good_leptons;
      bool            m_pass_mll;
      bool            m_pass_2_signal_leptons;
      FLAVOR_CHANNEL  m_flavor_channel;
      PHASE_SPACE     m_phase_space;
      bool            m_pass_ee_trigger;
      bool            m_pass_mm_trigger;
      bool            m_pass_em_trigger;
      bool            m_pass_me_trigger;
      bool            m_pass_trigger_match;
      SIGN_CHANNEL    m_sign_channel;

      SIGN_CHANNEL m_truth_sign_channel;
      bool         m_truth_matched;
      bool         m_truth_prompt;
      bool         m_cf_candidate;

      bool m_pass_tile_trip;
      bool m_pass_tau_veto;

      bool m_pass_sr_ss;

      // TODO move implementation to icc file
      template <class T>
        static ull_t getIntComp( T component
                               , unsigned int address
                               )
        {
          return ( static_cast<ull_t>(component) << address );
        }

      static unsigned int getComponent( const ull_t& rhs
                                      , unsigned int address
                                      , unsigned int size
                                      );
  };

} /* end of SusyAnalysisTools */


#endif /* end of include guard: SusyAnalysisTools_EventDescription_h */