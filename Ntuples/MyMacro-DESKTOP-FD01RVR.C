

void MyMacro(){

  //Open the inital root file
  TFile *f1 = TFile::Open("toy_sigbkg_categ_offset.root");

  //Get the trees in the root file
  TTree *treeS = (TTree*)f1->Get("TreeS");
  TTree *treeB = (TTree*)f1->Get("TreeB");

  //Creat new histogram with 10 bins, going from -5 to 5
  TH1F* histo1 = new TH1F("histo1", "histo1", 50, -5, 5);

  //Fill the histogram with var1
  treeS->Draw("var1>>histo1");

  //Change the line color of the histogram
  histo1->SetLineColor(6);

  //Draw the histogram
  histo1->Draw();

  //Fit the histogram to a gaussian
  //  histo1->Fit("gaus");


  //Or first define your function so you can access its specific parameters:
  //https://root.cern.ch/doc/master/classTF1.html#TF1:TF1
  TF1 *myfuncB = new TF1("myfuncB","gaus(0)",-5, 5);
  //  myfunc->SetParameter(0,1);
  histo1->Fit("myfuncB");

  cout<<"My gaussian parameter: "<<myfuncB->GetParameter(0)<<endl;

   myfuncB->SetLineColor(5);
   myfuncB->Draw("same");

  //Now do the same thing with the background tree

  //Create a new canvas
   TCanvas* c2 = new TCanvas( "c2", "", 0, 0, 550, 550 );
   c2->cd();

  TH1F* histo2 = new TH1F("histo2", "histo2", 50, -5, 5);
  treeB->Draw("var1>>histo2");
  histo2->SetLineColor(6);
  histo2->Draw();
  histo2->Fit("gaus");




}
