{

  std::string outPrefix = "results/20140508";

   tsw::Samples2012 samples("zEffiTree");
   std::string selnString = "(abs(mcZ_ele1_p4.Eta())<1.44 && abs(mcZ_ele2_p4.Eta())<1.44) && (mcZ_ele1_p4.Et()>35.0 && mcZ_ele2_p4.Et()>35.0)";
   tsw::DistPlotter plotter(true);

   plotter.setTree("zBosonEffiTree");
   plotter.setSelection(selnString);
   //plotter.descriptiveText("MC truth after acceptance cuts; gauge interaction.");
   plotter.outFilePrefix( outPrefix + "/qStarGI_afterAcc_" );
   plotter.rescaleMC();

   plotter.add( tsw::AxisDefn("ZpT", 90, 0.0, 1800, "Z boson p_{T} [GeV]") );
   plotter.add( tsw::AxisDefn("ZdR", 120, 0.0, 1.2, "#DeltaR_{ee}") );

   tsw::DistPlotter plotterCI(plotter);
   plotterCI.outFilePrefix( outPrefix + "/qStarCI_afterAcc_" );


   tsw::MCSample qStarM1500( samples.qStarGI_M1500() );
   qStarM1500.mName  = "1.5TeV q* (GI)";
   qStarM1500.mColor = tsw::Black;
   tsw::MCSample qStarM2500( samples.qStarGI_M2500() );
   qStarM2500.mName = "2.5TeV q* (GI)";

   tsw::MCSample qStarCI_M1500( samples.qStarCI_M1500() );
   qStarCI_M1500.mName  = "1.5TeV q* (CI)";
   tsw::MCSample qStarCI_M2500( samples.qStarCI_M2500() );
   qStarCI_M2500.mName = "2.5TeV q* (CI)";
   


   plotter.add( qStarM1500 );
   plotter.add( qStarM2500 );
   plotter.run();

   plotterCI.add( qStarCI_M1500 );
   plotterCI.add( qStarCI_M2500 );
   plotterCI.run();

}
