#ifndef _PIDEFFICIENCYMAKER_H_
#define _PIDEFFICIENCYMAKER_H_

#include "nt.h"
#include <TGraphErrors.h>
#include <TF1.h>
#include <array>
#include <string>
#include <TFile.h>

class pidEfficiencyMaker
{
  public:
    pidEfficiencyMaker(std::string outFileName, int centrality);
    ~pidEfficiencyMaker();

    enum PidNumbers {kPion = 0, kKaon = 1, kProton = 2};
    enum NBinsConsts {NptBins  = 9};

    void SetSimMaker(nt* simNTuple) 
    {simTuple = simNTuple;}
    void SetHftRatioCorrection(TGraphErrors *hftRatioCorrection) 
    {fHftRatioCorrection = hftRatioCorrection; }
    void SetAuAuWeight(TF1* f1AuAu010Weight) 
    {gf1AuAu010Weight = f1AuAu010Weight; }

    void SetNsigWeight(TF1* nSigEffFunc, int pidFlag) 
    {fNsig_eff[pidFlag] = nSigEffFunc; }
    void SetNSigTof(TF1* nSigTofEffFunc, int pidFlag) 
    {fNsigTof_eff[pidFlag] = nSigTofEffFunc;}
    void SetTofEff(TF1* tofEffFunc, int ptBin, int pidFlag) 
    {ftof[ptBin][pidFlag] = tofEffFunc;}

    void SetCentrality(int centrality) {mCentrality = centrality;}
    void SetMinPtCut  (float minPtCut) {mMinPtCut   = minPtCut;  }
    int  GetCentrality()  {return mCentrality;}
    int  GetMinPtCut  ()  {return mMinPtCut;  }

    void Init();
    void Make(Long64_t entry);
    void Finish();

  private:
    using std::array;

    nt *simTuple;

    TGraphErrors* fHftRatioCorrection;
    TF1* gf1AuAu010Weight;

    array<TF1*, 3> fNsig_eff;

    array<TF1*, 3> fNsigTof_eff;

    array<array<TF1*, NptBins>, 3> ftof;

    TH1D* hNoCuts;
    TH1D* hNoCutsPhysBinning;
    TH1D* hTopoCuts;
    TH1D* hHftMatchingOnly;
    TH1D* hPIDOnly;
    TH1D* hTpcOnly;
    TH1D* hTpcHftTopo;
    TH2D* h2MassPt;

    float mMinPtCut;
    int   mCentrality;

    TFile* outFile

    bool passTPC();
    float getPidEfficiency(float pT, int pidFlag)
    inline bool isGoodTrack(float pt, float eta);
};

#endif
