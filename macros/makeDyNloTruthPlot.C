{

   std::string outPrefix = "results/2014xxxx";

   tsw::Samples2012 samples("zEffiTree");
   tsw::DistPlotter plotter(true);

   plotter.setTree("zBosonEffiTree");
   plotter.setWeight("genWeight * puWeight");
   //std::string selnString = "(abs(mcZ_ele1_p4.Eta())<1.44 && abs(mcZ_ele2_p4.Eta())<1.44) && (mcZ_ele1_p4.Et()>35.0 && mcZ_ele2_p4.Et()>35.0)";
   //plotter.setSelection("(Zmass<105 && Zmass>75) && (abs(dPhi)>=0.3 || abs(dEta)>=0.07) && (eleA_modHeepStdThr==0 && eleB_modHeepStdThr==0)");
   plotter.setSelection("(abs(mcZ_ele1_p4.Eta())<2.1) && (abs(mcZ_ele2_p4.Eta())<2.1) && (mcZ_ele1_p4.Et()>20.0) && (mcZ_ele2_p4.Et()>20.0)");

   plotter.outFilePrefix( outPrefix + "/dySamplesTruth_" );
   plotter.rescaleMC();

   plotter.add( tsw::AxisDefn("ZpT", "[0,2,4,6,8,10,12.5,15,17.5,20,30,40,50,70,90,110,150,190,250,350,550, 750,1000,1250,1500,1750,2000]", "Z boson p_{T} [GeV]", 1.0) );

   //   plotter.add( tsw::AxisDefn("Zp4.P()", 100, 0.0, 2000, "Z boson momentum [GeV]") );
   //   plotter.add( tsw::AxisDefn("Zp4.Eta()", 50, -2.5, 2.5, "Z boson #eta") );
   //   plotter.add( tsw::AxisDefn("dR", 120, 0.0, 1.2, "#DeltaR_{ee}") );
   //   plotter.add( tsw::AxisDefn("eleA_p4.Eta()", 50, -2.5, 2.5, "Leading ele #eta") );
   //   plotter.add( tsw::AxisDefn("eleB_p4.Eta()", 50, -2.5, 2.5, "Sub-leading ele #eta") );


   plotter.add( samples.dyEE_mg_merged() );
   //plotter.add( samples.dyEE_sherpa() );
   //plotter.add( samples.dyEE_powheg() );
   //plotter.add( samples.dyEE_pythia() );

   //   plotter.run();

   std::string nloFileName( "data/ptV_CMS.plot.txt" );
   std::vector<Float_t> binLims = tsw::GetColumnFromFile(nloFileName, 0);
   binLims.push_back(1400);
   size_t nBins = binLims.size() - 1;

   std::vector<Float_t> central_LO  = tsw::GetColumnFromFile(nloFileName, 1);
   std::vector<Float_t> central_NLO = tsw::GetColumnFromFile(nloFileName, 3);
   std::vector<Float_t> doubleQ_LO  = tsw::GetColumnFromFile(nloFileName, 7);
   std::vector<Float_t> doubleQ_NLO = tsw::GetColumnFromFile(nloFileName, 8);
   std::vector<Float_t> halfQ_LO    = tsw::GetColumnFromFile(nloFileName, 9);
   std::vector<Float_t> halfQ_NLO   = tsw::GetColumnFromFile(nloFilename, 10);
   

}
