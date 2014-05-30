{

  std::string outPrefix = "results/2014xxxx";

  tsw::Samples2012 samples("zEffiTree");
  std::string selnString = "(abs(mcZ_ele1_p4.Eta())<=1.442 || (abs(mcZ_ele1_p4.Eta())>=1.56 && abs(mcZ_ele1_p4.Eta())<=2.5))";
  selnString += " && (abs(mcZ_ele2_p4.Eta())<=1.442 || (abs(mcZ_ele2_p4.Eta())>=1.56 && abs(mcZ_ele2_p4.Eta())<=2.5))";
  selnString += " && (mcZ_ele1_p4.Et()>20.0 && mcZ_ele2_p4.Et()>20.0)";
  tsw::TwoDimPlotter plotter;

  plotter.setTree("zBosonEffiTree");
  plotter.setSelection(selnString);
  //plotter.descriptiveText("MC truth after acceptance cuts; gauge interaction.");
  plotter.outFilePrefix( outPrefix + "/qStarGI_2D_afterBasicAcc_" );

  plotter.add( samples.qStarGI_M1000() );

  plotter.add( samples.qStarGI_M1500() );
  plotter.add( samples.qStarGI_M2000() );
  plotter.add( samples.qStarGI_M2500() );


  tsw::AxisDefn zPtAxis("ZpT", 60, 3e2, 15e2, "Z boson p_{T} [GeV]");

  plotter.makePlot( zPtAxis, tsw::AxisDefn("eleA_p4.Pt()", 140, 0.0, 1400, "Leading electron p_{T} [GeV]") );
  plotter.makePlot( zPtAxis, tsw::AxisDefn("eleA_p4.Eta()", 104, -2.6, 2.6, "Leading electron #eta") );
  plotter.makePlot( zPtAxis, tsw::AxisDefn("eleB_p4.Pt()", 80, 0.0, 800, "Sub-leading electron p_{T} [GeV]") );
  plotter.makePlot( zPtAxis, tsw::AxisDefn("eleB_p4.Eta()", 104, -2.6, 2.6, "Sub-leading electron #eta") );
  plotter.makePlot( zPtAxis, tsw::AxisDefn("ZdR", 35, 0.0, 0.7, "#DeltaR_{ee}") );
  plotter.makePlot( zPtAxis, tsw::AxisDefn("Zp4.Gamma()", 100, 0.0, 20.0, "Lorentz #gamma") );

}
