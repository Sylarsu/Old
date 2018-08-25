#include <iostream>
#include <string>
using namespace std;

TH1F* Mass300;
TH1F* Mass700;
TH1F* Mass1300;

void test(){
	
	TFile *file = new TFile("hist-DAOD_TRUTH1.test_ttbb_lh_300.root");
	
	TKey *key1;
	
	TKey *key2;
	
	TIter next1( file->GetListOfKeys());
	
	TIter next2( file->GetListOfKeys());
	
	int j=0;
	
		while ((key1 = (TKey *) next1())) {
		j++;
   }
   	string y[j];
	int i=0;
	while ((key2 = (TKey *) next2())) {
		y[i] = key2->GetName();
	}
	TString mystr;
		
	TFile *_file1 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_300.root");
	
	TFile *_file2 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_700.root");
	
	TFile *_file3 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_1300.root");
	
	char saythis[5000];
	
	sprintf(saythis, "c4%i",j);
	
	TCanvas *c4[26] = new TCanvas(saythis);
	
	for (int z=0; z<2 ; z++){
	
	c4[z]->cd();
	
	mystr = y[z];
	
	cout << mystr << endl;
	
	Int_t ci;      // for color index setting
	
	TColor *color; // for color definition with alpha
	
	TString newstring = mystr;
	
	Mass300 = (TH1F*)_file1->Get(newstring);
	
	Mass700 = (TH1F*)_file2->Get(newstring);
	
	Mass1300 = (TH1F*)_file3->Get(newstring);
	
	
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
	
	c4[z]->Print(newstring+".pdf");
	
	}
}
