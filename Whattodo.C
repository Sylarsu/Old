//Declare histograms globally so they can be used
//in root after this macro finishes

TH1F* Mass300;
TH1F* Mass700;
TH1F* Mass1300;


void Whattodo(){



  TFile *_file1 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_300.root");

  TFile *_file2 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_700.root");

  TFile *_file3 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_1300.root");



  Mass300 = (TH1F*)_file1->Get("h_higgs_mass");
  Mass700 = (TH1F*)_file2->Get("h_higgs_mass");
  Mass1300 = (TH1F*)_file3->Get("h_higgs_mass");

  TCanvas *c1 = new TCanvas("c1");
  TCanvas *c2 = new TCanvas("c2");
  TCanvas *c3 = new TCanvas("c3");
  TCanvas *c4 = new TCanvas("c4");
  
  c1->cd();
  Mass300->Draw();

  
  Mass700->SetLineColor(2);
  c2->cd();
  Mass700->Draw();

  Mass1300->SetLineColor(3);
  c3->cd();
  Mass1300->Draw();

  c4->cd();
  Mass300->Draw();
  Mass700->Draw("same");
  Mass1300->Draw("same");
 //gStyle->SetDrawBorder(0);
 //gStyle->SetCanvasBorderMode(0);


 // sum1 = (TH1F*)pt_rat2_1->Clone("sum1");
 // sum1->Add(pt_rat1_1);
 // sum1->Add(pt_rat3_1);
 // sum1->Add(pt_rat4_1);
 // sum1->Add(pt_rat4_1);
 // c2->Divide(4,2);
 // c2->cd(1);
 // float posy = 1200.0;
 // //gStyle->SetStatY(posy);
 // //gStyle->SetCanvasBorderMode(0);
 // sum1->SetFillColor(9);
 // sum1->Draw();
 // // sum1->SetTitle("Jet pT / Gam pT, Measured gam pT < 30 GeV");
 // sum1->SetTitle("Measured gam pT < 30 GeV");


 //sum->SetFillColor(9);
 //sum->Draw("HIST e");
 //sum->SetTitle("Combined");





 TFile *f = new TFile("Plot_300_700_1300.pdf","NEW");
 c1->Write();
 c2->Write();
 c3->Write();
 c4->Wirte();
 f->Close();
}
