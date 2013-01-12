#ifndef HistInfo_h
#define HistInfo_h

#include <iostream>
#include <TH1D.h>

// =============================================================================
class HistInfo
{
  // ---------------------------------------------------------------------------
  public:
    HistInfo();
    HistInfo( std::string var_exp
            , unsigned int x_num_bins
            , float x_min
            , float x_max
            , std::string name = "hist_name"
            , std::string title = "hist_title"
            , std::string x_axis = "x_axis"
            , std::string y_axis = "y_axis"
            , std::string hist_cut = ""
            );
    HistInfo(const HistInfo&);

    std::string getVarExp() const;
    unsigned int getNumXBins() const;
    float getXMin() const;
    float getXMax() const;
    std::string getName() const;
    std::string getTitle() const;
    std::string getXAxis() const;
    std::string getYAxis() const;
    std::string getHistCut() const;

    TH1D* genHist(std::string key);

  // ---------------------------------------------------------------------------
  private:
    std::string m_var_exp;
    unsigned int m_x_num_bins;
    float m_x_min;
    float m_x_max;
    std::string m_name;
    std::string m_title;
    std::string m_x_axis;
    std::string m_y_axis;
    std::string m_z_axis;
    std::string m_hist_cut;
};

#endif
