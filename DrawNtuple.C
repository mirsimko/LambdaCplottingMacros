#include "TNtuple.h"
#include "TFile.h"

void DrawNtuple()
{
  TFile *readF1 = new TFile("kPionKaonProton.root");
  TNtuple *particles1= readF1->Get("secondary");
  TCanvas *C1 = new TCanvas("C1", "", 600, 400);
  particles1 -> Draw("cosPntAngle*dLength:pt");
  //particles1 -> Draw("trackDistance >> hist1(50, 0,0.4)");
}
