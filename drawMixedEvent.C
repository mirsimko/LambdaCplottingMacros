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
using std::cerr;
using std::endl;

const float minPt = 3.;
const float maxPt = 6.;

const int minCent = 3;
const int maxCent = 7;
//--------------------------------------------------
float addErrors(float first, float second)
{
  return sqrt(first*first + second*second);
}
//--------------------------------------------------
float roundToPreviousBin(float number, int nBins = 40, float min = 2.1, float max = 2.5)
{
  float binStep = (max - min) / static_cast<float>(nBins);
  float prevBinNumber = floor(( number - min ) / binStep);

  return min + binStep*prevBinNumber;
}
//--------------------------------------------------
float roundToNextBin(float number, int nBins = 40, float min = 2.1, float max = 2.5)
{
  float binStep = (max - min) / static_cast<float>(nBins);
  float nextBinNumber = ceil(( number - min ) / binStep);

  return min + binStep*nextBinNumber;
}
//--------------------------------------------------

void drawMixedEvent()
{
  gStyle->SetOptStat(0);
  gStyle->SetLabelFont(132, "x");
  gStyle->SetLabelFont(132, "y");
  gStyle->SetTitleFont(132, "x");
  gStyle->SetTitleFont(132, "y");
  gStyle->SetLegendFont(132);

  TFile *f = new TFile("mixedEventSeparatedByCharge.root");

  const float massFrom = 0;
  const float massTo = 3;
  const float fixedBinWidth = 0.01;
  const int massNBins = (massTo - massFrom) / fixedBinWidth;

  TCanvas *C = new TCanvas("C", "mass plot", 500, 500);
  TH1D* sig = new TH1D("sig", "", massNBins, massFrom, massTo);
  TH1D* bkgSELS = new TH1D("bkgSELS", "", massNBins, massFrom, massTo);
  TH1D* bkgMEUS = new TH1D("bkgMEUS", "", massNBins, massFrom, massTo);
  TH1D* bkgMELS = new TH1D("bkgMELS", "", massNBins, massFrom, massTo);

  //--------------------------------------------------
  for (int iCent = minCent; iCent < maxCent; ++iCent)
  {
    for (int iVz = 0; iVz < 10; ++iVz)
    {
      std::string baseName = Form("Cent_%i_Vz_%i",iCent,iVz);

      TH2F* hSE_LS = static_cast<TH2F*>(f->Get(Form("%s_se_ls_mass", baseName.data())));
      TH2F* hSE_US_plus = static_cast<TH2F*>(f->Get(Form("%s_se_us_plus_mass", baseName.data())));
      TH2F* hSE_US_minus = static_cast<TH2F*>(f->Get(Form("%s_se_us_minus_mass", baseName.data())));
      TH2F* hME_LS = static_cast<TH2F*>(f->Get(Form("%s_me_ls_mass", baseName.data())));
      TH2F* hME_US_plus = static_cast<TH2F*>(f->Get(Form("%s_me_us_plus_mass", baseName.data())));
      TH2F* hME_US_minus = static_cast<TH2F*>(f->Get(Form("%s_me_us_minus_mass", baseName.data())));

      const int firstPtBin = 10.*minPt + 1;
      cout << "first bin " << firstPtBin << endl;
      const int lastPtBin = 10.*maxPt;
      cout << "last bin " << lastPtBin << endl;

      TH1D* massProj_SE_LS = hSE_LS->ProjectionY(Form("%s_se_ls_mass_proj", baseName.data()), firstPtBin, lastPtBin);
      TH1D* massProj_SE_US_plus = hSE_US_plus->ProjectionY(Form("%s_se_us_plus_mass_proj", baseName.data()), firstPtBin, lastPtBin);
      TH1D* massProj_SE_US_minus = hSE_US_minus->ProjectionY(Form("%s_se_us_minus_mass_proj", baseName.data()), firstPtBin, lastPtBin);
      TH1D* massProj_ME_LS = hME_LS->ProjectionY(Form("%s_me_ls_mass_proj", baseName.data()), firstPtBin, lastPtBin);
      TH1D* massProj_ME_US_plus = hME_US_plus->ProjectionY(Form("%s_me_us_plus_mass_proj", baseName.data()), firstPtBin, lastPtBin);
      TH1D* massProj_ME_US_minus = hME_US_minus->ProjectionY(Form("%s_me_us_minus_mass_proj", baseName.data()), firstPtBin, lastPtBin);

      // add the bin content
      const int firstBin = massFrom / fixedBinWidth;
      for (int iBin = 0; iBin < massNBins; ++iBin)
      {
	const int histBin = iBin+1;
	const int movedBin = firstBin + iBin + 1;

	sig->SetBinContent(histBin, massProj_SE_US_plus->GetBinContent(movedBin) + sig->GetBinContent(histBin));
	sig->SetBinContent(histBin, massProj_SE_US_minus->GetBinContent(movedBin) + sig->GetBinContent(histBin));
	bkgSELS->SetBinContent(histBin, massProj_SE_LS->GetBinContent(movedBin) + bkgSELS->GetBinContent(histBin));
	bkgMEUS->SetBinContent(histBin, massProj_ME_US_plus->GetBinContent(movedBin) + bkgMEUS->GetBinContent(histBin));
	bkgMEUS->SetBinContent(histBin, massProj_ME_US_minus->GetBinContent(movedBin) + bkgMEUS->GetBinContent(histBin));
	bkgMELS->SetBinContent(histBin, massProj_ME_LS->GetBinContent(movedBin) + bkgMELS->GetBinContent(histBin));

	sig->SetBinError(histBin, addErrors(sig->GetBinError(histBin), massProj_SE_US_plus->GetBinError(movedBin)) );
	sig->SetBinError(histBin, addErrors(sig->GetBinError(histBin), massProj_SE_US_minus->GetBinError(movedBin)) );
	bkgSELS->SetBinError(histBin, addErrors(bkgSELS->GetBinError(histBin), massProj_SE_LS->GetBinError(movedBin)) );
	bkgMEUS->SetBinError(histBin, addErrors(bkgMEUS->GetBinError(histBin), massProj_ME_US_plus->GetBinError(movedBin)) );
	bkgMEUS->SetBinError(histBin, addErrors(bkgMEUS->GetBinError(histBin), massProj_ME_US_minus->GetBinError(movedBin)) );
	bkgMELS->SetBinError(histBin, addErrors(bkgMELS->GetBinError(histBin), massProj_ME_LS->GetBinError(movedBin)) );
      }
    }
  }
  //--------------------------------------------------
  const float sigma = 7.76446e-03; // taken from fit of the whole dataset +-3.64310e-03
  const float meanInclusive = 2.28359; // +-2.14540e-03
  const float nSigma = 8.;
  const float sideBandTo = roundToPreviousBin(meanInclusive - nSigma*sigma, massNBins, massFrom, massTo);
  const float sideBandFrom = roundToNextBin(meanInclusive + nSigma*sigma, massNBins, massFrom, massTo);

  const float sideBand = sig->Integral(massFrom, sideBandTo) + sig->Integral(sideBandFrom, massTo);
  cout << "Side-band yield = " << sideBand << endl;

  // scaling the mixed event BKG by the yield of the side-band
  float sideBandYield = 0;
  float mixedSideBandYield = 0;
  for (int i = 0; i < massNBins; ++i)
  {
    const float binCenter = sig->GetXaxis()->GetBinCenter(i+1);
    if(binCenter < sideBandTo || binCenter > sideBandFrom)
    {
      sideBandYield += sig->GetBinContent(i+1);
      mixedSideBandYield += bkgMEUS->GetBinContent(i+1);
    }

  }
  TH1D* sideBandMarker = new TH1D("sideBandMarker","marker for the sideband in the form of a histogram", massNBins, massFrom, massTo);
  const float binWidth = (massTo - massFrom) / static_cast<float>(massNBins);
  for(int i = 0; i < massNBins; ++i)
    sideBandMarker->SetBinContent(i+1, 1000);
  for(float bin = sideBandTo; bin < sideBandFrom; bin += binWidth)
  {
    // cout << bin << endl;
    sideBandMarker->Fill(bin + 0.5*binWidth, -1e6);
  }
  sideBandMarker->SetFillColor(kRed);
  sideBandMarker->SetFillStyle(3004);
  sideBandMarker->SetLineColorAlpha(kRed,0);

  bkgSELS->Scale(1./3.);
  cout << "Scaling mixed event bg by " << sideBandYield / mixedSideBandYield << endl;
  bkgMEUS->Scale(sideBandYield / (mixedSideBandYield) );

  TF1 *line = new TF1("line", "[0] + [1]*x");
  TF1 *gaussPlusLine = new TF1("gaussPlusLine", "[0] + [1]*x + [2]*TMath::Gaus(x,[3],[4],1)");

  bkgMEUS->Fit(line, "", "", 2.1, 2.5);
  double offset = line->GetParameter(0);
  double slope = line->GetParameter(1);
  const double LcMass = 2.28646;

  gaussPlusLine->FixParameter(0,offset);
  gaussPlusLine->FixParameter(1,slope);
  gaussPlusLine->SetParameter(3,LcMass);

  gaussPlusLine->SetParameter(2,1);
  gaussPlusLine->SetParameter(4,sigma);

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

  sig->GetXaxis()->SetRangeUser(2.1,2.5);
  sig->Draw("E");
  bkgMEUS->Draw("Esame");
  bkgSELS->Draw("Esame");
  // bkgMELS->Draw("Esame");

  TLegend *leg = new TLegend(0.5,0.6,0.89,0.8);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(sig, "Same event correct sign", "pl");
  leg->AddEntry(bkgSELS, "Same event wrong sign", "pl");
  leg->AddEntry(bkgMEUS, "Mixed event correct sign", "pl");
  // leg->AddEntry(bkgMELS, "Mixed event wrong sign", "pl");
  leg->Draw();
  // sideBandMarker->Draw("same BAR");

  TLegend *dataSet = new TLegend(0., 0.7, 0.4, 0.89);
  dataSet->SetFillStyle(0);
  dataSet->SetBorderSize(0);
  dataSet->AddEntry("", "#font[22]{Au+Au 200 GeV, 10-60%}","");
  dataSet->AddEntry("",Form("%1.0f GeV/#font[12]{c} < #font[12]{p}_{T} < %1.0f GeV/#font[12]{c}", minPt, maxPt),"");
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
  float error = std::sqrt(NSig/norm);

  cout << "N Sig = " << NSig << endl;
  cout << "N Bkg = " << NBkg << endl;
  cout << "norm = " << norm << endl;
  cout << "N Lambda_c = " << Nlc << endl;
  cout << "sigma = " << error << endl;
}
//--------------------------------------------------
