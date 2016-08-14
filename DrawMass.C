#include "TCanvas.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH1.h"
#include "TCut.h"
#include "TString.h"
#include "TLegend.h"
#include <utility>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

//________________________________________________________
//________________________________________________________
void DrawMass(string listname = "nTuplesList.list")
{
  size_t lastSlashPos = listname.rfind("/");
  string listWithoutDir = listname.substr(lastSlashPos+1);
  TString outFileName = listWithoutDir + "massPlotGuannansCuts";
  cout << "Writing into: " << outFileName << ".root" << endl;

  // cuts
  TCut dLengthCut = "dLength > 0.008";
  TCut DCApairsCut = "dcaDaughters12 < 0.006 && dcaDaughters23 < 0.006 && dcaDaughters31 < 0.006";
  TCut ptCut = "p1pt > 0.5 && p2pt > 0.5 && p3pt > 0.5"; // K, p, pi
  TCut cosThetaCut = "cosPntAngle > 0.99";
  TCut maxVertexDistCut = "maxVertexDist < 0.01";
  TCut onePartDCA = "p1Dca > 0.008 && p2Dca > 0.008 && p3Dca > 0.008";
  TCut LcPtCut = "pt > 3";
  TCut nSigmaCuts = "abs(pNSigma) < 2. && abs(KNSigma) < 2. && abs(piNSigma) < 3.";
  TCut TOFused = "pTOFinvBetaDiff == pTOFinvBetaDiff && KTOFinvBetaDiff == KTOFinvBetaDiff"; // none of them is NaN
  TCut centralityCut = "centrality < 7 && centrality > 0.1";
  TCut etaCut = "abs(piEta) < 1. && abs(KEta) < 1. && abs(pEta) < 1.";
  TCut betaCut = "abs(pTOFinvBetaDiff) < 0.03 && abs(KTOFinvBetaDiff) < 0.03";
  TCut hybridBetaCut = "(abs(pTOFinvBetaDiff)  < 0.03 || pTOFinvBetaDiff < -0.5) && ( abs(KTOFinvBetaDiff) < 0.03 || KTOFinvBetaDiff < -0.5)";
  TCut piHybridBeta = "(abs(piTOFinvBetaDiff)  < 0.04 || piTOFinvBetaDiff < -0.5) ";
  TCut piTOFused = "piTOFinvBetaDiff > -0.5";

  TCut AllCuts = dLengthCut && DCApairsCut && cosThetaCut && onePartDCA && LcPtCut && nSigmaCuts && betaCut && maxVertexDist; //  TOF is used strictly, no centrality cut
  // TCut AllCuts = LcPtCut && centralityCut && betaCut && nSigmaCuts; // more open cuts
  // TCut AllCuts = betaCut && nSigmaCuts; // no centrality cut

  TCut correctSign = "charges > 0";
  TCut wrongSign = "charges < 0";

  TFile *outF = new TFile( Form("%s.root", outFileName.Data() ), "RECREATE");
  outF->cd();

  //________________________________________________________
  // setting up canvas
  TCanvas *C1 = new TCanvas("C1", "", 1200, 1200);
  C1->Divide(2,4);
  TCanvas *C2 = new TCanvas("C2", "", 1200, 900);
  C2->Divide(2,1);
  TCanvas *C3 = new TCanvas("C3", "", 1200, 900);
  C3->Divide(2,2);
  TCanvas *C4 = new TCanvas("C4", "", 800, 600);

  // creating histograms
  TH1D *decayLength = new TH1D("decayLength", "Decay length of background" , 40, 0, 0.0400);
  TH1D *pthist[3];
  TH1D *cosTheta = new TH1D("cosTheta", "cos(#theta)"  , 20, 0.98, 1.);
  TH1D *vDist = new TH1D("vDist", "Maximum distance between vertices of pairs", 60, 0, 0.0600);
  TH1D *massHist = new TH1D("massHist", "#Lambda_{c} mass", 40, 2.1, 2.5);
  TH1D *massHistBkg = new TH1D("massHistBkg", "BG mass", 40, 2.1, 2.5);
  TH1D * DCAhist23 = new TH1D("DCA23", "DCA K #pi", 40, 0., 0.02);
  TH1D * DCAhist31 = new TH1D("DCA31", "DCA K p", 40, 0., 0.02);

  TString partName[3] = {"K", "p", "pi"};
  for(int i = 1; i <= 3; ++i)
  {
    pthist[i-1] = new TH1D(Form("pt%s", partName[i-1].Data() ), Form("simulated p_{T} of %s", partName[i-1].Data()), 50, 0, 6.);
    pthist[i-1]->Sumw2();
  }

  TH1D *DCAhist[4];
  pair<float,float> ptLimits[4];
  for(int i = 0; i < 4; ++i)
  {
    ptLimits[i].first = 2.*i;
    ptLimits[i].second = 2.*i+2.;
    DCAhist[i] = new TH1D(Form("DCA%d", i), Form("DCA K #pi with %.0f GeV < pt < %.0f GeV", ptLimits[i].first, ptLimits[i].second), 40, 0., 0.02);
    DCAhist[i]->Sumw2();
  }

  decayLength->Sumw2();
  cosTheta->Sumw2();
  vDist->Sumw2();
  DCAhist23->Sumw2();
  DCAhist31->Sumw2();

  massHist->Sumw2();
  massHistBkg->Sumw2();

  //________________________________________________________
  ifstream fileList(listname.data());
  if(!fileList.is_open())
  {
    cerr << "list could not be opened" << endl;
    return;
  }
  
  string fileName;
  // loop on the fileList
  int fileN = 0;
  //________________________________________________________
  while(getline(fileList, fileName))
  {
    cout << "********************************************************" << endl;
    cout << "Reading from " << fileName << " ..."<< endl;
    cout << "file number " << fileN+1 << endl;
    cout << "********************************************************" << endl;

    TFile *inf = new TFile(fileName.data());
    TNtuple *particles = static_cast<TNtuple *>(inf->Get("secondary"));

    if(!particles)
    {
      cerr << "nTuple not found in file:" << endl << fileName << endl << "Skipping ..." << endl; 
      continue;
    }

    // creating increment histograms
    TH1D *decayLengthInc = new TH1D("decayLengthInc", "Decay length of background" , 40, 0, 0.0400);
    TH1D *pthistInc[3];
    TH1D *cosThetaInc = new TH1D("cosThetaInc", "cos(#theta)"  , 20, 0.98, 1.);
    TH1D *vDistInc = new TH1D("vDistInc", "Maximum distance between vertices of pairs", 60, 0, 0.0600);
    TH1D *massHistInc = new TH1D("massHistInc", "#Lambda_{c} mass", 40, 2.1, 2.5);
    TH1D *massHistBkgInc = new TH1D("massHistBkgInc", "BG mass", 40, 2.1, 2.5);
    TH1D *DCAhist23Inc = new TH1D("DCA23Inc", "DCA K #pi", 40, 0., 0.02);
    TH1D *DCAhist31Inc = new TH1D("DCA31Inc", "DCA K p", 40, 0., 0.02);

    for(int i = 1; i <= 3; ++i)
    {
      pthistInc[i-1] = new TH1D(Form("pt%sInc", partName[i-1].Data() ), Form("simulated p_{T} of %s", partName[i-1].Data()), 50, 0, 6.);
      pthistInc[i-1]->Sumw2();
    }

    TH1D *DCAhistInc[4];
    for(int i = 0; i < 4; ++i)
    {
      DCAhistInc[i] = new TH1D(Form("DCA%dInc", i), Form("DCA K #pi with %.0f GeV < pt < %.0f GeV", ptLimits[i].first, ptLimits[i].second), 40, 0., 0.02);
      DCAhistInc[i]->Sumw2();
    }

    decayLengthInc->Sumw2();
    cosThetaInc->Sumw2();
    vDistInc->Sumw2();
    DCAhist23Inc->Sumw2();
    massHistBkgInc->Sumw2();
    massHistInc->Sumw2();

    // filling increment histograms
    // cout << "filling decayLength ..." << endl;
    // particles -> Project("decayLengthInc","dLength");
    // decayLength->Add(decayLengthInc);
    //
    // cout << "filling pT ..." << endl;
    // for(int i = 1; i <= 3; ++i)
    // {
    //   particles->Project(Form("pt%sInc", partName[i-1].Data() ), Form("p%dpt", i));
    //   pthist[i-1]->Add(pthistInc[i-1]);
    // }
    //
    // cout << "filling cos(theta) ..." << endl;
    // particles -> Project("cosThetaInc", "cosPntAngle");
    // cosTheta->Add(cosThetaInc);
    // cout << "filling vDist ..." << endl;
    // particles->Project("vDistInc", "maxVertexDist");
    // vDist->Add(vDistInc);
    // cout << "filling DCA daughters ..." << endl;
    // particles->Project("DCA23Inc", "dcaDaughters23");
    // DCAhist23->Add(DCAhist23Inc);
    // particles->Project("DCA31Inc", "dcaDaughters31");
    // DCAhist31->Add(DCAhist31Inc);
    //
    // cout << "filling DCA daughters in pT bins..." << endl;
    // for(int i = 0; i < 4; ++i)
    // {
    //   particles->Project(Form("DCA%dInc", i), "dcaDaughters23", Form("%f < pt && pt < %f ", ptLimits[i].first, ptLimits[i].second));
    //   DCAhist[i]->Add(DCAhistInc[i]);
    // }

    cout << "filling mass ..." << endl;

    particles->Project("massHistInc", "m", AllCuts && correctSign);
    particles->Project("massHistBkgInc", "m", AllCuts && wrongSign );

    massHist->Add(massHistInc);
    massHistBkg->Add(massHistBkgInc);

    // cleaning up
    delete decayLengthInc;
    for(int i = 1; i <= 3; ++i)
      delete pthistInc[i-1];
    delete cosThetaInc;
    delete vDistInc;
    delete DCAhist23Inc;
    delete DCAhist31Inc;
    for(int i = 0; i < 4; ++i)
      delete DCAhistInc[i];
    delete massHistBkgInc;
    delete massHistInc;

    ++fileN;
    delete particles;
    inf->Close();
    delete inf;
  }
  fileList.close();

  //________________________________________________________
  // plotting
  cout << "********************************************************" << endl;
  cout << "Plotting" << endl;
  cout << "********************************************************" << endl;

  outF->cd();
  C1->cd(1);
  decayLength->Write();
  decayLength->SetMarkerStyle(kFullDotLarge);
  decayLength->Draw("E1");

  for (int i = 1; i <= 3; ++i)
  {
    cout << "pt plot #" << i << endl;
    C1->cd(i+1);

    pthist[i-1]->SetMarkerStyle(kFullDotLarge);
    pthist[i-1]->GetXaxis()->SetTitle("p_{T} [GeV]");
    

    pthist[i-1]->Write();

    pthist[i-1]->SetStats(false);
    pthist[i-1]->Draw("E1");

  }
  cout << "cos(theta)" << endl;
  C1->cd(5);
  cosTheta->SetMarkerStyle(kFullDotLarge);
  cosTheta->GetXaxis()->SetTitle("cos(#theta)");

  cosTheta->SetStats(false);
  cosTheta->Draw("E1");

  //________________________________________________________
  cout << "Maximum distance" << endl;
  C1->cd(6);

  vDist->SetMarkerStyle(kFullDotLarge);
  vDist->Write();

  vDist->SetStats(false);

  vDist->Draw("E1");

  //________________________________________________________
  // DCA K pi daughters


  C1->cd(7);
  printf("DCA K pi\n");


  DCAhist23->SetStats(false);

  DCAhist23->Write();

  DCAhist23 -> SetMarkerStyle(kFullDotLarge);
  DCAhist23->GetXaxis()->SetTitle("DCA K #pi [cm]");
  DCAhist23->Draw("E1");

  //________________________________________________________
  // DCA K p daughters

  C1->cd(8);
  printf("DCA K p\n");

  DCAhist31 -> SetMarkerStyle(kFullDotLarge);
  DCAhist31->SetStats(false);

  DCAhist31->GetXaxis()->SetTitle("DCA K p [cm]");
  DCAhist31->Draw("E1");

  // DCA daughters in pt
  // TLegend *DCAleg[4];
  for (int i = 0; i < 4; ++i)
  {
    C3->cd(i+1);
    pair<float,float> ptLimits(2.*i,2.*i+2.);
    printf("DCA daughters for %.0f < pt < %0.f\n", ptLimits.first, ptLimits.second);


    DCAhist[i]->SetStats(false);

    DCAhist[i]->Write();

    DCAhist[i]->GetXaxis()->SetTitle("DCA K #pi [cm]");
    DCAhist[i]->Draw("E1");
  }
  //________________________________________________________
  cout << "Mass plot ..." << endl;
  C4->cd();

  massHistBkg->Scale(1./3.);

  massHist->GetXaxis()->SetTitle("m (GeV)");
  massHist->GetYaxis()->SetTitle("N");
  massHist->SetStats(false);
  massHist->SetMarkerStyle(kFullDotLarge);
  massHistBkg->SetMarkerStyle(22);
  massHistBkg->SetMarkerColor(kRed);
  massHistBkg->SetLineColor(kRed);

  massHistBkg->Write();
  massHist->Write();

  massHist->Draw("E1");
  massHistBkg->Draw("E1same");



  //________________________________________________________
  // saving
  C1->Write();
  // C2->Write();
  C3->Write();
  C4->Write();

  
  outF->Close();
  cout << "Done" << endl;
}
//________________________________________________________
//________________________________________________________
