#define nt_cxx
#include "nt.h"
#include "pidEfficiencyMaker.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TStopwatch.h>

void nt::makeEff()
{
  //   In a ROOT session, you can do:
  //      Root > .L nt.C
  //      Root > nt t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  TStopwatch*   stopWatch = new TStopwatch();
  stopWatch->Start();

  TFile* fTofMatchFile = new TFile("tofMatch_fit_Run14_17Jan19.root");
  for (int i = 0; i < 9; i++)
  {
    ftofpi[i] = (TF1*)fTofMatchFile->Get(Form("funpip_%d", i))->Clone(Form("funpi_%d", i));
    // ftofpi[i]->SetDirectory(0);
    ftofk[i] = (TF1*)fTofMatchFile->Get(Form("funkm_%d", i))->Clone(Form("funk_%d", i));
    // ftofk[i]->SetDirectory(0);
    ftofp[i] = (TF1*)fTofMatchFile->Get(Form("funpp_%d", i))->Clone(Form("funp_%d", i));
    // ftofp[i]->SetDirectory(0);
  }
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  nt t(0);

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    getEfficiency(jentry);
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
  }
}
