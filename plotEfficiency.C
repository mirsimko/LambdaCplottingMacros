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
#include "TVectorD.h"

using std::cout;
using std::endl;

// -- binning
const int nBin = 1;
float ptBin[nBin+1] = {3., 6.};

const float firstCent = 0;
const float lastCent = 6;

//--------------------------------------------------
float addErrors(float first, float second)
{
  return sqrt(first*first + second*second);
}
//--------------------------------------------------

void plotEfficiency()
{
  // -- style
  gStyle->SetOptStat(0);
  gStyle->SetLabelFont(132, "x");
  gStyle->SetLabelFont(132, "y");
  gStyle->SetTitleFont(132, "x");
  gStyle->SetTitleFont(132, "y");
  gStyle->SetLegendFont(132);


  string outFileName = "efficiency_result_10-60cent.root";
  TFile *outFile = new TFile(outFileName.c_str(), "recreate");

  TCanvas *Ceff = new TCanvas("Ceff", "Efficiency", 400, 600);
  TCanvas *CtpcRatio = new TCanvas("CtpcRatio", "TPC ratio", 400, 600);
  TCanvas *ChftRatio = new TCanvas("ChftRatio", "HFT ratio", 400, 600);
  
  // -- efficiencies
  double effX[nBin], effY[nBin], effXL[nBin], effXH[nBin], effYL[nBin], effYH[nBin];
  double tpcRatioX[nBin], tpcRatioY[nBin], tpcRatioXL[nBin], tpcRatioXH[nBin], tpcRatioYL[nBin], tpcRatioYH[nBin];
  double hftRatioX[nBin], hftRatioY[nBin], hftRatioXL[nBin], hftRatioXH[nBin], hftRatioYL[nBin], hftRatioYH[nBin];

  for(int iBin = 0; iBin < nBin; ++iBin)
  {
    effY[iBin] = 0;
    effYL[iBin] = 0;
    effYH[iBin] = 0;

    tpcRatioY[iBin] = 0;
    tpcRatioYL[iBin] = 0;
    tpcRatioYH[iBin] = 0;

    hftRatioY[iBin] = 0;
    hftRatioYL[iBin] = 0;
    hftRatioYH[iBin] = 0;
  }

  float Ncoll[9] = {13.7, 30.6, 64., 124., 222.6, 375.9, 606.9, 852.8, 1066.5};

  for(int iBin = 0; iBin < nBin; ++iBin)
  {
    float NcollTotal = 0;
    for(int iCent = firstCent; iCent <= lastCent; ++iCent)
    {
      TFile *f = new TFile(Form("efficiencies/efficiency_cent%d.root", iCent));

      TGraphAsymmErrors *effInc = static_cast<TGraphAsymmErrors*>(f->Get("Graph;1"));
      TGraphAsymmErrors *tpcRatioInc = static_cast<TGraphAsymmErrors*>(f->Get("Graph;2"));
      TGraphAsymmErrors *hftRatioInc = static_cast<TGraphAsymmErrors*>(f->Get("Graph;3"));

      NcollTotal+=Ncoll[iCent];
      int start = ptBin[iBin] - 2;
      for(int iX = 0; iX < ptBin[iBin+1]-ptBin[iBin]; ++iX)
      {
	const int i = start + iX;
	const float normalization = Ncoll[iCent]/(ptBin[iBin+1]-ptBin[iBin]);
	double x, y;

	effInc->GetPoint(i, x, y);
	effY[iBin]      += y * normalization;
	tpcRatioInc->GetPoint(i, x, y);
	tpcRatioY[iBin] += y * normalization;
	hftRatioInc->GetPoint(i, x, y);
	hftRatioY[iBin] += y * normalization;

	effYL[iBin] = addErrors(effYL[iBin], effInc->GetErrorYlow(i)*normalization);
	effYH[iBin] = addErrors(effYH[iBin], effInc->GetErrorYhigh(i)*normalization);
	tpcRatioYL[iBin] = addErrors(tpcRatioYL[iBin], tpcRatioInc->GetErrorYlow(i)*normalization);
	tpcRatioYH[iBin] = addErrors(tpcRatioYH[iBin], tpcRatioInc->GetErrorYhigh(i)*normalization);
	hftRatioYL[iBin] = addErrors(hftRatioYL[iBin], hftRatioInc->GetErrorYlow(i)*normalization);
	hftRatioYH[iBin] = addErrors(hftRatioYH[iBin], hftRatioInc->GetErrorYhigh(i)*normalization);
      }

      f->Close();
    }
    effY[iBin] *= 1./NcollTotal;
    effYL[iBin] *= 1./NcollTotal;
    effYH[iBin] *= 1./NcollTotal;
    tpcRatioY[iBin] *= 1./NcollTotal;
    tpcRatioYL[iBin] *= 1./NcollTotal;
    tpcRatioYH[iBin] *= 1./NcollTotal;
    hftRatioY[iBin] *= 1./NcollTotal;
    hftRatioYL[iBin] *= 1./NcollTotal;
    hftRatioYH[iBin] *= 1./NcollTotal;
  }
  // -- set x bins
  for(int i = 0; i < nBin; ++i)
  {
    float halfBinWidth = (ptBin[i+1] - ptBin[i])/2.;
    float binMean = ptBin[i] + halfBinWidth;
    effX[i] =      binMean;
    tpcRatioX[i] = binMean;
    hftRatioX[i] = binMean;

    effXL[i] =      halfBinWidth;
    effXH[i] =      halfBinWidth;
    tpcRatioXL[i] = halfBinWidth;
    tpcRatioXH[i] = halfBinWidth;
    hftRatioXL[i] = halfBinWidth;
    hftRatioXH[i] = halfBinWidth;
  }
  // -- Make TGraphAsymmErrors
  TGraphAsymmErrors* eff = new TGraphAsymmErrors(nBin, effX, effY, effXL, effXH, effYL, effYH);
  TGraphAsymmErrors* tpcRatio = new TGraphAsymmErrors(nBin, tpcRatioX, tpcRatioY, tpcRatioXL, tpcRatioXH, tpcRatioYL, tpcRatioYH);
  TGraphAsymmErrors* hftRatio = new TGraphAsymmErrors(nBin, hftRatioX, hftRatioY, hftRatioXL, hftRatioXH, hftRatioYL, hftRatioYH);

  // -- Drawing
  string centralityMarker = " 10-60%";
  eff->SetTitle(Form("efficiency%s", centralityMarker.c_str()));
  tpcRatio->SetTitle(Form("TPC efficiency%s", centralityMarker.c_str()));
  hftRatio->SetTitle(Form("HFT efficiency%s", centralityMarker.c_str()));

  eff->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
  tpcRatio->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
  hftRatio->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");

  Ceff->cd();
  // Ceff->SetLogy();
  eff->SetMarkerStyle(20);
  eff->Draw("ap");
  CtpcRatio->cd();
  // CtpcRatio->SetLogy();
  tpcRatio->SetMarkerStyle(20);
  tpcRatio->Draw("ap");
  ChftRatio->cd();
  // ChftRatio->SetLogy();
  hftRatio->SetMarkerStyle(20);
  hftRatio->Draw("ap");

  // saving
  cout << "Writing into file " << outFileName << endl;
  outFile->cd();
  eff->Write();
  tpcRatio->Write();
  hftRatio->Write();

}

