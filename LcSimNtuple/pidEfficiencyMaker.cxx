#include "nt.h"
#include "pidEfficiencyMaker.h"
#include <TF1.h>
#include <array>
#include <TGraphErrors.h>
#include <string>
#include <TString.h>

class pidEfficiencyMaker;


// default constructor
pidEfficiencyMaker::pidEfficiencyMaker(std::string outFileName, int centrality):
  simTuple            (nullptr),
  fHftRatioCorrection (nullptr),
  gf1AuAu010Weight    (nullptr),
  hNoCuts             (nullptr), 
  hNoCutsPhysBinning  (nullptr),
  hTopoCuts           (nullptr),
  hHftMatchingOnly    (nullptr),
  hPIDOnly            (nullptr),
  hTpcOnly            (nullptr),
  hTpcHftTopo         (nullptr),
  h2MassPt            (nullptr),
  mCentrality         (centrality),
  mMinPtCut           (-1.),
  outFile             (nullptr)
{

  for( int i = 0; i < 3; ++i)
  {
    fNsig_eff[i] = nullptr;
    fNsigTof_eff[i] = nullptr;
    for (int j = 0; j < NptBins; ++j)
      ftof[j][i] = nullptr;
  }

  outFile = new TFile(outFile.data(), "RECREATE");
}

~pidEfficiencyMaker()
{
  // the pointers to the distributions are destroyed automatically when closing
  // the file
}

void pidEfficiencyMaker::Init()
{
  int nBins = 300;
  float minPt = 0.;
  float maxPt = 15.;

  float minPtCut;

  if (mMinPtCut <= 0;)
    minPtCut = 0;
  else
    minPtCut = mMinPtCut;

  hNoCuts = new TH1D(Form("hNoCuts_minPt%i_%i", (int)(minPtCut * 1e3), mCentrality), Form("No Cuts %s minPt>%1.2f", anaCuts::physCentralityName[mCentrality].Data(), minPtCut), nBins, minPt, maxPt);
  hNoCutsPhysBinning = new TH1D(Form("hNoCutsPhysBinning_minPt%i_%i", (int)(minPtCut * 1e3), mCentrality), Form("No Cuts Physics Binning %s minPt>%1.2f", anaCuts::physCentralityName[mCentrality].Data(), minPtCut), anaCuts::physNPtBins, anaCuts::physPtEdge);
  hTopoCuts = new TH1D(Form("hTopoCuts_minPt%i_%i", (int)(minPtCut * 1e3), mCentrality), Form("Topo Cuts %s minPt>%1.2f", anaCuts::physCentralityName[mCentrality].Data(), minPtCut), nBins, minPt, maxPt);
  hHftMatchingOnly = new TH1D(Form("hHftMatchingOnly_minPt%i_%i", (int)(minPtCut * 1e3), mCentrality), Form("HFT Matching Only %s minPt>%1.2f", anaCuts::physCentralityName[mCentrality].Data(), minPtCut), nBins, minPt, maxPt);
  hPIDOnly= new TH1D(Form("hPIDOnly_minPt%i_%i", (int)(minPtCut * 1e3), mCentrality), Form("PID Only %s minPt>%1.2f", anaCuts::physCentralityName[mCentrality].Data(), minPtCut), nBins, minPt, maxPt);
  hTpcOnly = new TH1D(Form("hTpcOnly_minPt%i_%i", (int)(minPtCut * 1e3), mCentrality), Form("TPC Only %s minPt>%1.2f", anaCuts::physCentralityName[mCentrality].Data(), minPtCut), nBins, minPt, maxPt);
  hTpcHftTopo = new TH1D(Form("hTpcHftTopo_minPt%i_%i", (int)(minPtCut * 1e3), mCentrality), Form("TPC + HFT + Topo %s minPt>%1.2f", anaCuts::physCentralityName[mCentrality].Data(), minPtCut), nBins, minPt, maxPt);
  h2MassPt = new TH2D(Form("h2MassPt_minPt%i_%i", (int)(minPtCut * 1e3), mCentrality), Form("Invariant Mass vs. Pt %s minPt>%1.2f", anaCuts::physCentralityName[mCentrality].Data(), minPtCut), nBins, minPt, maxPt, 210, 0, 2.1);

  hNoCuts->Sumw2();
  hNoCutsPhysBinning->Sumw2();
  hTopoCuts->Sumw2();
  hHftMatchingOnly->Sumw2();
  hPIDOnly->Sumw2();
  hTpcOnly->Sumw2();
  hTpcHftTopo->Sumw2();
  h2MassPt->Sumw2();

}

void pidEfficiencyMaker::Finish()
{
  //tbd
}

void pidEfficiencyMaker::Make() // for each LambdaC ... (not event)
{
  //tbd
}

bool pidEfficiencyMaker::passTPC()
{
  //tbd
}


