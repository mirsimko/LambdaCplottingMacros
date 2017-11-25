/* ************************************************** *
 * Not so simple macro for plotting of invarant mass  *
 * of the Lambda_c baryon from an ntuple              *
 * ************************************************** */
#include <iostream>
#include <cmath>

#include "TStyle.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCut.h"
#include "TF1.h"
#include "TLegend.h"
#include "TColor.h"
#include "TROOT.h"
#include "TText.h"
#include "TString.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

using std::cout;
using std::endl;

void efficiency(int centrality = 0)
{
  gStyle->SetOptStat(0);
  gStyle->SetLabelFont(132, "x");
  gStyle->SetLabelFont(132, "y");
  gStyle->SetTitleFont(132, "x");
  gStyle->SetTitleFont(132, "y");
  gStyle->SetLegendFont(132);

  TFile *f = new TFile(Form("2017-10-31-02:30:54/Lc.toyMc.%d.root", centrality));
  TNtuple *nt = static_cast<TNtuple*>(f->Get("nt"));

  string outFileName = Form("efficiency_cent%d.root", centrality);
  TFile *outFile = new TFile(outFileName.c_str(), "recreate");

  TCanvas *CAll = new TCanvas("CAll", "all", 400, 600);
  TCanvas *Ctpc = new TCanvas("Ctpc", "TPC", 400, 600);
  TCanvas *Chft = new TCanvas("Chft", "HFT", 400, 600);
  TCanvas *Cpassed = new TCanvas("Cpassed", "passed", 400, 600);
  TCanvas *Ceff = new TCanvas("Ceff", "Efficiency", 400, 600);
  TCanvas *CtpcRatio = new TCanvas("CtpcRatio", "TPC ratio", 400, 600);
  TCanvas *ChftRatio = new TCanvas("ChftRatio", "HFT ratio", 400, 600);
  const int nBins = 6;
  const float min = 2;
  const float max = 8;
  // -- histos
  TH1D* passed = new TH1D("passed", "all cuts", nBins, min, max	);
  TH1D* all =    new TH1D("all",    "all Lc",   nBins, min, max	);
  TH1D* HFT =    new TH1D("HFT",    "HFT Lc",   nBins, min, max	);
  TH1D* TPC =    new TH1D("TPC",    "TPC Lc",   nBins, min, max	);
  // -- efficiencies
  TGraphAsymmErrors* eff = new TGraphAsymmErrors(6);
  TGraphAsymmErrors *hftRatio = new TGraphAsymmErrors(6);
  TGraphAsymmErrors *tpcRatio = new TGraphAsymmErrors(6);

  passed->Sumw2();
  all->Sumw2();
  HFT->Sumw2();
  TPC->Sumw2();

  // -- set cuts
  // -- Constatns
  // -- LambdaC
  const float LCdcaDaughtersMax = 0.005;   // maximum 300um
  const float LCdecayLengthMin  = 0.0234;  // minimum  60um
  const float LCdecayLengthMax  = 9999.;
  const float LCcosThetaMin     = 0.995;   // minimum
  const float LCminMass         = 0.;
  const float LCmaxMass         = 3.;
  const float LCdcaToPv         = 0.01;

  // -- daughters
  const float etaMax = 1.;
  const float pTmin = 0.5;
  const float piDcaMin = 0.0065;
  const float kDcaMin = 0.0096;
  const float pDcaMin = 0.0075;

  // -- Cuts
  // -- LambdaC
  const float cmToUm = 10000.;
  const TCut dcaDaughtersCut   = Form("dcaDaughters < %f", LCdcaDaughtersMax*cmToUm);
  const TCut decayLengthMinCut = Form("decayLength > %f", LCdecayLengthMin*cmToUm);
  const TCut decayLengthMaxCut = Form("decayLength < %f", LCdecayLengthMax*cmToUm); // excluded for now
  const TCut cosThetaMinCut    = Form("cosTheta > %f", LCcosThetaMin);
  const TCut dcaToPvMaxCut     = Form("dcaLcToPv < %f", LCdcaToPv*cmToUm);

  // -- daughters
  const TCut ptMinCut           = Form("kRPt > %f && pRPt > %f && piRPt > %f", pTmin, pTmin, pTmin);
  const TCut etaMaxCut          = Form("kREta < %f && pREta < %f && piREta < %f", etaMax, etaMax, etaMax);
  const TCut daughtersDcaMinCut = Form("kRDca > %f && pRDca > %f && piRDca > %f", kDcaMin*cmToUm, pDcaMin*cmToUm, piDcaMin*cmToUm);
  const TCut TpcCut             = "piTpc > 0.5 && pTpc > 0.5 && kTpc > 0.5"; // all tracks are TPC tracks
  const TCut HftCut             = "piHft > 0.5 && pHft > 0.5 && kHft > 0.5"; // all tracks are HFT tracks

  // -- combine the cuts
  TCut allCuts = dcaDaughtersCut && decayLengthMinCut && cosThetaMinCut && ptMinCut && etaMaxCut && daughtersDcaMinCut && TpcCut && HftCut;
  TCut hftCuts = ptMinCut && etaMaxCut && TpcCut && HftCut;
  TCut tpcCuts = ptMinCut && etaMaxCut && TpcCut;

  // -- binning
  float ptBin[5] = {2., 3., 4., 6., 8.};

  // -- fill the histograms
  cout << "Filling \"all\" ..." << endl;
  nt->Project("all", "pt");
  cout << "Filling \"TPC\" ..." << endl;
  nt->Project("TPC", "rPt", tpcCuts);
  cout << "Filling \"hft\" ..." << endl;
  nt->Project("HFT", "rPt", hftCuts);
  cout << "Filling \"passed\" ..." << endl;
  nt->Project("passed", "rPt", allCuts);

  // -- set overflow and underflow bins to 0
  all->SetBinContent(0,0);
  all->SetBinContent(7,0);
  TPC->SetBinContent(0,0);
  TPC->SetBinContent(7,0);
  HFT->SetBinContent(0,0);
  HFT->SetBinContent(7,0);
  passed->SetBinContent(0,0);
  passed->SetBinContent(7,0);

  // calculate efficiencies
  eff->BayesDivide(passed, all);
  tpcRatio->BayesDivide(TPC, all);
  hftRatio->BayesDivide(HFT, all);

  // -- Drawing
  all->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
  TPC->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
  HFT->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
  passed->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
  eff->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
  tpcRatio->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
  hftRatio->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");

  CAll->cd();
  all->Draw();
  Ctpc->cd();
  TPC->Draw();
  Chft->cd();
  HFT->Draw();
  Cpassed->cd();
  passed->Draw();

  Ceff->cd();
  eff->SetMarkerStyle(20);
  eff->Draw("ap");
  CtpcRatio->cd();
  tpcRatio->SetMarkerStyle(20);
  tpcRatio->Draw("ap");
  ChftRatio->cd();
  hftRatio->SetMarkerStyle(20);
  hftRatio->Draw("ap");

  // saving
  cout << "Writing into file " << outFileName << endl;
  outFile->cd();
  all->Write();
  TPC->Write();
  HFT->Write();
  passed->Write();
  eff->Write();
  tpcRatio->Write();
  hftRatio->Write();

  // sig->GetXaxis()->SetTitle("#font[12]{m}_{pK#pi} (GeV/#font[12]{c}^{2})");
  // sig->GetXaxis()->CenterTitle();
  // sig->GetXaxis()->SetLabelSize(0.04);
  // sig->GetXaxis()->SetTitleSize(0.055);
  // sig->GetXaxis()->SetTitleOffset(0.8);
  // // sig->GetXaxis()->SetTickLength(0.001);
  // sig->GetYaxis()->SetTitle("#font[12]{N}/(10 MeV/#font[12]{c}^{2})");
  // sig->GetYaxis()->CenterTitle();
  // sig->GetYaxis()->SetLabelSize(0.04);
  // sig->GetYaxis()->SetTitleSize(0.055);
  // sig->GetYaxis()->SetTitleOffset(0.8);
  // // sig->GetYaxis()->SetRangeUser(17, 95);
  //
  // sig->SetMarkerStyle(20);
  // sig->SetLineColor(kBlack);
  // bkg->SetMarkerStyle(22);
  // bkg->SetMarkerColor(kBlue-7);
  // bkg->SetLineColor(kBlue-7);
  // bkg->GetFunction("line")->SetLineColor(kRed);
  // bkg->GetFunction("line")->SetLineStyle(2);
  // bkg->GetFunction("line")->SetNpx(10000);
  //
  // sig->GetFunction("gaussPlusLine")->SetLineColor(kRed);
  // sig->GetFunction("gaussPlusLine")->SetNpx(10000);
  //
  //
  // sig->Draw("E");
  // bkg->Draw("Esame");
  //
  // TLegend *leg = new TLegend(0.6,0.75,0.89,0.89);
  // leg->SetFillStyle(0);
  // leg->SetBorderSize(0);
  // leg->AddEntry(sig, "Correct sign", "pl");
  // leg->AddEntry(bkg, "Wrong sign", "pl");
  // leg->Draw();
  //
  // TLegend *dataSet = new TLegend(0., 0.8, 0.6, 0.89);
  // dataSet->SetFillStyle(0);
  // dataSet->SetBorderSize(0);
  // dataSet->AddEntry("", "#font[22]{Au+Au 200 GeV, 10-80%}","");
  // dataSet->AddEntry("","#font[12]{p}_{T} > 3 GeV/#font[12]{c}","");
  // dataSet->Draw();
}

