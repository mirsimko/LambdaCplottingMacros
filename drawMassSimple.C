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

void drawMassSimple()
{
  gStyle->SetOptStat(0);
  gStyle->SetLabelFont(132, "x");
  gStyle->SetLabelFont(132, "y");
  gStyle->SetTitleFont(132, "x");
  gStyle->SetTitleFont(132, "y");
  gStyle->SetLegendFont(132);

  TFile *f = new TFile("consistencyChk3GeVcut.root");
  TNtuple *secondary = static_cast<TNtuple*>(f->Get("secondary"));

  TCanvas *C = new TCanvas("C", "mass plot", 500, 500);
  TH1D* sig = new TH1D("sig", "", 40, 2.1, 2.5);
  TH1D* bkg = new TH1D("bkg", "", 40, 2.1, 2.5);

  sig->Sumw2();
  bkg->Sumw2();

  // -- set cuts
  const int LcPlus  = (0 <<2) | (1 <<1) | 1; // K,p,pi
  const int LcMinus = (1 <<2) | (0 <<1) | 0;
  TCut sigCut = Form("charges == %d || charges == %d", LcPlus, LcMinus);
  TCut LcPlusCut = Form("charges == %d", LcPlus);
  const int protonMap = 1 <<1;
  TCut protonCut = Form("(charges & %d) != 0", protonMap);

  TCut centralityCut = "centrality < 7"; // centrality 10 - 80 %
  TCut ptCut = "pt > 3";
  TCut allCuts = centralityCut && ptCut;
  TCut centralityWeight = "centralityCorrection";

  // -- fill the histograms
  secondary->Project("sig", "m", (allCuts && sigCut)*centralityWeight );
  secondary->Project("bkg", "m", (allCuts && !sigCut)*centralityWeight );
  bkg->Scale(1./3.);

  TF1 *line = new TF1("line", "[0] + [1]*x");
  TF1 *gaussPlusLine = new TF1("gaussPlusLine", "[0] + [1]*x + [2]*TMath::Gaus(x,[3],[4],1)");

  bkg->Fit(line, "", "", 2.1, 2.5);
  double offset = line->GetParameter(0);
  double slope = line->GetParameter(1);
  const double LcMass = 2.28646;

  gaussPlusLine->FixParameter(0,offset);
  gaussPlusLine->FixParameter(1,slope);
  gaussPlusLine->SetParameter(3,LcMass);

  gaussPlusLine->SetParameter(2,1);
  gaussPlusLine->SetParameter(4,0.15);

  sig->Fit(gaussPlusLine, "", "", 2.1, 2.5);

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

