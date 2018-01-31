#ifndef _PIDEFFICIENCYMAKER_H_
#define _PIDEFFICIENCYMAKER_H_

#include "nt.h"
#include <TGraphErrors.h>
#include <TF1.h>
#include <array>

class pidEfficiencyMaker
{
  public:

    pidEfficiencyMaker();
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


    void Init();
    void Make();
    void Finish();

  private:
    using std::array;

    nt *simTuple;

    TGraphErrors* fHftRatioCorrection;
    TF1* gf1AuAu010Weight;

    array<TF1*, 3> fNsig_eff;

    array<TF1*, 3> fNsigTof_eff;

    array<array<TF1*, NptBins>, 3> ftof;
}

#endif
