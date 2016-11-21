#include<TCanvas.h>
#include<TLine.h>
#include<TH1D.h>
#include<TF1.h>
#include<TFile.h>
#include<TGraph.h>
#include<TGraphAsymmErrors.h>
#include<iostream>
#include<cmath>

using namespace std;

void ratio(double plusMean = 44, double plusSigma = 20, double minusMean = 65, double minusSigma = 15)
{
  TF1 *gausPlus = new TF1("gausPlus", "TMath::Gaus(x, [0], [1])", plusMean - 5*plusSigma, plusMean + 5*plusSigma);
  TF1 *gausMinus   = new TF1("gausMinus",   "TMath::Gaus(x, [0], [1])", minusMean - 5*minusSigma, minusMean + 5*minusSigma);
  gausPlus->SetParameters(plusMean, plusSigma);
  gausMinus->SetParameters(minusMean, minusSigma);

  double pmRatio = plusMean/minusMean;
  double errorEstimate = pmRatio*std::sqrt(plusSigma*plusSigma/(plusMean*plusMean) + minusSigma*minusSigma/(minusMean*minusMean));
  TH1D *ratioHist = new TH1D("ratioHist", "distribution of division", 200, pmRatio - 6*errorEstimate,pmRatio + 6*errorEstimate);
  for (int i = 0; i < 1000000; ++i)
  {
    Double_t randomPlus = gausPlus->GetRandom(); 
    Double_t randomMinus = gausMinus->GetRandom();

    ratioHist->Fill(randomPlus/randomMinus);
  }

  TCanvas *CHist = new TCanvas("CHist", "", 800, 600);
  CHist->cd();

  ratioHist->GetXaxis()->SetTitle("R^{#pm}");
  ratioHist->Draw();

  TLine *l = new TLine(pmRatio, 0, pmRatio, 60000);
  l->SetLineColor(kRed);
  cout << "pmRatio = " << pmRatio << endl;

  double mean = ratioHist->GetMean();
  TLine *lMean = new TLine(mean, 0, mean, 60000);
  lMean->SetLineColor(kBlue);
  cout << "mean = " << mean << endl;

  double maxBin = ratioHist->GetBinCenter(ratioHist->GetMaximumBin());
  cout << "maxBin = " << maxBin << endl;

  TF1 *leftGaus = new TF1("leftGaus", "[1]*TMath::Gaus(x, [2], [0], 0)", pmRatio-5*errorEstimate,pmRatio);
  TF1 *rightGaus = new TF1("rightGaus", "[1]*TMath::Gaus(x, [2], [0], 0)", maxBin, pmRatio+5*errorEstimate);

  leftGaus->SetParameters(errorEstimate, 10000, maxBin);
  leftGaus->SetParName(0,"leftError");
  // leftGaus->FixParameter(2,ratio);
  rightGaus->SetParameters(errorEstimate, 10000, maxBin);
  rightGaus->SetParName(0,"rightError");

  ratioHist->Fit(leftGaus, "", "", pmRatio - 3.*errorEstimate, pmRatio);
  double leftMean = leftGaus->GetParameter(2);
  rightGaus->FixParameter(2,leftMean);
  ratioHist->Fit(rightGaus, "", "", pmRatio, pmRatio + 3.*errorEstimate);

  leftGaus->SetLineColor(kPink);
  rightGaus->SetLineColor(kTeal);
  leftGaus->SetNpx(100000);
  rightGaus->SetNpx(100000);
  leftGaus->Draw("same");
  rightGaus->Draw("same");
  l->Draw("same");
  lMean->Draw("same");

  cout << "R = " << pmRatio << " (+ " << leftMean - pmRatio + rightGaus->GetParameter(0) << " - " << pmRatio - leftMean + leftGaus->GetParameter(0)<< ")" << endl;
  cout << " ... or ... " << endl;
  cout << "R = " << leftMean << " (+ " << rightGaus->GetParameter(0) << " - " << leftGaus->GetParameter(0) << ")" << endl;

}
