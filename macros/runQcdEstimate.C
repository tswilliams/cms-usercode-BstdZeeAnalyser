{
   tsw::Samples2012 modIsoAnaTuples("modIsoZCandTree");
   tsw::Samples2012 emuAnaTuples("eleMuTree");
   tsw::Samples2012 abcdAnaTuples("abcdDiGsfTree");

   std::string outputDir("results/20140515");

   // QCD -- ABCD METHOD // 
   tsw::AbcdJetsEstimator abcdEstimator("abcdDiGsfFrPreTree");
   abcdEstimator
     .mcWeights("genWeight * 1 * puWeight")
     //     .mcWeights("genWeight * puWeight * tsw::totalClusEtTurnOn(eleA_p4.Pt(),eleA_p4.Eta()) * tsw::totalClusEtTurnOn(eleB_p4.Pt(),eleB_p4.Eta())")
     //     .mcWeights("genWeight * puWeight * tsw::totalClusEtTurnOn(eleA_p4.Pt(),eleA_p4.Eta())")// tsw::totalClusEtTurnOn(eleB_p4.Pt(),eleB_p4.Eta())")
      .baselineSeln("(Zmass<120.0 && Zmass>60.0) && trgDecision && (eleA_frPre==0 && eleB_frPre==0)")
      .data( abcdAnaTuples.data2012() )
      .add(  abcdAnaTuples.topBkgds() )
      .add(  abcdAnaTuples.vzBkgds() )
      .add(  abcdAnaTuples.dyTauTau_mg_merged() )
      .add(  abcdAnaTuples.dyEE_mg_merged() )
      .add(  abcdAnaTuples.wJets()  )
     .outFilePrefix( (outputDir+"/qcd_abcd/ABCD_all8TeV").c_str() );
   std::cout << "About to run ..." << std::endl;

   TH1* abcdEstimate = abcdEstimator.run();
   abcdEstimate->Scale(20., "width");

   // QCD -- SIDEBAND-BASED //

   tsw::SidebandJetsEstimator sidebandEstimator("modIsoZBosonTree", "1", "1");
   sidebandEstimator.ptBranch("ZpT");
   sidebandEstimator.massBranch("Zmass");
// sidebandEstimator.smearedMassBranch4mc("(tsw::GausianMultSmear(Zmass, 0.9935, 0.0082))");
   sidebandEstimator.setBaselineSelection( "(abs(dPhi)>=0.3 || abs(dEta)>=0.07)" );

   sidebandEstimator.add(  modIsoAnaTuples.dyTauTau_mg_merged() );
   sidebandEstimator.add(  modIsoAnaTuples.topBkgds() );
   sidebandEstimator.add(  modIsoAnaTuples.vzBkgds() );
   sidebandEstimator.add(  modIsoAnaTuples.dyEE_mg_merged() );
   sidebandEstimator.data( modIsoAnaTuples.data2012() );

   // sidebandEstimator.outputFileDir( "" );
   sidebandEstimator.outputFileTag( (outputDir+"/qcd_sideband/sidebandQCD_all8TeV").c_str() );
   TGraph* sidebandEstimate = sidebandEstimator.run();
   sidebandEstimate->SetLineColor(kRed);
   sidebandEstimate->SetMarkerColor(kRed);


   // QCD -- COMPARISON //

   TCanvas* c = new TCanvas("c_abcdVsSideband", "ABCD vs Sideband estimates");
   c->SetLogy();
   c->cd();
   abcdEstimate->SetYTitle("Events / 20GeV");
   abcdEstimate->Draw();

   TF1* fitFunc = new TF1("fitFunc", "exp([0]+[1]*x) + exp([2]+[3]*x)", 0, 900);
   fitFunc->SetParameter(0, 2.0);
   fitFunc->SetParameter(1, -9e-3);
   fitFunc->SetParameter(2, 5.5);
   fitFunc->SetParameter(3, -5.5e-2);
   fitFunc->SetLineColor(kBlue);
   TFitResultPtr fitResult = abcdEstimate->Fit("fitFunc", "I S");

   sidebandEstimate->Draw("P");

   c->SaveAs( (outputDir+"/qcd_abcdVsSideband_all8TeV_pt.pdf").c_str() );
   c->SaveAs( (outputDir+"/qcd_abcdVsSideband_all8TeV_pt.gif").c_str() );

   std::cout << std::endl << "chi2 = " << fitResult->Chi2() << std::endl;
}
