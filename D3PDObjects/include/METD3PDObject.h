// Dear emacs, this is -*- c++ -*-
// -------------------------------------------------------------
//             Code produced by D3PDMakerReader
//
//  author: Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
// -------------------------------------------------------------
#ifndef D3PDREADER_METD3PDObject_H
#define D3PDREADER_METD3PDObject_H

#include <map>

#include <TObject.h>
#include <TString.h>

#include "VarHandle.h"

class TTree;

namespace D3PDReader {

   /**
    * Code generated by CodeGenerator_v2 on:
    *  host = pc-penn-d-07
    *  OS   = Linux / 2.6.18-274.18.1.el5
    *  user = bjackson
    */
   class METD3PDObject : public TObject {

   public:
      /// Constructor used when reading from a TTree
      METD3PDObject( const ::Long64_t& master, const char* prefix = "MET_Egamma10NoTau_", bool is_data = true );
      /// Constructor when the object is only used for writing data out
      METD3PDObject( const char* prefix = "MET_Egamma10NoTau_", bool is_data = true );

      /// Get the currently configured prefix value
      const char* GetPrefix() const;
      /// Set the prefix for the variables
      void SetPrefix( const char* prefix );

      /// Connect the object to an input TTree
      void ReadFrom( ::TTree* tree );
      /// Connect the object to an output TTree
      void WriteTo( ::TTree* tree );

      /// Turn (selected) branches either on or off
      void SetActive( ::Bool_t active = kTRUE,
                      const ::TString& pattern = ".*" );
      /// Read in all the variables that we need to write out as well
      void ReadAllActive();

      VarHandle< Float_t > RefGamma_etx;
      VarHandle< Float_t > RefGamma_ety;
      VarHandle< Float_t > RefGamma_sumet;
      VarHandle< Float_t > RefGamma_etx_CentralReg;
      VarHandle< Float_t > RefGamma_ety_CentralReg;
      VarHandle< Float_t > RefGamma_sumet_CentralReg;
      VarHandle< Float_t > RefGamma_phi_CentralReg;
      VarHandle< Float_t > RefGamma_etx_EndcapRegion;
      VarHandle< Float_t > RefGamma_ety_EndcapRegion;
      VarHandle< Float_t > RefGamma_sumet_EndcapRegion;
      VarHandle< Float_t > RefGamma_phi_EndcapRegion;
      VarHandle< Float_t > RefGamma_etx_ForwardReg;
      VarHandle< Float_t > RefGamma_ety_ForwardReg;
      VarHandle< Float_t > RefGamma_sumet_ForwardReg;
      VarHandle< Float_t > RefGamma_phi_ForwardReg;
      VarHandle< Float_t > STVF_RefGamma_etx;
      VarHandle< Float_t > STVF_RefGamma_ety;
      VarHandle< Float_t > STVF_RefGamma_sumet;
      VarHandle< Float_t > STVF_RefGamma_etx_CentralReg;
      VarHandle< Float_t > STVF_RefGamma_ety_CentralReg;
      VarHandle< Float_t > STVF_RefGamma_sumet_CentralReg;
      VarHandle< Float_t > STVF_RefGamma_phi_CentralReg;
      VarHandle< Float_t > STVF_RefGamma_etx_EndcapRegion;
      VarHandle< Float_t > STVF_RefGamma_ety_EndcapRegion;
      VarHandle< Float_t > STVF_RefGamma_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_RefGamma_phi_EndcapRegion;
      VarHandle< Float_t > STVF_RefGamma_etx_ForwardReg;
      VarHandle< Float_t > STVF_RefGamma_ety_ForwardReg;
      VarHandle< Float_t > STVF_RefGamma_sumet_ForwardReg;
      VarHandle< Float_t > STVF_RefGamma_phi_ForwardReg;
      VarHandle< Float_t > RefFinal_etx;
      VarHandle< Float_t > RefFinal_ety;
      VarHandle< Float_t > RefFinal_sumet;
      VarHandle< Float_t > RefFinal_etx_CentralReg;
      VarHandle< Float_t > RefFinal_ety_CentralReg;
      VarHandle< Float_t > RefFinal_sumet_CentralReg;
      VarHandle< Float_t > RefFinal_phi_CentralReg;
      VarHandle< Float_t > RefFinal_etx_EndcapRegion;
      VarHandle< Float_t > RefFinal_ety_EndcapRegion;
      VarHandle< Float_t > RefFinal_sumet_EndcapRegion;
      VarHandle< Float_t > RefFinal_phi_EndcapRegion;
      VarHandle< Float_t > RefFinal_etx_ForwardReg;
      VarHandle< Float_t > RefFinal_ety_ForwardReg;
      VarHandle< Float_t > RefFinal_sumet_ForwardReg;
      VarHandle< Float_t > RefFinal_phi_ForwardReg;
      VarHandle< Float_t > STVF_RefFinal_etx;
      VarHandle< Float_t > STVF_RefFinal_ety;
      VarHandle< Float_t > STVF_RefFinal_sumet;
      VarHandle< Float_t > STVF_RefFinal_etx_CentralReg;
      VarHandle< Float_t > STVF_RefFinal_ety_CentralReg;
      VarHandle< Float_t > STVF_RefFinal_sumet_CentralReg;
      VarHandle< Float_t > STVF_RefFinal_phi_CentralReg;
      VarHandle< Float_t > STVF_RefFinal_etx_EndcapRegion;
      VarHandle< Float_t > STVF_RefFinal_ety_EndcapRegion;
      VarHandle< Float_t > STVF_RefFinal_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_RefFinal_phi_EndcapRegion;
      VarHandle< Float_t > STVF_RefFinal_etx_ForwardReg;
      VarHandle< Float_t > STVF_RefFinal_ety_ForwardReg;
      VarHandle< Float_t > STVF_RefFinal_sumet_ForwardReg;
      VarHandle< Float_t > STVF_RefFinal_phi_ForwardReg;
      VarHandle< Float_t > RefJet_etx;
      VarHandle< Float_t > RefJet_ety;
      VarHandle< Float_t > RefJet_sumet;
      VarHandle< Float_t > RefJet_etx_CentralReg;
      VarHandle< Float_t > RefJet_ety_CentralReg;
      VarHandle< Float_t > RefJet_sumet_CentralReg;
      VarHandle< Float_t > RefJet_phi_CentralReg;
      VarHandle< Float_t > RefJet_etx_EndcapRegion;
      VarHandle< Float_t > RefJet_ety_EndcapRegion;
      VarHandle< Float_t > RefJet_sumet_EndcapRegion;
      VarHandle< Float_t > RefJet_phi_EndcapRegion;
      VarHandle< Float_t > RefJet_etx_ForwardReg;
      VarHandle< Float_t > RefJet_ety_ForwardReg;
      VarHandle< Float_t > RefJet_sumet_ForwardReg;
      VarHandle< Float_t > RefJet_phi_ForwardReg;
      VarHandle< Float_t > STVF_RefJet_etx;
      VarHandle< Float_t > STVF_RefJet_ety;
      VarHandle< Float_t > STVF_RefJet_sumet;
      VarHandle< Float_t > STVF_RefJet_etx_CentralReg;
      VarHandle< Float_t > STVF_RefJet_ety_CentralReg;
      VarHandle< Float_t > STVF_RefJet_sumet_CentralReg;
      VarHandle< Float_t > STVF_RefJet_phi_CentralReg;
      VarHandle< Float_t > STVF_RefJet_etx_EndcapRegion;
      VarHandle< Float_t > STVF_RefJet_ety_EndcapRegion;
      VarHandle< Float_t > STVF_RefJet_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_RefJet_phi_EndcapRegion;
      VarHandle< Float_t > STVF_RefJet_etx_ForwardReg;
      VarHandle< Float_t > STVF_RefJet_ety_ForwardReg;
      VarHandle< Float_t > STVF_RefJet_sumet_ForwardReg;
      VarHandle< Float_t > STVF_RefJet_phi_ForwardReg;
      VarHandle< Float_t > RefEle_etx;
      VarHandle< Float_t > RefEle_ety;
      VarHandle< Float_t > RefEle_sumet;
      VarHandle< Float_t > RefEle_etx_CentralReg;
      VarHandle< Float_t > RefEle_ety_CentralReg;
      VarHandle< Float_t > RefEle_sumet_CentralReg;
      VarHandle< Float_t > RefEle_phi_CentralReg;
      VarHandle< Float_t > RefEle_etx_EndcapRegion;
      VarHandle< Float_t > RefEle_ety_EndcapRegion;
      VarHandle< Float_t > RefEle_sumet_EndcapRegion;
      VarHandle< Float_t > RefEle_phi_EndcapRegion;
      VarHandle< Float_t > RefEle_etx_ForwardReg;
      VarHandle< Float_t > RefEle_ety_ForwardReg;
      VarHandle< Float_t > RefEle_sumet_ForwardReg;
      VarHandle< Float_t > RefEle_phi_ForwardReg;
      VarHandle< Float_t > STVF_RefEle_etx;
      VarHandle< Float_t > STVF_RefEle_ety;
      VarHandle< Float_t > STVF_RefEle_sumet;
      VarHandle< Float_t > STVF_RefEle_etx_CentralReg;
      VarHandle< Float_t > STVF_RefEle_ety_CentralReg;
      VarHandle< Float_t > STVF_RefEle_sumet_CentralReg;
      VarHandle< Float_t > STVF_RefEle_phi_CentralReg;
      VarHandle< Float_t > STVF_RefEle_etx_EndcapRegion;
      VarHandle< Float_t > STVF_RefEle_ety_EndcapRegion;
      VarHandle< Float_t > STVF_RefEle_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_RefEle_phi_EndcapRegion;
      VarHandle< Float_t > STVF_RefEle_etx_ForwardReg;
      VarHandle< Float_t > STVF_RefEle_ety_ForwardReg;
      VarHandle< Float_t > STVF_RefEle_sumet_ForwardReg;
      VarHandle< Float_t > STVF_RefEle_phi_ForwardReg;
      VarHandle< Float_t > Muon_Total_Staco_etx;
      VarHandle< Float_t > Muon_Total_Staco_ety;
      VarHandle< Float_t > Muon_Total_Staco_sumet;
      VarHandle< Float_t > Muon_Total_Staco_etx_CentralReg;
      VarHandle< Float_t > Muon_Total_Staco_ety_CentralReg;
      VarHandle< Float_t > Muon_Total_Staco_sumet_CentralReg;
      VarHandle< Float_t > Muon_Total_Staco_phi_CentralReg;
      VarHandle< Float_t > Muon_Total_Staco_etx_EndcapRegion;
      VarHandle< Float_t > Muon_Total_Staco_ety_EndcapRegion;
      VarHandle< Float_t > Muon_Total_Staco_sumet_EndcapRegion;
      VarHandle< Float_t > Muon_Total_Staco_phi_EndcapRegion;
      VarHandle< Float_t > Muon_Total_Staco_etx_ForwardReg;
      VarHandle< Float_t > Muon_Total_Staco_ety_ForwardReg;
      VarHandle< Float_t > Muon_Total_Staco_sumet_ForwardReg;
      VarHandle< Float_t > Muon_Total_Staco_phi_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Total_Staco_etx;
      VarHandle< Float_t > STVF_Muon_Total_Staco_ety;
      VarHandle< Float_t > STVF_Muon_Total_Staco_sumet;
      VarHandle< Float_t > STVF_Muon_Total_Staco_etx_CentralReg;
      VarHandle< Float_t > STVF_Muon_Total_Staco_ety_CentralReg;
      VarHandle< Float_t > STVF_Muon_Total_Staco_sumet_CentralReg;
      VarHandle< Float_t > STVF_Muon_Total_Staco_phi_CentralReg;
      VarHandle< Float_t > STVF_Muon_Total_Staco_etx_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Total_Staco_ety_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Total_Staco_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Total_Staco_phi_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Total_Staco_etx_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Total_Staco_ety_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Total_Staco_sumet_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Total_Staco_phi_ForwardReg;
      VarHandle< Float_t > Muon_Isol_Staco_etx;
      VarHandle< Float_t > Muon_Isol_Staco_ety;
      VarHandle< Float_t > Muon_Isol_Staco_sumet;
      VarHandle< Float_t > Muon_Isol_Staco_etx_CentralReg;
      VarHandle< Float_t > Muon_Isol_Staco_ety_CentralReg;
      VarHandle< Float_t > Muon_Isol_Staco_sumet_CentralReg;
      VarHandle< Float_t > Muon_Isol_Staco_phi_CentralReg;
      VarHandle< Float_t > Muon_Isol_Staco_etx_EndcapRegion;
      VarHandle< Float_t > Muon_Isol_Staco_ety_EndcapRegion;
      VarHandle< Float_t > Muon_Isol_Staco_sumet_EndcapRegion;
      VarHandle< Float_t > Muon_Isol_Staco_phi_EndcapRegion;
      VarHandle< Float_t > Muon_Isol_Staco_etx_ForwardReg;
      VarHandle< Float_t > Muon_Isol_Staco_ety_ForwardReg;
      VarHandle< Float_t > Muon_Isol_Staco_sumet_ForwardReg;
      VarHandle< Float_t > Muon_Isol_Staco_phi_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_etx;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_ety;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_sumet;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_etx_CentralReg;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_ety_CentralReg;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_sumet_CentralReg;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_phi_CentralReg;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_etx_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_ety_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_phi_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_etx_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_ety_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_sumet_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Isol_Staco_phi_ForwardReg;
      VarHandle< Float_t > Muon_NonIsol_Staco_etx;
      VarHandle< Float_t > Muon_NonIsol_Staco_ety;
      VarHandle< Float_t > Muon_NonIsol_Staco_sumet;
      VarHandle< Float_t > Muon_NonIsol_Staco_etx_CentralReg;
      VarHandle< Float_t > Muon_NonIsol_Staco_ety_CentralReg;
      VarHandle< Float_t > Muon_NonIsol_Staco_sumet_CentralReg;
      VarHandle< Float_t > Muon_NonIsol_Staco_phi_CentralReg;
      VarHandle< Float_t > Muon_NonIsol_Staco_etx_EndcapRegion;
      VarHandle< Float_t > Muon_NonIsol_Staco_ety_EndcapRegion;
      VarHandle< Float_t > Muon_NonIsol_Staco_sumet_EndcapRegion;
      VarHandle< Float_t > Muon_NonIsol_Staco_phi_EndcapRegion;
      VarHandle< Float_t > Muon_NonIsol_Staco_etx_ForwardReg;
      VarHandle< Float_t > Muon_NonIsol_Staco_ety_ForwardReg;
      VarHandle< Float_t > Muon_NonIsol_Staco_sumet_ForwardReg;
      VarHandle< Float_t > Muon_NonIsol_Staco_phi_ForwardReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_etx;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_ety;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_sumet;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_etx_CentralReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_ety_CentralReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_sumet_CentralReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_phi_CentralReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_etx_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_ety_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_phi_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_etx_ForwardReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_ety_ForwardReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_sumet_ForwardReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Staco_phi_ForwardReg;
      VarHandle< Float_t > CellOut_etx;
      VarHandle< Float_t > CellOut_ety;
      VarHandle< Float_t > CellOut_sumet;
      VarHandle< Float_t > CellOut_etx_CentralReg;
      VarHandle< Float_t > CellOut_ety_CentralReg;
      VarHandle< Float_t > CellOut_sumet_CentralReg;
      VarHandle< Float_t > CellOut_phi_CentralReg;
      VarHandle< Float_t > CellOut_etx_EndcapRegion;
      VarHandle< Float_t > CellOut_ety_EndcapRegion;
      VarHandle< Float_t > CellOut_sumet_EndcapRegion;
      VarHandle< Float_t > CellOut_phi_EndcapRegion;
      VarHandle< Float_t > CellOut_etx_ForwardReg;
      VarHandle< Float_t > CellOut_ety_ForwardReg;
      VarHandle< Float_t > CellOut_sumet_ForwardReg;
      VarHandle< Float_t > CellOut_phi_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_etx;
      VarHandle< Float_t > STVF_CellOut_ety;
      VarHandle< Float_t > STVF_CellOut_sumet;
      VarHandle< Float_t > STVF_CellOut_etx_CentralReg;
      VarHandle< Float_t > STVF_CellOut_ety_CentralReg;
      VarHandle< Float_t > STVF_CellOut_sumet_CentralReg;
      VarHandle< Float_t > STVF_CellOut_phi_CentralReg;
      VarHandle< Float_t > STVF_CellOut_etx_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_ety_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_phi_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_etx_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_ety_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_sumet_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_phi_ForwardReg;
      VarHandle< Float_t > Muon_Isol_Muid_etx;
      VarHandle< Float_t > Muon_Isol_Muid_ety;
      VarHandle< Float_t > Muon_Isol_Muid_sumet;
      VarHandle< Float_t > Muon_Isol_Muid_etx_CentralReg;
      VarHandle< Float_t > Muon_Isol_Muid_ety_CentralReg;
      VarHandle< Float_t > Muon_Isol_Muid_sumet_CentralReg;
      VarHandle< Float_t > Muon_Isol_Muid_phi_CentralReg;
      VarHandle< Float_t > Muon_Isol_Muid_etx_EndcapRegion;
      VarHandle< Float_t > Muon_Isol_Muid_ety_EndcapRegion;
      VarHandle< Float_t > Muon_Isol_Muid_sumet_EndcapRegion;
      VarHandle< Float_t > Muon_Isol_Muid_phi_EndcapRegion;
      VarHandle< Float_t > Muon_Isol_Muid_etx_ForwardReg;
      VarHandle< Float_t > Muon_Isol_Muid_ety_ForwardReg;
      VarHandle< Float_t > Muon_Isol_Muid_sumet_ForwardReg;
      VarHandle< Float_t > Muon_Isol_Muid_phi_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_etx;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_ety;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_sumet;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_etx_CentralReg;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_ety_CentralReg;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_sumet_CentralReg;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_phi_CentralReg;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_etx_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_ety_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_phi_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_etx_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_ety_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_sumet_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Isol_Muid_phi_ForwardReg;
      VarHandle< Float_t > Muon_NonIsol_Muid_etx;
      VarHandle< Float_t > Muon_NonIsol_Muid_ety;
      VarHandle< Float_t > Muon_NonIsol_Muid_sumet;
      VarHandle< Float_t > Muon_NonIsol_Muid_etx_CentralReg;
      VarHandle< Float_t > Muon_NonIsol_Muid_ety_CentralReg;
      VarHandle< Float_t > Muon_NonIsol_Muid_sumet_CentralReg;
      VarHandle< Float_t > Muon_NonIsol_Muid_phi_CentralReg;
      VarHandle< Float_t > Muon_NonIsol_Muid_etx_EndcapRegion;
      VarHandle< Float_t > Muon_NonIsol_Muid_ety_EndcapRegion;
      VarHandle< Float_t > Muon_NonIsol_Muid_sumet_EndcapRegion;
      VarHandle< Float_t > Muon_NonIsol_Muid_phi_EndcapRegion;
      VarHandle< Float_t > Muon_NonIsol_Muid_etx_ForwardReg;
      VarHandle< Float_t > Muon_NonIsol_Muid_ety_ForwardReg;
      VarHandle< Float_t > Muon_NonIsol_Muid_sumet_ForwardReg;
      VarHandle< Float_t > Muon_NonIsol_Muid_phi_ForwardReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_etx;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_ety;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_sumet;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_etx_CentralReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_ety_CentralReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_sumet_CentralReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_phi_CentralReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_etx_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_ety_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_phi_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_etx_ForwardReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_ety_ForwardReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_sumet_ForwardReg;
      VarHandle< Float_t > STVF_Muon_NonIsol_Muid_phi_ForwardReg;
      VarHandle< Float_t > Muon_Total_Muid_etx;
      VarHandle< Float_t > Muon_Total_Muid_ety;
      VarHandle< Float_t > Muon_Total_Muid_sumet;
      VarHandle< Float_t > Muon_Total_Muid_etx_CentralReg;
      VarHandle< Float_t > Muon_Total_Muid_ety_CentralReg;
      VarHandle< Float_t > Muon_Total_Muid_sumet_CentralReg;
      VarHandle< Float_t > Muon_Total_Muid_phi_CentralReg;
      VarHandle< Float_t > Muon_Total_Muid_etx_EndcapRegion;
      VarHandle< Float_t > Muon_Total_Muid_ety_EndcapRegion;
      VarHandle< Float_t > Muon_Total_Muid_sumet_EndcapRegion;
      VarHandle< Float_t > Muon_Total_Muid_phi_EndcapRegion;
      VarHandle< Float_t > Muon_Total_Muid_etx_ForwardReg;
      VarHandle< Float_t > Muon_Total_Muid_ety_ForwardReg;
      VarHandle< Float_t > Muon_Total_Muid_sumet_ForwardReg;
      VarHandle< Float_t > Muon_Total_Muid_phi_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Total_Muid_etx;
      VarHandle< Float_t > STVF_Muon_Total_Muid_ety;
      VarHandle< Float_t > STVF_Muon_Total_Muid_sumet;
      VarHandle< Float_t > STVF_Muon_Total_Muid_etx_CentralReg;
      VarHandle< Float_t > STVF_Muon_Total_Muid_ety_CentralReg;
      VarHandle< Float_t > STVF_Muon_Total_Muid_sumet_CentralReg;
      VarHandle< Float_t > STVF_Muon_Total_Muid_phi_CentralReg;
      VarHandle< Float_t > STVF_Muon_Total_Muid_etx_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Total_Muid_ety_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Total_Muid_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Total_Muid_phi_EndcapRegion;
      VarHandle< Float_t > STVF_Muon_Total_Muid_etx_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Total_Muid_ety_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Total_Muid_sumet_ForwardReg;
      VarHandle< Float_t > STVF_Muon_Total_Muid_phi_ForwardReg;
      VarHandle< Float_t > Track_etx;
      VarHandle< Float_t > Track_ety;
      VarHandle< Float_t > Track_sumet;
      VarHandle< Float_t > Track_etx_CentralReg;
      VarHandle< Float_t > Track_ety_CentralReg;
      VarHandle< Float_t > Track_sumet_CentralReg;
      VarHandle< Float_t > Track_phi_CentralReg;
      VarHandle< Float_t > Track_etx_EndcapRegion;
      VarHandle< Float_t > Track_ety_EndcapRegion;
      VarHandle< Float_t > Track_sumet_EndcapRegion;
      VarHandle< Float_t > Track_phi_EndcapRegion;
      VarHandle< Float_t > Track_etx_ForwardReg;
      VarHandle< Float_t > Track_ety_ForwardReg;
      VarHandle< Float_t > Track_sumet_ForwardReg;
      VarHandle< Float_t > Track_phi_ForwardReg;
      VarHandle< Float_t > STVF_Track_etx;
      VarHandle< Float_t > STVF_Track_ety;
      VarHandle< Float_t > STVF_Track_sumet;
      VarHandle< Float_t > STVF_Track_etx_CentralReg;
      VarHandle< Float_t > STVF_Track_ety_CentralReg;
      VarHandle< Float_t > STVF_Track_sumet_CentralReg;
      VarHandle< Float_t > STVF_Track_phi_CentralReg;
      VarHandle< Float_t > STVF_Track_etx_EndcapRegion;
      VarHandle< Float_t > STVF_Track_ety_EndcapRegion;
      VarHandle< Float_t > STVF_Track_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_Track_phi_EndcapRegion;
      VarHandle< Float_t > STVF_Track_etx_ForwardReg;
      VarHandle< Float_t > STVF_Track_ety_ForwardReg;
      VarHandle< Float_t > STVF_Track_sumet_ForwardReg;
      VarHandle< Float_t > STVF_Track_phi_ForwardReg;
      VarHandle< Float_t > SoftJets_etx;
      VarHandle< Float_t > SoftJets_ety;
      VarHandle< Float_t > SoftJets_sumet;
      VarHandle< Float_t > SoftJets_etx_CentralReg;
      VarHandle< Float_t > SoftJets_ety_CentralReg;
      VarHandle< Float_t > SoftJets_sumet_CentralReg;
      VarHandle< Float_t > SoftJets_phi_CentralReg;
      VarHandle< Float_t > SoftJets_etx_EndcapRegion;
      VarHandle< Float_t > SoftJets_ety_EndcapRegion;
      VarHandle< Float_t > SoftJets_sumet_EndcapRegion;
      VarHandle< Float_t > SoftJets_phi_EndcapRegion;
      VarHandle< Float_t > SoftJets_etx_ForwardReg;
      VarHandle< Float_t > SoftJets_ety_ForwardReg;
      VarHandle< Float_t > SoftJets_sumet_ForwardReg;
      VarHandle< Float_t > SoftJets_phi_ForwardReg;
      VarHandle< Float_t > STVF_SoftJets_etx;
      VarHandle< Float_t > STVF_SoftJets_ety;
      VarHandle< Float_t > STVF_SoftJets_sumet;
      VarHandle< Float_t > STVF_SoftJets_etx_CentralReg;
      VarHandle< Float_t > STVF_SoftJets_ety_CentralReg;
      VarHandle< Float_t > STVF_SoftJets_sumet_CentralReg;
      VarHandle< Float_t > STVF_SoftJets_phi_CentralReg;
      VarHandle< Float_t > STVF_SoftJets_etx_EndcapRegion;
      VarHandle< Float_t > STVF_SoftJets_ety_EndcapRegion;
      VarHandle< Float_t > STVF_SoftJets_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_SoftJets_phi_EndcapRegion;
      VarHandle< Float_t > STVF_SoftJets_etx_ForwardReg;
      VarHandle< Float_t > STVF_SoftJets_ety_ForwardReg;
      VarHandle< Float_t > STVF_SoftJets_sumet_ForwardReg;
      VarHandle< Float_t > STVF_SoftJets_phi_ForwardReg;
      VarHandle< Float_t > RefMuon_etx;
      VarHandle< Float_t > RefMuon_ety;
      VarHandle< Float_t > RefMuon_sumet;
      VarHandle< Float_t > RefMuon_etx_CentralReg;
      VarHandle< Float_t > RefMuon_ety_CentralReg;
      VarHandle< Float_t > RefMuon_sumet_CentralReg;
      VarHandle< Float_t > RefMuon_phi_CentralReg;
      VarHandle< Float_t > RefMuon_etx_EndcapRegion;
      VarHandle< Float_t > RefMuon_ety_EndcapRegion;
      VarHandle< Float_t > RefMuon_sumet_EndcapRegion;
      VarHandle< Float_t > RefMuon_phi_EndcapRegion;
      VarHandle< Float_t > RefMuon_etx_ForwardReg;
      VarHandle< Float_t > RefMuon_ety_ForwardReg;
      VarHandle< Float_t > RefMuon_sumet_ForwardReg;
      VarHandle< Float_t > RefMuon_phi_ForwardReg;
      VarHandle< Float_t > STVF_RefMuon_etx;
      VarHandle< Float_t > STVF_RefMuon_ety;
      VarHandle< Float_t > STVF_RefMuon_sumet;
      VarHandle< Float_t > STVF_RefMuon_etx_CentralReg;
      VarHandle< Float_t > STVF_RefMuon_ety_CentralReg;
      VarHandle< Float_t > STVF_RefMuon_sumet_CentralReg;
      VarHandle< Float_t > STVF_RefMuon_phi_CentralReg;
      VarHandle< Float_t > STVF_RefMuon_etx_EndcapRegion;
      VarHandle< Float_t > STVF_RefMuon_ety_EndcapRegion;
      VarHandle< Float_t > STVF_RefMuon_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_RefMuon_phi_EndcapRegion;
      VarHandle< Float_t > STVF_RefMuon_etx_ForwardReg;
      VarHandle< Float_t > STVF_RefMuon_ety_ForwardReg;
      VarHandle< Float_t > STVF_RefMuon_sumet_ForwardReg;
      VarHandle< Float_t > STVF_RefMuon_phi_ForwardReg;
// -- slimmed --       VarHandle< Float_t > MuonBoy_etx;
// -- slimmed --       VarHandle< Float_t > MuonBoy_ety;
// -- slimmed --       VarHandle< Float_t > MuonBoy_sumet;
// -- slimmed --       VarHandle< Float_t > MuonBoy_etx_CentralReg;
// -- slimmed --       VarHandle< Float_t > MuonBoy_ety_CentralReg;
// -- slimmed --       VarHandle< Float_t > MuonBoy_sumet_CentralReg;
// -- slimmed --       VarHandle< Float_t > MuonBoy_phi_CentralReg;
// -- slimmed --       VarHandle< Float_t > MuonBoy_etx_EndcapRegion;
// -- slimmed --       VarHandle< Float_t > MuonBoy_ety_EndcapRegion;
// -- slimmed --       VarHandle< Float_t > MuonBoy_sumet_EndcapRegion;
// -- slimmed --       VarHandle< Float_t > MuonBoy_phi_EndcapRegion;
// -- slimmed --       VarHandle< Float_t > MuonBoy_etx_ForwardReg;
// -- slimmed --       VarHandle< Float_t > MuonBoy_ety_ForwardReg;
// -- slimmed --       VarHandle< Float_t > MuonBoy_sumet_ForwardReg;
// -- slimmed --       VarHandle< Float_t > MuonBoy_phi_ForwardReg;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_etx;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_ety;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_sumet;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_etx_CentralReg;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_ety_CentralReg;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_sumet_CentralReg;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_phi_CentralReg;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_etx_EndcapRegion;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_ety_EndcapRegion;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_sumet_EndcapRegion;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_phi_EndcapRegion;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_etx_ForwardReg;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_ety_ForwardReg;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_sumet_ForwardReg;
// -- slimmed --       VarHandle< Float_t > STVF_MuonBoy_phi_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_Track_etx;
      VarHandle< Float_t > STVF_CellOut_Track_ety;
      VarHandle< Float_t > STVF_CellOut_Track_sumet;
      VarHandle< Float_t > STVF_CellOut_Track_etx_CentralReg;
      VarHandle< Float_t > STVF_CellOut_Track_ety_CentralReg;
      VarHandle< Float_t > STVF_CellOut_Track_sumet_CentralReg;
      VarHandle< Float_t > STVF_CellOut_Track_phi_CentralReg;
      VarHandle< Float_t > STVF_CellOut_Track_etx_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_Track_ety_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_Track_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_Track_phi_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_Track_etx_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_Track_ety_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_Track_sumet_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_Track_phi_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_TrackPV_etx;
      VarHandle< Float_t > STVF_CellOut_TrackPV_ety;
      VarHandle< Float_t > STVF_CellOut_TrackPV_sumet;
      VarHandle< Float_t > STVF_CellOut_TrackPV_etx_CentralReg;
      VarHandle< Float_t > STVF_CellOut_TrackPV_ety_CentralReg;
      VarHandle< Float_t > STVF_CellOut_TrackPV_sumet_CentralReg;
      VarHandle< Float_t > STVF_CellOut_TrackPV_phi_CentralReg;
      VarHandle< Float_t > STVF_CellOut_TrackPV_etx_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_TrackPV_ety_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_TrackPV_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_TrackPV_phi_EndcapRegion;
      VarHandle< Float_t > STVF_CellOut_TrackPV_etx_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_TrackPV_ety_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_TrackPV_sumet_ForwardReg;
      VarHandle< Float_t > STVF_CellOut_TrackPV_phi_ForwardReg;
      VarHandle< Float_t > STVF_CellOutCorr_etx;
      VarHandle< Float_t > STVF_CellOutCorr_ety;
      VarHandle< Float_t > STVF_CellOutCorr_sumet;
      VarHandle< Float_t > STVF_CellOutCorr_etx_CentralReg;
      VarHandle< Float_t > STVF_CellOutCorr_ety_CentralReg;
      VarHandle< Float_t > STVF_CellOutCorr_sumet_CentralReg;
      VarHandle< Float_t > STVF_CellOutCorr_phi_CentralReg;
      VarHandle< Float_t > STVF_CellOutCorr_etx_EndcapRegion;
      VarHandle< Float_t > STVF_CellOutCorr_ety_EndcapRegion;
      VarHandle< Float_t > STVF_CellOutCorr_sumet_EndcapRegion;
      VarHandle< Float_t > STVF_CellOutCorr_phi_EndcapRegion;
      VarHandle< Float_t > STVF_CellOutCorr_etx_ForwardReg;
      VarHandle< Float_t > STVF_CellOutCorr_ety_ForwardReg;
      VarHandle< Float_t > STVF_CellOutCorr_sumet_ForwardReg;
      VarHandle< Float_t > STVF_CellOutCorr_phi_ForwardReg;

   private:
      std::map< ::TString, VarHandleBase* > fHandles; ///< Book-keeper of the VarHandle members
      const ::Bool_t fFromInput; ///< Flag specifying if object is used for D3PD reading
      const ::TString fPrefix; ///< Prefix to the branch names


bool is_data; // ~bj 

      ClassDef( METD3PDObject, 0 )

   }; // class METD3PDObject

} // namespace D3PDReader

#endif // D3PDREADER_METD3PDObject_H
