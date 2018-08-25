//Example of graph with SetPoint
{
	//Define Data
	h=new TH1D("h","First Histogram", 500, 0, 100);
	//g = new TGraph();
	double x,y;
	for(i=0; i<1000; i++) {
		x = gRandom->Integer(10)+1;
		y= gRandom->Gaus(10,20);
		//y= gRandom->Gaus(5,1);
		h->Fill(y);
	}
	
	//Define Fit Function
	f= new TF1("f","[0]*x**2+exp(x*[1])", 0, 10);
	f->SetParNames("quad","decay");
	f->SetParameters(1,1);
	
	h->Fit(f);
	
	
	h->SetMinimum(0);
	h->SetFillColor(kBlue-7);
	h->Draw();
}