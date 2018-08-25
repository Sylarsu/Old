{
	h=new TH1D("h","First Histogram", 10, 0, 10);
	
	for(int i=0; i<1000; i++){
		 h->Fill( gRandom->Gaus(5,2));
	}
	
	h->SetMinimum(0);
	h->SetFillColor(kBlue-7);
	h->Draw();
}