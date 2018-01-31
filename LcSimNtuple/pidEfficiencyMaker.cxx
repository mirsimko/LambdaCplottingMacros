#include "nt.h"
#include "pidEfficiencyMaker.h"
#include <TF1.h>
#include <array>
#include <TGraphErrors.h>

class pidEfficiencyMaker;


// default constructor
pidEfficiencyMaker::pidEfficiencyMaker():
  simTuple(nullptr),
  fHftRatioCorrection(nullptr),
  gf1AuAu010Weight(nullptr)
{

  for( int i = 0; i < 3; ++i)
  {
    fNsig_eff[i] = nullptr;
    fNsigTof_eff[i] = nullptr;
    for (int j = 0; j < NptBins; ++j)
      ftof[j][i] = nullptr;
  }
}

~pidEfficiencyMaker()
{}


