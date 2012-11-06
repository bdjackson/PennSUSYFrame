#ifndef CutFlowDump_h
#define CutFlowDump_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>

#include "SusyAnalysisTools/include/EventDescription.h"
#include "SusyAnalysisTools/include/SusyEnums.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

/// enum WEIGHTS { WEIGHT_NONE = 0
///              , WEIGHT_N
///              };

class CutFlowDump {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          m_run_number;
   UInt_t          m_event_number;
   ULong64_t       m_event_desc;

   // List of branches
   TBranch        *b_run_number;   //!
   TBranch        *b_event_number;   //!
   TBranch        *b_event_desc;   //!

   CutFlowDump(TTree *tree=0);
   virtual ~CutFlowDump();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   void initCutFlowHists();
   void checkEvent(PHASE_SPACE);

   void fillHist(PHASE_SPACE phase, unsigned int cut_bin, double weight = 1.);

   void printToFile(std::string out_file_name);

   std::vector<TH1D*> m_cutflow;
};

#endif