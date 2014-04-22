{
   tsw::Samples2012 modIsoAnaTuples("modIsoZCandTree");
   tsw::Samples2012 emuAnaTuples("eleMuTree");
   tsw::Samples2012 abcdAnaTuples("abcdDiGsfTree");


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
      .outFilePrefix("results/20140422/qcd_abcd/ABCD_all8TeV");
   std::cout << "About to run ..." << std::endl;
   abcdEstimator.run();


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
   sidebandEstimator.outputFileTag( "results/20140422/qcd_sideband/sidebandQCD_all8TeV" );
   sidebandEstimator.run();


   // QCD -- COMPARISON //

}
