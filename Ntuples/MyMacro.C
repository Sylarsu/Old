
void MyMacro(){
	
	TFile *dataFile = TFile::Open("toy_sigbkg_categ_offset.root");
    
	TTree *treeS = (TTree*)dataFile->Get("TreeS");
    TTree *treeB = (TTree*)dataFile->Get("TreeB");
	
	TH1F* histo1 = new TH1F( "histo1", "histo1", 50, -5,5);
	TH1F* histo2 = new TH1F( "histo2", "histo2", 50, -5,5);

	treeS -> Draw("var1>>histo1");
	treeB -> Draw("var1>>histo2");
	
	histo1 ->SetLineColor(6);
	histo2 ->SetLineColor(7);
	
	histo1 -> Draw();
	histo2 -> Draw("same");
	
	g1 = histo1;
	g2 = histo2;
	
	f1 = new TF1("histo1","gaus",-5,5);
	f2 = new TF1("histo2","gaus",-5,5);
	
	g1 -> Fit(f1);
	g2 -> Fit(f2);
	
	g1->Draw("same");
	g2->Draw("same");
	
	Print
	f1->Print();
	}