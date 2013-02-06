// Dear emacs, this is -*- c++ -*-
// -------------------------------------------------------------
//             Code produced by D3PDMakerReader
//
//  author: Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
// -------------------------------------------------------------
#ifndef D3PDREADER_ElectronD3PDObject_H
#define D3PDREADER_ElectronD3PDObject_H

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
   class ElectronD3PDObject;

   /**
    * Code generated by CodeGenerator_v2 on:
    *  host = pc-penn-d-07
    *  OS   = Linux / 2.6.18-274.18.1.el5
    *  user = bjackson
    */
   class ElectronD3PDObjectElement : public TObject {

      friend class ElectronD3PDObject;

   protected:
      /// Constructor only visible to ElectronD3PDObject
      ElectronD3PDObjectElement( size_t index, const ElectronD3PDObject& parent, bool is_data = true );

   public:
      /// Copy constructor
      ElectronD3PDObjectElement( const ElectronD3PDObjectElement& parent, bool is_data = true );

      VarProxy< float > E;
      VarProxy< float > Et;
      VarProxy< float > pt;
      VarProxy< float > m;
      VarProxy< float > eta;
      VarProxy< float > phi;
      VarProxy< float > px;
      VarProxy< float > py;
      VarProxy< float > pz;
      VarProxy< float > charge;
      VarProxy< int > author;
      /// IsEM mask --- bits are set for each cut that FAILS.
      VarProxy< unsigned int > isEM;
      /// Loose IsEM mask --- bits are set for each cut that FAILS.
      VarProxy< unsigned int > isEMLoose;
      /// Medium IsEM mask --- bits are set for each cut that FAILS.
      VarProxy< unsigned int > isEMMedium;
      /// Tight IsEM mask --- bits are set for each cut that FAILS.
      VarProxy< unsigned int > isEMTight;
      VarProxy< unsigned int > OQ;
      /// Number of tracks for the first conversion candidate; 0 if no conversion or if there are more than two tracks.
      VarProxy< int > convFlag;
      /// True if the first conversion candidate has 1 or 2 tracks.
      VarProxy< int > isConv;
      /// Number of conversion vertices.
      VarProxy< int > nConv;
      /// Number of conversion vertices with exactly one track.
      VarProxy< int > nSingleTrackConv;
      /// Number of conversion vertices with exactly two tracks.
      VarProxy< int > nDoubleTrackConv;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_time] 
      VarProxy< float > maxEcell_time;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_energy] 
      VarProxy< float > maxEcell_energy;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_onlId] 
      VarProxy< unsigned int > maxEcell_onlId;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_gain] 
      VarProxy< int > maxEcell_gain;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_x] 
      VarProxy< float > maxEcell_x;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_y] 
      VarProxy< float > maxEcell_y;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_z] 
      VarProxy< float > maxEcell_z;
// MC only
      /// MC particle type, from classifier tool.
      VarProxy< int > type;
      /// MC particle origin, from classifier tool.
      VarProxy< int > origin;
      /// Type of photon for background electron from conversions, from classifier tool
      VarProxy< int > typebkg;
      /// Origin of photon for background electron from conversions, from classifier tool.
      VarProxy< int > originbkg;
      VarProxy< float > truth_E;
      VarProxy< float > truth_pt;
      VarProxy< float > truth_eta;
      VarProxy< float > truth_phi;
      VarProxy< int > truth_type;
      VarProxy< int > truth_status;
      VarProxy< int > truth_barcode;
      VarProxy< int > truth_mothertype;
      VarProxy< int > truth_motherbarcode;
      VarProxy< int > truth_hasHardBrem;
      /// Index in mc_
      VarProxy< int > truth_index;
      VarProxy< int > truth_matched;
// end MC only
      VarProxy< int > mediumWithoutTrack;
      VarProxy< int > mediumIsoWithoutTrack;
      VarProxy< int > tightWithoutTrack;
      VarProxy< int > tightIsoWithoutTrack;
      VarProxy< int > loose;
      VarProxy< int > looseIso;
      VarProxy< int > medium;
      VarProxy< int > mediumIso;
      VarProxy< int > tight;
      VarProxy< int > tightIso;
      VarProxy< int > loosePP;
      VarProxy< int > loosePPIso;
      VarProxy< int > mediumPP;
      VarProxy< int > mediumPPIso;
      VarProxy< int > tightPP;
      VarProxy< int > tightPPIso;
      VarProxy< int > goodOQ;
      /// [detail 9]
      VarProxy< float > Ethad;
      /// [detail 8]
      VarProxy< float > Ethad1;
      /// [detail 11]
      VarProxy< float > f1;
      /// [detail 13]
      VarProxy< float > f1core;
      /// [detail 38]
      VarProxy< float > Emins1;
      /// [detail 28]
      VarProxy< float > fside;
      /// [detail 27]
      VarProxy< float > Emax2;
      /// [detail 24]
      VarProxy< float > ws3;
      /// [detail 37]
      VarProxy< float > wstot;
      /// [detail 39]
      VarProxy< float > emaxs1;
      VarProxy< float > deltaEs;
      /// [detail 15]
      VarProxy< float > E233;
      /// [detail 18]
      VarProxy< float > E237;
      /// [detail 19]
      VarProxy< float > E277;
      /// [detail 25]
      VarProxy< float > weta2;
      /// [detail 12]
      VarProxy< float > f3;
      /// [detail 14]
      VarProxy< float > f3core;
      /// [detail 40]
      VarProxy< float > rphiallcalo;
      /// [detail 0]
      VarProxy< float > Etcone45;
      /// [detail 285]
      VarProxy< float > Etcone15;
      /// [detail 1]
      VarProxy< float > Etcone20;
      /// [detail 286]
      VarProxy< float > Etcone25;
      /// [detail 2]
      VarProxy< float > Etcone30;
      /// [detail 287]
      VarProxy< float > Etcone35;
      /// [detail 3]
      VarProxy< float > Etcone40;
      /// [detail 293]
      VarProxy< float > ptcone20;
      /// [detail 241]
      VarProxy< float > ptcone30;
      /// [detail 294]
      VarProxy< float > ptcone40;
      /// [detail 295]
      VarProxy< float > nucone20;
      /// [detail 296]
      VarProxy< float > nucone30;
      /// [detail 297]
      VarProxy< float > nucone40;
      /// [detail 72]
      VarProxy< float > convanglematch;
      /// [detail 71]
      VarProxy< float > convtrackmatch;
      VarProxy< int > hasconv;
      VarProxy< float > convvtxx;
      VarProxy< float > convvtxy;
      VarProxy< float > convvtxz;
      VarProxy< float > Rconv;
      VarProxy< float > zconv;
      VarProxy< float > convvtxchi2;
      VarProxy< float > pt1conv;
      VarProxy< int > convtrk1nBLHits;
      VarProxy< int > convtrk1nPixHits;
      VarProxy< int > convtrk1nSCTHits;
      VarProxy< int > convtrk1nTRTHits;
      VarProxy< float > pt2conv;
      VarProxy< int > convtrk2nBLHits;
      VarProxy< int > convtrk2nPixHits;
      VarProxy< int > convtrk2nSCTHits;
      VarProxy< int > convtrk2nTRTHits;
      VarProxy< float > ptconv;
      VarProxy< float > pzconv;
      /// [detail 35]
      VarProxy< float > pos7;
      /// [detail 42]
      VarProxy< float > etacorrmag;
      /// [detail 45]
      VarProxy< float > deltaeta1;
      /// [detail 46]
      VarProxy< float > deltaeta2;
      /// [detail 50]
      VarProxy< float > deltaphi2;
      /// [detail 247]
      VarProxy< float > deltaphiRescaled;
      /// [detail 305]Difference between the cluster phi (sampling 2) and the eta of the track extrapolated from the last measurement
      VarProxy< float > deltaPhiFromLast;
      /// [detail 284]Difference between the track phi at perigee and the phi at which the track crosses the calorimeter
      VarProxy< float > deltaPhiRot;
      /// [detail 288]Do we expect to see a hit from this track in the B pixel layer?
      VarProxy< float > expectHitInBLayer;
      /// [detail 274]Transverse impact parameter with respect to the beam spot.
      VarProxy< float > trackd0_physics;
      /// [detail 248]Eta position at sampling 1 for track extrapolated from the last hit.
      VarProxy< float > etaSampling1;
      VarProxy< float > reta;
      VarProxy< float > rphi;
      /// [detail 306]
      VarProxy< float > topoEtcone20;
      /// [detail 307]
      VarProxy< float > topoEtcone30;
      /// [detail 308]
      VarProxy< float > topoEtcone40;
      /// [detail 328]
      VarProxy< float > ptcone20_zpv05;
      /// [detail 329]
      VarProxy< float > ptcone30_zpv05;
      /// [detail 330]
      VarProxy< float > ptcone40_zpv05;
      /// [detail 331]
      VarProxy< float > nucone20_zpv05;
      /// [detail 332]
      VarProxy< float > nucone30_zpv05;
      /// [detail 333]
      VarProxy< float > nucone40_zpv05;
      /// [detail 73]
      VarProxy< float > zvertex;
      /// [detail 74]
      VarProxy< float > errz;
      /// [detail 75]
      VarProxy< float > etap;
      /// [detail 76]
      VarProxy< float > depth;
      /// Number of ntuple rows.
      VarProxy< int > refittedTrack_n;
      VarProxy< float > Es0;
      VarProxy< float > etas0;
      VarProxy< float > phis0;
      VarProxy< float > Es1;
      VarProxy< float > etas1;
      VarProxy< float > phis1;
      VarProxy< float > Es2;
      VarProxy< float > etas2;
      VarProxy< float > phis2;
      VarProxy< float > Es3;
      VarProxy< float > etas3;
      VarProxy< float > phis3;
      VarProxy< float > cl_E;
      VarProxy< float > cl_pt;
      VarProxy< float > cl_eta;
      VarProxy< float > cl_phi;
      VarProxy< float > firstEdens;
      VarProxy< float > cellmaxfrac;
      VarProxy< float > longitudinal;
      VarProxy< float > secondlambda;
      VarProxy< float > lateral;
      VarProxy< float > secondR;
      VarProxy< float > centerlambda;
      VarProxy< float > cl_time;
      VarProxy< float > trackd0;
      VarProxy< float > trackz0;
      VarProxy< float > trackphi;
      VarProxy< float > tracktheta;
      VarProxy< float > trackqoverp;
      VarProxy< float > trackpt;
      VarProxy< float > tracketa;
      VarProxy< int > nBLHits;
      VarProxy< int > nPixHits;
      VarProxy< int > nSCTHits;
      VarProxy< int > nTRTHits;
      VarProxy< int > nTRTHighTHits;
      VarProxy< int > nTRTXenonHits;
      VarProxy< int > nPixHoles;
      VarProxy< int > nSCTHoles;
      VarProxy< int > nTRTHoles;
      VarProxy< int > nPixelDeadSensors;
      VarProxy< int > nSCTDeadSensors;
      VarProxy< int > nBLSharedHits;
      VarProxy< int > nPixSharedHits;
      VarProxy< int > nSCTSharedHits;
      VarProxy< int > nBLayerSplitHits;
      VarProxy< int > nPixSplitHits;
      VarProxy< int > nBLayerOutliers;
      VarProxy< int > nPixelOutliers;
      VarProxy< int > nSCTOutliers;
      VarProxy< int > nTRTOutliers;
      VarProxy< int > nTRTHighTOutliers;
      VarProxy< int > nContribPixelLayers;
      VarProxy< int > nGangedPixels;
      VarProxy< int > nGangedFlaggedFakes;
      VarProxy< int > nPixelSpoiltHits;
      VarProxy< int > nSCTDoubleHoles;
      VarProxy< int > nSCTSpoiltHits;
      VarProxy< int > expectBLayerHit;
      VarProxy< int > nSiHits;
      VarProxy< float > TRTHighTHitsRatio;
      VarProxy< float > TRTHighTOutliersRatio;
      VarProxy< float > pixeldEdx;
      VarProxy< int > nGoodHitsPixeldEdx;
      VarProxy< float > massPixeldEdx;
      VarProxy< vector<float> > likelihoodsPixeldEdx;
      VarProxy< float > vertweight;
      VarProxy< float > trackd0pv;
      VarProxy< float > trackz0pv;
      /// Uncertainty on transverse impact parameter.
      VarProxy< float > tracksigd0pv;
      /// Uncertainty on longitudinal impact parameter.
      VarProxy< float > tracksigz0pv;
      VarProxy< float > trackIPEstimate_d0_biasedpvunbiased;
      VarProxy< float > trackIPEstimate_z0_biasedpvunbiased;
      VarProxy< float > trackIPEstimate_sigd0_biasedpvunbiased;
      VarProxy< float > trackIPEstimate_sigz0_biasedpvunbiased;
      VarProxy< float > trackIPEstimate_d0_unbiasedpvunbiased;
      VarProxy< float > trackIPEstimate_z0_unbiasedpvunbiased;
      VarProxy< float > trackIPEstimate_sigd0_unbiasedpvunbiased;
      VarProxy< float > trackIPEstimate_sigz0_unbiasedpvunbiased;
      VarProxy< int > hastrack;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_Etcone40_ED_corrected] 
      VarProxy< float > Etcone40_ED_corrected;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_Etcone40_corrected] 
      VarProxy< float > Etcone40_corrected;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_topoEtcone20_corrected] 
      VarProxy< float > topoEtcone20_corrected;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_topoEtcone30_corrected] 
      VarProxy< float > topoEtcone30_corrected;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_topoEtcone40_corrected] 
      VarProxy< float > topoEtcone40_corrected;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_ED_median] 
      VarProxy< float > ED_median;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_ED_sigma] 
      VarProxy< float > ED_sigma;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_ED_Njets] 
      VarProxy< float > ED_Njets;
      /// DeltaR between the offline and trigger objects.
      VarProxy< float > EF_dr;
      /// Index in trig_EF_el_
      VarProxy< int > EF_index;
      VarProxy< float > ptcone20_trk500MeV;
      VarProxy< float > ptcone30_trk500MeV;
      VarProxy< float > ptcone40_trk500MeV;
      VarProxy< int > nucone20_trk500MeV;
      VarProxy< int > nucone30_trk500MeV;
      VarProxy< int > nucone40_trk500MeV;
      VarProxy< vector<float> > MET_Egamma10NoTau_wpx;
      VarProxy< vector<float> > MET_Egamma10NoTau_wpy;
      VarProxy< vector<float> > MET_Egamma10NoTau_wet;
      VarProxy< vector<unsigned int> > MET_Egamma10NoTau_statusWord;
      VarProxy< vector<float> > MET_LooseEgamma10NoTau_wpx;
      VarProxy< vector<float> > MET_LooseEgamma10NoTau_wpy;
      VarProxy< vector<float> > MET_LooseEgamma10NoTau_wet;
      VarProxy< vector<unsigned int> > MET_LooseEgamma10NoTau_statusWord;
      VarProxy< vector<float> > MET_Egamma10LooseTau_wpx;
      VarProxy< vector<float> > MET_Egamma10LooseTau_wpy;
      VarProxy< vector<float> > MET_Egamma10LooseTau_wet;
      VarProxy< vector<unsigned int> > MET_Egamma10LooseTau_statusWord;
      VarProxy< vector<float> > MET_wpx;
      VarProxy< vector<float> > MET_wpy;
      VarProxy< vector<float> > MET_wet;
      VarProxy< vector<unsigned int> > MET_statusWord;


bool is_data; // ~bj 

      ClassDef( ElectronD3PDObjectElement, 0 )

   }; // class ElectronD3PDObjectElement

   /**
    * Code generated by CodeGenerator_v2 on:
    *  host = pc-penn-d-07
    *  OS   = Linux / 2.6.18-274.18.1.el5
    *  user = bjackson
    */
   class ElectronD3PDObject : public TObject {

   public:
      /// Constructor used when reading from a TTree
      ElectronD3PDObject( const ::Long64_t& master, const char* prefix = "el_", bool is_data = true );
      /// Constructor when the object is only used for writing data out
      ElectronD3PDObject( const char* prefix = "el_", bool is_data = true );

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
      ElectronD3PDObject& Add( const ElectronD3PDObjectElement& el );

      /// Access a proxy class describing one element of the container
      ElectronD3PDObjectElement& operator[]( size_t index );
      /// Access a proxy class describing one element of the container (constant version)
      const ElectronD3PDObjectElement& operator[]( size_t index ) const;
      /// Add one element to an output collection
      ElectronD3PDObject& operator+=( const ElectronD3PDObjectElement& el );

      /// Number of ntuple rows.
      VarHandle< Int_t > n;
      VarHandle< vector<float>* > E;
      VarHandle< vector<float>* > Et;
      VarHandle< vector<float>* > pt;
      VarHandle< vector<float>* > m;
      VarHandle< vector<float>* > eta;
      VarHandle< vector<float>* > phi;
      VarHandle< vector<float>* > px;
      VarHandle< vector<float>* > py;
      VarHandle< vector<float>* > pz;
      VarHandle< vector<float>* > charge;
      VarHandle< vector<int>* > author;
      /// IsEM mask --- bits are set for each cut that FAILS.
      VarHandle< vector<unsigned int>* > isEM;
      /// Loose IsEM mask --- bits are set for each cut that FAILS.
      VarHandle< vector<unsigned int>* > isEMLoose;
      /// Medium IsEM mask --- bits are set for each cut that FAILS.
      VarHandle< vector<unsigned int>* > isEMMedium;
      /// Tight IsEM mask --- bits are set for each cut that FAILS.
      VarHandle< vector<unsigned int>* > isEMTight;
      VarHandle< vector<unsigned int>* > OQ;
      /// Number of tracks for the first conversion candidate; 0 if no conversion or if there are more than two tracks.
      VarHandle< vector<int>* > convFlag;
      /// True if the first conversion candidate has 1 or 2 tracks.
      VarHandle< vector<int>* > isConv;
      /// Number of conversion vertices.
      VarHandle< vector<int>* > nConv;
      /// Number of conversion vertices with exactly one track.
      VarHandle< vector<int>* > nSingleTrackConv;
      /// Number of conversion vertices with exactly two tracks.
      VarHandle< vector<int>* > nDoubleTrackConv;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_time] 
      VarHandle< vector<float>* > maxEcell_time;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_energy] 
      VarHandle< vector<float>* > maxEcell_energy;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_onlId] 
      VarHandle< vector<unsigned int>* > maxEcell_onlId;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_gain] 
      VarHandle< vector<int>* > maxEcell_gain;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_x] 
      VarHandle< vector<float>* > maxEcell_x;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_y] 
      VarHandle< vector<float>* > maxEcell_y;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_maxEcell_z] 
      VarHandle< vector<float>* > maxEcell_z;
// MC only
      /// MC particle type, from classifier tool.
      VarHandle< vector<int>* > type;
      /// MC particle origin, from classifier tool.
      VarHandle< vector<int>* > origin;
      /// Type of photon for background electron from conversions, from classifier tool
      VarHandle< vector<int>* > typebkg;
      /// Origin of photon for background electron from conversions, from classifier tool.
      VarHandle< vector<int>* > originbkg;
      VarHandle< vector<float>* > truth_E;
      VarHandle< vector<float>* > truth_pt;
      VarHandle< vector<float>* > truth_eta;
      VarHandle< vector<float>* > truth_phi;
      VarHandle< vector<int>* > truth_type;
      VarHandle< vector<int>* > truth_status;
      VarHandle< vector<int>* > truth_barcode;
      VarHandle< vector<int>* > truth_mothertype;
      VarHandle< vector<int>* > truth_motherbarcode;
      VarHandle< vector<int>* > truth_hasHardBrem;
      /// Index in mc_
      VarHandle< vector<int>* > truth_index;
      VarHandle< vector<int>* > truth_matched;
// end MC only
      VarHandle< vector<int>* > mediumWithoutTrack;
      VarHandle< vector<int>* > mediumIsoWithoutTrack;
      VarHandle< vector<int>* > tightWithoutTrack;
      VarHandle< vector<int>* > tightIsoWithoutTrack;
      VarHandle< vector<int>* > loose;
      VarHandle< vector<int>* > looseIso;
      VarHandle< vector<int>* > medium;
      VarHandle< vector<int>* > mediumIso;
      VarHandle< vector<int>* > tight;
      VarHandle< vector<int>* > tightIso;
      VarHandle< vector<int>* > loosePP;
      VarHandle< vector<int>* > loosePPIso;
      VarHandle< vector<int>* > mediumPP;
      VarHandle< vector<int>* > mediumPPIso;
      VarHandle< vector<int>* > tightPP;
      VarHandle< vector<int>* > tightPPIso;
      VarHandle< vector<int>* > goodOQ;
      /// [detail 9]
      VarHandle< vector<float>* > Ethad;
      /// [detail 8]
      VarHandle< vector<float>* > Ethad1;
      /// [detail 11]
      VarHandle< vector<float>* > f1;
      /// [detail 13]
      VarHandle< vector<float>* > f1core;
      /// [detail 38]
      VarHandle< vector<float>* > Emins1;
      /// [detail 28]
      VarHandle< vector<float>* > fside;
      /// [detail 27]
      VarHandle< vector<float>* > Emax2;
      /// [detail 24]
      VarHandle< vector<float>* > ws3;
      /// [detail 37]
      VarHandle< vector<float>* > wstot;
      /// [detail 39]
      VarHandle< vector<float>* > emaxs1;
      VarHandle< vector<float>* > deltaEs;
      /// [detail 15]
      VarHandle< vector<float>* > E233;
      /// [detail 18]
      VarHandle< vector<float>* > E237;
      /// [detail 19]
      VarHandle< vector<float>* > E277;
      /// [detail 25]
      VarHandle< vector<float>* > weta2;
      /// [detail 12]
      VarHandle< vector<float>* > f3;
      /// [detail 14]
      VarHandle< vector<float>* > f3core;
      /// [detail 40]
      VarHandle< vector<float>* > rphiallcalo;
      /// [detail 0]
      VarHandle< vector<float>* > Etcone45;
      /// [detail 285]
      VarHandle< vector<float>* > Etcone15;
      /// [detail 1]
      VarHandle< vector<float>* > Etcone20;
      /// [detail 286]
      VarHandle< vector<float>* > Etcone25;
      /// [detail 2]
      VarHandle< vector<float>* > Etcone30;
      /// [detail 287]
      VarHandle< vector<float>* > Etcone35;
      /// [detail 3]
      VarHandle< vector<float>* > Etcone40;
      /// [detail 293]
      VarHandle< vector<float>* > ptcone20;
      /// [detail 241]
      VarHandle< vector<float>* > ptcone30;
      /// [detail 294]
      VarHandle< vector<float>* > ptcone40;
      /// [detail 295]
      VarHandle< vector<float>* > nucone20;
      /// [detail 296]
      VarHandle< vector<float>* > nucone30;
      /// [detail 297]
      VarHandle< vector<float>* > nucone40;
      /// [detail 72]
      VarHandle< vector<float>* > convanglematch;
      /// [detail 71]
      VarHandle< vector<float>* > convtrackmatch;
      VarHandle< vector<int>* > hasconv;
      VarHandle< vector<float>* > convvtxx;
      VarHandle< vector<float>* > convvtxy;
      VarHandle< vector<float>* > convvtxz;
      VarHandle< vector<float>* > Rconv;
      VarHandle< vector<float>* > zconv;
      VarHandle< vector<float>* > convvtxchi2;
      VarHandle< vector<float>* > pt1conv;
      VarHandle< vector<int>* > convtrk1nBLHits;
      VarHandle< vector<int>* > convtrk1nPixHits;
      VarHandle< vector<int>* > convtrk1nSCTHits;
      VarHandle< vector<int>* > convtrk1nTRTHits;
      VarHandle< vector<float>* > pt2conv;
      VarHandle< vector<int>* > convtrk2nBLHits;
      VarHandle< vector<int>* > convtrk2nPixHits;
      VarHandle< vector<int>* > convtrk2nSCTHits;
      VarHandle< vector<int>* > convtrk2nTRTHits;
      VarHandle< vector<float>* > ptconv;
      VarHandle< vector<float>* > pzconv;
      /// [detail 35]
      VarHandle< vector<float>* > pos7;
      /// [detail 42]
      VarHandle< vector<float>* > etacorrmag;
      /// [detail 45]
      VarHandle< vector<float>* > deltaeta1;
      /// [detail 46]
      VarHandle< vector<float>* > deltaeta2;
      /// [detail 50]
      VarHandle< vector<float>* > deltaphi2;
      /// [detail 247]
      VarHandle< vector<float>* > deltaphiRescaled;
      /// [detail 305]Difference between the cluster phi (sampling 2) and the eta of the track extrapolated from the last measurement
      VarHandle< vector<float>* > deltaPhiFromLast;
      /// [detail 284]Difference between the track phi at perigee and the phi at which the track crosses the calorimeter
      VarHandle< vector<float>* > deltaPhiRot;
      /// [detail 288]Do we expect to see a hit from this track in the B pixel layer?
      VarHandle< vector<float>* > expectHitInBLayer;
      /// [detail 274]Transverse impact parameter with respect to the beam spot.
      VarHandle< vector<float>* > trackd0_physics;
      /// [detail 248]Eta position at sampling 1 for track extrapolated from the last hit.
      VarHandle< vector<float>* > etaSampling1;
      VarHandle< vector<float>* > reta;
      VarHandle< vector<float>* > rphi;
      /// [detail 306]
      VarHandle< vector<float>* > topoEtcone20;
      /// [detail 307]
      VarHandle< vector<float>* > topoEtcone30;
      /// [detail 308]
      VarHandle< vector<float>* > topoEtcone40;
      /// [detail 328]
      VarHandle< vector<float>* > ptcone20_zpv05;
      /// [detail 329]
      VarHandle< vector<float>* > ptcone30_zpv05;
      /// [detail 330]
      VarHandle< vector<float>* > ptcone40_zpv05;
      /// [detail 331]
      VarHandle< vector<float>* > nucone20_zpv05;
      /// [detail 332]
      VarHandle< vector<float>* > nucone30_zpv05;
      /// [detail 333]
      VarHandle< vector<float>* > nucone40_zpv05;
      /// [detail 73]
      VarHandle< vector<float>* > zvertex;
      /// [detail 74]
      VarHandle< vector<float>* > errz;
      /// [detail 75]
      VarHandle< vector<float>* > etap;
      /// [detail 76]
      VarHandle< vector<float>* > depth;
      /// Number of ntuple rows.
      VarHandle< vector<int>* > refittedTrack_n;
      VarHandle< vector<float>* > Es0;
      VarHandle< vector<float>* > etas0;
      VarHandle< vector<float>* > phis0;
      VarHandle< vector<float>* > Es1;
      VarHandle< vector<float>* > etas1;
      VarHandle< vector<float>* > phis1;
      VarHandle< vector<float>* > Es2;
      VarHandle< vector<float>* > etas2;
      VarHandle< vector<float>* > phis2;
      VarHandle< vector<float>* > Es3;
      VarHandle< vector<float>* > etas3;
      VarHandle< vector<float>* > phis3;
      VarHandle< vector<float>* > cl_E;
      VarHandle< vector<float>* > cl_pt;
      VarHandle< vector<float>* > cl_eta;
      VarHandle< vector<float>* > cl_phi;
      VarHandle< vector<float>* > firstEdens;
      VarHandle< vector<float>* > cellmaxfrac;
      VarHandle< vector<float>* > longitudinal;
      VarHandle< vector<float>* > secondlambda;
      VarHandle< vector<float>* > lateral;
      VarHandle< vector<float>* > secondR;
      VarHandle< vector<float>* > centerlambda;
      VarHandle< vector<float>* > cl_time;
      VarHandle< vector<float>* > trackd0;
      VarHandle< vector<float>* > trackz0;
      VarHandle< vector<float>* > trackphi;
      VarHandle< vector<float>* > tracktheta;
      VarHandle< vector<float>* > trackqoverp;
      VarHandle< vector<float>* > trackpt;
      VarHandle< vector<float>* > tracketa;
      VarHandle< vector<int>* > nBLHits;
      VarHandle< vector<int>* > nPixHits;
      VarHandle< vector<int>* > nSCTHits;
      VarHandle< vector<int>* > nTRTHits;
      VarHandle< vector<int>* > nTRTHighTHits;
      VarHandle< vector<int>* > nTRTXenonHits;
      VarHandle< vector<int>* > nPixHoles;
      VarHandle< vector<int>* > nSCTHoles;
      VarHandle< vector<int>* > nTRTHoles;
      VarHandle< vector<int>* > nPixelDeadSensors;
      VarHandle< vector<int>* > nSCTDeadSensors;
      VarHandle< vector<int>* > nBLSharedHits;
      VarHandle< vector<int>* > nPixSharedHits;
      VarHandle< vector<int>* > nSCTSharedHits;
      VarHandle< vector<int>* > nBLayerSplitHits;
      VarHandle< vector<int>* > nPixSplitHits;
      VarHandle< vector<int>* > nBLayerOutliers;
      VarHandle< vector<int>* > nPixelOutliers;
      VarHandle< vector<int>* > nSCTOutliers;
      VarHandle< vector<int>* > nTRTOutliers;
      VarHandle< vector<int>* > nTRTHighTOutliers;
      VarHandle< vector<int>* > nContribPixelLayers;
      VarHandle< vector<int>* > nGangedPixels;
      VarHandle< vector<int>* > nGangedFlaggedFakes;
      VarHandle< vector<int>* > nPixelSpoiltHits;
      VarHandle< vector<int>* > nSCTDoubleHoles;
      VarHandle< vector<int>* > nSCTSpoiltHits;
      VarHandle< vector<int>* > expectBLayerHit;
      VarHandle< vector<int>* > nSiHits;
      VarHandle< vector<float>* > TRTHighTHitsRatio;
      VarHandle< vector<float>* > TRTHighTOutliersRatio;
      VarHandle< vector<float>* > pixeldEdx;
      VarHandle< vector<int>* > nGoodHitsPixeldEdx;
      VarHandle< vector<float>* > massPixeldEdx;
      VarHandle< vector<vector<float> >* > likelihoodsPixeldEdx;
      VarHandle< vector<float>* > vertweight;
      VarHandle< vector<float>* > trackd0pv;
      VarHandle< vector<float>* > trackz0pv;
      /// Uncertainty on transverse impact parameter.
      VarHandle< vector<float>* > tracksigd0pv;
      /// Uncertainty on longitudinal impact parameter.
      VarHandle< vector<float>* > tracksigz0pv;
      VarHandle< vector<float>* > trackIPEstimate_d0_biasedpvunbiased;
      VarHandle< vector<float>* > trackIPEstimate_z0_biasedpvunbiased;
      VarHandle< vector<float>* > trackIPEstimate_sigd0_biasedpvunbiased;
      VarHandle< vector<float>* > trackIPEstimate_sigz0_biasedpvunbiased;
      VarHandle< vector<float>* > trackIPEstimate_d0_unbiasedpvunbiased;
      VarHandle< vector<float>* > trackIPEstimate_z0_unbiasedpvunbiased;
      VarHandle< vector<float>* > trackIPEstimate_sigd0_unbiasedpvunbiased;
      VarHandle< vector<float>* > trackIPEstimate_sigz0_unbiasedpvunbiased;
      VarHandle< vector<int>* > hastrack;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_Etcone40_ED_corrected] 
      VarHandle< vector<float>* > Etcone40_ED_corrected;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_Etcone40_corrected] 
      VarHandle< vector<float>* > Etcone40_corrected;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_topoEtcone20_corrected] 
      VarHandle< vector<float>* > topoEtcone20_corrected;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_topoEtcone30_corrected] 
      VarHandle< vector<float>* > topoEtcone30_corrected;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_topoEtcone40_corrected] 
      VarHandle< vector<float>* > topoEtcone40_corrected;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_ED_median] 
      VarHandle< vector<float>* > ED_median;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_ED_sigma] 
      VarHandle< vector<float>* > ED_sigma;
      /// [UserData: egammaD3PDAnalysis::_ElectronAODCollection_ED_Njets] 
      VarHandle< vector<float>* > ED_Njets;
      /// DeltaR between the offline and trigger objects.
      VarHandle< vector<float>* > EF_dr;
      /// Index in trig_EF_el_
      VarHandle< vector<int>* > EF_index;
      VarHandle< vector<float>* > ptcone20_trk500MeV;
      VarHandle< vector<float>* > ptcone30_trk500MeV;
      VarHandle< vector<float>* > ptcone40_trk500MeV;
      VarHandle< vector<int>* > nucone20_trk500MeV;
      VarHandle< vector<int>* > nucone30_trk500MeV;
      VarHandle< vector<int>* > nucone40_trk500MeV;
      VarHandle< vector<vector<float> >* > MET_Egamma10NoTau_wpx;
      VarHandle< vector<vector<float> >* > MET_Egamma10NoTau_wpy;
      VarHandle< vector<vector<float> >* > MET_Egamma10NoTau_wet;
      VarHandle< vector<vector<unsigned int> >* > MET_Egamma10NoTau_statusWord;
      VarHandle< vector<vector<float> >* > MET_LooseEgamma10NoTau_wpx;
      VarHandle< vector<vector<float> >* > MET_LooseEgamma10NoTau_wpy;
      VarHandle< vector<vector<float> >* > MET_LooseEgamma10NoTau_wet;
      VarHandle< vector<vector<unsigned int> >* > MET_LooseEgamma10NoTau_statusWord;
      VarHandle< vector<vector<float> >* > MET_Egamma10LooseTau_wpx;
      VarHandle< vector<vector<float> >* > MET_Egamma10LooseTau_wpy;
      VarHandle< vector<vector<float> >* > MET_Egamma10LooseTau_wet;
      VarHandle< vector<vector<unsigned int> >* > MET_Egamma10LooseTau_statusWord;
      VarHandle< vector<vector<float> >* > MET_wpx;
      VarHandle< vector<vector<float> >* > MET_wpy;
      VarHandle< vector<vector<float> >* > MET_wet;
      VarHandle< vector<vector<unsigned int> >* > MET_statusWord;

   private:
      mutable std::vector< ElectronD3PDObjectElement > fProxies; ///< Internal list of proxy objects
      std::map< ::TString, VarHandleBase* > fHandles; ///< Book-keeper of the VarHandle members
      const ::Bool_t fFromInput; ///< Flag specifying if object is used for D3PD reading
      const ::TString fPrefix; ///< Prefix to the branch names


bool is_data; // ~bj 

      ClassDef( ElectronD3PDObject, 0 )

   }; // class ElectronD3PDObject

} // namespace D3PDReader

#endif // D3PDREADER_ElectronD3PDObject_H
