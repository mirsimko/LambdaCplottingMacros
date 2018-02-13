#include "nt.h"
#include "pidEfficiencyMaker.h"
#include <TF1.h>
#include <array>
#include <TGraphErrors.h>
#include <string>
#include <TString.h>
#include <cmath>
#include "StLambdaCCutsConsts.h"
#include <iostream>
#include <limits>

using std::cout, std::cerr, std::endl;

class pidEfficiencyMaker;


//-----------------------------------------------------------------------
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
  outFile             (nullptr),
  mPiDcaMin( std::numeric_limits<float>::lowest() ),
  mKDcaMin( std::numeric_limits<float>::lowest() ),
  mPDcaMin( std::numeric_limits<float>::lowest() ),
  mMinDaughtersPt( std::numeric_limits<float>::lowest() ),
  mPiTpcNSigma( std::numeric_limits<float>::lowest() ),
  mKTpcNSigma( std::numeric_limits<float>::lowest() ),
  mPTpcNSigma( std::numeric_limits<float>::lowest() ),
  mTofDeltaOneOverBeta( std::numeric_limits<float>::lowest() ),
  mLCdcaDaughtersMax( std::numeric_limits<float>::max() ),
  mLCdecayLengthMin( std::numeric_limits<float>::lowest() ),
  mLCdecayLengthMax( std::numeric_limits<float>::max() ),
  mLCcosThetaMin( std::numeric_limits<float>::lowest() ),
  mLCminMass( std::numeric_limits<float>::lowest() ),
  mLCmaxMass( std::numeric_limits<float>::max() ),
  mLCdcaToPvMax( std::numeric_limits<float>::lowest() )
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

//-----------------------------------------------------------------------
~pidEfficiencyMaker()
{
  // the pointers to the histograms are destroyed automatically when closing
  // the file
}

//-----------------------------------------------------------------------
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

  outFile->cd();

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

//-----------------------------------------------------------------------
void pidEfficiencyMaker::Finish()
{
  outFile->cd();

  hNoCuts->Write();
  hNoCutsPhysBinning->Write();
  hTopoCuts->Write();
  hHftMatchingOnly->Write();
  hPIDOnly->Write();
  hTpcOnly->Write();
  hTpcHftTopo->Write();
  h2MassPt->Write();

  outFile->Close();
}

//-----------------------------------------------------------------------
void pidEfficiencyMaker::Make(Long64_t entry) // for each LambdaC (not event)
{
  nt->GetEntry(entry);

  const float pt = nt->rPt;

  const float piPt = nt->piRPt;
  const float kPt  = nt->kRPt;
  const float pPt  = nt->pRPt;

  const bool  passTPC = passTPC();
  const float pidEfficiency = getPidEfficiency(piPt, kPion)*getPidEfficiency(kPt, kKaon)*getPidEfficiency(pPt, kProton);

  
}

//-----------------------------------------------------------------------
inline bool pidEfficiencyMaker::isGoodTrack(float pt, float eta)
{
  return ( pt > mMinPtCut && abs(eta) < 1. );
}

//-----------------------------------------------------------------------
bool pidEfficiencyMaker::passTPC()
{
  bool allGoodTracks = ( isGoodTrack(nt->piRPt, nt->piREta) && isGoodTrack(nt->kRPt, nt->kREta) && isGoodTrack(nt->pRPt, nt->kREta) );
  bool allGoodTpc = ( nt->piTpc && nt->kTpc && nt->pTpc );

  return allGoodTpc && allGoodTracks;
}

//-----------------------------------------------------------------------
float pidEfficiencyMaker::getPidEfficiency(float pT, int pidFlag)
{
  const float fTofEff       = ftof         [pidFlag] -> Eval(pT);
  const float fTpcNSigma    = fNsig_eff    [pidFlag] -> Eval(pT);
  const float fTofNsigmaEff = fNsigTof_eff [pidFlag] -> Eval(pT);

  if (pidFlag == kPion)
  {
    // hybrid TOF
    return fTofEff*fTpcNSigma*fTofNsigmaEff + (1 - fTofEff)*fTpcNSigma;
  }
  else if (pidFlag == kKaon || pidFlag == kProton)
  {
    // strict TOF requirement
    return fTofEff*fTpcNSigma*fTofNsigmaEff;
  }
  else
  {
    cerr << "pidEfficiencyMaker::getPidEfficiency: Unexpected PID flag" << endl;
    return -1;
  }
}

//-----------------------------------------------------------------------
bool pidEfficiencyMaker::passHft()
{
  //tbd
}

//-----------------------------------------------------------------------
inline bool pidEfficiencyMaker::passTopologicalCuts()
{
  
  return (nt->rPt > mMinPtCut && 
      nt->cosTheta > mLCcosThetaMin && 
      nt->piRDca > mPiDcaMin &&
      nt->kRDca  > mKDcaMin  &&
      nt->pRDca  > mPDcaMin  &&
      nt->dcaDaughters < mLCdcaDaughtersMax &&
      nt->decayLength > mLCdecayLengthMin && nt->decayLength < mLCdecayLengthMax &&
      nt->dcaLcToPv < mLCdcaToPvMax
      );
}
