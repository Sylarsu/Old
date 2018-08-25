//Example of graph with SetPoint
{
	#include "TF1.h"
	#include "TH1.h"
	#include "TMath.h"
	
	gROOT->LoadMacro("BW.C");
	gStyle->SetOptFit(111111);
	
	TFile f("myZPeakCRAB.root");
	Z_mass=(TH1F*)Zmass->Clone();
	
	
	int   division = Zmass->GetNbinsX();
	float massMIN = Zmass->GetBinLowEdge(1);
	float massMAX = Zmass->GetBinLowEdge(division+1);
	float BIN_SIZE = Zmass->GetBinWidth(1);
	//Define Data
	//g = new TGraph();
	TFile f("myZPeakCRAB.root");
	Z_mass=(TH1F*)Zmass->Clone();
	//TF1 *fit = Z_mass->GetFunction("g");
	//Define Fit Function
	f = new TF1("f","[0]*exp(-(x-[1])*[2])", massMIN, massMAX);
	f -> SetParNames( "amp","disp","decay");
	f -> SetParameters(1,1,1);
	
	Z_mass->Fit(f);
	Z_mass->SetMarkerStyle(22);
	Z_mass->Draw("AP");

}