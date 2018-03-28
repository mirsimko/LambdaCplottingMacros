#include "pidEfficiencyMaker.h"
#include "nt.h"
#include "StLambdaCCutsConsts.h"
#include <TFile.h>
#include <TNtuple.h>
#include <string>
#include <cstdio>

void setDefaultCuts(pidEfficiencyMaker &);

// ---------------------------------------------------------------
void runEfficiencyMaker(char *inFileName, char *outFileDir, char *baseName = "LcSimEffPlots")
{
  TFile * inFile(inFileName);
  TNtuple *simTuple = static_cast<TNtuple*>(inFile->Get("nt"));

  int centrality;
  sscanf(inFileName, "%*s%d.root", &centrality); // %*s means that the string is to be read, but ignored
  nt simNtupleReader(simTuple, centrality);

  char outFileName[200];
  sprintf(outFileName, "%s/%s%dout.root", outFileDir, baseName, centrality);
  pidEfficiencyMaker myEffMaker(outFileName, centrality);
  setDefaultCuts(myEffMaker);
  myEffMaker.SetSimMaker(&simNtupleReader);
  myEffMaker.Init();


  unsigned long nEntries = simTuple->GetEntriesFast();
  for(unsigned long i = 0; i < nEntries; ++i )
  {StLambdaCCutsConsts.h
    myEffMaker.Make(i);
  }
  myEffMaker.Finish();
}
// ---------------------------------------------------------------

void setDefaultCuts(pidEfficiencyMaker &effMaker)
{
  // loading cut constants from StLambdaCCutsConsts.h
  using namespace LambdaCthreePartDecayReadConsts;

  effMaker.SetPiDcaMin(piDcaMin);
  effMaker.SetPDcaMin(pDcaMin);
  effMaker.SetKDcaMin(KDcaMin);
  effMaker.SetMinDaughtersPt(minDaughtersPt);
  effMaker.SetPiTpcNSigma(piTpcNSigma);
  effMaker.SetPTpcNSigma(pTpcNSigma);
  effMaker.SetKTpcNSigma(KTpcNSigma);
  effMaker.SetTofDeltaOneOverBeta(tofDeltaOneOverBeta);
  effMaker.SetLCdcaDaughtersMax(LCdcaDaughtersMax);
  effMaker.SetLCdecayLengthMin(LCdecayLengthMin);
  effMaker.SetLCdcaDaughtersMax(LCdecayLengthMax);
  effMaker.SetLCcosThetaMin(LCcosThetaMin);
  effMaker.SetLCminMass(LCminMass);
  effMaker.SetLCmaxMass(LCmaxMass);
  effMaker.SetLCdcaToPv(LCdcaToPv);
}
// ---------------------------------------------------------------
