void ok(){
	TString fal[10];
	for (int z=0; z<10 ; z++){
		TF1 *fal[z] = new TF1("fal[z]","sin(x)/x",0,z);
		fal[z]->Draw();
	}
}