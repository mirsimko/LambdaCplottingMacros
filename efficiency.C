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

using std::cout;
using std::endl;

void efficiency()
{
  gStyle->SetOptStat(0);
  gStyle->SetLabelFont(132, "x");
  gStyle->SetLabelFont(132, "y");
  gStyle->SetTitleFont(132, "x");
  gStyle->SetTitleFont(132, "y");
  gStyle->SetLegendFont(132);

  TFile *f = new TFile(Form("Lc.toyMc.%d.root", centrality));
  TNtuple *secondary = static_cast<TNtuple*>(f->Get("secondary"));

  TCanvas *C = new TCanvas("C", "mass plot", 500, 500);
  TH1D* passed = new TH1D("passed", "", 40, 2.1, 2.5);
  TH1D* all = new TH1D("all", "", 40, 2.1, 2.5);
  TH1D* HFT = new TH1D("HFT", "", 40, 2.1, 2.5);

  passed->Sumw2();
  all->Sumw2();
  HFT->Sumw2();

  // -- set cuts
  TCut centralityCut = "centrality < 7"; // centrality 10 - 80 %
  TCut ptCut = "pt > 3";
  TCut 
  TCut allCuts = centralityCut && ptCut;
  TCut centralityWeight = "centralityCorrection";

  // -- fill the histograms
  // -- Drawing
  sig->GetXaxis()->SetTitle("#font[12]{m}_{pK#pi} (GeV/#font[12]{c}^{2})");
  sig->GetXaxis()->CenterTitle();
  sig->GetXaxis()->SetLabelSize(0.04);
  sig->GetXaxis()->SetTitleSize(0.055);
  sig->GetXaxis()->SetTitleOffset(0.8);
  // sig->GetXaxis()->SetTickLength(0.001);
  sig->GetYaxis()->SetTitle("#font[12]{N}/(10 MeV/#font[12]{c}^{2})");
  sig->GetYaxis()->CenterTitle();
  sig->GetYaxis()->SetLabelSize(0.04);
  sig->GetYaxis()->SetTitleSize(0.055);
  sig->GetYaxis()->SetTitleOffset(0.8);
  // sig->GetYaxis()->SetRangeUser(17, 95);

  sig->SetMarkerStyle(20);
  sig->SetLineColor(kBlack);
  bkg->SetMarkerStyle(22);
  bkg->SetMarkerColor(kBlue-7);
  bkg->SetLineColor(kBlue-7);
  bkg->GetFunction("line")->SetLineColor(kRed);
  bkg->GetFunction("line")->SetLineStyle(2);
  bkg->GetFunction("line")->SetNpx(10000);
  
  sig->GetFunction("gaussPlusLine")->SetLineColor(kRed);
  sig->GetFunction("gaussPlusLine")->SetNpx(10000);


  sig->Draw("E");
  bkg->Draw("Esame");

  TLegend *leg = new TLegend(0.6,0.75,0.89,0.89);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(sig, "Correct sign", "pl");
  leg->AddEntry(bkg, "Wrong sign", "pl");
  leg->Draw();

  TLegend *dataSet = new TLegend(0., 0.8, 0.6, 0.89);
  dataSet->SetFillStyle(0);
  dataSet->SetBorderSize(0);
  dataSet->AddEntry("", "#font[22]{Au+Au 200 GeV, 10-80%}","");
  dataSet->AddEntry("","#font[12]{p}_{T} > 3 GeV/#font[12]{c}","");
  dataSet->Draw();

  // --  yield calculation
  const float min = 2.26;
  const float max = 2.31;

  // -- get part of the Gauss curve
  TF1 *normGaus = new TF1("normGaus", "TMath::Gaus(x,[0],[1],1)");
  double mean = gaussPlusLine->GetParameter(3);
  double width= gaussPlusLine->GetParameter(4);
  normGaus->SetParameter(0,mean);
  normGaus->SetParameter(1,width);
  double norm = normGaus->Integral(min, max);

  int minBin = sig->FindBin(min) + 1;
  int maxBin = sig->FindBin(max);
  cout << "integral from " << sig->GetBinCenter(minBin) - 0.005 << " to " << sig->GetBinCenter(maxBin) + 0.005 << endl;
  float NSig = sig->Integral(minBin,maxBin);
  float NBkg = bkg->Integral(minBin, maxBin);
  float Nlc = (NSig - NBkg)/norm;
  float error = std::sqrt(NSig + NBkg/3.)/norm;

  cout << "N Sig = " << NSig << endl;
  cout << "N Bkg = " << NBkg << endl;
  cout << "norm = " << norm << endl;
  cout << "N Lambda_c = " << round(Nlc) << endl;
  cout << "sigma = " << round(error) << endl;
}

