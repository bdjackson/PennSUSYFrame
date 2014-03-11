// Dear emacs, this is -*- c++ -*-
// -------------------------------------------------------------
//             Code produced by D3PDMakerReader
//
//  author: Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
// -------------------------------------------------------------
#ifndef D3PDREADER_TauD3PDObject_H
#define D3PDREADER_TauD3PDObject_H

#include <map>
#include <vector>
using std::vector;

#include <TObject.h>
#include <TString.h>

#include "VarHandle.h"
#include "VarProxy.h"

class TTree;

namespace D3PDReader {

   // Forward declaration(s):
   class TauD3PDObject;

   /**
    * Code generated by CodeGenerator_v2 on:
    *  host = pc-penn-d-07
    *  OS   = Linux / 2.6.18-274.18.1.el5
    *  user = bjackson
    */
   class TauD3PDObjectElement : public TObject {

      friend class TauD3PDObject;

   protected:
      /// Constructor only visible to TauD3PDObject
      TauD3PDObjectElement( size_t index, const TauD3PDObject& parent, bool is_data = true );

   public:
      /// Copy constructor
      TauD3PDObjectElement( const TauD3PDObjectElement& parent, bool is_data = true );

      VarProxy< float > pt;
      VarProxy< float > m;
      VarProxy< float > eta;
      VarProxy< float > phi;
      VarProxy< float > charge;
      VarProxy< float > BDTEleScore;
      VarProxy< float > BDTJetScore;
      VarProxy< int > muonVeto;
      VarProxy< int > JetBDTSigLoose;
      VarProxy< int > JetBDTSigMedium;
      VarProxy< int > JetBDTSigTight;
      VarProxy< int > EleBDTLoose;
      VarProxy< int > EleBDTMedium;
      VarProxy< int > EleBDTTight;
      VarProxy< int > numTrack;
      VarProxy< float > leadTrkPt;
      VarProxy< float > leadTrack_eta;
      VarProxy< float > leadTrack_phi;


bool is_data; // ~bj 

      ClassDef( TauD3PDObjectElement, 0 )

   }; // class TauD3PDObjectElement

   /**
    * Code generated by CodeGenerator_v2 on:
    *  host = pc-penn-d-07
    *  OS   = Linux / 2.6.18-274.18.1.el5
    *  user = bjackson
    */
   class TauD3PDObject : public TObject {

   public:
      /// Constructor used when reading from a TTree
      TauD3PDObject( const ::Long64_t& master, const char* prefix = "tau_", bool is_data = true );
      /// Constructor when the object is only used for writing data out
      TauD3PDObject( const char* prefix = "tau_", bool is_data = true );

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

      /// Clear the container. Useful when writing new branches.
      void Clear( Option_t* option = "" );
      /// Add one element to an output collection
      TauD3PDObject& Add( const TauD3PDObjectElement& el );

      /// Access a proxy class describing one element of the container
      TauD3PDObjectElement& operator[]( size_t index );
      /// Access a proxy class describing one element of the container (constant version)
      const TauD3PDObjectElement& operator[]( size_t index ) const;
      /// Add one element to an output collection
      TauD3PDObject& operator+=( const TauD3PDObjectElement& el );

      /// Number of ntuple rows.
      VarHandle< Int_t > n;
      VarHandle< vector<float>* > pt;
      VarHandle< vector<float>* > m;
      VarHandle< vector<float>* > eta;
      VarHandle< vector<float>* > phi;
      VarHandle< vector<float>* > charge;
      VarHandle< vector<float>* > BDTEleScore;
      VarHandle< vector<float>* > BDTJetScore;
      VarHandle< vector<int>* > muonVeto;
      VarHandle< vector<int>* > JetBDTSigLoose;
      VarHandle< vector<int>* > JetBDTSigMedium;
      VarHandle< vector<int>* > JetBDTSigTight;
      VarHandle< vector<int>* > EleBDTLoose;
      VarHandle< vector<int>* > EleBDTMedium;
      VarHandle< vector<int>* > EleBDTTight;
      VarHandle< vector<int>* > numTrack;
      VarHandle< vector<float>* > leadTrkPt;
      VarHandle< vector<float>* > leadTrack_eta;
      VarHandle< vector<float>* > leadTrack_phi;

   private:
      mutable std::vector< TauD3PDObjectElement > fProxies; ///< Internal list of proxy objects
      std::map< ::TString, VarHandleBase* > fHandles; ///< Book-keeper of the VarHandle members
      const ::Bool_t fFromInput; ///< Flag specifying if object is used for D3PD reading
      const ::TString fPrefix; ///< Prefix to the branch names


bool is_data; // ~bj 

      ClassDef( TauD3PDObject, 0 )

   }; // class TauD3PDObject

} // namespace D3PDReader

#endif // D3PDREADER_TauD3PDObject_H