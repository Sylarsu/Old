//Katy:  Read in (one or two) file(s) and write out select histograms with new binning

TH1F* h_s[500]; 

void MergeHistosRebin_LepHad(){

/*	ofstream file0;
	file0.open("testfile.txt");
	if(file0.is_open()){ file0 << "The file is open." << endl;
			     file0 << "testing 1,2,3,.." << endl;
			     file0.close();
			   }
	else cout << "Unable to open file0" << endl;
*/		

  //  Set Flag:
  bool ControlRegion =0; //0 for SR, 1 for CR


  ///Open File(s)///////////////

  //  TFile *f1 = TFile::Open("/afs/cern.ch/work/a/aparker/public/FinalPlots.TauHH.HopefullyWorked.root");//Sept17
  //  TFile *f1 = TFile::Open("/tmp/kgrimm/FinalPlots.TauHH.HopefullyWorked.root");//Sept17
  //  TFile *f1 = TFile::Open("/tmp/kgrimm/FinalPlots.TauHH.Systs.root");//Sept30
  //  TFile *f1 = TFile::Open("/afs/cern.ch/user/g/gwilliam/workspace/WSMaker/inputs/HH090517b/13TeV_TauLH_CUT_2tag2pjet_0ptv_SR_2HDM_BDT_325.root");

  TFile *f1 = TFile::Open("13TeV_TauLH_CUT_2tag2pjet_0ptv_SR_2HDM_BDT_325.root");


  //  TFile *f1 = TFile::Open("/tmp/kgrimm/FinalPlots.TauHH.No0to2tagSyst.root");//Oct 3 lxplus153
  ///End Open File(s)///

  f1->cd();  

  ///If writing out Ztautau CR plots, CD to that directory///
  //  if(ControlRegion)    gDirectory->cd("ControlZJet");
  ///end If writing out Ztautau CR plots, CD to that directory///


  TList *mylist1 = (TList*)gDirectory->GetListOfKeys();     

  //Set Binnging/////////////////  
  //     if(ControlRegion==0)
       const Int_t NBINS = 9; 
       // if(ControlRegion==1){cout<<"inside"<<endl;  const Int_t NBINS = 41; }
  //CR:
       //  if(ControlRegion==1) {
    //  const Int_t NBINS = 41;
//trial  ////  Double_t edges[NBINS + 1] = {0., 50., 100.,120.,140.,160.,180.,200.,250., 300., 400., 600.};//seem to be events to 800 at least
//  Double_t edges[NBINS + 1] = {0.,  20., 30., 40., 50., 60., 70., 80., 90., 100.,
//			       110.,120.,130.,140.,150.,160.,170.,180.,190.,200.,
//			       210.,220.,230.,240.,250.,260.,270., 280.,290.,300.,
//			       310., 320.,330.,340.,350.,360.,370.,400.,420.,450.,475.,500.};
  //  }else{
 //  const Int_t NBINS = 7;
  //  Double_t edges[NBINS + 1] = {60.0, 90.0, 100.0, 110.0, 120.0, 130.0, 140.0, 600.0};
  //Signal Region:
    //    const Int_t NBINS = 3;
       //    Double_t edges[NBINS + 1] = {85., 300., 400., 600.};//bin edges including lowest edge and highest edge
       //   Double_t edges[NBINS + 1] = {85., 200.,300., 400.,500., 1000.};//bin edges including lowest edge and highest edge
       //       Double_t edges[NBINS + 1] = {0., 100.,200.,300., 400.,500.,600.,700., 1000.};//bin edges including lowest edge and highest edge
       Double_t edges[NBINS + 1] = {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0};//bin edges including lowest edge and highest edge

/*
	cout<<"Hello"<<endl;

	for(int i = 0; i < NBINS + 1; ++i){
		cout << edges[i] << endl;
	}
	cout << "Done with check 1." << endl;
*/ 

   //  }
  ///End Set Binnging///   


  int diboson_count = 0; 
  int Zlight_count = 0; 
  int Zheavy_count = 0; 
  TH1F* new_histo[50000];

  TH1F* h_data = new TH1F("h_data", "data", NBINS,edges);
  TH1F* h_diboson = new TH1F("h_diboson", "diboson", NBINS,edges);
  TH1F* h_Zlight = new TH1F("h_Zlight", "Ztautaul", NBINS,edges);
  TH1F* h_ZtautauHF = new TH1F("h_ZtautauHF", "ZtautauHF", NBINS,edges);
  TH1F* h_Ztautau = new TH1F("h_Ztautau", "Ztautau", NBINS,edges);
  TH1F* h_ttbar = new TH1F("h_ttbar", "ttbar", NBINS,edges);
  TH1F* h_Fakes = new TH1F("h_Fakes", "Fakes", NBINS,edges);
  TH1F* h_fake;
  TH1F* h_ttbarFake;
  TH1F* h_ZZ;
  TH1F* h_WZ;
  TH1F* h_WW;
  TH1F* h_Zbb;
  TH1F* h_Zttl;
  TH1F* h_Zttcl;
  TH1F* h_Zttcc;
  TH1F* h_Zttbb;
  TH1F* h_Zttbc;
  TH1F* h_Zttbl;
  TH1F* h_ZttDY;
  TH1F* h_Graviton;
  TH1F* h_HeavyHiggs_260;
  TH1F* h_HeavyHiggs_300;
  TH1F* h_HeavyHiggs_275;
  TH1F* h_HeavyHiggs_325;
  TH1F* h_stopWt;
  TH1F* h_stopt;
  TH1F* h_stops;
  TH1F* h_WFake;

  TH1F* h_BkgTotal = new TH1F("h_BkgTotal", "Total Background", NBINS, edges);

  for(int i=0; i<mylist1->GetSize(); i++){

    TString mystring(mylist1->At(i)->GetName());


    //    if(ControlRegion)    if(mystring.Contains("0tag2pjet_0ptv_pTBB")){
    //    else   if(mystring.Contains("2tag2pjet_0ptv_SR_mHH_400")){

    //    if(ControlRegion)    if(mystring.Contains("0tag2pjet_0ptv_pTBB")){
    //      if(mystring.Contains("2tag2pjet_0ptv_SR_mHH_800")){




    //Rebin diboson histograms
      if(mystring.Contains("ZZ")){
	new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_ZZ = (TH1F*)new_histo[i]->Rebin(NBINS,"h_ZZ",edges);
      }
      else if(mystring.Contains("WW")){
	new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_WW = (TH1F*)new_histo[i]->Rebin(NBINS,"h_WW",edges);
      }
      else if(mystring.Contains("WZ")){
	new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_WZ = (TH1F*)new_histo[i]->Rebin(NBINS,"h_WZ",edges);
      }

      //Rebin Z+jets all jets
      else if(mystring.Contains("Zttcc") ){
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
        h_Zttcc = (TH1F*)new_histo[i]->Rebin(NBINS,"h_Zttcc",edges);
      }
      else if(mystring.Contains("Zttbb") ){
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
        h_Zttbb = (TH1F*)new_histo[i]->Rebin(NBINS,"h_Zttbb",edges);
      }
      else if(mystring.Contains("Zttbc") ){
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
        h_Zttbc = (TH1F*)new_histo[i]->Rebin(NBINS,"h_Zttbc",edges);
      }
      else if(mystring.Contains("Zttl") ){
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
        h_Zttl = (TH1F*)new_histo[i]->Rebin(NBINS,"h_Zttl",edges);
      }
      else if(mystring.Contains("Zttbl") ){
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
        h_Zttbl = (TH1F*)new_histo[i]->Rebin(NBINS,"h_Zttbl",edges);
      }
      else if(mystring.Contains("Zttcl") ){
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
        h_Zttcl = (TH1F*)new_histo[i]->Rebin(NBINS,"h_Zttcl",edges);
      }
      else if(mystring.Contains("Zbb") ){
	new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_Zbb = (TH1F*)new_histo[i]->Rebin(NBINS,"h_Zbb",edges);
      }
//      else if(mystring.Contains("ZttMGDY") ){
//        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
//        h_ZttMGDY = (TH1F*)new_histo[i]->Rebin(NBINS,"h_ZttMGDY",edges);
//      }


      else if(mystring.Contains("ttbarFake") ){  
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");                                                                       
        h_ttbarFake = (TH1F*)new_histo[i]->Rebin(NBINS,"h_ttbarFake",edges);                                                                                        
      }       
      else if(mystring.Contains("ttbar") ){
	new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_ttbar = (TH1F*)new_histo[i]->Rebin(NBINS,"h_ttbar",edges);
	for(int j=1;j<=NBINS; j++){
	  if(h_ttbar->GetBinContent(j)==0){ 
	     h_ttbar->SetBinContent(j,0.00001);
	     h_ttbar->SetBinError(j,0.00001);
	  }
	}
      }
      else if(mystring.Contains("stopt") ){
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
        h_stopt = (TH1F*)new_histo[i]->Rebin(NBINS,"h_stopt",edges);
      }
      else if(mystring.Contains("stops") ){
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
        h_stops = (TH1F*)new_histo[i]->Rebin(NBINS,"h_stops",edges);
      }
      else if(mystring.Contains("stopWt") ){
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
        h_stopWt = (TH1F*)new_histo[i]->Rebin(NBINS,"h_stopWt",edges);
      }
      else if(mystring.Contains("WFake") ){
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_WFake = (TH1F*)new_histo[i]->Rebin(NBINS,"h_WFake",edges);
      }
      else if(mystring.Contains("Fake") ){
	new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_fake = (TH1F*)new_histo[i]->Rebin(NBINS,"h_fake",edges);
	//	for(int j=1;j<=NBINS; j++){
//	  if(h_fake->GetBinContent(j)==0){ 
//	    h_fake->SetBinContent(j,0.00001);
//	    h_fake->SetBinError(j,0.00001);
//	  }
//	  if(h_fake->GetBinContent(j)<0){ 
//	    h_fake->SetBinContent(j,0.00001);
//	    //	    h_fake->SetBinError(j,0.00001);
//	}
      }//else
      else if(mystring.Contains("data") ){
	new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_data = (TH1F*)new_histo[i]->Rebin(NBINS,"h_data",edges);
      }//else
      else if(mystring.Contains("Ghhbbtautau300c10") ){
	new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_Graviton = (TH1F*)new_histo[i]->Rebin(NBINS,"h_Graviton",edges);
      }//else
      else if(mystring.Contains("Hhhbbtautau260") ){
	new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_HeavyHiggs_260 = (TH1F*)new_histo[i]->Rebin(NBINS,"h_HeavyHiggs_260",edges);
      }//else
      else if(mystring.Contains("Hhhbbtautau275") ){
	new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_HeavyHiggs_275 = (TH1F*)new_histo[i]->Rebin(NBINS,"h_HeavyHiggs_275",edges);
      }//else
      else if(mystring.Contains("Hhhbbtautau300") ){
	new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
	h_HeavyHiggs_300 = (TH1F*)new_histo[i]->Rebin(NBINS,"h_HeavyHiggs_300",edges);
      }//else
      else if(mystring.Contains("Hhhbbtautau325") ){
        new_histo[i] = (TH1F*)gDirectory->Get(mylist1->At(i)->GetName())->Clone("new_histo");
        h_HeavyHiggs_325 = (TH1F*)new_histo[i]->Rebin(NBINS,"h_HeavyHiggs_325",edges);
      }//else  
  }//mHH loop
  //}
  
  //Merge dibosons
  //  h_ZZ->Sumw2();
  h_diboson->Add(h_ZZ);
  cout<<"here"<<endl;
  h_diboson->Add(h_WW);
  cout<<"here2"<<endl;
  h_diboson->Add(h_WZ);
 	
	for(int i = 0; i < NBINS; i++){

		cout << "diboson bin " << i << " Bin Content: " << h_diboson -> GetBinContent(i) << " Error: " << h_diboson -> GetBinError(i);

		if(h_diboson -> GetBinContent(i) == 0){
		cout << " No relative error to calculate" << endl;
		}
		else{	
		double relativeError_diboson = (h_diboson -> GetBinError(i))/(h_diboson -> GetBinContent(i));
		cout << " Relative Error: " << relativeError_diboson << endl;
		}
 	}

 //Merge Z+jets
  cout<<"here3"<<endl;
  h_Ztautau->Add( h_Zttl);
  h_Ztautau->Add( h_Zttcl);
  h_Ztautau->Add( h_Zttbl);

	for(int i = 0; i < NBINS; i++){
               
		cout << "Ztautau bin " << i << " Bin Content: " << h_Ztautau -> GetBinContent(i) << " Error: " << h_Ztautau -> GetBinError(i);

		if(h_Ztautau -> GetBinContent(i) == 0){
                cout << " No relative error to calculate" << endl;
                }
                else{
		double relativeError_Ztautau = (h_Ztautau -> GetBinError(i))/(h_Ztautau -> GetBinContent(i));
                cout << " Relative Error: " << relativeError_Ztautau << endl;
		}
        }

  h_ZtautauHF->Add( h_Zttcc);
  h_ZtautauHF->Add( h_Zttbb);
  h_ZtautauHF->Add( h_Zttbc);
  h_ZtautauHF->Add( h_Zbb);
  h_ZtautauHF->Scale(1.4);

	for(int i = 0; i < NBINS; i++){

		cout << "ZtautauHF bin " << i << " Bin Content: " << h_ZtautauHF -> GetBinContent(i) << " Error: " << h_ZtautauHF -> GetBinError(i);
		
		if(h_ZtautauHF -> GetBinContent(i) == 0){
		cout << " No relative error to calculate" << endl;
                }
                else{ 
	        double relativeError_ZtautauHF = (h_ZtautauHF -> GetBinError(i))/(h_ZtautauHF -> GetBinContent(i));
                cout << " Relative Error: " << relativeError_ZtautauHF << endl;
		}
        }

  h_Fakes->Add(h_fake);
  h_Fakes->Add(h_ttbarFake);
  h_Fakes->Add(h_WFake);

	for(int i = 0; i < NBINS; i++){
         	
		cout << "Fakes bin " << i << " Bin Content: " << h_Fakes -> GetBinContent(i) << " Error: " << h_Fakes -> GetBinError(i);
	
		if(h_Fakes -> GetBinContent(i) == 0){
                cout << " No relative error to calculate" << endl;
                }
                else{
		double relativeError_Fakes = (h_Fakes -> GetBinError(i))/(h_Fakes -> GetBinContent(i));
                cout << " Relative Error: " << relativeError_Fakes << endl;
                }
        }

  h_ttbar->Add(h_stopt);
  h_ttbar->Add(h_stops);
  h_ttbar->Add(h_stopWt);

	for(int i = 0; i < NBINS; i++){

		cout << "ttbar bin " << i << " Bin Content: " << h_ttbar -> GetBinContent(i) << " Error: " << h_ttbar -> GetBinError(i);

		if(h_ttbar -> GetBinContent(i) == 0){
                cout << " No relative error to calculate" << endl;
                }
                else{
                double relativeError_ttbar = (h_ttbar -> GetBinError(i))/(h_ttbar -> GetBinContent(i));
                cout << " Relative Error: " << relativeError_ttbar << endl;
		}
        }	

  h_HeavyHiggs_260->Scale(1./1000.);

	for(int i = 0; i < NBINS; i++){

		cout << "Heavy Higgs 260 GeV bin " << i << " Bin Content: " << h_HeavyHiggs_260 -> GetBinContent(i) << " Error: " << h_HeavyHiggs_260 -> GetBinError(i);

		if(h_HeavyHiggs_260 -> GetBinContent(i) == 0){
                cout << " No relative error to calculate" << endl;
                }
                else{
                double relativeError_HeavyHiggs_260 = (h_HeavyHiggs_260  -> GetBinError(i))/(h_HeavyHiggs_260 -> GetBinContent(i));
                cout << " Relative Error: " << relativeError_HeavyHiggs_260 << endl; 
		 }
        }

  h_HeavyHiggs_275->Scale(1./1000.);

	for(int i = 0; i < NBINS; i++){
	
		cout << "Heavy Higgs 275 GeV bin " << i << " Bin Content: " << h_HeavyHiggs_275 -> GetBinContent(i) << " Error: " << h_HeavyHiggs_275 -> GetBinError(i);
                 
                if(h_HeavyHiggs_275 -> GetBinContent(i) == 0){
                cout << " No relative error to calculate" << endl;
                }
                else{
                double relativeError_HeavyHiggs_275 = (h_HeavyHiggs_275  -> GetBinError(i))/(h_HeavyHiggs_275 -> GetBinContent(i)); 
                cout << " Relative Error: " << relativeError_HeavyHiggs_275 << endl;
                 }
        }

  h_HeavyHiggs_300->Scale(1./1000.);

	for(int i = 0; i < NBINS; i++){

		cout << "Heavy Higgs 300 GeV bin " << i << " Bin Content: " << h_HeavyHiggs_300 -> GetBinContent(i) << " Error: " << h_HeavyHiggs_300 -> GetBinError(i);
                 
                if(h_HeavyHiggs_300 -> GetBinContent(i) == 0){
                cout << " No relative error to calculate" << endl;
                }
                else{
                double relativeError_HeavyHiggs_300 = (h_HeavyHiggs_300  -> GetBinError(i))/(h_HeavyHiggs_300 -> GetBinContent(i)); 
                cout << " Relative Error: " << relativeError_HeavyHiggs_300 << endl;
                 }

        }

  h_HeavyHiggs_325->Scale(1./1000.);

	for(int i = 0; i < NBINS; i++){

                cout << "Heavy Higgs 325 GeV bin " << i << " Bin Content: " << h_HeavyHiggs_325-> GetBinContent(i) << " Error: " << h_HeavyHiggs_325 -> GetBinError(i);

                if(h_HeavyHiggs_325 -> GetBinContent(i) == 0){
                cout << " No relative error to calculate" << endl;
                } 
                else{
                double relativeError_HeavyHiggs_325 = (h_HeavyHiggs_325  -> GetBinError(i))/(h_HeavyHiggs_325 -> GetBinContent(i));
                cout << " Relative Error: " << relativeError_HeavyHiggs_325 << endl;
                 }
        }

  //Signal injection....
  h_data->Add( h_HeavyHiggs_325, 4./1000.);//limit is 3.18

	for(int i = 0; i < NBINS; i++){

		cout << "Data bin " << i << " Bin Content: " << h_data -> GetBinContent(i) << " Error: " << h_data -> GetBinError(i);

		if(h_data -> GetBinContent(i) == 0){
                cout << " No relative error to calculate" << endl;
                }
                else{
                double relativeError_data = (h_data  -> GetBinError(i))/(h_data -> GetBinContent(i));
                cout << " Relative Error: " << relativeError_data << endl;
		}
        }

//Graviton errors
        for(int i = 0; i < NBINS; i++){

                cout << "Graviton bin " << i << " Bin Content: " << h_Graviton -> GetBinContent(i) << " Error: " << h_data -> GetBinError(i);

                if(h_Graviton -> GetBinContent(i) == 0){
                cout << " No relative error to calculate" << endl;
                }
                else{
                double relativeError_Graviton = (h_Graviton  -> GetBinError(i))/(h_Graviton -> GetBinContent(i));
                cout << " Relative Error: " << relativeError_Graviton << endl;
                }
        }


	ofstream file1;
	file1.open("Graviton_ttbar_binning1.txt");
	if(file1.is_open()){
	file1 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;
		
		file1 << "Entries per bin > 0" << endl;
		for(int i = 0; i < NBINS; i++){
			if(h_Graviton -> GetBinContent(i) > 0 && h_ttbar -> GetBinContent(i) > 0){
				float signal = h_Graviton -> GetBinContent(i);
				float bkg    = h_ttbar -> GetBinContent(i);
				float StoB    = signal/bkg;
				file1 << "For bin: " << i << " the signal to background ratio is: " << StoB << endl;
			}	
			else {continue;}	
		}				
		
		file1 << "Entries per bin > 2" << endl;
		for(int i = 0; i < NBINS; i++){	
			if(h_Graviton -> GetBinContent(i) > 2 && h_ttbar -> GetBinContent(i) > 2){
                                float signal = h_Graviton -> GetBinContent(i);
                                float bkg    = h_ttbar -> GetBinContent(i);
                                float StoB    = signal/bkg;
                                file1 << "For bin: " << i << " the signal to background ratio is: " << StoB << endl;
			}
			else {continue;}
                }
	file1.close();
	}
	else {cout << "Unable to open file1" << endl;}

        ofstream file2;
        file2.open("HeavyHiggs_325_fake_binning1.txt");
        if(file2.is_open()){
        file2 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;

                file2 << "Entries per bin > 0" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_HeavyHiggs_325 -> GetBinContent(i) > 0 && h_Fakes -> GetBinContent(i) > 0){
                                float signal = h_HeavyHiggs_325 -> GetBinContent(i);
                                float bkg    = h_Fakes -> GetBinContent(i);
                                float StoB    = signal/bkg;
                                file2 << "For bin: " << i << " the signal to background ratio is: " << StoB << endl;
                        }
                        else {continue;}
                }

                file2 << "Entries per bin > 2" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_HeavyHiggs_325 -> GetBinContent(i) > 2 && h_Fakes -> GetBinContent(i) > 2){
                                float signal = h_HeavyHiggs_325 -> GetBinContent(i);
                                float bkg    = h_Fakes -> GetBinContent(i);
                                float StoB    = signal/bkg;
                                file2 << "For bin: " << i << " the signal to background ratio is: " << StoB << endl;
                        }
                        else {continue;}
                }
        file2.close();
	}
        else {cout << "Unable to open file2" << endl;}

	ofstream file3;
        file3.open("diboson_ZtautauHF_binning1.txt");
        if(file3.is_open()){
        file3 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;

                file3 << "Entries per bin > 0" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_diboson -> GetBinContent(i) > 0 && h_ZtautauHF -> GetBinContent(i) > 0){
                                float signal = h_diboson -> GetBinContent(i);
                                float bkg    = h_ZtautauHF -> GetBinContent(i);
                                float StoB    = signal/bkg;
                                file3 << "For bin: " << i << " the signal to background ratio is: " << StoB << endl;
                        }
                        else {continue;}
                }

                file3 << "Entries per bin > 2" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_diboson -> GetBinContent(i) > 2 && h_ZtautauHF -> GetBinContent(i) > 2){
                                float signal = h_diboson -> GetBinContent(i);
                                float bkg    = h_ZtautauHF -> GetBinContent(i);
                                float StoB    = signal/bkg;
                                file3 << "For bin: " << i << " the signal to background ratio is: " << StoB << endl;
                        }
                        else {continue;}
                }
        file3.close();
	}
        else {cout << "Unable to open file3" << endl;}

	ofstream file4;
        file4.open("HeavyHiggs_260_ttbar_binning1.txt");
        if(file4.is_open()){
        file4 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;

                file4 << "Entries per bin > 0" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_HeavyHiggs_260 -> GetBinContent(i) > 0 && h_ttbar -> GetBinContent(i) > 0){
                                float signal = h_HeavyHiggs_260 -> GetBinContent(i);
                                float bkg    = h_ttbar -> GetBinContent(i);
                                float StoB    = signal/bkg;
                                file4 << "For bin: " << i << " the signal to background ratio is: " << StoB << endl;
                        }
                        else {continue;}
                }

                file4 << "Entries per bin > 2" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_HeavyHiggs_260 -> GetBinContent(i) > 2 && h_ttbar -> GetBinContent(i) > 2){
                                float signal = h_HeavyHiggs_260 -> GetBinContent(i);
                                float bkg    = h_ttbar -> GetBinContent(i);
                                float StoB    = signal/bkg;
                                file4 << "For bin: " << i << " the signal to background ratio is: " << StoB << endl;
                        }
                        else {continue;}
                }
        file4.close();
	}
        else {cout << "Unable to open file4" << endl;}

	ofstream file5;
        file5.open("Graviton_ttbar_binning1.txt");
        if(file5.is_open()){
        file5 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;

                file5 << "Entries per bin > 0" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_Graviton -> GetBinContent(i) > 0 && h_Fakes -> GetBinContent(i) > 0){
                                float signal = h_Graviton -> GetBinContent(i);
                                float bkg    = h_Fakes -> GetBinContent(i);
                                float StoB    = signal/bkg;
                                file5 << "For bin: " << i << " the signal to background ratio is: " << StoB << endl;
                        }
                        else {continue;}
                }

                file5 << "Entries per bin > 2" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_Graviton -> GetBinContent(i) > 2 && h_Fakes -> GetBinContent(i) > 2){
                                float signal = h_Graviton -> GetBinContent(i);
                                float bkg    = h_Fakes -> GetBinContent(i);
                                float StoB    = signal/bkg;
                                file5 << "For bin: " << i << " the signal to background ratio is: " << StoB << endl;
                        }
                        else {continue;}
                }
        file5.close();
	}
        else {cout << "Unable to open file5" << endl;}


	ofstream file6;
        file6.open("Graviton_data_binning1.txt");
        if(file6.is_open()){
        file6 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;

                file6 << "Entries per bin > 0" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_Graviton -> GetBinContent(i) > 0 && h_data -> GetBinContent(i) > 0){
                                float signal = h_Graviton -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float StoD    = signal/data;
                                file6 << "For bin: " << i << " the signal to data ratio is: " << StoD << endl;
                        }
                        else {continue;}
                }

                file6 << "Entries per bin > 2" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_Graviton -> GetBinContent(i) > 2 && h_data -> GetBinContent(i) > 2){
                                float signal = h_Graviton -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float StoD    = signal/data;
                                file6 << "For bin: " << i << " the signal to data ratio is: " << StoD << endl;
                        }
                        else {continue;}
                }
        file6.close();
        }
	else {cout << "Unable to open file6" << endl;}

	ofstream file7;
        file7.open("diboson_data_binning1.txt");
        if(file7.is_open()){
        file7 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;

                file7 << "Entries per bin > 0" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_diboson -> GetBinContent(i) > 0 && h_data -> GetBinContent(i) > 0){
                                float signal = h_diboson -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float StoD    = signal/data; 
                                file6 << "For bin: " << i << " the signal to data ratio is: " << StoD << endl;
                        }
                        else {continue;}
                }

                file7 << "Entries per bin > 2" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_diboson -> GetBinContent(i) > 2 && h_data -> GetBinContent(i) > 2){
                                float signal = h_diboson -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float StoD    = signal/data;
                                file7 << "For bin: " << i << " the signal to data ratio is: " << StoD << endl;
                        }
                        else {continue;}
                }
        file7.close();
        }
	else {cout << "Unable to open file7" << endl;}

	ofstream file8;
        file8.open("HeavyHiggs_300_data_binning1.txt");
        if(file8.is_open()){
        file8 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;

                file8 << "Entries per bin > 0" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_HeavyHiggs_300 -> GetBinContent(i) > 0 && h_data -> GetBinContent(i) > 0){
                                float signal = h_diboson -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float StoD    = signal/data; 
                                file8 << "For bin: " << i << " the signal to data ratio is: " << StoD << endl;
                        }
                        else {continue;}
                }

                file8 << "Entries per bin > 2" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_HeavyHiggs_300 -> GetBinContent(i) > 2 && h_data -> GetBinContent(i) > 2){
                                float signal = h_HeavyHiggs_300 -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float StoD    = signal/data; 
                                file8 << "For bin: " << i << " the signal to data ratio is: " << StoD << endl;
                        }
                        else {continue;}
                }
        file8.close();
        }
	else {cout << "Unable to open file8" << endl;}
/*
	ofstream file9;
        file9.open("Fakes_data_binning1.txt");
        if(file9.is_open()){
        file9 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;

                file9 << "Entries per bin > 0" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_Fakes -> GetBinContent(i) > 0 && h_data -> GetBinContent(i) > 0){
                                float bkg     = h_Fakes -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float BtoD    = bkg/data; 
                                file9 << "For bin: " << i << " the background to data ratio is: " << BtoD << endl;         
                        }
                        else {continue;}
                }

                file9 << "Entries per bin > 2" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_Fakes -> GetBinContent(i) > 2 && h_data -> GetBinContent(i) > 2){
                                float bkg     = h_Fakes -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float BtoD    = bkg/data; 
                                file9 << "For bin: " << i << " the background to data ratio is: " << BtoD << endl;
                        }
                        else {continue;}
                }
        file9.close();
        }
	else {cout << "Unable to open file9" << endl;}

	ofstream file10;
        file10.open("ttbar_data_binning1.txt");
        if(file10.is_open()){
        file10 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;

                file10 << "Entries per bin > 0" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_ttbar -> GetBinContent(i) > 0 && h_data -> GetBinContent(i) > 0){
                                float bkg     = h_ttbar -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float BtoD    = bkg/data; 
                                file10 << "For bin: " << i << " the background to data ratio is: " << BtoD << endl;
                        }
                        else {continue;}
                }

                file10 << "Entries per bin > 2" << endl;
                for(int i = 0; i < NBINS; i++){
                        if(h_ttbar -> GetBinContent(i) > 2 && h_data -> GetBinContent(i) > 2){
                                float bkg     = h_ttbar -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float BtoD    = bkg/data; 
                                file10 << "For bin: " << i << " the background to data ratio is: " << BtoD << endl;
                        }
                        else {continue;}
                }
        file10.close();
        }
	else {cout << "Unable to open file10" << endl;}

	ofstream file11;
        file11.open("ZtautauHF_data_binning1.txt");
        if(file11.is_open()){
        file11 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;

                file11 << "Entries per bin > 0" << endl;
                for(int i = 0; i < NBINS; i++){ 
                        if(h_ZtautauHF -> GetBinContent(i) > 0 && h_data -> GetBinContent(i) > 0){
                                float bkg     = h_ZtautauHF -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float BtoD    = bkg/data;
                                file11 << "For bin: " << i << " the background to data ratio is: " << BtoD << endl;
                        }
                        else {continue;}
                }

                file11 << "Entries per bin > 2" << endl;
                for(int i = 0; i < NBINS; i++){ 
                        if(h_ZtautauHF -> GetBinContent(i) > 2 && h_data -> GetBinContent(i) > 2){
                                float bkg     = h_ZtautauHF -> GetBinContent(i);
                                float data    = h_data -> GetBinContent(i);
                                float BtoD    = bkg/data;
                                file11 << "For bin: " << i << " the background to data ratio is: " << BtoD << endl;
                        }
                        else {continue;}
                }
        file11.close();
        }
	else {cout << "Unable to open file11" << endl;}
*/

	float relErrorBT[NBINS];

	h_BkgTotal -> Add(h_Fakes);
 	h_BkgTotal -> Add(h_ttbar);
  	h_BkgTotal -> Add(h_ZtautauHF);
  	h_BkgTotal -> Add(h_Ztautau); 

	ofstream file12;
        file12.open("Graviton_BkgTotal_binning1.txt");
        if(file12.is_open()){
        file12 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;
        file12 << "Entries per bin > 1" << endl;

        float GtoBT[NBINS];
        float relErrorG[NBINS];

        for(int i = 0; i < NBINS; i++){
                if(h_Graviton -> GetBinContent(i) > 1 && h_BkgTotal -> GetBinContent(i) > 1){
                        double relativeError_Graviton = (h_Graviton  -> GetBinError(i))/(h_Graviton -> GetBinContent(i));
                        relErrorG[i] = relativeError_Graviton;
			file12 << "Graviton bin " << i << " Bin Content: " << h_Graviton -> GetBinContent(i) << " Error: " << h_Graviton -> GetBinError(i) << " Relative Error of Signal: " << relativeError_Graviton << endl;
                                                   
                        float signal = h_Graviton -> GetBinContent(i);
                        float bkg    = h_BkgTotal -> GetBinContent(i);
                        float StoB   = signal/bkg;
                        GtoBT[i] = StoB;
			file12 << "For bin: " << i << " the signal to total background ratio is: " << StoB << endl;


                        double relativeError_BkgTotal = (h_BkgTotal -> GetBinError(i))/(h_BkgTotal -> GetBinContent(i));
                        relErrorBT[i] = relativeError_BkgTotal;
			file12 << "Total Background bin " << i << " Bin Content: " << h_BkgTotal -> GetBinContent(i) << " Error: " << h_BkgTotal -> GetBinError(i) << " Relative Error of total background: " << relativeError_BkgTotal << endl;
               
		 }
                else {continue;}
        }
        file12.close();
	}
        else {cout << "Unable to open file12" << endl;}

	ofstream file13;
        file13.open("diboson_BkgTotal_binning1.txt");
        if(file13.is_open()){
        file13 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;
        file13 << "Entries per bin > 1" << endl;

        float dBtoBT[NBINS];
        float relErrordB[NBINS];

        for(int i = 0; i < NBINS; i++){
                if(h_diboson -> GetBinContent(i) > 1 && h_BkgTotal -> GetBinContent(i) > 1){
                        double relativeError_diboson = (h_diboson  -> GetBinError(i))/(h_Graviton -> GetBinContent(i));
                        relErrordB[i] = relativeError_diboson;
			file13 << "diboson bin " << i << " Bin Content: " << h_diboson -> GetBinContent(i) << " Error: " << h_diboson -> GetBinError(i) << " Relative Error of Signal: " << relativeError_diboson << endl;

                        float signal = h_diboson -> GetBinContent(i);
                        float bkg    = h_BkgTotal -> GetBinContent(i);
                        float StoB   = signal/bkg;
                        dBtoBT[i] = StoB;
			file13 << "For bin: " << i << " the signal to total background ratio is: " << StoB << endl;

                        double relativeError_BkgTotal = (h_BkgTotal -> GetBinError(i))/(h_BkgTotal -> GetBinContent(i));
                        relErrorBT[i] = relativeError_BkgTotal;
			file13 << "Total Background bin " << i << " Bin Content: " << h_BkgTotal -> GetBinContent(i) << " Error: " << h_BkgTotal -> GetBinError(i) << " Relative Error of total background: " << relativeError_BkgTotal << endl;

                }
                else {continue;}
        }
        file13.close();
	}
        else {cout << "Unable to open file13" << endl;}

	ofstream file14;
        file14.open("HeavyHiggs_300_BkgTotal_binning1.txt");
        if(file14.is_open()){
        file14 << "For binning: {-1., -0.75,-0.50,-0.3, -0.17, 0.,0.2,0.55,0.81,1.0}" << endl;
        file14 << "Entries per bin > 1" << endl;

        float HH300toBT[NBINS];
        float relErrorHH300[NBINS];

        for(int i = 0; i < NBINS; i++){
                if(h_HeavyHiggs_300 -> GetBinContent(i) > 1 && h_BkgTotal -> GetBinContent(i) > 1){                
                        double relativeError_HeavyHiggs_300 = (h_HeavyHiggs_300  -> GetBinError(i))/(h_HeavyHiggs_300 -> GetBinContent(i)); 
                        relErrorHH300[i] = relativeError_HeavyHiggs_300;
			file14 << "Heavy Higgs 300 bin " << i << " Bin Content: " << h_HeavyHiggs_300 -> GetBinContent(i) << " Error: " << h_HeavyHiggs_300 -> GetBinError(i) << " Relative Error of Signal: " << relativeError_HeavyHiggs_300 << endl;                             
                      
                        float signal = h_HeavyHiggs_300 -> GetBinContent(i);
                        float bkg    = h_BkgTotal -> GetBinContent(i);
                        float StoB   = signal/bkg;
                        HH300toBT[i] = StoB;
			file14 << "For bin: " << i << " the signal to total background ratio is: " << StoB << endl;

                        
                        double relativeError_BkgTotal = (h_BkgTotal -> GetBinError(i))/(h_BkgTotal -> GetBinContent(i));
                        relErrorBT[i] = relativeError_BkgTotal;
			file14 << "Total Background bin " << i << " Bin Content: " << h_BkgTotal -> GetBinContent(i) << " Error: " << h_BkgTotal -> GetBinError(i) << " Relative Error of total background: " << relativeError_BkgTotal << endl;

                }
                else {continue;}
        }

	
 //	TGraph* graph = new TGraph(9, HH300toBT, relErrorHH300);
	float bins[9] = {1.,2.,3.,4.,5.,6.,7.,8.,9.};
	
	TCanvas* c0    = new TCanvas("c0", " ", 1500, 600);
	TPad* pad1 = new TPad();
	pad1 -> Draw();
	pad1 -> cd();
	TGraph* graphStoBT = new TGraph(9, bins, HH300toBT);
	graphStoBT -> Draw();
	graphStoBT -> GetYaxis() -> SetTitle("S/B");
	graphStoBT -> GetXaxis() -> SetTitle("Bin Number");
	TGaxis* secondY = new TGaxis(9.8, 0, 9.8, 0.024, 0, 0.024, 510, "Y+");
        secondY -> SetTitle("S/B");
        secondY -> Draw();
	
	TCanvas* c1 = new TCanvas("c1", " " , 1500, 600);	
        TPad* pad2 = new TPad("pad2","",0,0,1,1);
	pad2 -> Draw();
	pad2 -> cd();
	TGraph* graphRelErrorS = new TGraph(NBINS, bins, relErrorHH300);
	graphRelErrorS -> Draw();
	graphRelErrorS -> GetYaxis() -> SetTitle("relError Signal");
        graphRelErrorS -> GetXaxis() -> SetTitle("Bin Number");
	
	TCanvas* c2 = new TCanvas("c2", " " , 1500, 600);
	TPad*   p  = new TPad();
	p -> Draw();
	p -> cd();
	graphRelErrorS -> Draw();
	graphRelErrorS -> GetYaxis() -> SetTitle("relError Signal");
        graphRelErrorS -> GetXaxis() -> SetTitle("Bin Number");
//      TGaxis* secondY = new TGaxis(9.8, 0, 9.8, 0.024, 0, 0.024, 510, "Y+");
	secondY -> SetTitle("S/B");
        secondY -> Draw();
	graphStoBT -> Draw("CP");
        
	file14.close();
	}
        else {cout << "Unable to open file14" << endl;}
	
  //  if(ControlRegion){TFile *f_out = TFile::Open("pTBB_ZCR_Sept30.root","RECREATE");}
  //  else  {
 TFile *f_out = TFile::Open("mHH_LepHad_325BDT_325injected.root","RECREATE");
 //}
  
  f_out->cd();
  h_Graviton->Write("Graviton");
  h_HeavyHiggs_260->Write("HeavyHiggs_260");
  h_HeavyHiggs_275->Write("HeavyHiggs_275");
  h_HeavyHiggs_300->Write("HeavyHiggs_300");
  h_HeavyHiggs_325->Write("HeavyHiggs_325");
  h_diboson->Write("diboson");  
  h_Ztautau->Write("Ztautau");  
  h_ZtautauHF->Write("ZtautauHF");  
  h_ttbar->Write("ttbar");  
  h_fake->Write("Fake");  
  h_data->Write("Data"); 

  h_BkgTotal -> Write("BkgTotal");
 
  f_out->Close();
 




  /* 
//This part was when the fake histogram was missing
  //Get the fake histogram from the Sr_300 dir:
  f1->cd();
  gDirectory->cd("SR_300");
  TList *mylist_sr = (TList*)gDirectory->GetListOfKeys();
  for(int i=0; i<mylist_sr->GetSize(); i++){      
    TString mystring_s(mylist_sr->At(i)->GetName()); 
    //    if(mystring_s.Contains("Fake_2tag2pjet_0ptv_SR_mHH_300")){
      if(mystring_s.Contains("Fake_2tag2pjet_0ptv_mHH")){
       TH1F *new_histo_s = (TH1F*)gDirectory->Get(mylist_sr->At(i)->GetName())->Clone("new_histo_s");                                     
       h_s[1] = new TH1F("h1_s"+mystring_s, mystring_s, NBINS,edges);   
       for(int j=0;j<(new_histo_s->GetNbinsX());j++){         
	 h_s[1]->Fill(j,new_histo_s->GetBinContent(j));    
       }   
      }
  }

  
  TFile *f_out_2 = TFile::Open("mHH_Sept9_Fake.root","RECREATE");   
  f_out_2->cd();                                                                                                          
  if(h_s[1])      h_s[1]->Write(); 
  
  */
  //Systematics:
  /*
  gDirectory->cd("Systematics");
  TList *mylist_s = (TList*)gDirectory->GetListOfKeys();

  int count =0;
  const int set_count =50;
  for(int i=0; i<mylist_s->GetSize(); i++){
    TString mystring_s(mylist_s->At(i)->GetName());
    if(mystring_s.Contains("Ghhbbtautau300c10_2tag2pjet_0ptv_SR_mMMC_300")|| mystring_s.Contains("Fake_2tag2pjet_0ptv_SR_mMMC_300")||mystring_s.Contains("Zttbb_2tag2pjet_0ptv_SR_mMMC_300")||mystring_s.Contains("ttbar_2tag2pjet_0ptv_SR_mMMC_300")){
      cout <<count<<" "<< mystring_s << endl;
	TH1F *new_histo_s = (TH1F*)gDirectory->Get(mylist_s->At(i)->GetName())->Clone("new_histo_s");
	h_s[count] = new TH1F("h1_s"+mystring_s, mystring_s, NBINS,edges);
	for(int j=0;j<(new_histo_s->GetNbinsX());j++){
	  h_s[count]->Fill(j,new_histo_s->GetBinContent(j));
	}
	count++;
	//	f_out->cd();	
	//	h_s->Write(mystring_s);
      }
    }
  
  TFile *f_out_2 = TFile::Open("MMC_Aug9_Syst.root","RECREATE");
  f_out_2->cd();   
    for(int n=0; n<500; n++){
      if(h_s[n])      h_s[n]->Write();
      cout<<"second loop: "<<n<<" "<<h_s[n]->GetName() <<endl;
      //      h_s[1]->Write();
        }

  f_out_2->Close();
  
  //  for(int i=0; i<mylist2->GetSize(); i++){
  //    f2->Get(mylist2->At(i)->GetName())->Write();
  //  }
  
  */


}
