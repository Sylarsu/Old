{
	//Define Data
	g = new TGraph();
	double x, y;
	for(i=0; i<100; i++){
		x = 0.05 *i;
		y = 2*exp(-3*(x-3)**2);
		g -> SetPoint(i,x,y);
	}
	
	//Define Fit Function
	
	f = new TF1("f","[0]*exp([2]*(x+[1]))**2", 0, 3);
	f -> SetParNames( "amp","disp","decay");
	f -> SetParameters(1,1,1);
	
	g->Fit(f);
	
	g->SetMarkerStyle(22);
	g->Draw("AP");

}