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

void DrawCtrlPlots(int decayMode=3)
{
  // 
  // declare variables
  TString outFileName = "ctrlPlots";
  enum DecayMode{kKstar, kLambda, kDelta, kThreeBody};

  DecayMode dm = (DecayMode)decayMode;

  const float simScaleFactor  = 0.0001;
  // cuts
  TCut dLengthCut = "dLength > 0.0150";
  TCut DCApairsCut = "dcaDaugthers12 < 0.0200 && dcaDaugthers23 < 0.0200 && dcaDaugthers31 < 0.0200";
  TCut ptCut = "p3pt > 1.2"; // K, p, pi
  TCut cosThetaCut = "cosPntAngle > 0.998";
  TCut maxVertexDistCut = "maxVertexDist < 0.03";

  TCut AllCuts = dLengthCut && DCApairsCut && ptCut && cosThetaCut && maxVertexDistCut;

  // getting the Ntuple and setting variables for all decay modes
  TFile *readF1 = new TFile("lambdaCTMVAkPionKaonProtonCuts.root");
  TNtuple *particles = (TNtuple*) readF1->Get("ntTMVA");
  TFile *readF2 = new TFile("bgSelectedLc.root");
  TNtuple *bkg =(TNtuple*) readF2->Get("secondarySelected");
  TFile *outF = new TFile( Form("%snew.root", outFileName.Data() ), "RECREATE");
  outF->cd();

  // setting up canvas
  TCanvas *C1 = new TCanvas("C1", "", 1200, 1200);
  C1->Divide(2,4);
  TCanvas *C2 = new TCanvas("C2", "", 1200, 900);
  C2->Divide(2,1);
  TCanvas *C3 = new TCanvas("C3", "", 1200, 900);
  C3->Divide(2,2);

  float scale, maxBkg, maxSim;
  //________________________________________________________
  // fill histograms
  
  
  cout << "Decay length" << endl;
  TH1D *decayLength = new TH1D("decayLength", "Decay length of background" , 40, 0, 0.0400);
  C1->cd(1);
  bkg -> Project("decayLength","dLength");
  decayLength->Write();
  TH1D *dLengthSim = new TH1D("dLengthSimulation", "Decay length of simulation", 40, 0, 0.0400);
  dLengthSim->Sumw2();
  particles->Project("dLengthSimulation", "dLength");
  dLengthSim->Scale(simScaleFactor);
  dLengthSim->SetMarkerStyle(kFullDotLarge);
  dLengthSim->Write();
  dLengthSim->GetXaxis()->SetTitle("decay length [cm]");
  dLengthSim->SetStats(false);
  dLengthSim->SetAxisRange(0,22.,"Y");
  dLengthSim->Draw("E1");
  maxSim = dLengthSim->GetBinContent(dLengthSim->GetMaximumBin() );
  maxBkg = decayLength->GetBinContent(decayLength->GetMaximumBin() );
  scale = maxSim / maxBkg;
  decayLength->Scale(scale);
  decayLength->SetLineColor(kRed);
  decayLength->Draw("same");

  TLegend *dLengthLeg = new TLegend(0.5, 0.7, 0.9, 0.9);
  dLengthLeg->AddEntry(dLengthSim, "Simulation", "lp");
  dLengthLeg->AddEntry(decayLength, Form("Background (x%e)", scale*3.), "l");
  dLengthLeg->SetFillColor(kWhite);
  dLengthLeg->Draw();
  //________________________________________________________

  TH1D *pthist[3];
  TH1D *pthistBkg[3];
  TLegend *ptLeg[3];
  TString partName[3] = {"K", "p", "pi"};
  for (int i = 1; i <= 3; ++i)
  {
    cout << "pt plot #" << i << endl;
    C1->cd(i+1);

    pthist[i-1] = new TH1D(Form("pt%s", partName[i-1].Data() ), Form("simulated p_{T} of %s", partName[i-1].Data()), 50, 0, 6.);
    pthistBkg[i-1] = new TH1D(Form("ptBkg%s", partName[i-1].Data() ),Form("simulated p_{T} of %s", partName[i-1].Data()),  50, 0, 6.);
    pthist[i-1]->Sumw2();
    particles->Project(Form("pt%s", partName[i-1].Data() ), Form("p%dpt", i));
    pthist[i-1]->SetMarkerStyle(kFullDotLarge);
    pthist[i-1]->GetXaxis()->SetTitle("p_{T} [GeV]");
    pthist[i-1]->Scale(simScaleFactor);
    bkg->Project(Form("ptBkg%s", partName[i-1].Data() ), Form("p%dpt", i) );
    pthistBkg[i-1]->SetLineColor(kRed);
    

    pthist[i-1]->Write();
    pthistBkg[i-1]->Write();

    maxSim = pthist[i-1]->GetBinContent(pthist[i-1]->GetMaximumBin() );
    maxBkg = pthistBkg[i-1]->GetBinContent(pthistBkg[i-1]->GetMaximumBin() );
    scale = maxSim/maxBkg;
    pthistBkg[i-1]->Scale(scale);

    pthist[i-1]->SetStats(false);
    pthist[i-1]->Draw("E1");
    pthistBkg[i-1]->Draw("same");

    ptLeg[i-1]= new TLegend(0.5, 0.7, 0.9, 0.9);
    ptLeg[i-1] ->AddEntry(pthist[i-1], "Simulation", "pl");
    ptLeg[i-1] ->AddEntry(pthistBkg[i-1], Form("Background (x%e)", scale*3.), "l");
    ptLeg[i-1] ->SetFillColor(kWhite);
    ptLeg[i-1] -> Draw();

  }
  //________________________________________________________
  cout << "cos(theta)" << endl;
  TH1D *cosTheta = new TH1D("cosTheta", "cos(#theta)"  , 20, 0.98, 1.);
  C1->cd(5);
  cosTheta->Sumw2();
  particles -> Project("cosTheta", "cosPntAngle");
  cosTheta->SetMarkerStyle(kFullDotLarge);
  cosTheta->GetXaxis()->SetTitle("cos(#theta)");
  cosTheta->Scale(simScaleFactor);
  cosTheta->Write();

  TH1D *cosThetaBkg = new TH1D("cosThetaBkg", "cos(#theta)", 20, 0.98, 1.);
  bkg -> Project("cosThetaBkg", "cosPntAngle");
  cosThetaBkg->SetLineColor(kRed);
  maxSim = cosTheta->GetBinContent(cosTheta->GetMaximumBin() );
  maxBkg = cosThetaBkg->GetBinContent(cosThetaBkg->GetMaximumBin() );
  scale = maxSim / maxBkg;
  cosThetaBkg->Scale(scale);
  cosTheta->SetStats(false);
  cosTheta->Draw("E1");
  cosThetaBkg->Draw("same");

  TLegend *legCosTheta = new TLegend(0.1, 0.7, 0.5, 0.9);
  legCosTheta->AddEntry(cosTheta, "Simulation", "pl");
  legCosTheta->AddEntry(cosThetaBkg, Form("Background (x%e)", scale*3.), "l");
  legCosTheta->SetFillColor(kWhite);
  legCosTheta->Draw();

  //________________________________________________________
  cout << "Maximum distance" << endl;
  C1->cd(6);
  TH1D *vDist = new TH1D("vDist", "Maximum distance between vertices of pairs", 60, 0, 0.0600);
  TH1D *vDistBkg = new TH1D("vDistBkg", "Maximum distance between vertices of pairs background", 60, 0, 0.0600);

  vDist->Sumw2();
  particles->Project("vDist", "maxVertexDist");
  vDist->SetMarkerStyle(kFullDotLarge);
  bkg->Project("vDistBkg", "maxVertexDist");
  vDist->Scale(simScaleFactor);
  vDist->Write();
  vDistBkg->SetLineColor(kRed);
  vDistBkg->Write();

  vDist->SetStats(false);
  maxSim = vDist->GetBinContent(vDist->GetMaximumBin() );
  maxBkg = vDistBkg->GetBinContent( vDistBkg->GetMaximumBin() );
  scale = maxSim / maxBkg;
  vDistBkg->Scale(scale);

  vDist->Draw("E1");
  vDistBkg->Draw("same");

  TLegend *vDistLeg = new TLegend(0.5, 0.7, 0.9, 0.9);
  vDistLeg->AddEntry(vDist, "Simulation", "lp");
  vDistLeg->AddEntry(vDistBkg, Form("background (x%e)", scale*3.), "l");
  vDistLeg->SetFillColor(kWhite);
  vDistLeg->Draw();
  
  //________________________________________________________
  // DCA K pi daughters

  TH1D *DCAhistBg23;
  TH1D *DCAhistSim23;
  TLegend *DCAleg23;

  C1->cd(7);
  printf("DCA K pi\n");

  DCAhistSim23 = new TH1D("DCAsim23", "DCA K #pi", 40, 0., 0.02);
  DCAhistSim23 ->Sumw2();
  DCAhistSim23 -> SetMarkerStyle(kFullDotLarge);
  particles->Project("DCAsim23", "dcaDaugthers23");

  DCAhistBg23 = new TH1D("DCAbg23", "DCA K #pi", 40, 0., 0.02);
  bkg->Project("DCAbg23", "dcaDaugthers23");

  DCAhistBg23->SetLineColor(kRed);
  DCAhistSim23->SetStats(false);

  DCAhistSim23->Scale(simScaleFactor);
  DCAhistSim23->Write();
  DCAhistBg23->Write();
  maxSim = DCAhistSim23->Integral();
  maxBkg = DCAhistBg23->Integral();
  scale = maxSim / maxBkg;
  DCAhistBg23->Scale(scale);

  DCAhistSim23->GetXaxis()->SetTitle("DCA K #pi [cm]");
  DCAhistSim23->Draw("E1");
  DCAhistBg23->Draw("same");

  DCAleg23 = new TLegend(0.5, 0.7, 0.9, 0.9);
  DCAleg23->AddEntry(DCAhistSim23, "Simulation", "lp");
  DCAleg23->AddEntry(DCAhistBg23, Form("background (x%e)", scale*3.), "l");
  DCAleg23->SetFillColor(kWhite);
  DCAleg23->Draw();
  
  TH1D *DCAhistBg23;
  TH1D *DCAhistSim23;
  TLegend *DCAleg23;

  //________________________________________________________
  // DCA K p daughters

  C1->cd(8);
  printf("DCA K p\n");

  DCAhistSim31 = new TH1D("DCAsim31", "DCA K p", 40, 0., 0.02);
  DCAhistSim31 -> SetMarkerStyle(kFullDotLarge);
  DCAhistSim31 ->Sumw2();
  particles->Project("DCAsim31", "dcaDaugthers31");

  DCAhistBg31 = new TH1D("DCAbg31", "DCA K p", 40, 0., 0.02);
  bkg->Project("DCAbg31", "dcaDaugthers31");

  DCAhistBg31->SetLineColor(kRed);
  DCAhistSim31->SetStats(false);

  DCAhistSim31->Scale(simScaleFactor);
  DCAhistSim31->Write();
  DCAhistBg31->Write();
  maxSim = DCAhistSim31->Integral();
  maxBkg = DCAhistBg31->Integral();
  scale = maxSim / maxBkg;
  DCAhistBg31->Scale(scale);

  DCAhistSim31->GetXaxis()->SetTitle("DCA K p [cm]");
  DCAhistSim31->Draw("E1");
  DCAhistBg31->Draw("same");

  DCAleg31 = new TLegend(0.5, 0.7, 0.9, 0.9);
  DCAleg31->AddEntry(DCAhistSim31, "Simulation", "lp");
  DCAleg31->AddEntry(DCAhistBg31, Form("background (x%e)", scale*3.), "l");
  DCAleg31->SetFillColor(kWhite);
  DCAleg31->Draw();
  //________________________________________________________
  // DCA daughters in pt
  TH1D *DCAhistBg[4];
  TH1D *DCAhistSim[4];
  TLegend *DCAleg[4];
  for (int i = 0; i < 4; ++i)
  {
    C3->cd(i+1);
    pair<float,float> ptLimits(2.*i,2.*i+2.);
    printf("DCA daughters for %.0f < pt < %0.f\n", ptLimits.first, ptLimits.second);

    DCAhistSim[i] = new TH1D(Form("DCAsim%d", i), Form("DCA K #pi with %.0f GeV < pt < %.0f GeV", ptLimits.first, ptLimits.second), 40, 0., 0.02);
    DCAhistSim[i]->Sumw2();
    particles->Project(Form("DCAsim%d", i), "dcaDaugthers23", Form("%f < pt && pt < %f ", ptLimits.first, ptLimits.second));

    DCAhistBg[i] = new TH1D(Form("DCAbg%d", i), Form("DCA K #pi with %.0f GeV < pt < %.0f GeV", ptLimits.first, ptLimits.second), 40, 0., 0.02);
    bkg->Project(Form("DCAbg%d", i), "dcaDaugthers23", Form("%f < pt && pt < %f", ptLimits.first, ptLimits.second));

    DCAhistBg[i]->SetLineColor(kRed);
    DCAhistSim[i]->SetStats(false);

    DCAhistSim[i]->Scale(simScaleFactor);
    DCAhistSim[i]->Write();
    DCAhistBg[i]->Write();
    maxSim = DCAhistSim[i]->Integral();
    maxBkg = DCAhistBg[i]->Integral();
    scale = maxSim / maxBkg;
    DCAhistBg[i]->Scale(scale);

    DCAhistSim[i]->GetXaxis()->SetTitle("DCA K #pi [cm]");
    DCAhistSim[i]->Draw("E1");
    DCAhistBg[i]->Draw("same");

    DCAleg[i] = new TLegend(0.5, 0.7, 0.9, 0.9);
    DCAleg[i]->AddEntry(DCAhistSim[i], "Simulation", "lp");
    DCAleg[i]->AddEntry(DCAhistBg[i], Form("background (x%e)", scale*3.), "l");
    DCAleg[i]->SetFillColor(kWhite);
    DCAleg[i]->Draw();
  }

  //________________________________________________________
  // saving
  C1->Write();
  // C2->Write();
  C3->Write();

  C1->SaveAs(Form("%s_1new.pdf", outFileName.Data()));
  // C2->SaveAs(Form("%s_2.pdf", outFileName.Data()));
  // C3->SaveAs(Form("%s_3.pdf", outFileName.Data()));
  C1->SaveAs(Form("%s_1new.png", outFileName.Data()));
  C1->SaveAs(Form("%s_1new.eps", outFileName.Data()));
  // C2->SaveAs(Form("%s_2.png", outFileName.Data()));
  // C3->SaveAs(Form("%s_3.png", outFileName.Data()));
  
  outF->Close();
}
