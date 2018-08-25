//Declare histograms globally so they can be used
//in root after this macro finishes

TH1F* Mass300;
TH1F* Mass700;
TH1F* Mass1300;


void h_bjet_pt(){



  TFile *_file1 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_300.root");

  TFile *_file2 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_700.root");

  TFile *_file3 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_1300.root");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha

  Mass300 = (TH1F*)_file1->Get("h_bjet_pt");
  Mass700 = (TH1F*)_file2->Get("h_bjet_pt");
  Mass1300 = (TH1F*)_file3->Get("h_bjet_pt");

//  TCanvas *c1 = new TCanvas("c1");
//  TCanvas *c2 = new TCanvas("c2");
//  TCanvas *c3 = new TCanvas("c3");
  TCanvas *c4 = new TCanvas("c4");
  
//  c1->cd();
//  Mass300->Draw();

  
//  Mass700->SetLineColor(2);
//  c2->cd();
//  Mass700->Draw();
//  Mass1300->SetLineColor(3);
//  c3->cd();
//  Mass1300->Draw();

  c4->cd();
  Mass300->Draw();
  Mass700->SetLineColor(2);
  Mass700->Draw("same");
  Mass1300->SetLineColor(3);
  Mass1300->Draw("same");

  
   TLegend *leg = new TLegend(0.6504298,0.1518987,0.8667622,0.2658228,NULL,"brNDC");
   TLegendEntry *entry=leg->AddEntry("Mass300","300_h_bjet_pt","l");
   entry->SetLineColor(1);
   TLegendEntry *entry=leg->AddEntry("Mass700","700_h_bjet_pt","l");
   entry->SetLineColor(2);  
   TLegendEntry *entry=leg->AddEntry("Mass1300","1300_h_bjet_pt","l");
   entry->SetLineColor(3);
   leg->Draw();
 
 TFile *f = new TFile("h_bjet_pt.root","NEW");
// c1->Write();
// c2->Write();
// c3->Write();
 c4->Write();
 
 f->Close();
}
