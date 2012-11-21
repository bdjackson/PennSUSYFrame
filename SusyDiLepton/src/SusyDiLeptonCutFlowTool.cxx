// $Id: CycleCreators.py 173 2010-05-12 15:49:33Z krasznaa $

// Local include(s):
#include "include/SusyDiLeptonCutFlowTool.h"
#include "AtlasSFrameUtils/include/CycleMacros.h"

ClassImp( SusyDiLeptonCutFlowTool );

// =============================================================================
SusyDiLeptonCutFlowTool::SusyDiLeptonCutFlowTool( SCycleBase* parent
                                                , const char* name
                                                )
                                                : ToolBase(parent, name)
                                                , m_grl_tool(NULL)
                                                , m_trigger_cut_tool(NULL)
                                                , m_truth_match_tool(NULL)
{
  // // = declare user defined properties =
  DeclareProperty("super_verbose_info", c_super_verbose_info = false);

  DeclareProperty("Crit_grl"              , c_crit_grl              = false);
  DeclareProperty("Crit_incomplete_event" , c_crit_incomplete_event = false);
  DeclareProperty("Crit_lar_error"        , c_crit_lar_error        = false);
  DeclareProperty("Crit_tile_error"       , c_crit_tile_error       = false);
  DeclareProperty("Crit_tile_hot_spot"    , c_crit_tile_hot_spot    = false);
  DeclareProperty("Crit_bad_jet_veto"     , c_crit_bad_jet_veto     = false);
  DeclareProperty("Crit_primary_vertex"   , c_crit_primary_vertex   = false);
  DeclareProperty("Crit_bad_mu_veto"      , c_crit_bad_mu_veto      = false);
  DeclareProperty("Crit_cosmic_mu_veto"   , c_crit_cosmic_mu_veto   = false);
  DeclareProperty("Crit_hfor"             , c_crit_hfor             = false);
  DeclareProperty("Crit_ge_2_lep"         , c_crit_ge_2_lep         = false);
  DeclareProperty("Crit_2_lep"            , c_crit_2_lep            = false);
  DeclareProperty("Crit_mll"              , c_crit_mll              = false);
  DeclareProperty("Crit_signal_lep"       , c_crit_signal_lep       = false);
  DeclareProperty("Crit_phase_space"      , c_crit_phase_space      = false);
  DeclareProperty("Crit_trigger"          , c_crit_trigger          = false);
  DeclareProperty("Crit_trigger_match"    , c_crit_trigger_match    = false);
  DeclareProperty("Crit_prompt_leptons"   , c_crit_prompt_leptons   = false);
}

// -----------------------------------------------------------------------------
SusyDiLeptonCutFlowTool::~SusyDiLeptonCutFlowTool()
{
  // do nothing
}

// // -----------------------------------------------------------------------------
// void SusyDiLeptonCutFlowTool::BeginCycleImp() throw( SError )
// {
//   // do nothing
// }
// 
// // -----------------------------------------------------------------------------
// void SusyDiLeptonCutFlowTool::EndCycleImp() throw( SError )
// {
//   // do nothing
// }

// -----------------------------------------------------------------------------
void SusyDiLeptonCutFlowTool::BeginInputData( const SInputData& )
    throw( SError )
{
  m_logger << DEBUG
           << "SusyDiLeptonCutFlowTool::beginInputData()"
           << SLogger::endmsg;

  getTools();
}

// -----------------------------------------------------------------------------
void SusyDiLeptonCutFlowTool::getTools()
{
  std::cout << "Getting tools for the cut flow tool!\n";
  // GRL
  GET_TOOL( grl_tool
          , SelectionTools::GoodRunsListTool
          , "GRL"
          );
  m_grl_tool = grl_tool;

  // Event cleaning tool
  GET_TOOL( event_cleaning
          , SelectionTools::EventCleaningTool
          , "Event_Cleaning"
          );
  m_event_cleaning_tool = event_cleaning;

  GET_TOOL( trigger_cut
          , SelectionTools::TriggerCutTool
          , "Trigger_Cut"
          );
  m_trigger_cut_tool = trigger_cut;

  GET_TOOL( truth_match_tool
          , CommonTools::TruthMatchTool
          , "Truth_Match"
          );
  m_truth_match_tool = truth_match_tool;
}

// // -----------------------------------------------------------------------------
// void SusyDiLeptonCutFlowTool::EndInputDataImp( const SInputData& )
//     throw( SError )
// {
//   m_logger << DEBUG
//            << "SusyDiLeptonCutFlowTool::EndInputData()"
//            << SLogger::endmsg;
//   // do nothing
// }
// 
// // -----------------------------------------------------------------------------
// void SusyDiLeptonCutFlowTool::BeginMasterInputDataImp( const SInputData& )
//     throw( SError )
// {
//   // do nothing
// }
// 
// // -----------------------------------------------------------------------------
// void SusyDiLeptonCutFlowTool::EndMasterInputDataImp( const SInputData& /*id*/ )
//     throw( SError )
// {
//   m_logger << DEBUG
//            << "EndMasterInputDataImp()"
//            << SLogger::endmsg;
// 
//   // do nothing
// }
// 
// // -----------------------------------------------------------------------------
// void SusyDiLeptonCutFlowTool::BeginInputFileImp( const SInputData& )
//     throw( SError )
// {
//   m_logger << DEBUG
//            << "SusyDiLeptonCutFlowTool::BeginInputFile()"
//            << SLogger::endmsg;
// 
//   // do nothing
// }

// -----------------------------------------------------------------------------
// bool SusyDiLeptonCutFlowTool::runCutFlow( Event* event,
bool SusyDiLeptonCutFlowTool::runBasicCutFlow( Event* event,
    ElectronContainer& electrons,
    MuonContainer&     muons,
    JetContainer&      jets,
    VertexContainer&   vertices,
    const Trigger*           /*trigger*/,
    const TriggerVec*        /*trigger_vec*/,
    D3PDReader::MuonTruthD3PDObject* /*muon_truth_d3pdobject*/)
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check GRL
  bool pass_grl = m_grl_tool->passed(*event);
  event->getEventDesc()->setPassGrl(pass_grl);
  if (c_crit_grl && pass_grl == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed GRL --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check TTC veto
  bool pass_incomplete_event =
      m_event_cleaning_tool->passIncompleteEvent(event);
  event->getEventDesc()->setPassIncompleteEvent(pass_incomplete_event);
  if (c_crit_incomplete_event && pass_incomplete_event == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed incomplete event --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check LAr error
  bool pass_lar_error = m_event_cleaning_tool->passLARError(event);
  event->getEventDesc()->setPassLarError(pass_lar_error);
  if (c_crit_lar_error && pass_lar_error == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed LAr error --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check Tile Error
  bool pass_tile_error = m_event_cleaning_tool->passTileError(event);
  event->getEventDesc()->setPassTileError(pass_tile_error);
  if (c_crit_tile_error && pass_tile_error == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed tile error --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check Tile hot spot
  bool pass_tile_hot_spot = m_event_cleaning_tool->passTileHotSpot( event
                                                                  , jets
                                                                  );
  event->getEventDesc()->setPassTileHotSpot(pass_tile_hot_spot);
  if (c_crit_tile_hot_spot && pass_tile_hot_spot == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed tile hot spot --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check jet cleaning
  bool pass_jet_cleaning = (jets.num(JET_BAD) == 0);
  event->getEventDesc()->setPassBadJets(pass_jet_cleaning);
  if (c_crit_bad_jet_veto && pass_jet_cleaning == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed jet cleaning --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check primary vertex
  bool pass_good_vertex = vertices.firstGood(VERT_ALL);
  event->getEventDesc()->setPassPrimaryVertex(pass_good_vertex);
  if (c_crit_primary_vertex && pass_good_vertex == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed primary vertex --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check for bad muons
  bool pass_bad_muon_veto = (muons.getMuons(MU_BAD).size() == 0);
  event->getEventDesc()->setPassBadMuons(pass_bad_muon_veto);
  if (c_crit_bad_mu_veto && pass_bad_muon_veto == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed bad muon veto --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check for cosmic muons
  bool pass_cosmic_muon_veto = (muons.num(MU_COSMIC) == 0);
  event->getEventDesc()->setPassCosmicMuons(pass_cosmic_muon_veto);
  if (c_crit_cosmic_mu_veto && pass_cosmic_muon_veto == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed cosmic muon veto --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check HFOR
  // TODO do proper HFOR cut
  bool pass_hfor = true;
  event->getEventDesc()->setPassHFOR(pass_hfor);
  if (c_crit_hfor && pass_hfor == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed HFOR -- "
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check for At least two leptons
  size_t num_good_el = electrons.num(EL_GOOD);
  size_t num_good_mu = muons.num(MU_GOOD);
  size_t num_good_leptons = num_good_el + num_good_mu;

  bool pass_ge_2_good_leptons = (num_good_leptons >= 2);
  event->getEventDesc()->setPassGE2GoodLeptons(pass_ge_2_good_leptons);
  if (c_crit_ge_2_lep && pass_ge_2_good_leptons == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed >= 2 leptons --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check for exactly two leptons
  bool pass_2_good_leptons = (num_good_leptons == 2);
  event->getEventDesc()->setPass2GoodLeptons(pass_2_good_leptons);
  if (c_crit_2_lep && pass_2_good_leptons == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed == 2 leptons --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check flavor channel for this event
  FLAVOR_CHANNEL flavor_channel = FLAVOR_NONE;
  if (num_good_el == 2 && num_good_mu == 0) {
    flavor_channel = FLAVOR_EE;
  }
  if (num_good_el == 0 && num_good_mu == 2) {
    flavor_channel = FLAVOR_MM;
  }
  if (num_good_el == 1 && num_good_mu == 1) {
    flavor_channel = FLAVOR_EM;
  }
  event->getEventDesc()->setFlavorChannel(flavor_channel);


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Reached the end of the cut flow. Return true to signify this event did
  // not fail any critical cuts
  return true;
}

// -----------------------------------------------------------------------------
bool SusyDiLeptonCutFlowTool::runAdvancedCutFlow( Event* event,
    ElectronContainer& electrons,
    MuonContainer&     muons,
    JetContainer&      /*jets*/,
    VertexContainer&   /*vertices*/,
    const Trigger*     trigger,
    const TriggerVec*  trigger_vec,
    D3PDReader::MuonTruthD3PDObject* muon_truth_d3pdobject)
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check mll of di-lepton pair
  bool pass_mll = m_event_cleaning_tool->passMllCut(event);
  event->getEventDesc()->setPassMll(pass_mll);
  if (c_crit_mll && pass_mll == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed mll --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check for signal leptons
  size_t num_signal_leptons = ( electrons.num(EL_SIGNAL)
                              + muons.num(MU_SIGNAL)
                              );
  bool pass_2_signal_leptons = (num_signal_leptons == 2);
  event->getEventDesc()->setPass2SignalLeptons(pass_2_signal_leptons);
  if (c_crit_signal_lep && pass_2_signal_leptons == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed == 2 signal leptons --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check sign channel for this event
  SIGN_CHANNEL sign_channel = CommonTools::SignChannel::getSignChannel(
      event->getFlavorChannel(),
      electrons.getElectrons(EL_GOOD),
      muons.getMuons(MU_GOOD));
  event->getEventDesc()->setSignChannel(sign_channel);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check for real leptons
  bool pass_real_leptons = m_truth_match_tool->isRealLeptonEvent(
      event->getFlavorChannel(),
      electrons.getElectrons(EL_GOOD),
      muons.getMuons(MU_GOOD),
      muon_truth_d3pdobject);
  event->getEventDesc()->setTruthPrompt(pass_real_leptons);
  if (c_crit_prompt_leptons && pass_real_leptons == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed prompt leptons --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check for valid pt phase space
  TRIG_PHASE trigger_phase_space =
      m_trigger_cut_tool->getPhaseSpace( electrons.getElectrons(EL_GOOD)
                                       , muons.getMuons(MU_GOOD)
                                       );
  event->getEventDesc()->setPhaseSpace(trigger_phase_space);
  if (  c_crit_phase_space
     && event->getEventDesc()->getPhaseSpace() == PHASE_NONE
     ) {
    if (c_super_verbose_info) {
      std::cout << "Failed phase space --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check trigger for this event
  bool pass_ee_trigger = m_trigger_cut_tool->passedEETriggerChannel(
      event, trigger);
  event->getEventDesc()->setEETrigger(pass_ee_trigger);

  bool pass_mm_trigger = m_trigger_cut_tool->passedMMTriggerChannel(
      event, trigger);
  event->getEventDesc()->setMMTrigger(pass_mm_trigger);

  bool pass_em_trigger = m_trigger_cut_tool->passedEMTriggerChannel(
      event, trigger);
  event->getEventDesc()->setEMTrigger(pass_em_trigger);

  bool pass_me_trigger = m_trigger_cut_tool->passedMETriggerChannel(
      event, trigger);
  event->getEventDesc()->setMETrigger(pass_me_trigger);

  if (  c_crit_trigger
     && pass_ee_trigger == false
     && pass_mm_trigger == false
     && pass_em_trigger == false
     && pass_me_trigger == false
     ) {
    if (c_super_verbose_info) {
      std::cout << "Failed trigger --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Check trigger matching
  bool pass_trigger_match = false;

  switch (event->getPhaseSpace()) {
    case PHASE_EE: pass_trigger_match =
                      m_trigger_cut_tool->passedEETriggerMatching(
                          event,
                          trigger_vec,
                          electrons.getElectrons(EL_GOOD),
                          muons.getMuons(MU_GOOD));
                   break;
    case PHASE_MM: pass_trigger_match =
                      m_trigger_cut_tool->passedMMTriggerMatching(
                          event,
                          trigger_vec,
                          electrons.getElectrons(EL_GOOD),
                          muons.getMuons(MU_GOOD));
                   break;
    case PHASE_EM: pass_trigger_match =
                      m_trigger_cut_tool->passedEMTriggerMatching(
                          event,
                          trigger_vec,
                          electrons.getElectrons(EL_GOOD),
                          muons.getMuons(MU_GOOD));
                   break;
    case PHASE_ME: pass_trigger_match =
                      m_trigger_cut_tool->passedMETriggerMatching(
                          event,
                          trigger_vec,
                          electrons.getElectrons(EL_GOOD),
                          muons.getMuons(MU_GOOD));
                   break;
    default:       pass_trigger_match = false;
  };
  event->getEventDesc()->setPassTriggerMatch(pass_trigger_match);
  if (c_crit_trigger_match && pass_trigger_match == false) {
    if (c_super_verbose_info) {
      std::cout << "Failed trigger match --"
                << " Run: "   << event->RunNumber()
                << " Event: " << event->EventNumber()
                << std::endl;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Reached the end of the cut flow. Return true to signify this event did
  // not fail any critical cuts
  return true;
}

// -----------------------------------------------------------------------------
void SusyDiLeptonCutFlowTool::computeGoodEventVariables( Event* event,
    ElectronContainer& electrons,
    MuonContainer& muons,
    JetContainer& jets,
    Met* met)
{
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // compute mll
  event->setMll(CommonTools::MllTool::getMll( event->getFlavorChannel()
                                            , electrons.getElectrons(EL_GOOD)
                                            , muons.getMuons(MU_GOOD)
                                            )
               );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // compute met and met-rel
  met->prep(event, &electrons, &muons, &jets);
  event->setMetRel(Met::getMetRel( met
                                 , electrons.getElectrons(EL_GOOD)
                                 , muons.getMuons(MU_GOOD)
                                 , jets.getJets(JET_ALL_CENTRAL)
                                 )
                    );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // compute mt2
  event->setMt2( CommonTools::MT2Tool::getMt2( event->getFlavorChannel()
               , met
               , electrons.getElectrons(EL_GOOD)
               , muons.getMuons(MU_GOOD))
               );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // compute ptll
  event->setPtll( CommonTools::PtllTool::getPtll(event->getFlavorChannel()
                , electrons.getElectrons(EL_GOOD)
                , muons.getMuons(MU_GOOD))
                );
}