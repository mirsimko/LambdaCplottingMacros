//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 16 17:08:06 2017 by ROOT version 5.34/30
// from TTree nt/
// found on file: Lc.toyMc.7.root
//////////////////////////////////////////////////////////

#ifndef nt_h
#define nt_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class nt {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         cent;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Float_t         vzIdx;
   Float_t         pid;
   Float_t         w;
   Float_t         m;
   Float_t         pt;
   Float_t         eta;
   Float_t         y;
   Float_t         phi;
   Float_t         v0x;
   Float_t         v0y;
   Float_t         v0z;
   Float_t         rM;
   Float_t         rPt;
   Float_t         rEta;
   Float_t         rY;
   Float_t         rPhi;
   Float_t         rV0x;
   Float_t         rV0y;
   Float_t         rV0z;
   Float_t         rV12x;
   Float_t         rV12y;
   Float_t         rV12z;
   Float_t         rV23x;
   Float_t         rV23y;
   Float_t         rV23z;
   Float_t         rV31x;
   Float_t         rV31y;
   Float_t         rV31z;
   Float_t         dcaDaughters;
   Float_t         decayLength;
   Float_t         dcaLcToPv;
   Float_t         cosTheta;
   Float_t         angle12;
   Float_t         cosThetaStar;
   Float_t         dcaDaughters12;
   Float_t         dcaDaughters23;
   Float_t         dcaDaughters31;
   Float_t         kM;
   Float_t         kPt;
   Float_t         kEta;
   Float_t         kY;
   Float_t         kPhi;
   Float_t         kDca;
   Float_t         kRM;
   Float_t         kRPt;
   Float_t         kREta;
   Float_t         kRY;
   Float_t         kRPhi;
   Float_t         kRVx;
   Float_t         kRVy;
   Float_t         kRVz;
   Float_t         kRDca;
   Float_t         kRSDca;
   Float_t         kRDcaXY;
   Float_t         kRDcaZ;
   Float_t         kEtaIdx;
   Float_t         kPtIdx;
   Float_t         kTpc;
   Float_t         piM;
   Float_t         piPt;
   Float_t         piEta;
   Float_t         piY;
   Float_t         piPhi;
   Float_t         piDca;
   Float_t         piRM;
   Float_t         piRPt;
   Float_t         piREta;
   Float_t         piRY;
   Float_t         piRPhi;
   Float_t         piRVx;
   Float_t         piRVy;
   Float_t         piRVz;
   Float_t         piRDca;
   Float_t         piRSDca;
   Float_t         piRDcaXY;
   Float_t         piRDcaZ;
   Float_t         piEtaIdx;
   Float_t         piPtIdx;
   Float_t         piTpc;
   Float_t         pM;
   Float_t         pPt;
   Float_t         pEta;
   Float_t         pY;
   Float_t         pPhi;
   Float_t         pDca;
   Float_t         pRM;
   Float_t         pRPt;
   Float_t         pREta;
   Float_t         pRY;
   Float_t         pRPhi;
   Float_t         pRVx;
   Float_t         pRVy;
   Float_t         pRVz;
   Float_t         pRDca;
   Float_t         pRSDca;
   Float_t         pRDcaXY;
   Float_t         pRDcaZ;
   Float_t         pEtaIdx;
   Float_t         pPtIdx;
   Float_t         pTpc;
   Float_t         kHft;
   Float_t         piHft;
   Float_t         pHft;

   // List of branches
   TBranch        *b_cent;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_vzIdx;   //!
   TBranch        *b_pid;   //!
   TBranch        *b_w;   //!
   TBranch        *b_m;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_y;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_v0x;   //!
   TBranch        *b_v0y;   //!
   TBranch        *b_v0z;   //!
   TBranch        *b_rM;   //!
   TBranch        *b_rPt;   //!
   TBranch        *b_rEta;   //!
   TBranch        *b_rY;   //!
   TBranch        *b_rPhi;   //!
   TBranch        *b_rV0x;   //!
   TBranch        *b_rV0y;   //!
   TBranch        *b_rV0z;   //!
   TBranch        *b_rV12x;   //!
   TBranch        *b_rV12y;   //!
   TBranch        *b_rV12z;   //!
   TBranch        *b_rV23x;   //!
   TBranch        *b_rV23y;   //!
   TBranch        *b_rV23z;   //!
   TBranch        *b_rV31x;   //!
   TBranch        *b_rV31y;   //!
   TBranch        *b_rV31z;   //!
   TBranch        *b_dcaDaughters;   //!
   TBranch        *b_decayLength;   //!
   TBranch        *b_dcaLcToPv;   //!
   TBranch        *b_cosTheta;   //!
   TBranch        *b_angle12;   //!
   TBranch        *b_cosThetaStar;   //!
   TBranch        *b_dcaDaughters12;   //!
   TBranch        *b_dcaDaughters23;   //!
   TBranch        *b_dcaDaughters31;   //!
   TBranch        *b_kM;   //!
   TBranch        *b_kPt;   //!
   TBranch        *b_kEta;   //!
   TBranch        *b_kY;   //!
   TBranch        *b_kPhi;   //!
   TBranch        *b_kDca;   //!
   TBranch        *b_kRM;   //!
   TBranch        *b_kRPt;   //!
   TBranch        *b_kREta;   //!
   TBranch        *b_kRY;   //!
   TBranch        *b_kRPhi;   //!
   TBranch        *b_kRVx;   //!
   TBranch        *b_kRVy;   //!
   TBranch        *b_kRVz;   //!
   TBranch        *b_kRDca;   //!
   TBranch        *b_kRSDca;   //!
   TBranch        *b_kRDcaXY;   //!
   TBranch        *b_kRDcaZ;   //!
   TBranch        *b_kEtaIdx;   //!
   TBranch        *b_kPtIdx;   //!
   TBranch        *b_kTpc;   //!
   TBranch        *b_piM;   //!
   TBranch        *b_piPt;   //!
   TBranch        *b_piEta;   //!
   TBranch        *b_piY;   //!
   TBranch        *b_piPhi;   //!
   TBranch        *b_piDca;   //!
   TBranch        *b_piRM;   //!
   TBranch        *b_piRPt;   //!
   TBranch        *b_piREta;   //!
   TBranch        *b_piRY;   //!
   TBranch        *b_piRPhi;   //!
   TBranch        *b_piRVx;   //!
   TBranch        *b_piRVy;   //!
   TBranch        *b_piRVz;   //!
   TBranch        *b_piRDca;   //!
   TBranch        *b_piRSDca;   //!
   TBranch        *b_piRDcaXY;   //!
   TBranch        *b_piRDcaZ;   //!
   TBranch        *b_piEtaIdx;   //!
   TBranch        *b_piPtIdx;   //!
   TBranch        *b_piTpc;   //!
   TBranch        *b_pM;   //!
   TBranch        *b_pPt;   //!
   TBranch        *b_pEta;   //!
   TBranch        *b_pY;   //!
   TBranch        *b_pPhi;   //!
   TBranch        *b_pDca;   //!
   TBranch        *b_pRM;   //!
   TBranch        *b_pRPt;   //!
   TBranch        *b_pREta;   //!
   TBranch        *b_pRY;   //!
   TBranch        *b_pRPhi;   //!
   TBranch        *b_pRVx;   //!
   TBranch        *b_pRVy;   //!
   TBranch        *b_pRVz;   //!
   TBranch        *b_pRDca;   //!
   TBranch        *b_pRSDca;   //!
   TBranch        *b_pRDcaXY;   //!
   TBranch        *b_pRDcaZ;   //!
   TBranch        *b_pEtaIdx;   //!
   TBranch        *b_pPtIdx;   //!
   TBranch        *b_pTpc;   //!
   TBranch        *b_kHft;   //!
   TBranch        *b_piHft;   //!
   TBranch        *b_pHft;   //!

   nt(TTree *tree=0);
   virtual ~nt();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif
