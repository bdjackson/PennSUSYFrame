// Dear emacs, this is -*- c++ -*-
// -------------------------------------------------------------
//             Code produced by D3PDMakerReader
//
//  author: Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
// -------------------------------------------------------------
#ifndef D3PDREADER_TriggerVecD3PDObject_H
#define D3PDREADER_TriggerVecD3PDObject_H

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
   class TriggerVecD3PDObject;

   /**
    * Code generated by CodeGenerator_v2 on:
    *  host = pc-penn-d-07
    *  OS   = Linux / 2.6.18-274.18.1.el5
    *  user = bjackson
    */
   class TriggerVecD3PDObjectElement : public TObject {

      friend class TriggerVecD3PDObject;

   protected:
      /// Constructor only visible to TriggerVecD3PDObject
      TriggerVecD3PDObjectElement( size_t index, const TriggerVecD3PDObject& parent, bool is_data = true );

   public:
      /// Copy constructor
      TriggerVecD3PDObjectElement( const TriggerVecD3PDObjectElement& parent, bool is_data = true );

      /// Did this object pass the chain EF_e12Tvh_loose1
      VarProxy< int > trig_EF_el_EF_e12Tvh_loose1;
      /// Did this object pass the chain EF_e12Tvh_medium1
      VarProxy< int > trig_EF_el_EF_e12Tvh_medium1;
      /// Did this object pass the chain EF_e24vh_medium1
      VarProxy< int > trig_EF_el_EF_e24vh_medium1;
      /// Did this object pass the chain EF_e24vh_medium1_e7_medium1
      VarProxy< int > trig_EF_el_EF_e24vh_medium1_e7_medium1;
      /// Did this object pass the chain EF_e7T_medium1
      VarProxy< int > trig_EF_el_EF_e7T_medium1;
      /// Did this object pass the chain EF_mu13
      VarProxy< int > trig_EF_trigmuonef_EF_mu13;
      /// Did this object pass the chain EF_mu18_tight
      VarProxy< int > trig_EF_trigmuonef_EF_mu18_tight;
      /// Did this object pass the chain EF_mu18_tight_mu8_EFFS
      VarProxy< int > trig_EF_trigmuonef_EF_mu18_tight_mu8_EFFS;
      /// Did this object pass the chain EF_mu8
      VarProxy< int > trig_EF_trigmuonef_EF_mu8;
      VarProxy< float > trig_EF_el_E;
      VarProxy< float > trig_EF_el_px;
      VarProxy< float > trig_EF_el_py;
      VarProxy< float > trig_EF_el_pz;
      VarProxy< vector<float> > trig_EF_trigmuonef_track_CB_pt;
      VarProxy< vector<float> > trig_EF_trigmuonef_track_CB_eta;
      VarProxy< vector<float> > trig_EF_trigmuonef_track_CB_phi;
      VarProxy< vector<int> > trig_EF_trigmuonef_track_CB_hasCB;


bool is_data; // ~bj 

      ClassDef( TriggerVecD3PDObjectElement, 0 )

   }; // class TriggerVecD3PDObjectElement

   /**
    * Code generated by CodeGenerator_v2 on:
    *  host = pc-penn-d-07
    *  OS   = Linux / 2.6.18-274.18.1.el5
    *  user = bjackson
    */
   class TriggerVecD3PDObject : public TObject {

   public:
      /// Constructor used when reading from a TTree
      TriggerVecD3PDObject( const ::Long64_t& master, const char* prefix = "", bool is_data = true );
      /// Constructor when the object is only used for writing data out
      TriggerVecD3PDObject( const char* prefix = "", bool is_data = true );

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
      TriggerVecD3PDObject& Add( const TriggerVecD3PDObjectElement& el );

      /// Access a proxy class describing one element of the container
      TriggerVecD3PDObjectElement& operator[]( size_t index );
      /// Access a proxy class describing one element of the container (constant version)
      const TriggerVecD3PDObjectElement& operator[]( size_t index ) const;
      /// Add one element to an output collection
      TriggerVecD3PDObject& operator+=( const TriggerVecD3PDObjectElement& el );

      /// Did this object pass the chain EF_e12Tvh_loose1
      VarHandle< vector<int>* > trig_EF_el_EF_e12Tvh_loose1;
      /// Did this object pass the chain EF_e12Tvh_medium1
      VarHandle< vector<int>* > trig_EF_el_EF_e12Tvh_medium1;
      /// Did this object pass the chain EF_e24vh_medium1
      VarHandle< vector<int>* > trig_EF_el_EF_e24vh_medium1;
      /// Did this object pass the chain EF_e24vh_medium1_e7_medium1
      VarHandle< vector<int>* > trig_EF_el_EF_e24vh_medium1_e7_medium1;
      /// Did this object pass the chain EF_e7T_medium1
      VarHandle< vector<int>* > trig_EF_el_EF_e7T_medium1;
      /// Did this object pass the chain EF_mu13
      VarHandle< vector<int>* > trig_EF_trigmuonef_EF_mu13;
      /// Did this object pass the chain EF_mu18_tight
      VarHandle< vector<int>* > trig_EF_trigmuonef_EF_mu18_tight;
      /// Did this object pass the chain EF_mu18_tight_mu8_EFFS
      VarHandle< vector<int>* > trig_EF_trigmuonef_EF_mu18_tight_mu8_EFFS;
      /// Did this object pass the chain EF_mu8
      VarHandle< vector<int>* > trig_EF_trigmuonef_EF_mu8;
      VarHandle< vector<float>* > trig_EF_el_E;
      VarHandle< vector<float>* > trig_EF_el_px;
      VarHandle< vector<float>* > trig_EF_el_py;
      VarHandle< vector<float>* > trig_EF_el_pz;
      VarHandle< vector<vector<float> >* > trig_EF_trigmuonef_track_CB_pt;
      VarHandle< vector<vector<float> >* > trig_EF_trigmuonef_track_CB_eta;
      VarHandle< vector<vector<float> >* > trig_EF_trigmuonef_track_CB_phi;
      VarHandle< vector<vector<int> >* > trig_EF_trigmuonef_track_CB_hasCB;

   private:
      mutable std::vector< TriggerVecD3PDObjectElement > fProxies; ///< Internal list of proxy objects
      std::map< ::TString, VarHandleBase* > fHandles; ///< Book-keeper of the VarHandle members
      const ::Bool_t fFromInput; ///< Flag specifying if object is used for D3PD reading
      const ::TString fPrefix; ///< Prefix to the branch names


bool is_data; // ~bj 

      ClassDef( TriggerVecD3PDObject, 0 )

   }; // class TriggerVecD3PDObject

} // namespace D3PDReader

#endif // D3PDREADER_TriggerVecD3PDObject_H
