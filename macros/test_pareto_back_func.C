{
  gSystem->Load("libRooFit") ;
  using namespace RooFit ;

  TCanvas* c1 = new TCanvas("c1","",500,500);
  c1->SetLogy();

  // get data set 

  // declare variables in ntuple wanted. 

  RooRealVar pT("ZpT","ZpT",100,800) ;


  // --> SETTING UP DATASET

  //TFile fg("/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_53X_20130212/batch/DYToEE-M50-MG_1_modIsoZCandTree.root") ;
  TChain* modIsoZBosonTree = new TChain("modIsoZBosonTree");
  modIsoZBosonTree->Add("/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_53X_20130212/batch/DYToEE-M50-MG_1_modIsoZCandTree.root");
  modIsoZBosonTree->Add("/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_53X_20130212/batch/DYToEE-M50-MG_2_modIsoZCandTree.root");
  modIsoZBosonTree->Add("/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_53X_20130212/batch/DYToEE-M50-MG_3_modIsoZCandTree.root");
  modIsoZBosonTree->Add("/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_53X_20130212/batch/DYToEE-M50-MG_4_modIsoZCandTree.root");
  modIsoZBosonTree->Add("/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_53X_20130212/batch/DYToEE-M50-MG_5_modIsoZCandTree.root");
  modIsoZBosonTree->Add("/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_53X_20130212/batch/DYToEE-M50-MG_6_modIsoZCandTree.root");
  RooDataSet ds("ds","ds",RooArgSet(pT),Import(*modIsoZBosonTree));

  TH1F *tmp = new TH1F("tmp","pt",140,100,800);
  modIsoZBosonTree->Draw("ZpT >> tmp");
 

  // --> BASIC PLOTS OF DISTRIBUTION

  c1->Draw(); c1->Update(); 
  cout << "Waiting for you to press any key ... " << endl;
  cin.get() ;


  RooPlot* xframe = pT.frame(Title("Pt distribution")) ;
  ds.plotOn(xframe,Binning(140),MarkerStyle(7)) ;
  xframe->Draw();

  c1->Draw(); c1->Update();
  cout << "Waiting for you to press any key ... " << endl; 
  cin.get();

 
  // --> SETTING UP FOR FITS

  //declare function and variables 
  RooRealVar a("a","a",0.02,0.01,10) ;
  RooRealVar b("b","b",2,0.01,5) ;
  RooGenericPdf genpdf("genpdf","genpdf","(pow(ZpT,-b)*exp(-a*ZpT) )",RooArgSet(pT,a,b));

  RooRealVar a1("a1","a1",0.02,0.01,10) ;
  RooRealVar b1("b1","b1",1,0.01,5) ;
  RooGenericPdf genpdf1("genpdf1","genpdf1","(exp(-a1*pow(ZpT,b1))  )",RooArgSet(pT,a1,b1));

  // pareto function test 

  RooRealVar a2("a2","a2",45,0.01,100) ;
  RooRealVar b2("b2","b2",0.15,0.01,5) ;
  RooRealVar pTmin("pTmin","pTmin",100,0.01,1000);
  pTmin.setConstant(kTRUE);
  RooGenericPdf pareto("pareto","pareto"," ( 1/a2*pow( (1+b2*(ZpT-pTmin)/a2), (-1/b2-1))  )", RooArgSet(pT,a2,b2,pTmin));


  //  pareto.plotOn(xframe,LineColor(kMagenta));
  xframe->Draw() ; 


  // Do fits for various functions 
  //    Type 
  //          1. pow(pT,-b)*exp(-a*pT)
  //          2. exp(-a1*pow(pT,b1)
  //          3. Pareto
  //        100. Define all functions

  
  Int_t func_type = 100 ; 
  Double_t llim = 100;
  Double_t ulim = 600;


  if (func_type == 1 || func_type == 100) { 
    cout << " Using function 1 pow(pT,-b)*exp(-a*pT) " << endl; 
    genpdf.fitTo(ds,Range(100,ulim));
  }
  if (func_type == 2 || func_type == 100) {
    cout << " Using function 2  exp(-a1*pow(pT,b1) " << endl; 
    genpdf1.fitTo(ds,Range(100,300));
  }
  if (func_type == 3 || func_type == 100) {
    cout << " Using function 3 Pareto " << endl; 
    pareto.fitTo(ds,Range(100,ulim));
  } 


  cout << " "<< endl ;
  cout << " end of fits" << endl; 
  cout << "Waiting for you to press any key ... " << endl; 
  cin.get();

  xframe->Draw();

  pareto.plotOn(xframe, Range(100,600), LineColor(kBlue));
  std::cout << "pareto chi^2 : " << xframe->chiSquare() << std::endl;
  genpdf.plotOn(xframe, Range(100,600), LineColor(kGreen));
  xframe->Draw() ; 


  // --> CALCULATING INTEGRALS

  // find integral of function. More painful than it should be !!! 
  cout << endl ; 
  RooAbsReal* Int_pareto = pareto.createIntegral(pT) ;
  cout << " integral of Pareto function " << Int_pareto.getVal() << endl ; 

  // set sub range over which to integrate

  pT.setRange("Int_range",400,500); 
  RooAbsReal* Int_pareto = pareto.createIntegral(pT, NormSet(pT), Range("Int_range")  ) ;
  Double_t int_sub_range[10];
  int_sub_range[1] = Int_pareto.getVal() ;
  cout << " integral of Pareto function sub range " << int_sub_range[1] << endl;

  cout << "Waiting for you to press any key ... " << endl; 
  cin.get();

  // --> REFITTING TO REDUCED RANGE

  std::cout << std::endl
            << " ------------------------------------" << std::endl
            << "  ++ REFITTING pareto to low pt part" << std::endl
            << " ------------------------------------" << std::endl;
  pareto.fitTo(ds,Range(100,300)) ;
  RooAbsReal* Int_pareto = pareto.createIntegral(pT) ;
  cout << " integral of Pareto function " << Int_pareto.getVal() << endl ; 

  pareto.plotOn(xframe,Range(100,600),LineColor(kRed),NormRange("full"));
  xframe->Draw() ; 

// set sub range over which to integrate

  pT.setRange("Int_range",400,500); 
  RooAbsReal* Int_pareto = pareto.createIntegral(pT,NormSet(pT), Range("Int_range")  ) ;

  int_sub_range[2] = Int_pareto.getVal() ;
  cout << " integral of Pareto function sub range " << int_sub_range[1] << " " << int_sub_range[2] << " " << int_sub_range[1]/int_sub_range[2] << endl ;   




}  // end for the moment


  genpdf.plotOn(xframe,LineColor(kMagenta));
  xframe->Draw() ; 

  c1->Draw();c1->Update();cin.get() ;

  genpdf1.plotOn(xframe,LineColor(kBlue));
  xframe->Draw() ; 


  c1->Draw();c1->Update();cin.get() ;
  genpdf.plotOn(xframe,Range(100,600),LineColor(kMagenta));
  genpdf1.plotOn(xframe,Range(100,600),LineColor(kBlue));
  xframe->Draw() ;

}

