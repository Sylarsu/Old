#include <string>
#include <iostream>
#include <fstream>


void Ntest() {
	TFile *file = new TFile("hist-DAOD_TRUTH1.test_ttbb_lh_300.root");
	TKey *key1;
	TKey *key2;
	TIter next1( file->GetListOfKeys());
	TIter next2( file->GetListOfKeys());
	int j=0;
	while ((key1 = (TKey *) next1())) {
		j++;
   }
   	string y[j];
	int i=0;
	while ((key2 = (TKey *) next2())) {
		y[i] = key2->GetName();
		i++;
	}
		
	ofstream myfile;
	
	myfile.open("textfile.txt");
	
	for (int z=0; z<j ; z++){
	
	myfile << y[z] << "  ";
	
	}
}