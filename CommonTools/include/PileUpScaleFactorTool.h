// Dear emacs, this is -*- c++ -*-
#ifndef CommonTools_PileUpScaleFactorTool_H
#define CommonTools_PileUpScaleFactorTool_H
// ============================================================================
#include <vector>
#include "AtlasSFrameUtils/include/ToolBase.h"

// ============================================================================
class Event;
namespace D3PDReader
{
  class TruthD3PDObject;
}
namespace Root
{
  class TPileupReweighting;
}

namespace CommonTools{
// ============================================================================
  class PileUpScaleFactorTool : public ToolBase
  {
  public:

    PileUpScaleFactorTool(SCycleBase* parent, const char* name = "CutTool");
    virtual ~PileUpScaleFactorTool();

    void BeginInputData( const SInputData& id );
    void EndInputData( const SInputData& id );

    void clear();

    double getPileupScaleFactor( const Event*
                               , const D3PDReader::TruthD3PDObject*
                               );


    double getIntegratedLumiFraction( unsigned int run_number
                                    , unsigned int start
                                    , unsigned int end
                                    );

    std::vector<double> getIntegratedLumiVector();

  private:
    //configurables
    bool c_do_pile_up_sf;

    std::string c_pile_up_var;
    bool c_generate_mc_hist;

    std::string c_data_hist_name;
    std::string c_mc_hist_name;
    std::string c_pile_up_data_file;
    std::string c_pile_up_mc_file;

    //other stuff

    Root::TPileupReweighting* m_pile_up_reweight;

    double m_pileup_sf;
    bool m_is_cached;

    ClassDef(PileUpScaleFactorTool, 0);
  };

}
#endif

