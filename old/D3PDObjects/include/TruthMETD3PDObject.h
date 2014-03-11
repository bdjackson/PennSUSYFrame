// Dear emacs, this is -*- c++ -*-
// -------------------------------------------------------------
//             Code produced by D3PDMakerReader
//
//  author: Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
// -------------------------------------------------------------
#ifndef D3PDREADER_TruthMETD3PDObject_H
#define D3PDREADER_TruthMETD3PDObject_H

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
    *  time = Wed Feb  6 10:48:29 2013
    */
   class TruthMETD3PDObject : public TObject {

   public:
      /// Constructor used when reading from a TTree
      TruthMETD3PDObject( const ::Long64_t& master, const char* prefix = "MET_Truth_" );
      /// Constructor when the object is only used for writing data out
      TruthMETD3PDObject( const char* prefix = "MET_Truth_" );

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

      VarHandle< Float_t > NonInt_etx;
      VarHandle< Float_t > NonInt_ety;
      VarHandle< Float_t > NonInt_sumet;
      VarHandle< Float_t > Int_etx;
      VarHandle< Float_t > Int_ety;
      VarHandle< Float_t > IntCentral_etx;
      VarHandle< Float_t > IntCentral_ety;
      VarHandle< Float_t > IntFwd_etx;
      VarHandle< Float_t > IntFwd_ety;
      VarHandle< Float_t > IntOutCover_etx;
      VarHandle< Float_t > IntOutCover_ety;
      VarHandle< Float_t > IntMuons_etx;
      VarHandle< Float_t > IntMuons_ety;
      VarHandle< Float_t > Int_sumet;
      VarHandle< Float_t > IntCentral_sumet;
      VarHandle< Float_t > IntFwd_sumet;
      VarHandle< Float_t > IntOutCover_sumet;
      VarHandle< Float_t > IntMuons_sumet;

   private:
      std::map< ::TString, VarHandleBase* > fHandles; ///< Book-keeper of the VarHandle members
      const ::Bool_t fFromInput; ///< Flag specifying if object is used for D3PD reading
      const ::TString fPrefix; ///< Prefix to the branch names

      ClassDef( TruthMETD3PDObject, 0 )

   }; // class TruthMETD3PDObject

} // namespace D3PDReader

#endif // D3PDREADER_TruthMETD3PDObject_H