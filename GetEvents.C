#include <TList.h>
#include <TFile.h>
#include <TH1.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void GetEvents(string listname = "newProd.list")
{
  ifstream fileList(listname.data());
  if(!fileList.is_open())
  {
    cerr << "list could not be opened" << endl;
    return;
  }
  
  double all = 0;
  double goodRun = 0;
  double trigger = 0;
  double Vz = 0;
  double VzVzVPD = 0;
  double accepted = 0;
  string fileName;
  // loop on the fileList
  //________________________________________________________
  while(getline(fileList, fileName))
  {
    cout << "Reading from " << fileName << " ..."<< endl;

    TFile *f = new TFile(fileName.data());
    TList *l = (TList*) f->Get("picoHFLambdaCMaker");
    if(!l)
    {
      cerr << "list not found" << endl;
      f->Close();
      delete f;
      continue;
    }
    TH1D *statHist = (TH1D*) l->FindObject("hEventStat1");

    all += statHist->GetBinContent(1);
    goodRun += statHist->GetBinContent(2);
    trigger += statHist->GetBinContent(3);
    Vz += statHist->GetBinContent(4);
    VzVzVPD  += statHist->GetBinContent(5);
    accepted  += statHist->GetBinContent(6);

    // delete statHist;
    // delete l;
    f->Close();
    // delete f;
  }

  cout << "all:      " << all      << endl;
  cout << "goodRun:  " << goodRun  << endl;
  cout << "trigger:  " << trigger  << endl;
  cout << "Vz:       " << Vz       << endl;
  cout << "VzVzVPD:  " << VzVzVPD  << endl;
  cout << "accepted: " << accepted << endl;
}
