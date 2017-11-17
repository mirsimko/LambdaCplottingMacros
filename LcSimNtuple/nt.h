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

#ifdef nt_cxx
nt::nt(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Lc.toyMc.7.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Lc.toyMc.7.root");
      }
      f->GetObject("nt",tree);

   }
   Init(tree);
}

nt::~nt()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t nt::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t nt::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void nt::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("cent", &cent, &b_cent);
   fChain->SetBranchAddress("vx", &vx, &b_vx);
   fChain->SetBranchAddress("vy", &vy, &b_vy);
   fChain->SetBranchAddress("vz", &vz, &b_vz);
   fChain->SetBranchAddress("vzIdx", &vzIdx, &b_vzIdx);
   fChain->SetBranchAddress("pid", &pid, &b_pid);
   fChain->SetBranchAddress("w", &w, &b_w);
   fChain->SetBranchAddress("m", &m, &b_m);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("eta", &eta, &b_eta);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("phi", &phi, &b_phi);
   fChain->SetBranchAddress("v0x", &v0x, &b_v0x);
   fChain->SetBranchAddress("v0y", &v0y, &b_v0y);
   fChain->SetBranchAddress("v0z", &v0z, &b_v0z);
   fChain->SetBranchAddress("rM", &rM, &b_rM);
   fChain->SetBranchAddress("rPt", &rPt, &b_rPt);
   fChain->SetBranchAddress("rEta", &rEta, &b_rEta);
   fChain->SetBranchAddress("rY", &rY, &b_rY);
   fChain->SetBranchAddress("rPhi", &rPhi, &b_rPhi);
   fChain->SetBranchAddress("rV0x", &rV0x, &b_rV0x);
   fChain->SetBranchAddress("rV0y", &rV0y, &b_rV0y);
   fChain->SetBranchAddress("rV0z", &rV0z, &b_rV0z);
   fChain->SetBranchAddress("rV12x", &rV12x, &b_rV12x);
   fChain->SetBranchAddress("rV12y", &rV12y, &b_rV12y);
   fChain->SetBranchAddress("rV12z", &rV12z, &b_rV12z);
   fChain->SetBranchAddress("rV23x", &rV23x, &b_rV23x);
   fChain->SetBranchAddress("rV23y", &rV23y, &b_rV23y);
   fChain->SetBranchAddress("rV23z", &rV23z, &b_rV23z);
   fChain->SetBranchAddress("rV31x", &rV31x, &b_rV31x);
   fChain->SetBranchAddress("rV31y", &rV31y, &b_rV31y);
   fChain->SetBranchAddress("rV31z", &rV31z, &b_rV31z);
   fChain->SetBranchAddress("dcaDaughters", &dcaDaughters, &b_dcaDaughters);
   fChain->SetBranchAddress("decayLength", &decayLength, &b_decayLength);
   fChain->SetBranchAddress("dcaLcToPv", &dcaLcToPv, &b_dcaLcToPv);
   fChain->SetBranchAddress("cosTheta", &cosTheta, &b_cosTheta);
   fChain->SetBranchAddress("angle12", &angle12, &b_angle12);
   fChain->SetBranchAddress("cosThetaStar", &cosThetaStar, &b_cosThetaStar);
   fChain->SetBranchAddress("dcaDaughters12", &dcaDaughters12, &b_dcaDaughters12);
   fChain->SetBranchAddress("dcaDaughters23", &dcaDaughters23, &b_dcaDaughters23);
   fChain->SetBranchAddress("dcaDaughters31", &dcaDaughters31, &b_dcaDaughters31);
   fChain->SetBranchAddress("kM", &kM, &b_kM);
   fChain->SetBranchAddress("kPt", &kPt, &b_kPt);
   fChain->SetBranchAddress("kEta", &kEta, &b_kEta);
   fChain->SetBranchAddress("kY", &kY, &b_kY);
   fChain->SetBranchAddress("kPhi", &kPhi, &b_kPhi);
   fChain->SetBranchAddress("kDca", &kDca, &b_kDca);
   fChain->SetBranchAddress("kRM", &kRM, &b_kRM);
   fChain->SetBranchAddress("kRPt", &kRPt, &b_kRPt);
   fChain->SetBranchAddress("kREta", &kREta, &b_kREta);
   fChain->SetBranchAddress("kRY", &kRY, &b_kRY);
   fChain->SetBranchAddress("kRPhi", &kRPhi, &b_kRPhi);
   fChain->SetBranchAddress("kRVx", &kRVx, &b_kRVx);
   fChain->SetBranchAddress("kRVy", &kRVy, &b_kRVy);
   fChain->SetBranchAddress("kRVz", &kRVz, &b_kRVz);
   fChain->SetBranchAddress("kRDca", &kRDca, &b_kRDca);
   fChain->SetBranchAddress("kRSDca", &kRSDca, &b_kRSDca);
   fChain->SetBranchAddress("kRDcaXY", &kRDcaXY, &b_kRDcaXY);
   fChain->SetBranchAddress("kRDcaZ", &kRDcaZ, &b_kRDcaZ);
   fChain->SetBranchAddress("kEtaIdx", &kEtaIdx, &b_kEtaIdx);
   fChain->SetBranchAddress("kPtIdx", &kPtIdx, &b_kPtIdx);
   fChain->SetBranchAddress("kTpc", &kTpc, &b_kTpc);
   fChain->SetBranchAddress("piM", &piM, &b_piM);
   fChain->SetBranchAddress("piPt", &piPt, &b_piPt);
   fChain->SetBranchAddress("piEta", &piEta, &b_piEta);
   fChain->SetBranchAddress("piY", &piY, &b_piY);
   fChain->SetBranchAddress("piPhi", &piPhi, &b_piPhi);
   fChain->SetBranchAddress("piDca", &piDca, &b_piDca);
   fChain->SetBranchAddress("piRM", &piRM, &b_piRM);
   fChain->SetBranchAddress("piRPt", &piRPt, &b_piRPt);
   fChain->SetBranchAddress("piREta", &piREta, &b_piREta);
   fChain->SetBranchAddress("piRY", &piRY, &b_piRY);
   fChain->SetBranchAddress("piRPhi", &piRPhi, &b_piRPhi);
   fChain->SetBranchAddress("piRVx", &piRVx, &b_piRVx);
   fChain->SetBranchAddress("piRVy", &piRVy, &b_piRVy);
   fChain->SetBranchAddress("piRVz", &piRVz, &b_piRVz);
   fChain->SetBranchAddress("piRDca", &piRDca, &b_piRDca);
   fChain->SetBranchAddress("piRSDca", &piRSDca, &b_piRSDca);
   fChain->SetBranchAddress("piRDcaXY", &piRDcaXY, &b_piRDcaXY);
   fChain->SetBranchAddress("piRDcaZ", &piRDcaZ, &b_piRDcaZ);
   fChain->SetBranchAddress("piEtaIdx", &piEtaIdx, &b_piEtaIdx);
   fChain->SetBranchAddress("piPtIdx", &piPtIdx, &b_piPtIdx);
   fChain->SetBranchAddress("piTpc", &piTpc, &b_piTpc);
   fChain->SetBranchAddress("pM", &pM, &b_pM);
   fChain->SetBranchAddress("pPt", &pPt, &b_pPt);
   fChain->SetBranchAddress("pEta", &pEta, &b_pEta);
   fChain->SetBranchAddress("pY", &pY, &b_pY);
   fChain->SetBranchAddress("pPhi", &pPhi, &b_pPhi);
   fChain->SetBranchAddress("pDca", &pDca, &b_pDca);
   fChain->SetBranchAddress("pRM", &pRM, &b_pRM);
   fChain->SetBranchAddress("pRPt", &pRPt, &b_pRPt);
   fChain->SetBranchAddress("pREta", &pREta, &b_pREta);
   fChain->SetBranchAddress("pRY", &pRY, &b_pRY);
   fChain->SetBranchAddress("pRPhi", &pRPhi, &b_pRPhi);
   fChain->SetBranchAddress("pRVx", &pRVx, &b_pRVx);
   fChain->SetBranchAddress("pRVy", &pRVy, &b_pRVy);
   fChain->SetBranchAddress("pRVz", &pRVz, &b_pRVz);
   fChain->SetBranchAddress("pRDca", &pRDca, &b_pRDca);
   fChain->SetBranchAddress("pRSDca", &pRSDca, &b_pRSDca);
   fChain->SetBranchAddress("pRDcaXY", &pRDcaXY, &b_pRDcaXY);
   fChain->SetBranchAddress("pRDcaZ", &pRDcaZ, &b_pRDcaZ);
   fChain->SetBranchAddress("pEtaIdx", &pEtaIdx, &b_pEtaIdx);
   fChain->SetBranchAddress("pPtIdx", &pPtIdx, &b_pPtIdx);
   fChain->SetBranchAddress("pTpc", &pTpc, &b_pTpc);
   fChain->SetBranchAddress("kHft", &kHft, &b_kHft);
   fChain->SetBranchAddress("piHft", &piHft, &b_piHft);
   fChain->SetBranchAddress("pHft", &pHft, &b_pHft);
   Notify();
}

Bool_t nt::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void nt::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t nt::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef nt_cxx
