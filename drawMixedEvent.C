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
#include "TH2F.h"
#include "TF1.h"
#include "TLegend.h"
#include "TColor.h"
#include "TROOT.h"
#include "TText.h"
#include "TString.h"
#include "string"

using std::cout;
using std::endl;

void drawMixedEvent()
{
  gStyle->SetOptStat(0);
  gStyle->SetLabelFont(132, "x");
  gStyle->SetLabelFont(132, "y");
  gStyle->SetTitleFont(132, "x");
  gStyle->SetTitleFont(132, "y");
  gStyle->SetLegendFont(132);

  TFile *f = new TFile("2017-05-11_14-53.MixedEvent.root");

  TCanvas *C = new TCanvas("C", "mass plot", 500, 500);
  TH1D* sig = new TH1D("sig", "", 40, 2.1, 2.5);
  TH1D* bkgSELS = new TH1D("bkgSELS", "", 40, 2.1, 2.5);
  TH1D* bkgMEUS = new TH1D("bkgMEUS", "", 40, 2.1, 2.5);
  TH1D* bkgMELS = new TH1D("bkgSELS", "", 40, 2.1, 2.5);

  for (int iCent = 0; iCent <= 6; ++iCent)
  {
    for (int iVz = 0; iVz < 10; ++iVz)
    {
      std::string baseName = Form("Cent_%i_Vz_%i",iCent,iVz);

      TH2F* hSE_LS = static_cast<TH2F*>(f->Get(Form("%s_se_ls_mass", baseName.data())));
      TH2F* hSE_US = static_cast<TH2F*>(f->Get(Form("%s_se_us_mass", baseName.data())));
      TH2F* hME_LS = static_cast<TH2F*>(f->Get(Form("%s_me_ls_mass", baseName.data())));
      TH2F* hME_US = static_cast<TH2F*>(f->Get(Form("%s_me_us_mass", baseName.data())));

      TH1D* massProj_SE_LS = hSE_LS->ProjectionY(Form("%s_se_ls_mass_proj", baseName.data()));
      TH1D* massProj_SE_US = hSE_US->ProjectionY(Form("%s_se_us_mass_proj", baseName.data()));
      TH1D* massProj_ME_LS = hME_LS->ProjectionY(Form("%s_me_ls_mass_proj", baseName.data()));
      TH1D* massProj_ME_US = hME_US->ProjectionY(Form("%s_me_us_mass_proj", baseName.data()));

      // add the bin content
      const int firstBin = 210;
      for (int iBin = 0; iBin < 40; ++iBin)
      {
	sig->SetBinContent(iBin+1, massProj_SE_US->GetBinContent(iBin+firstBin+1));
	bkgSELS->SetBinContent(iBin+1, massProj_SE_LS->GetBinContent(iBin+firstBin+1));
	bkgMEUS->SetBinContent(iBin+1, massProj_ME_US->GetBinContent(iBin+firstBin+1));
	bkgMELS->SetBinContent(iBin+1, massProj_ME_LS->GetBinContent(iBin+firstBin+1));

	sig->SetBinError(iBin+1, sqrt(sig->GetBinContent(iBin+1)));
	bkgSELS->SetBinError(iBin+1, sqrt(bkgSELS->GetBinContent(iBin+1)));
	bkgMEUS->SetBinError(iBin+1, sqrt(bkgMEUS->GetBinContent(iBin+1)));
	bkgMELS->SetBinError(iBin+1, sqrt(bkgMELS->GetBinContent(iBin+1)));
      }
    }
  }
  bkgSELS->Scale(1./3.);
  bkgMEUS->Scale(1./6.);
  bkgMELS->Scale(1./(6. * 3.));

  TF1 *line = new TF1("line", "[0] + [1]*x");
  TF1 *gaussPlusLine = new TF1("gaussPlusLine", "[0] + [1]*x + [2]*TMath::Gaus(x,[3],[4],1)");

  bkgMEUS->Fit(line, "", "", 2.1, 2.5);
  double offset = line->GetParameter(0);
  double slope = line->GetParameter(1);
  const double LcMass = 2.28646;

  gaussPlusLine->FixParameter(0,offset);
  gaussPlusLine->FixParameter(1,slope);
  gaussPlusLine->FixParameter(3,LcMass);

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

  bkgMEUS->SetMarkerStyle(21);
  bkgMEUS->SetMarkerColor(kOrange+5);
  bkgMEUS->SetLineColor(kOrange+5);
  bkgMEUS->GetFunction("line")->SetLineColor(kRed);
  bkgMEUS->GetFunction("line")->SetLineStyle(2);
  bkgMEUS->GetFunction("line")->SetNpx(10000);

  bkgSELS->SetMarkerStyle(22);
  bkgSELS->SetMarkerColor(kBlue-7);
  bkgSELS->SetLineColor(kBlue-7);

  bkgMELS->SetMarkerStyle(23);
  bkgMELS->SetMarkerColor(kGreen+2);
  bkgMELS->SetLineColor(kGreen+2);
  
  sig->GetFunction("gaussPlusLine")->SetLineColor(kRed);
  sig->GetFunction("gaussPlusLine")->SetNpx(10000);


  sig->Draw("E");
  bkgMEUS->Draw("Esame");
  bkgSELS->Draw("Esame");
  bkgMELS->Draw("Esame");

  TLegend *leg = new TLegend(0.6,0.65,0.89,0.89);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(sig, "Same event correct sign", "pl");
  leg->AddEntry(bkgSELS, "Same event wrong sign", "pl");
  leg->AddEntry(bkgMEUS, "Mixed event correct sign", "pl");
  leg->AddEntry(bkgMELS, "Mixed event wrong sign", "pl");
  leg->Draw();

  TLegend *dataSet = new TLegend(0., 0.7, 0.6, 0.89);
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
  float NBkg = bkgMEUS->Integral(minBin, maxBin);
  float Nlc = (NSig - NBkg)/norm;
  float error = std::sqrt(NSig + NBkg/3.)/norm;

  cout << "N Sig = " << NSig << endl;
  cout << "N Bkg = " << NBkg << endl;
  cout << "norm = " << norm << endl;
  cout << "N Lambda_c = " << round(Nlc) << endl;
  cout << "sigma = " << round(error) << endl;
}

