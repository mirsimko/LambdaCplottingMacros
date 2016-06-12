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
  TString outFileName = "massPlotXinsCuts";

  // cuts
  TCut dLengthCut = "dLength > 0.02";
  TCut DCApairsCut = "dcaDaughters12 < 0.0065 && dcaDaughters23 < 0.0065 && dcaDaughters31 < 0.0065";
  TCut ptCut = "p1pt > 0.5 && p2pt > 0.5 && p3pt > 0.5"; // K, p, pi
  TCut cosThetaCut = "cosPntAngle > 0.992";
  TCut maxVertexDistCut = "maxVertexDist < 1.";
  TCut onePartDCA = "p1Dca > 0.0080 && p2Dca > 0.0080 && p3Dca > 0.0080";
  TCut LcPtCut = "pt > 3.";
  TCut nSigmaCuts = "pNSigma < 2. && KNSigma < 2. && piNSigma < 3.";
  TCut TOFused = "pTOFinvBetaDiff == pTOFinvBetaDiff && piTOFinvBetaDiff == piTOFinvBetaDiff && KTOFnvBetaDiff == KTOFnvBetaDiff"; // none of them is NaN
  TCut centralityCut = "centrality < 6.5";
  TCut etaCut = "abs(piEta) < 1. && abs(KEta) < 1. && abs(pEta) < 1.";

  TCut AllCuts = dLengthCut && DCApairsCut && cosThetaCut && maxVertexDistCut && onePartDCA && ptCut && nSigmaCuts && TOFused && centralityCut && etaCut; 

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
  TH1D *massHist = new TH1D("massHist", "#Lambda_{c} mass", 100, 2.0, 2.5);
  TH1D *massHistBkg = new TH1D("massHistBkg", "BG mass", 100, 2.0, 2.5);
  TH1D *DCAhist23;
  DCAhist23 = new TH1D("DCA23", "DCA K #pi", 40, 0., 0.02);
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

    cout << "filling decayLength ..." << endl;
    particles -> Project("decayLength","dLength");

    cout << "filling pT ..." << endl;
    for(int i = 1; i <= 3; ++i)
    {
      particles->Project(Form("pt%s", partName[i-1].Data() ), Form("p%dpt", i));
    }

    cout << "filling cos(theta) ..." << endl;
    particles -> Project("cosTheta", "cosPntAngle");
    cout << "filling vDist ..." << endl;
    particles->Project("vDist", "maxVertexDist");
    cout << "filling DCA daughters ..." << endl;
    particles->Project("DCA23", "dcaDaughters23");
    particles->Project("DCA31", "dcaDaughters31");

    cout << "filling DCA daughters in pT bins..." << endl;
    for(int i = 0; i < 4; ++i)
    {
      particles->Project(Form("DCA%d", i), "dcaDaughters23", Form("%f < pt && pt < %f ", ptLimits[i].first, ptLimits[i].second));
    }

    cout << "filling mass ..." << endl;
    particles->Project("massHist", "m", AllCuts && correctSign);
    particles->Project("massHistBkg", "m", AllCuts && wrongSign );

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
  C2->Write();
  C3->Write();
  C4->Write();

  
  outF->Close();
  cout << "Done" << endl;
}
//________________________________________________________
//________________________________________________________
