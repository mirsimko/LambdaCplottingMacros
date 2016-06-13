void significance(int const decayMode = 3)
{

  // declare variables
  enum DecayMode{kKstar, kLambda, kDelta, kThreeBody};

  DecayMode dm = (DecayMode)decayMode;
  float minRes = -0.1;
  float maxRes = 1.7;

  TString outFileName = "";
  TString decayName = "";
  TString resonanceName = "";
  // cuts
  // simulation	

  // background
  TCut dLengthCut = "dLength > 0.0190";
  TCut DCApairsCut = "dcaDaugthers12 < 0.016 && dcaDaugthers23 < 0.016 && dcaDaugthers31 < 0.016";
  TCut ptCut = "p3pt > 0.5"; // K, p, pi
  TCut cosThetaCut = "cosPntAngle > 0.9825";
  TCut maxVertexDistCut = "maxVertexDist < 0.03";
  TCut chargeCut = "charges < 0.";

  // TCut DCAbkgCut = "dcaDaugthers12 < 0.007 && dcaDaugthers23 < 0.007 && dcaDaugthers31 < 0.007";
  // TCut dLengthBkgCut = "dLength > 0.01";
  // TCut cosTbkgCut = "cosPntAngle > 0.98";
  // TCut chargeCut = "charges < 0";
  TCut massCut = "m > 2.266 && m < 2.306";

  // getting the Ntuple and setting variables for all decay modes
  TFile *readF1 = new TFile("lambdaCTMVAkPionKaonProtonCuts.root");
  // switch(dm)
  // {
  //   case kKstar:
  //     readF1 = new TFile("lambdaCkKstarProton.root");
  //     minRes = 0.6;
  //     maxRes = 1.2;
  //     outFileName = "lambdaCkKstarProton";
  //     decayName = "K* p";
  //     resonanceName = "mKstar";
  //     break;
  //   case kLambda:
  //     readF1 = new TFile("lambdaCkLambda1520Pion.root");
  //     minRes = 1.4;
  //     maxRes = 1.65;
  //     outFileName = "lambdaCkLambda1520Pion";
  //     decayName = "#Lambda(1520) #pi";
  //     resonanceName = "mLambda1520";
  //     break;
  //   case kDelta:
  //     readF1 = new TFile("lambdaCkDeltaPPkaon.root");
  //     minRes = 1.;
  //     maxRes = 1.4;
  //     outFileName = "lambdaCkDeltaPPkaon";
  //     decayName = "#Delta^{++} K";
  //     resonanceName = "mDelta";
  //     break;
  //   case kThreeBody:
  //     // readF1 = new TFile("lambdaCkPionKaonProton.root");
  //     readF1 = new TFile("../lambdaC.root");
  //     minRes = -0.2;
  //     maxRes = 0.2;
  //     outFileName = "lambdaCkPionKaonProton";
  //     decayName = "#pi K p";
  //     break;
  //   default:
  //     cerr << "Wrong decay mode" << endl;
  //     return;
  //     break;
  // }
  // // resonance masses
  // TCut RMcut;
  // TCut RMbkgCut;
  // if (dm == kThreeBody)
  // {
  //   RMcut = "";
  //   RMbkgCut = "";
  // }
  // else
  // {
  // RMcut = Form("MRResonance < %f && MRResonance > %f", maxRes, minRes);
  // RMbkgCut = Form("%s < %f && %s > %f", resonanceName.Data(), maxRes, resonanceName.Data(), minRes);
  // }
  // combine cuts
  TCut AllCuts = dLengthCut && DCApairsCut && ptCut && cosThetaCut && maxVertexDistCut && massCut;
  TCut AllexceptMass = dLengthCut && DCApairsCut && ptCut && cosThetaCut && maxVertexDistCut && chargeCut;
  // end of cuts PHEW...

  TNtuple *particles= readF1->Get("ntTMVA");

  TFile *readF2 = new TFile("bgSelectedLc.root");
  TNtuple *bkg = (TNtuple*)readF2->Get("secondarySelected");
  TFile *outF = new TFile("significanceBest.root", "RECREATE");
  // end of setting
  // time to fill histograms

  TH1D * simPt = new TH1D("simPt", "pT distribution of the simulated Lc", 50, 0, 13);
  simPt->GetXaxis()->SetTitle("p_{T} [GeV]");
  simPt->Sumw2();
  TH1D * bkgPt = new TH1D("bkgPt", "pT distribution of the background", 50, 0, 13);
  bkgPt->GetXaxis()->SetTitle("p_{T} [GeV]");
  bkgPt->Sumw2();
  // TH2D * bkgMvsPt = new TH2D("bkgMpt", "m vs pt background", 20, 0, 12, 20, 2., 2.5);

  // filling histograms
  cout << "Filling simulation histogram ..." << endl;
  particles->Project("simPt", "pt", AllCuts);
  cout << "Filling bg histogram ..." << endl;
  bkg->Project("bkgPt", "pt", AllCuts && chargeCut);
  // cout << "Filling mass vs pt histogram for bg ..." << endl;
  // bkg->Project("bkgMpt", "m:pt", AllexceptMass);

  // plotting m vs pt background histogram
  // bkgMvsPt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  // bkgMvsPt->GetYaxis()->SetTitle("m [GeV/c^{2}]");
  // TCanvas *C1 = new TCanvas("C1", "", 600, 400);
  // C1->SetLogz();
  // bkgMvsPt->Draw("colz");

  // Save histograms
  outF->cd();
  simPt->Write();
  bkgPt->Write();
  
  // calculate significance
  float sigYield = simPt->Integral() * 0.0001;
  float bkgYield = bkgPt->Integral() / 3.;

  // significance: s/(\sqrt(s + b/3) ) ... there is 3 times more bg with wrong sign
  float significance = sigYield / TMath::Sqrt( bkgYield + sigYield );

  
  cout << "Background counts: " << bkgYield<< endl;
  cout << "Signal counts: " << sigYield << endl;
  cout << "significance: " << significance << endl;

}
