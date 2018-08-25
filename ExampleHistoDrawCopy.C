//Declare histograms globally so they can be used
//in root after this macro finishes

TH1F* Mass300;


void ExampleHistoDraw(){



  TFile *_file1 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_300.root");

  // TFile *_file2 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_700.root");

  // TFile *_file3 = TFile::Open("hist-DAOD_TRUTH1.test_ttbb_lh_1300.root");



  Mass300 = (TH1F*)_file1->Get("h_higgs_mass");


  TCanvas *c2 = new TCanvas("c2");
  c2->cd();
  Mass300->Draw();

  //Mass700->SetLineColor(9);
  //Mass700->Draw("same");



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





 TFile *f = new TFile("Plot_300_700_1300.root","NEW");
  c2->Write();
 f->Close();
}
