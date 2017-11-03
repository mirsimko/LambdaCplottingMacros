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

// -- binning
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

const float firstCent = 0;
const float lastCent = 6;

//--------------------------------------------------
float addErrors(float first, float second)
{
  return sqrt(first*first + second*second);
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

  string inFileNameSixty = "efficiency_result_10-60cent.root";
  TFile *inFileSixty = new TFile(inFileNameSixty.c_str());
  TGraphAsymmErrors* effSixty = static_cast<TGraphAsymmErrors*>(inFileSixty->Get("Graph;1"));
  string inFileNameEighty = "efficiency_result10-80cent.root";
  TFile *inFileEighty = new TFile(inFileNameEighty.c_str());
  TGraphAsymmErrors* effEighty = static_cast<TGraphAsymmErrors*>(inFileEighty->Get("Graph;1"));

  string outFileName = "spectrum.root";
  TFile *outFile = new TFile(outFileName.c_str(), "recreate");

  TCanvas *Csixty = new TCanvas("Csixty", "10-60\% centrality", 400, 600);
  TCanvas *Ceighty = new TCanvas("Ceighty", "10-80\% centrality", 400, 600);

  double scalingFactorSixty[nBinSixty];
  double scalingFactorEighty[nBinEighty];
 
  // correction for sixty
  for (int iBin = 0; iBin < nBinSixty; ++iBin)
  {
    double effX, effY;
    effSixty->GetPoint(iBin, effX, effY);
    scalingFactorSixty[iBin]= 1./(2*TMath::Pi()*2*BR*2.*xSixty[iBin]*nEvents*.5*xEsixty[iBin]*effY);
    cout << scalingFactorSixty[iBin] << endl;

    nSixty[iBin] = nSixty[iBin]*scalingFactorSixty[iBin];
    errorSixty[iBin] = errorSixty[iBin]*scalingFactorSixty[iBin];
  }

  // correction for eighty
  for (int iBin = 0; iBin < nBinEighty; ++iBin)
  {
    double effX, effY;
    effEighty->GetPoint(iBin, effX, effY);
    scalingFactorEighty[iBin]= 1./(2*TMath::Pi()*2*BR*2.*xEighty[iBin]*nEvents*.7*xEeighty[iBin]*effY);

    cout << scalingFactorEighty[iBin] << endl;
    nEighty[iBin] *= scalingFactorEighty[iBin];
    errorEighty[iBin] *= scalingFactorEighty[iBin];
  }
  // -- Make TGraphErrors
  TGraphErrors* gSixty = new TGraphErrors(nBinSixty, xSixty, nSixty, xEsixty, errorSixty);
  TGraphErrors* gEighty = new TGraphErrors(nBinEighty, xEighty, nEighty, xEeighty, errorEighty);

  // -- Drawing
  gSixty->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
  gSixty->GetXaxis()->SetRangeUser(0, 6);
  gSixty->GetYaxis()->SetRangeUser(3e-6, 6e-4);
  gEighty->GetXaxis()->SetTitle("#font[12]{p}_{T} (GeV/#font[12]{c})");
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
  cout << "Writing into file " << outFileName << endl;
  outFile->cd();
  gSixty->Write();
  gEighty->Write();
}

