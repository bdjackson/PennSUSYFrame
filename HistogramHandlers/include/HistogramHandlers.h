#ifndef PennSusyFrame_HistogramHandlers_h
#define PennSusyFrame_HistogramHandlers_h

// =============================================================================
#include <vector>
#include "PennSusyFrameCore/include/PennSusyFrameEnums.h"

// =============================================================================
class TFile;
class TDirectory;
class TH1F;

namespace PennSusyFrame
{
  class Event;
  class EventLevelQuantities;
  class Electron;
  class Muon;
  class Jet;
  class Met;
}

// =============================================================================
namespace PennSusyFrame
{
  // =============================================================================
  // = HistogramHandler - used as parent class for other histograms
  // =============================================================================
  class HistogramHandler
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      HistogramHandler(std::string name_tag = "");
      virtual ~HistogramHandler();

      virtual void Fill( const PennSusyFrame::Event&
                       , const PennSusyFrame::EventLevelQuantities&
                       , const std::vector<PennSusyFrame::Electron*>*
                       , const std::vector<PennSusyFrame::Muon*>*
                       , const std::vector<PennSusyFrame::Jet*>*
                       , const PennSusyFrame::Met&
                       , float weight
                       );
      virtual void write(TDirectory*);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    private:
  };

  // =============================================================================
  // = EventLevelHists
  // =============================================================================
  class EventLevelHists : public HistogramHandler
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      EventLevelHists(std::string name_tag = "");
      virtual ~EventLevelHists();

      virtual void Fill( const PennSusyFrame::Event&
                       , const PennSusyFrame::EventLevelQuantities&
                       , const std::vector<PennSusyFrame::Electron*>*
                       , const std::vector<PennSusyFrame::Muon*>*
                       , const std::vector<PennSusyFrame::Jet*>*
                       , const PennSusyFrame::Met&
                       , float weight
                       );
      virtual void write(TDirectory*);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    private:
      std::vector<TH1F*> m_h_mll;
      std::vector<TH1F*> m_h_mt2;
  };

  // =============================================================================
  // = LeptonKinematicsHists
  // =============================================================================
  class LeptonKinematicsHists : public HistogramHandler
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      LeptonKinematicsHists(std::string name_tag = "");
      virtual ~LeptonKinematicsHists();

      virtual void Fill( const PennSusyFrame::Event&
                       , const PennSusyFrame::EventLevelQuantities&
                       , const std::vector<PennSusyFrame::Electron*>*
                       , const std::vector<PennSusyFrame::Muon*>*
                       , const std::vector<PennSusyFrame::Jet*>*
                       , const PennSusyFrame::Met&
                       , float weight
                       );
      virtual void write(TDirectory*);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    private:
      std::vector<TH1F*> m_h_pt_all;
      std::vector<TH1F*> m_h_pt_0;
      std::vector<TH1F*> m_h_pt_1;

      std::vector<TH1F*> m_h_ptiso_all;
      std::vector<TH1F*> m_h_ptiso_0;
      std::vector<TH1F*> m_h_ptiso_1;

      std::vector<TH1F*> m_h_etiso_all;
      std::vector<TH1F*> m_h_etiso_0;
      std::vector<TH1F*> m_h_etiso_1;
  };

  // =============================================================================
  // = JetKinematicsHists
  // =============================================================================
  class JetKinematicsHists : public HistogramHandler
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      JetKinematicsHists(std::string name_tag = "");
      virtual ~JetKinematicsHists();

      virtual void Fill( const PennSusyFrame::Event&
                       , const PennSusyFrame::EventLevelQuantities&
                       , const std::vector<PennSusyFrame::Electron*>*
                       , const std::vector<PennSusyFrame::Muon*>*
                       , const std::vector<PennSusyFrame::Jet*>*
                       , const PennSusyFrame::Met&
                       , float weight
                       );
      virtual void write(TDirectory*);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    private:
      std::vector<TH1F*> m_h_num_jet;

      std::vector<TH1F*> m_h_pt_all;
      std::vector<TH1F*> m_h_pt_0;
      std::vector<TH1F*> m_h_pt_1;
  };

  // =============================================================================
  // = MetHists
  // =============================================================================
  class MetHists : public HistogramHandler
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    public:
      MetHists(std::string name_tag = "");
      virtual ~MetHists();

      virtual void Fill( const PennSusyFrame::Event&
                       , const PennSusyFrame::EventLevelQuantities&
                       , const std::vector<PennSusyFrame::Electron*>*
                       , const std::vector<PennSusyFrame::Muon*>*
                       , const std::vector<PennSusyFrame::Jet*>*
                       , const PennSusyFrame::Met&
                       , float weight
                       );
      virtual void write(TDirectory*);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    private:
      std::vector<TH1F*> m_h_met_et;
      std::vector<TH1F*> m_h_met_rel;

      std::vector<TH1F*> m_h_dphi_nearest_object; // dphi between met and nearest object
      std::vector<TH1F*> m_h_dphi_jet_0; // dphi between met and nearest jet
      std::vector<TH1F*> m_h_dphi_jet_1; // dphi between met and next-to-nearest jet
      std::vector<TH1F*> m_h_dphi_lep_0; // dphi between met and nearest lep
      std::vector<TH1F*> m_h_dphi_lep_1; // dphi between met and next-to-nearest lep
  };
}

#endif
