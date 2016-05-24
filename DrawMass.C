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

using namespace std;

void DrawMass()
{
  // 
  // declare variables
  TString outFileName = "plot_noBug";

  // cuts
  TCut dLengthCut = "dLength > 0.0060";
  TCut DCApairsCut = "dcaDaugthers12 < 0.0100 && dcaDaugthers23 < 0.0100 && dcaDaugthers31 < 0.0100";
  TCut ptCut = ""; // K, p, pi
  TCut cosThetaCut = "cosPntAngle > 0.998";
  TCut maxVertexDistCut = "maxVertexDist < 0.03";
  TCut onePartDCA = "p1Dca > 50 && p2Dca > 50 && p3Dca > 50";

  TCut AllCuts = dLengthCut && DCApairsCut && ptCut && cosThetaCut && maxVertexDistCut && onePartDCA; 

  // getting the Ntuple and setting variables for all decay modes
  TFile *readF1 = new TFile("picoHFLambdaCMaker_noBug.root");
  TNtuple *particles = (TNtuple*) readF1->Get("secondary");
  TFile *outF = new TFile( Form("%snew.root", outFileName.Data() ), "RECREATE");
  outF->cd();

  // setting up canvas
  TCanvas *C1 = new TCanvas("C1", "", 1200, 1200);
  C1->Divide(2,4);
  TCanvas *C2 = new TCanvas("C2", "", 1200, 900);
  C2->Divide(2,1);
  TCanvas *C3 = new TCanvas("C3", "", 1200, 900);
  C3->Divide(2,2);
  TCanvas *C4 = new TCanvas("C4", "", 800, 600);

  //________________________________________________________
  // fill histograms
  
  
  cout << "Decay length" << endl;
  TH1D *decayLength = new TH1D("decayLength", "Decay length of background" , 40, 0, 0.0400);
  C1->cd(1);
  particles -> Project("decayLength","dLength");
  decayLength->Write();
  decayLength->SetLineColor(kRed);
  decayLength->Draw();

  // TLegend *dLengthLeg = new TLegend(0.5, 0.7, 0.9, 0.9);
  // dLengthLeg->AddEntry(dLengthSim, "Simulation", "lp");
  // dLengthLeg->AddEntry(decayLength, Form("Background (x%e)", scale*3.), "l");
  // dLengthLeg->SetFillColor(kWhite);
  // dLengthLeg->Draw();
  //________________________________________________________

  TH1D *pthist[3];
  // TLegend *ptLeg[3];
  TString partName[3] = {"K", "p", "pi"};
  for (int i = 1; i <= 3; ++i)
  {
    cout << "pt plot #" << i << endl;
    C1->cd(i+1);

    pthist[i-1] = new TH1D(Form("pt%s", partName[i-1].Data() ), Form("simulated p_{T} of %s", partName[i-1].Data()), 50, 0, 6.);
    pthist[i-1]->Sumw2();
    particles->Project(Form("pt%s", partName[i-1].Data() ), Form("p%dpt", i));
    pthist[i-1]->SetMarkerStyle(kFullDotLarge);
    pthist[i-1]->GetXaxis()->SetTitle("p_{T} [GeV]");
    

    pthist[i-1]->Write();

    pthist[i-1]->SetStats(false);
    pthist[i-1]->Draw("E1");

    // ptLeg[i-1]= new TLegend(0.5, 0.7, 0.9, 0.9);
    // ptLeg[i-1] ->AddEntry(pthist[i-1], "Simulation", "pl");
    // ptLeg[i-1] ->AddEntry(pthistBkg[i-1], Form("Background (x%e)", scale*3.), "l");
    // ptLeg[i-1] ->SetFillColor(kWhite);
    // ptLeg[i-1] -> Draw();

  }
  //________________________________________________________
  cout << "cos(theta)" << endl;
  TH1D *cosTheta = new TH1D("cosTheta", "cos(#theta)"  , 20, 0.98, 1.);
  C1->cd(5);
  cosTheta->Sumw2();
  particles -> Project("cosTheta", "cosPntAngle");
  cosTheta->SetMarkerStyle(kFullDotLarge);
  cosTheta->GetXaxis()->SetTitle("cos(#theta)");

  cosTheta->SetStats(false);
  cosTheta->Draw("E1");

  // TLegend *legCosTheta = new TLegend(0.1, 0.7, 0.5, 0.9);
  // legCosTheta->AddEntry(cosTheta, "Simulation", "pl");
  // legCosTheta->AddEntry(cosThetaBkg, Form("Background (x%e)", scale*3.), "l");
  // legCosTheta->SetFillColor(kWhite);
  // legCosTheta->Draw();

  //________________________________________________________
  cout << "Maximum distance" << endl;
  C1->cd(6);
  TH1D *vDist = new TH1D("vDist", "Maximum distance between vertices of pairs", 60, 0, 0.0600);

  vDist->Sumw2();
  particles->Project("vDist", "maxVertexDist");
  vDist->SetMarkerStyle(kFullDotLarge);
  vDist->Write();

  vDist->SetStats(false);

  vDist->Draw("E1");

  // TLegend *vDistLeg = new TLegend(0.5, 0.7, 0.9, 0.9);
  // vDistLeg->AddEntry(vDist, "Simulation", "lp");
  // vDistLeg->AddEntry(vDistBkg, Form("background (x%e)", scale*3.), "l");
  // vDistLeg->SetFillColor(kWhite);
  // vDistLeg->Draw();
  
  //________________________________________________________
  // DCA K pi daughters

  TH1D *DCAhist23;

  C1->cd(7);
  printf("DCA K pi\n");

  DCAhist23 = new TH1D("DCA23", "DCA K #pi", 40, 0., 0.02);
  particles->Project("DCA23", "dcaDaugthers23");

  DCAhist23->SetStats(false);

  DCAhist23->Write();

  DCAhist23->GetXaxis()->SetTitle("DCA K #pi [cm]");
  DCAhist23->Draw("E1");

  // DCAleg23 = new TLegend(0.5, 0.7, 0.9, 0.9);
  // DCAleg23->AddEntry(DCAhistSim23, "Simulation", "lp");
  // DCAleg23->AddEntry(DCAhistBg23, Form("background (x%e)", scale*3.), "l");
  // DCAleg23->SetFillColor(kWhite);
  // DCAleg23->Draw();
  
  //________________________________________________________
  // DCA K p daughters

  C1->cd(8);
  printf("DCA K p\n");

  TH1D * DCAhist31 = new TH1D("DCA31", "DCA K p", 40, 0., 0.02);
  DCAhist31 -> SetMarkerStyle(kFullDotLarge);
  DCAhist31 ->Sumw2();
  particles->Project("DCA31", "dcaDaugthers31");

  DCAhist31->SetStats(false);

  DCAhist31->GetXaxis()->SetTitle("DCA K p [cm]");
  DCAhist31->Draw("E1");

  // DCAleg31 = new TLegend(0.5, 0.7, 0.9, 0.9);
  // DCAleg31->AddEntry(DCAhistSim31, "Simulation", "lp");
  // DCAleg31->AddEntry(DCAhistBg31, Form("background (x%e)", scale*3.), "l");
  // DCAleg31->SetFillColor(kWhite);
  // DCAleg31->Draw();
  //________________________________________________________
  
  // DCA daughters in pt
  TH1D *DCAhist[4];
  // TLegend *DCAleg[4];
  for (int i = 0; i < 4; ++i)
  {
    C3->cd(i+1);
    pair<float,float> ptLimits(2.*i,2.*i+2.);
    printf("DCA daughters for %.0f < pt < %0.f\n", ptLimits.first, ptLimits.second);

    DCAhist[i] = new TH1D(Form("DCA%d", i), Form("DCA K #pi with %.0f GeV < pt < %.0f GeV", ptLimits.first, ptLimits.second), 40, 0., 0.02);
    DCAhist[i]->Sumw2();
    particles->Project(Form("DCA%d", i), "dcaDaugthers23", Form("%f < pt && pt < %f ", ptLimits.first, ptLimits.second));

    DCAhist[i]->SetStats(false);

    DCAhist[i]->Write();

    DCAhist[i]->GetXaxis()->SetTitle("DCA K #pi [cm]");
    DCAhist[i]->Draw("E1");

    // DCAleg[i] = new TLegend(0.5, 0.7, 0.9, 0.9);
    // DCAleg[i]->AddEntry(DCAhistSim[i], "Simulation", "lp");
    // DCAleg[i]->AddEntry(DCAhistBg[i], Form("background (x%e)", scale*3.), "l");
    // DCAleg[i]->SetFillColor(kWhite);
    // DCAleg[i]->Draw();
  }
  //________________________________________________________
  cout << "Mass plot ..." << endl;
  C4->cd();
  TH1D *massHist = new TH1D("massHist", "#Lambda_{c} mass", 100, 2.0, 2.5);
  TH1D *massHistBkg = new TH1D("massHistBkg", "BG mass", 100, 2.0, 2.5);

  massHistBkg->Sumw2();
  massHist->Sumw2();

  TCut correctSign = "charges > 0";
  TCut wrongSign = "charges < 0";

  particles->Project("massHist", "m", AllCuts && correctSign);
  particles->Project("massHistBkg", "m", AllCuts && wrongSign );

  massHistBkg->Scale(1./3.);

  massHist->GetXaxis()->SetTitle("m (GeV)");
  massHist->GetYaxis()->SetTitle("N");
  massHist->SetStats(false);
  massHist->SetMarkerStyle(kFullDotLarge);
  massHistBkg->SetMarkerStyle(22);
  massHistBkg->SetMarkerColor(kRed);
  massHistBkg->SetLineColor(kRed);

  massHist->Draw("E1");
  massHistBkg->Draw("E1same");



  //________________________________________________________
  // saving
  C1->Write();
  C2->Write();
  C3->Write();
  C4->Write();

  // C1->SaveAs(Form("%s_1new.pdf", outFileName.Data()));
  // C2->SaveAs(Form("%s_2.pdf", outFileName.Data()));
  // C3->SaveAs(Form("%s_3.pdf", outFileName.Data()));
  // C1->SaveAs(Form("%s_1new.png", outFileName.Data()));
  // C1->SaveAs(Form("%s_1new.eps", outFileName.Data()));
  // C2->SaveAs(Form("%s_2.png", outFileName.Data()));
  // C3->SaveAs(Form("%s_3.png", outFileName.Data()));
  
  outF->Close();
}
