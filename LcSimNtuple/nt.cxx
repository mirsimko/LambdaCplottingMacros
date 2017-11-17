#include "nt.h"

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
