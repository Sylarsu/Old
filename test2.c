#include <iostream>
#include <string>
using namespace std;

TH1F* Mass300;
TH1F* Mass700;
TH1F* Mass1300;

void test(){
	ifstream input;
	
	input.open("ListofN");
	
	string ListofName[27];
	
	for (int j=0; j<27 ; j++){
		
	input >> ListofName[j];
	}
	
	string mystr;
	
	for (int z=0; z<27 ; z++){
		
	mystr = ListofName[z];
	//cout << mystr << endl;
	
	TFile *_file1 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_300.root");
	
	TFile *_file2 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_700.root");
	
	TFile *_file3 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_1300.root");
	
	
	Int_t ci;      // for color index setting
	
	TColor *color; // for color definition with alpha
	
	TString newstring = mystr;
	
	Mass300 = (TH1F*)_file1->Get(newstring);
	
	Mass700 = (TH1F*)_file2->Get(newstring);
	
	Mass1300 = (TH1F*)_file3->Get(newstring);
	
	TCanvas *c4 = new TCanvas("c4");
	
	c4->cd();
	Mass300->GetYaxis()->SetRangeUser(0,700);
	
	Mass300->Draw();
	Mass700->SetLineColor(2);
	Mass700->Draw("same");
	Mass1300->SetLineColor(3);
	Mass1300->Draw("same");
	
	
	TLegend *leg = new TLegend(0.6504298,0.1518987,0.8667622,0.2658228,NULL,"brNDC");
	TLegendEntry *entry=leg->AddEntry("Mass300","300_"+newstring,"l");
	entry->SetLineColor(1);
	TLegendEntry *entry=leg->AddEntry("Mass700","700_"+newstring,"l");
	entry->SetLineColor(2);  
	TLegendEntry *entry=leg->AddEntry("Mass1300","1300_"+newstring,"l");
	entry->SetLineColor(3);
	leg->Draw();
	
//	TFile *f = new TFile(newstring+".pdf","NEW");
	
	c4->Print(newstring+".pdf");
	
	}
}
