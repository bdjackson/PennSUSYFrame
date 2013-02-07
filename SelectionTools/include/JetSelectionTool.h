// Dear emacs, this is -*- c++ -*-
#ifndef SelectionTools_JetSelectionTool_h
#define SelectionTools_JetSelectionTool_h

// =============================================================================
#include <vector>
#include "AtlasSFrameUtils/include/ToolBase.h"

// =============================================================================
class Met;
class Jet;
class JetContainer;

// =============================================================================
namespace SelectionTools
{
  // ===========================================================================
  class JetSelectionTool : public ToolBase
  {
  // ---------------------------------------------------------------------------
  public:
    JetSelectionTool(SCycleBase* parent, const char* name = "CutTool");
    virtual ~JetSelectionTool();

    void process(Jet*);
    bool isBaselineGood(Jet*);
    bool isBaselineBad(Jet*);
    bool isLJet(Jet*);
    bool isBJet(Jet*);
    bool isFJet(Jet*);
    bool isBadJet(Jet*);
    bool isCaloProblemJet(const Jet*, const Met*);

    std::vector<Jet*> getBaselineGoodJets(const JetContainer&);
    std::vector<Jet*> getBaselineGoodJets(const std::vector<Jet*>& all_jets);

    std::vector<Jet*> getBaselineBadJets(const JetContainer&);
    std::vector<Jet*> getBaselineBadJets(const std::vector<Jet*>& all_jets);

    std::vector<Jet*> getCaloProblemJets(const JetContainer&, const Met*);
    std::vector<Jet*> getCaloProblemJets(const std::vector<Jet*>& all_jets, const Met*);

    std::vector<Jet*> getLJets(const JetContainer&);
    std::vector<Jet*> getLJets(const std::vector<Jet*>& good_jets);

    std::vector<Jet*> getBJets(const JetContainer&);
    std::vector<Jet*> getBJets(const std::vector<Jet*>& good_jets);

    std::vector<Jet*> getFJets(const JetContainer&);
    std::vector<Jet*> getFJets(const std::vector<Jet*>& good_jets);

  // ---------------------------------------------------------------------------
  private:
    // = user configurables =
    // baseline cut values
    double c_baseline_min_pt;
    double c_baseline_max_pt;

    double c_baseline_min_eta;
    double c_baseline_max_eta;

    // light-central jet cut values
    double c_light_min_pt;
    double c_light_max_pt;

    double c_light_min_eta;
    double c_light_max_eta;

    double c_light_min_jvf;
    double c_light_max_jvf;

    double c_light_min_mv1;
    double c_light_max_mv1;

    // central b jet cut values
    double c_b_min_pt;
    double c_b_max_pt;

    double c_b_min_eta;
    double c_b_max_eta;

    double c_b_min_mv1;
    double c_b_max_mv1;

    // forward jet cut values
    double c_forward_min_pt;
    double c_forward_max_pt;

    double c_forward_min_eta;
    double c_forward_max_eta;

    bool passCut(double test, double min, double max);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ClassDef(JetSelectionTool, 0);
  };
}

#endif
