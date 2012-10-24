#include "include/EventCleaningTool.h"

// ----------------------------------------------------------------------------
SelectionTools::EventCleaningTool::EventCleaningTool(
    SCycleBase* parent, const char* name): ToolBase(parent, name)
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  //do nothing for now

  DeclareProperty("total_lumi", c_total_lumi = 0);

}

// ----------------------------------------------------------------------------
SelectionTools::EventCleaningTool::~EventCleaningTool()
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // do nothing
}
// ----------------------------------------------------------------------------
bool SelectionTools::EventCleaningTool::passFCALCleaning(Event* event, 
							 const std::vector<Jet*>& jets
							 )
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // first check run number and data
  // TODO: Implement MC for fraction of events if we swtich to that
  if (!checkFCALProblemRuns(event)) return true;
  bool passed_cut = true;
  
  size_t n_jets = jets.size();

  for (size_t jet_it=0; jet_it != n_jets && passed_cut; ++jet_it) 
    {
      if (inFCALProblemArea(jets.at(jet_it)->getTlv().Pt(),jets.at(jet_it)->eta(),jets.at(jet_it)->phi())) 
        {
          passed_cut = false;
          break;
        }
    }
  return passed_cut;

}
// ----------------------------------------------------------------------------
bool SelectionTools::EventCleaningTool::passLARError(Event* event)
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  m_logger << DEBUG
           << "SelectionTools::EventCleaningTool::passedLARError()"
           << SLogger::endmsg;

  // only check for LAr error in data
  //  if (is_data() && event->larError()) return false; 
  //Changing to new recommendation of reject LarError =2, not LarError>0 per Guilliame
  if (is_data() && event->larError()==2) return false;

  return true;

}

// ----------------------------------------------------------------------------
bool SelectionTools::EventCleaningTool::passIncompleteEvent(Event* event)
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  m_logger << DEBUG
           << "SelectionTools::EventCleaningTool::passedIncompleteEvent()"
           << SLogger::endmsg;

  bool passed_cut = true;

  if ((event->coreFlags()&0x40000) != 0) 
    {
      passed_cut = false; // This is an incomplete event remove from analysis }
      m_logger << DEBUG
	       << "SelectionTools::IncompleteEventCutTool Failed"
	       << SLogger::endmsg;
      
    }
  return passed_cut;
  
}

// ----------------------------------------------------------------------------
bool SelectionTools::EventCleaningTool::passTileError(Event* event)
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  m_logger << DEBUG
           << "SelectionTools::EventCleaningTool::passedTileError()"
           << SLogger::endmsg;
  
  //Changing to new recommendation of reject TileError =2, not TileError>0 per Guilliame
  if (is_data() && event->tileError()==2) return false;
  return true;

}
// ----------------------------------------------------------------------------
bool SelectionTools::EventCleaningTool::passTileHotSpot(Event* event, 
							const std::vector<Jet*>& jets
							)
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // first check run number 
  if (!checkTileHotSpotRuns(event)) return true;
  bool passed_cut = true;

  size_t n_jets = jets.size();
  
  for (size_t jet_it=0; jet_it != n_jets && passed_cut; ++jet_it) 
    {
      if (inTileHotSpot(jets.at(jet_it)->eta(),jets.at(jet_it)->phi()))
        {
          if (jets.at(jet_it)->fracSamplingMax()>0.6 && jets.at(jet_it)->SamplingMax()==13) passed_cut=false; 
        }
    }
  return passed_cut;

}
// ---------------------------------------------------------------------------
bool SelectionTools::EventCleaningTool::checkFCALProblemRuns(Event* event)
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  return (  is_data() 
            && (  event->RunNumber() >= 206248
		  && event->RunNumber() <= 207332
		  )
	    );
}


// ----------------------------------------------------------------------------
bool SelectionTools::EventCleaningTool::inFCALProblemArea( float pt, float eta
							   , float phi
							   )
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // check if object is in Hot Spot
  
  if (pt < 20000.) return false;
  if (fabs(eta)<3.2) return false;
  if (phi < 1.6 || phi > 3.1) return false;
  return true;
}
// ---------------------------------------------------------------------------
bool SelectionTools::EventCleaningTool::checkTileHotSpotRuns(Event* event)
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  return (  is_data() 
            && (  event->RunNumber() >= 202660
            && event->RunNumber() <= 203027
               )
         );


}
// ----------------------------------------------------------------------------
bool SelectionTools::EventCleaningTool::inTileHotSpot(float eta, float phi)
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // check if object is in Hot Spot
  
  if (eta < -0.2 || eta > 0.1) return false;
  if (phi < 2.65 || phi > 2.75) return false;
  
  return true;
}

