//Scattering Calculation
{
	//Common constant
	k = 1
	Tcomplex
	
	for i=0,i++,i<10{
	x =i;
	y = exp(k*x)
	g->SetPoint(i,x,y);
	}
	f = New TF1("f","pol1",0,5);
	g->Fit(f);
	
	g->SetMarkerStyle(22);
	g->Draw();
}