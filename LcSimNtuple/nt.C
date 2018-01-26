#define nt_cxx
#include "nt.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

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

  loadHftRatio();
  gRandom->SetSeed();
  TFile* fHftRatioCorrection = new TFile("hftRatioCorrection_v1.root");
  gHftRatioCorrection = (TGraphErrors*)fHftRatioCorrection->Get("Graph");
  // gHftRatioCorrection->SetDirectory(0);
  // fHftRatioCorrection->Close();

  TFile* fAuAu010Weight = new TFile("AuAu010_weight.root");
  gf1AuAu010Weight = (TF1*)fAuAu010Weight->Get("f1Levy010");
  // gf1AuAu010Weight->SetDirectory(0);
  // fAuAu010Weight->Close();

  TFile* fpionPid = new TFile("pion_PidEff_FromXiaolong.root");
  fpionNsig_eff = (TF1*)fpionPid->Get("fNsig_eff")->Clone("fpionNsig_eff");
  // fpionNsig_eff->SetDirectory(0);
  fpionNsigTof_eff = (TF1*)fpionPid->Get("fNsigTof_eff")->Clone("fpionNsigTof_eff");
  // fpionNsigTof_eff->SetDirectory(0);
  // fpionPid->Close();

  TFile* fkaonPid = new TFile("kaon_PidEff_FromXiaolong.root");
  fkaonNsig_eff = (TF1*)fkaonPid->Get("fNsig_eff")->Clone("fkaonNsig_eff");
  // fkaonNsig_eff->SetDirectory(0);
  fkaonNsigTof_eff = (TF1*)fkaonPid->Get("fNsigTof_eff")->Clone("fkaonNsigTof_eff");
  // fkaonNsigTof_eff->SetDirectory(0);
  // fkaonPid->Close();

  TFile* fprotonPid = new TFile("proton_PidEff_Lambda0.root");
  gprotonNsig_eff = (TGraphErrors*)fprotonPid->Get("gNsig_eff")->Clone("gprotonNsig_eff");
  // gprotonNsig_eff->SetDirectory(0);
  gprotonNsigTof_eff = (TGraphErrors*)fprotonPid->Get("gNsigTof_eff")->Clone("gprotonNsigTof_eff");
  // gprotonNsigTof_eff->SetDirectory(0);
  // fprotonPid->Close();

  // TF1 *myGaus = new TF1("myGaus", "gaus(0)", -10, 10); //for tpc
  // myGaus->SetName("myGaus");
  // myGaus->SetNpx(100);

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

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
  }
}
