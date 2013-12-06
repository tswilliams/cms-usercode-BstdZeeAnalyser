{
	gSystem->Load("/home/ppd/nnd85574/Work/BstdZee/tswAnaTools/lib/libtswAnaTools_CMSSW5XY.so");

	// DISTPLOTTER test

	//-> 0) Sample declarations

	tsw::MCSample qStarGI_private_1900("/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_20120909/int/qStarGI_1.9TeV_privReco_modIsoZCandTree.root", "PRIVATE", tsw::Red, 12.1);
	tsw::MCSample qStarGI_central_1900("/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_20120909/int/qStarGI_1.9TeV_prodReco_modIsoZCandTree.root", "CENTRAL", tsw::Black, 12.1);

	//-> 1) priv MC vs prod MC plots
	tsw::DistPlotter mcComparison(true);
	mcComparison.setTree("modIsoZBosonTree");
	mcComparison.setSelection("Zmass<105 && Zmass>75");
//	mcComparison.setWeight("genWeight*puWeight");
//	mcComparison.rescaleMC();
	mcComparison.plotTextBoxContents("1.9TeV q* (GI); HEEPModIso, 75-105, no PU re-weight");
	mcComparison.outputFileTag("results/2012-09-09/PrivateVsCentralReco/ZCand_PrivVsCentralReco53X");

	mcComparison.add( qStarGI_private_1900 );
	mcComparison.add( qStarGI_central_1900 );

	mcComparison.add( tsw::AxisDefn("ZpT", 70, 0.0, 1400.0, "p_{T,ee}", -1.0, "GeV"), false, true );
	mcComparison.add( tsw::AxisDefn("Zp4.P()", 40, 0.0, 1600.0, "Z momentum", -1.0, "GeV"), false, true);
	mcComparison.add( tsw::AxisDefn("Zmass", 32, 74.0, 106.0, "M_{ee}", -1.0, "GeV"));
	mcComparison.add( tsw::AxisDefn("Zp4.Eta()", 26, -2.6, +2.6, "Z boson #eta", -1.0, ""));
	mcComparison.add( tsw::AxisDefn("Zp4.Phi()", 20, -3.14, +3.14, "Z boson #phi", -1.0, ""));
	mcComparison.add( tsw::AxisDefn("eleA_p4.Pt()", 40, 0.0, 1000.0, "Leading ele p_{T}", -1.0, "GeV"));
	mcComparison.add( tsw::AxisDefn("eleB_p4.Pt()", 25, 0.0, 500.0, "Sub-leading ele p_{T}", -1.0, "GeV"), true, true);
	mcComparison.add( tsw::AxisDefn("nVtx", 40, -0.5, 39.5, "N_{vtx}", -1.0, ""), false, true);

	mcComparison.add( tsw::AxisDefn("dR", 40, 0.0, 1.0, "#DeltaR_{ee}", -1.0, ""));
	mcComparison.add( tsw::AxisDefn("dEta", 40, -1.0, +1.0, "#Delta#eta_{ee}", -1.0, ""));
	mcComparison.add( tsw::AxisDefn("dPhi", 44, -1.1, +1.1, "#Delta#phi_{ee}", -1.0, ""));

	mcComparison.run( );

}
