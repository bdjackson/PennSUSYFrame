#ifndef ObjectDefs_H
#define ObjectDefs_H

#include <vector>

#include "TLorentzVector.h"
#include "PennSusyFrameCore/include/RescalerTools.h"
#include "RootCore/MissingETUtility/MissingETUtility/METUtility.h"

// =============================================================================
namespace PennSusyFrame
{
  class D3PDReader;

  class PhysicsObject;
  class Event;
  class Particle;
  class Lepton;
  class Electron;
  class Muon;
  class Jet;
  class Vertex;
  class Met;
}

// =============================================================================
namespace PennSusyFrame
{
  // =============================================================================
  class PhysicsObject
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      // PhysicsObject();

      virtual void updateWithMet(const PennSusyFrame::Met&);
  };

  // =============================================================================
  class Event : public PhysicsObject
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      Event();

      void init();
      void getEvent(const PennSusyFrame::D3PDReader*);

      // TODO move accessors to cxx file
      void setEventNumber(unsigned int val) { m_event_number = val; }
      void setRunNumber(unsigned int val)   { m_run_number = val; }
      void setLumiBlock(unsigned int val)   { m_lumi_block = val; }
      void setAverageIntPerXing(float val)  { m_average_int_per_xing = val; }
      void setEventShapeRhoKt4LC(float val) { m_eventshape_rhoKt4LC = val; }

      // TODO move accessors to cxx file
      unsigned int getEventNumber() const { return m_event_number; }
      unsigned int getRunNumber() const { return m_run_number; }
      unsigned int getLumiBlock() const { return m_lumi_block; }
      float getAverageIntPerXing() const { return m_average_int_per_xing; }
      float getEventShapeRhoKt4LC() const { return m_eventshape_rhoKt4LC; }

      void print() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    protected:
      bool m_is_data;

      unsigned int m_event_number;
      unsigned int m_run_number;
      unsigned int m_lumi_block;

      float m_average_int_per_xing;
      float m_eventshape_rhoKt4LC;
  };

  // =============================================================================
  class Particle : public PhysicsObject
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      Particle();

      virtual void printGeneralInfo() const;

      // TODO move accessors to cxx file
      virtual void setParticleIndex(int val) { m_particle_index = val; }

      virtual void setTlv(const TLorentzVector&);
      virtual void setRawTlv(const TLorentzVector&);

      // TODO move accessors to cxx file
      virtual int getParticleIndex() const { return m_particle_index; }

      virtual const TLorentzVector* getTlv() const;
      virtual const TLorentzVector* getRawTlv() const;

      virtual double getPt() const;
      virtual double getEta() const;
      virtual double getPhi() const;
      virtual double getE() const;

      virtual double getRawPt() const;
      virtual double getRawEta() const;
      virtual double getRawPhi() const;
      virtual double getRawE() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    protected:
      int m_particle_index;

      bool m_tlv_set;
      bool m_raw_tlv_set;
      TLorentzVector m_tlv;
      TLorentzVector m_raw_tlv;
  };

  // =============================================================================
  class Lepton : public Particle
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      Lepton();

      // TODO move accessors to cxx file
      void setIsLightLepton(bool val) { m_is_light_lepton = val; }
      void setIsElectron(bool val) { m_is_electron = val; }
      void setCharge(double val) { m_charge = val; }
      // TODO move accessors to cxx file
      bool isElectron() const { return (m_is_light_lepton && m_is_electron); }
      bool isMuon() const { return (m_is_light_lepton && !m_is_electron); }
      bool isTau() const { return !m_is_light_lepton; }
      double getCharge() const { return m_charge; }


      virtual void print() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    protected:
      bool m_is_light_lepton;
      bool m_is_electron;
      double m_charge;

  };

  // =============================================================================
  class Electron : public Lepton
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      Electron();
      Electron( const PennSusyFrame::D3PDReader*
              , int el_index
              , PennSusyFrame::ElectronRescalerTool*
              , bool verbose = false
              );

      // TODO move accessors to cxx file
      void setAuthor(int val) { m_author = val; }
      void setMediumPP(bool val) { m_medium_pp = val; }
      void setTightPP(bool val) { m_tight_pp = val; }
      void setPassOtx(bool val) { m_pass_otx = val; }
      void setClE(double val) { m_cl_E = val; }
      void setClEta(double val) { m_cl_eta = val; }
      void setClPhi(double val) { m_cl_phi = val; }
      void setD0(double val) { m_d0 = val; }
      void setSigD0(double val) { m_sig_d0 = val; }
      void setZ0(double val) { m_z0 = val; }
      // TODO rename these functions to give access to all iso variables - raw and corrected
      void setPtIso(double val) { m_pt_iso = val; }
      void setEtIso(double val) { m_et_iso = val; }
      void setMetStatusWord(const std::vector<unsigned int>& val) { m_met_status_word = val; }
      void setMetWet(const std::vector<float>& val) { m_met_wet = val; }
      void setMetWpx(const std::vector<float>& val) { m_met_wpx = val; }
      void setMetWpy(const std::vector<float>& val) { m_met_wpy = val; }

      // TODO move accessors to cxx file
      int getAuthor() const { return m_author; }
      bool getMediumPP() const { return m_medium_pp; }
      bool getTightPP() const { return m_tight_pp; }
      bool getPassOTX() const { return m_pass_otx; }
      double getClE() const { return m_cl_E; }
      double getClEta() const { return m_cl_eta; }
      double getClPhi() const { return m_cl_phi; }
      double getD0() const { return m_d0; }
      double getSigD0() const { return m_sig_d0; }
      double getD0Significance() const { return m_d0/m_sig_d0; }
      double getZ0() const { return m_z0; }
      double getZ0SinTheta() const { return m_z0*sin(m_tlv.Theta()); }
      // TODO rename these functions to give access to all iso variables - raw and corrected
      double getPtIso() const { return m_pt_iso; }
      double getEtIso() const { return m_et_iso; }
      std::vector<unsigned int> getMetStatusWord() const { return m_met_status_word; }
      std::vector<float>  getMetWet() const { return m_met_wet; }
      std::vector<float>  getMetWpx() const { return m_met_wpx; }
      std::vector<float>  getMetWpy() const { return m_met_wpy; }

      virtual void print() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    protected:
      void setElTlv(const PennSusyFrame::D3PDReader* reader, PennSusyFrame::ElectronRescalerTool*);

      int m_author;
      bool m_medium_pp;
      bool m_tight_pp;
      bool m_pass_otx;
      double m_cl_E;
      double m_cl_eta;
      double m_cl_phi;
      double m_d0;
      double m_sig_d0;
      double m_z0;
      double m_pt_iso;
      double m_et_iso;

      std::vector<unsigned int> m_met_status_word;
      std::vector<float> m_met_wet;
      std::vector<float> m_met_wpx;
      std::vector<float> m_met_wpy;
  };

  // =============================================================================
  class Muon : public Lepton
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      Muon();
      Muon( const PennSusyFrame::D3PDReader*
          , int mu_index
          , PennSusyFrame::MuonRescalerTool*
          , bool verbose = false
          );

      // TODO move accessors to cxx file
      void setIsCombined(int val) { m_is_combined = val; }
      void setIsSegmentTagged(int val) { m_is_segment_tagged = val; }
      void setIdQOverP(double val) { m_id_qoverp = val; }
      void setIdTheta(double val) { m_id_theta = val; }
      void setMEQOverP(double val) { m_me_qoverp = val; }
      void setMETheta(double val) { m_me_theta = val; }
      void setTrackEta(double val) { m_track_eta = val; }
      void setQOverPRatio(double val) { m_q_over_p_ratio = val; }
      void setNumBLayerHits(int val) { m_num_b_layer_hits = val; }
      void setNumPixelHits(int val) { m_num_pixel_hits = val; }
      void setNumSctHits(int val) { m_num_sct_hits = val; }
      void setNumSiHoles(int val) { m_num_si_holes = val; }
      void setNumTrtHits(int val) { m_num_trt_hits = val; }
      void setTrtOlFraction(double val) { m_trt_ol_frac = val; }
      void setD0(double val) { m_d0 = val; }
      void setSigD0(double val) { m_sig_d0 = val; }
      void setZ0(double val) { m_z0 = val; }
      void setPtIso(double val) { m_pt_iso = val; }
      void setEtIso(double val) { m_et_iso = val; }

      void setMsQOverP(double val) { m_ms_q_over_p = val; }
      void setMsTheta(double val) { m_ms_theta = val; }
      void setMsPhi(double val) { m_ms_phi = val; }

      // TODO move accessors to cxx file
      int getIsCombined() const { return m_is_combined; }
      int getIsSegmentTagged() const { return m_is_segment_tagged; }
      double getIdQOverP() const { return m_id_qoverp; }
      double getIdTheta() const { return m_id_theta; }
      double getMEQOverP() const { return m_me_qoverp; }
      double getMETheta() const { return m_me_theta; }
      double getTrackEta() const { return m_track_eta; }
      double getQOverPRatio() const { return m_q_over_p_ratio; }
      int getNumBLayerHits() const { return m_num_b_layer_hits; }
      int getNumPixelHits() const { return m_num_pixel_hits; }
      int getNumSctHits() const { return m_num_sct_hits; }
      int getNumSiHoles() const { return m_num_si_holes; }
      int getNumTrtHits() const { return m_num_trt_hits; }
      double getTrtOlFraction() const { return m_trt_ol_frac; }
      double getD0() const { return m_d0; }
      double getSigD0() const { return m_sig_d0; }
      double getD0Significance() const { return m_d0/m_sig_d0; }
      double getZ0() const { return m_z0; }
      double getZ0SinTheta() const { return m_z0*sin(m_tlv.Theta()); }
      double getPtIso() const { return m_pt_iso; }
      double getEtIso() const { return m_et_iso; }

      double getMsQOverP() const { return m_ms_q_over_p; }
      double getMsTheta() const { return m_ms_theta; }
      double getMsPhi() const { return m_ms_phi; }

      virtual void print() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    protected:
      void setMuTlv( const PennSusyFrame::D3PDReader* reader
                   , PennSusyFrame::MuonRescalerTool* mu_rescaler
                   );

      int m_is_combined;
      int m_is_segment_tagged;
      double m_id_qoverp;
      double m_id_theta;
      double m_track_eta;
      double m_me_qoverp;
      double m_me_theta;
      double m_q_over_p_ratio;

      int m_num_b_layer_hits;
      int m_num_pixel_hits;
      int m_num_sct_hits;
      int m_num_si_holes;
      int m_num_trt_hits;
      double m_trt_ol_frac;

      double m_d0;
      double m_sig_d0;
      double m_z0;
      double m_pt_iso;
      double m_et_iso;

      double m_ms_q_over_p;
      double m_ms_theta;
      double m_ms_phi;

  };

  // =============================================================================
  class Tau : public Lepton
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      Tau();
      Tau( const PennSusyFrame::D3PDReader*
         , int tau_index
         , PennSusyFrame::TauRescalerTool*
         , bool verbose = false
         );

      // TODO move accessors to cxx file
      void setNumTracks(int val) { m_num_tracks = val; }
      void setJetBdtLoose(bool val) { m_jet_bdt_loose = val; }
      void setJetBdtMedium(bool val) { m_jet_bdt_medium = val; }
      void setJetBdtTight(bool val) { m_jet_bdt_tight = val; }
      void setEleBdtLoose(bool val) { m_ele_bdt_loose = val; }
      void setEleBdtMedium(bool val) { m_ele_bdt_medium = val; }
      void setEleBdtTight(bool val) { m_ele_bdt_tight = val; }
      void setMuVeto(bool val) { m_mu_veto = val; }

      // TODO move accessors to cxx file
      int getNumTracks() const { return m_num_tracks; }
      bool getJetBdtLoose()  const { return m_jet_bdt_loose; }
      bool getJetBdtMedium() const { return m_jet_bdt_medium; }
      bool getJetBdtTight()  const { return m_jet_bdt_tight; }
      bool getEleBdtLoose() const { return m_ele_bdt_loose; }
      bool getEleBdtMedium() const { return m_ele_bdt_medium; }
      bool getEleBdtTight() const { return m_ele_bdt_tight; }
      bool getMuVeto() const { return m_mu_veto; }

      virtual void print() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    protected:
      void setTauTlv( const PennSusyFrame::D3PDReader* reader
                    , PennSusyFrame::TauRescalerTool* tau_rescaler
                    );

      int m_num_tracks;
      bool m_jet_bdt_loose;
      bool m_jet_bdt_medium;
      bool m_jet_bdt_tight;
      bool m_ele_bdt_loose;
      bool m_ele_bdt_medium;
      bool m_ele_bdt_tight;
      bool m_mu_veto;

  };

  // =============================================================================
  class Jet : public Particle
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      Jet();
      Jet( const PennSusyFrame::D3PDReader*
         , int jet_index
         , PennSusyFrame::JetRescalerTool*
         , PennSusyFrame::Event*
         , int num_vertices_ge_2_tracks
         , bool verbose = false
         );

      // TODO move accessors to cxx file
      void setConstScaleE(double val) { m_constscale_e = val; }
      void setConstScaleEta(double val) { m_constscale_eta = val; }
      void setConstScalePhi(double val) { m_constscale_phi = val; }
      void setConstScaleM(double val) { m_constscale_m = val; }
      void setActiveAreaPx(double val) { m_active_area_px = val; }
      void setActiveAreaPy(double val) { m_active_area_py = val; }
      void setActiveAreaPz(double val) { m_active_area_pz = val; }
      void setActiveAreaE(double val) { m_active_area_e = val; }
      void setJvf(double val) { m_jvf = val; }
      void setMv1(double val) { m_mv1 = val; }
      void getBchCorr(double val) { m_bch_corr = val; }
      void getDphiMet(double val) { m_dphi_met = val; }
      void setIsBad(bool val) { m_is_bad = val; }
      void setMetStatusWord(const std::vector<unsigned int>& val) { m_met_status_word = val; }
      void setMetWet(const std::vector<float>& val) { m_met_wet = val; }
      void setMetWpx(const std::vector<float>& val) { m_met_wpx = val; }
      void setMetWpy(const std::vector<float>& val) { m_met_wpy = val; }

      // TODO move accessors to cxx file
      double getConstScaleE() const { return m_constscale_e; }
      double getConstScaleEta() const { return m_constscale_eta; }
      double getConstScalePhi() const { return m_constscale_phi; }
      double getConstScaleM() const { return m_constscale_m; }
      double getActiveAreaPx() const { return m_active_area_px; }
      double getActiveAreaPy() const { return m_active_area_py; }
      double getActiveAreaPz() const { return m_active_area_pz; }
      double getActiveAreaE() const { return m_active_area_e; }
      double getJvf() const { return m_jvf; }
      double getMv1() const { return m_mv1; }
      double getBchCorr() const { return m_bch_corr; }
      double getDphiMet() const { return m_dphi_met; }
      bool getIsBad() const { return m_is_bad; }
      std::vector<unsigned int> getMetStatusWord() const { return m_met_status_word; }
      std::vector<float>  getMetWet() const { return m_met_wet; }
      std::vector<float>  getMetWpx() const { return m_met_wpx; }
      std::vector<float>  getMetWpy() const { return m_met_wpy; }

      virtual void print() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    protected:
      void setJetTlv( const PennSusyFrame::D3PDReader* reader
                    , PennSusyFrame::JetRescalerTool*
                    , PennSusyFrame::Event*
                    , int num_vertices_ge_2_tracks
                    );

      bool isBad(const PennSusyFrame::D3PDReader*);

      double m_constscale_e;
      double m_constscale_eta;
      double m_constscale_phi;
      double m_constscale_m;
      double m_active_area_px;
      double m_active_area_py;
      double m_active_area_pz;
      double m_active_area_e;
      double m_jvf;
      double m_mv1;
      double m_bch_corr;
      double m_dphi_met;

      std::vector<unsigned int> m_met_status_word;
      std::vector<float>  m_met_wet;
      std::vector<float>  m_met_wpx;
      std::vector<float>  m_met_wpy;

      bool m_is_bad;
  };

  // =============================================================================
  class Vertex : public PhysicsObject
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      Vertex();
      Vertex( const PennSusyFrame::D3PDReader*
            , int vertex_index
            , bool verbose = false
            );

      // TODO move accessors to cxx file
      void setVertexIndex(int val) { m_vertex_index = val; }
      void setNumTracks(int val) { m_num_tracks = val; }
      void setX(double val) { m_x = val; }
      void setY(double val) { m_y = val; }
      void setZ(double val) { m_z = val; }
      void setE(double val) { m_e = val; }
      void setM(double val) { m_m = val; }

      // TODO move accessors to cxx file
      int getVertexIndex() const { return m_vertex_index; }
      int getNumTracks() const { return m_num_tracks; }
      double getX() const { return m_x; }
      double getY() const { return m_y; }
      double getZ() const { return m_z; }
      double getE() const { return m_e; }
      double getM() const { return m_m; }

      void print() const;

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    protected:
      int m_vertex_index;
      int m_num_tracks;
      double m_x;
      double m_y;
      double m_z;
      double m_e;
      double m_m;
  };

  // =============================================================================
  class Met : public PhysicsObject
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      Met();

      void init();

      void prep( const PennSusyFrame::D3PDReader*
               , const PennSusyFrame::Event&
               , const std::vector<PennSusyFrame::Electron*>*
               , const std::vector<PennSusyFrame::Muon*>*
               , const std::vector<PennSusyFrame::Jet*>*
               );
      void clear();

      void print() const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    protected:
      void addMet(const PennSusyFrame::D3PDReader*);
      void addElectrons(const std::vector<PennSusyFrame::Electron*>*);
      void addMuons(const std::vector<PennSusyFrame::Muon*>*);
      void addJets(const std::vector<PennSusyFrame::Jet*>*);
      void doWeightFix( std::vector<float>&
                      , std::vector<float>&
                      , std::vector<float>&
                      );

      bool m_prepared;

      METUtility m_met_utility;
      TVector2 m_met_vec;
  };
}

#endif
