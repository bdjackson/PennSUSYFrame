// Dear emacs, this is -*- c++ -*-
// -------------------------------------------------------------
//             Code produced by D3PDMakerReader
//
//  author: Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
// -------------------------------------------------------------
#ifndef D3PDREADER_EventInfoD3PDObject_H
#define D3PDREADER_EventInfoD3PDObject_H

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
   class EventInfoD3PDObject : public TObject {

   public:
      /// Constructor used when reading from a TTree
      EventInfoD3PDObject( const ::Long64_t& master, const char* prefix = "", bool is_data = true );
      /// Constructor when the object is only used for writing data out
      EventInfoD3PDObject( const char* prefix = "", bool is_data = true );

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

      /// Run number
      VarHandle< UInt_t > RunNumber;
      /// Event number
      VarHandle< UInt_t > EventNumber;
      /// Timestamp, in seconds
      VarHandle< UInt_t > timestamp;
      /// Timestamp offset from last whole second, in ns
      VarHandle< UInt_t > timestamp_ns;
      /// Luminosity block number
      VarHandle< UInt_t > lbn;
      /// Bunch crossing ID
      VarHandle< UInt_t > bcid;
      /// Detector mask 0
      VarHandle< UInt_t > detmask0;
      /// Detector mask 1
      VarHandle< UInt_t > detmask1;
      /// Interactions per crossing for the current BCID - for in-time pile-up
      VarHandle< Float_t > actualIntPerXing;
      /// Interactions per crossing for all BCIDs - for out-of-time pile-up
      VarHandle< Float_t > averageIntPerXing;
      VarHandle< UInt_t > pixelFlags;
      VarHandle< UInt_t > sctFlags;
      VarHandle< UInt_t > trtFlags;
      VarHandle< UInt_t > larFlags;
      VarHandle< UInt_t > tileFlags;
      VarHandle< UInt_t > muonFlags;
      VarHandle< UInt_t > fwdFlags;
      VarHandle< UInt_t > coreFlags;
      VarHandle< UInt_t > pixelError;
      VarHandle< UInt_t > sctError;
      VarHandle< UInt_t > trtError;
      VarHandle< UInt_t > larError;
      VarHandle< UInt_t > tileError;
      VarHandle< UInt_t > muonError;
      VarHandle< UInt_t > fwdError;
      VarHandle< UInt_t > coreError;

   private:
      std::map< ::TString, VarHandleBase* > fHandles; ///< Book-keeper of the VarHandle members
      const ::Bool_t fFromInput; ///< Flag specifying if object is used for D3PD reading
      const ::TString fPrefix; ///< Prefix to the branch names


bool is_data; // ~bj 

      ClassDef( EventInfoD3PDObject, 0 )

   }; // class EventInfoD3PDObject

} // namespace D3PDReader

#endif // D3PDREADER_EventInfoD3PDObject_H
