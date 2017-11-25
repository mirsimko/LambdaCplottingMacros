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
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TVectorD.h"
#include "TMath.h"

using std::cout;
using std::endl;

float addErrors(float first, float second);

// -- namespace with consts
namespace LCyieldsNov2017
{
  // -- consts
  const int nBinSixty = 1;
  float ptBinSixty[nBinSixty+1] = {3., 6.};
  float nSixty[nBinSixty] = {81.7087};
  float errorSixty[nBinSixty] = {15.8583};
  float xSixty[nBinSixty] = {4.5};
  float xEsixty[nBinSixty] = {1.5};

  const int nBinEighty = 2;
  float ptBinEighty[nBinEighty+1] = {3., 4., 6.};
  float nEighty[nBinEighty] = {73.3045, 19.8597};
  float errorEighty[nBinEighty] = {14.921, 6.47855};
  float xEighty[nBinEighty] = {3.5, 5.};
  float xEeighty[nBinEighty] = {0.5, 1.};

  const float BR = 0.0635;
  const float nEvents = 9.75433e+08;

  const int nCharges = 2;
  const float fracEventsSixty = 0.5;
  const float fracEventsEighty = 0.7;
  const float deltaRapidity = 2.;

  const float firstCent = 0;
  const float lastCent = 6;

//--------------------------------------------------
  double scalingFactor(int iBin, TGraph* eff, float pt, float deltaPt)
  {
    double effX, effY;
    eff->GetPoint(iBin, effX, effY);
    const double scaling= 1./(2.*TMath::Pi()*nCharges*BR*deltaRapidity*pt*nEvents*fracEventsSixty*deltaPt*effY);
    return scaling;
  }
//--------------------------------------------------
}

//--------------------------------------------------

void plotSpectrum()
{
  // -- style
  gStyle->SetOptStat(0);
  gStyle->SetLabelFont(132, "x");
  gStyle->SetLabelFont(132, "y");
  gStyle->SetTitleFont(132, "x");
  gStyle->SetTitleFont(132, "y");
  gStyle->SetLegendFont(132);

  using namespace LCyieldsNov2017;

  string inFileNameSixty = "images/efficiency_result_10-60cent.root";
  TFile *inFileSixty = new TFile(inFileNameSixty.c_str());
  TGraphAsymmErrors* effSixty = static_cast<TGraphAsymmErrors*>(inFileSixty->Get("Graph;1"));
  string inFileNameEighty = "images/efficiency_result10-80cent.root";
  TFile *inFileEighty = new TFile(inFileNameEighty.c_str());
  TGraphAsymmErrors* effEighty = static_cast<TGraphAsymmErrors*>(inFileEighty->Get("Graph;1"));

  string outFileName = "spectrum.root";
  TFile *outFile = new TFile(outFileName.c_str(), "recreate");

  TCanvas *Csixty = new TCanvas("Csixty", "10-60\% centrality", 200, 300);
  TCanvas *Ceighty = new TCanvas("Ceighty", "10-80\% centrality", 200, 300);

  // correction for sixty
  for (int iBin = 0; iBin < nBinSixty; ++iBin)
  {
    const double correction = scalingFactor(iBin, effSixty, xSixty[iBin], xEsixty[iBin]);

    nSixty[iBin] *= correction;
    errorSixty[iBin] *= correction;
  }

  // correction for eighty
  for (int iBin = 0; iBin < nBinEighty; ++iBin)
  {
    const double correction = scalingFactor(iBin, effEighty, xEighty[iBin], xEeighty[iBin]);

    nEighty[iBin] *= correction;
    errorEighty[iBin] *= correction;
  }
  // -- Make TGraphErrors
  TGraphErrors* gSixty = new TGraphErrors(nBinSixty, xSixty, nSixty, xEsixty, errorSixty);
  TGraphErrors* gEighty = new TGraphErrors(nBinEighty, xEighty, nEighty, xEeighty, errorEighty);

  // -- Drawing
  gSixty ->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
  gSixty ->GetYaxis()->SetTitle("#frac{d^{2}#font[12]{N}}{d#font[12]{p}_{T}d#font[12]{y}}#frac{1}{2#pi^{}#font[12]{p}_{T}}");
  gSixty ->GetXaxis()->CenterTitle();
  gSixty ->GetYaxis()->CenterTitle();
  gSixty ->GetXaxis()->SetRangeUser(0, 6);
  gSixty ->GetYaxis()->SetRangeUser(3e-6, 6e-4);

  gEighty->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
  gEighty->GetYaxis()->CenterTitle();
  gEighty->GetXaxis()->CenterTitle();
  gEighty->GetYaxis()->SetTitle("#frac{d^{2}#font[12]{N}}{d#font[12]{p}_{T}d#font[12]{y}}#frac{1}{2#pi^{}#font[12]{p}_{T}}");
  gEighty->GetXaxis()->SetRangeUser(0, 6);
  gEighty->GetYaxis()->SetRangeUser(3e-6, 6e-4);

  Csixty->cd();
  Csixty->SetLogy();
  gSixty->SetMarkerStyle(20);
  gSixty->Draw("ap");
  Ceighty->cd();
  Ceighty->SetLogy();
  gEighty->SetMarkerStyle(20);
  gEighty->Draw("ap");

  // saving
  // cout << "Writing into file " << outFileName << endl;
  // outFile->cd();
  // gSixty->Write();
  // gEighty->Write();
}

//--------------------------------------------------
float addErrors(float first, float second)
{
  return sqrt(first*first + second*second);
}
