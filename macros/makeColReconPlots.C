{

	std::string BASE_NT_DIR = "/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_20120913/";

	// SIGNAL DATASETS - 42X

	tsw::CompositeMC qStar_GI_42X("q*, GI, 42X", tsw::Red, "M_{q*}", "TeV");
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M500_7TeV_42X_20120918_zEffiTree.root", "GI, 0.5TeV", tsw::Green), 0.5 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M600_7TeV_42X_20120918_zEffiTree.root", "GI, 0.6TeV", tsw::Green), 0.6 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M700_7TeV_42X_20120918_zEffiTree.root", "GI, 0.7TeV", tsw::Green), 0.7 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M800_7TeV_42X_20120918_zEffiTree.root", "GI, 0.8TeV", tsw::Green), 0.8 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1000_7TeV_42X_20120918_zEffiTree.root", "GI, 1.0TeV", tsw::Green), 1.0 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1100_7TeV_42X_20120918_zEffiTree.root", "GI, 1.1TeV", tsw::Green), 1.1 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1200_7TeV_42X_20120918_zEffiTree.root", "GI, 1.2TeV", tsw::Green), 1.2 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1300_7TeV_42X_20120918_zEffiTree.root", "GI, 1.3TeV", tsw::Green), 1.3 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1400_7TeV_42X_20120918_zEffiTree.root", "GI, 1.4TeV", tsw::Green), 1.4 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1500_7TeV_42X_20120918_zEffiTree.root", "GI, 1.5TeV", tsw::Green), 1.5 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1600_7TeV_42X_20120918_zEffiTree.root", "GI, 1.6TeV", tsw::Green), 1.6 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1700_7TeV_42X_20120918_zEffiTree.root", "GI, 1.7TeV", tsw::Green), 1.7 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1800_7TeV_42X_20120918_zEffiTree.root", "GI, 1.8TeV", tsw::Green), 1.8 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1900_7TeV_42X_20120918_zEffiTree.root", "GI, 1.9TeV", tsw::Green), 1.9 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M2000_7TeV_42X_20120918_zEffiTree.root", "GI, 2.0TeV", tsw::Green), 2.0 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M2500_7TeV_42X_20120918_zEffiTree.root", "GI, 2.5TeV", tsw::Green), 2.5 );
	qStar_GI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M3000_7TeV_42X_20120918_zEffiTree.root", "GI, 3.0TeV", tsw::Green), 3.0 );

	tsw::MCSample qStar_GI_42X_M500( BASE_NT_DIR+"int_42X/QstarGI_M500_7TeV_42X_20120918_zEffiTree.root",  "0.5TeV q*, 42X", tsw::Red, 0.5);
	tsw::MCSample qStar_GI_42X_M1500(BASE_NT_DIR+"int_42X/QstarGI_M1500_7TeV_42X_20120918_zEffiTree.root", "1.5TeV q*, 42X", tsw::Red, 1.0);
	tsw::MCSample qStar_GI_42X_M2000(BASE_NT_DIR+"int_42X/QstarGI_M2000_7TeV_42X_20120918_zEffiTree.root", "2.0TeV q*, 42X", tsw::Red, 1.5);
	tsw::MCSample qStar_GI_42X_M2500(BASE_NT_DIR+"int_42X/QstarGI_M2500_7TeV_42X_20120918_zEffiTree.root", "2.5TeV q*, 42X", tsw::Red, 2.0);


	tsw::CompositeMC qStar_CI_42X("q*, CI, 42X", tsw::LightGreen, "M_{q*}", "TeV");
	qStar_CI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarCI_M1300_7TeV_42X_20120918_zEffiTree.root", "CI, 1.3TeV", tsw::Blue), 1.3 );
	qStar_CI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarCI_M1500_7TeV_42X_20120918_zEffiTree.root", "CI, 1.5TeV", tsw::Blue), 1.5 );
	qStar_CI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarCI_M1700_7TeV_42X_20120918_zEffiTree.root", "CI, 1.7TeV", tsw::Blue), 1.7 );
	qStar_CI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarCI_M2600_7TeV_42X_20120918_zEffiTree.root", "CI, 2.6TeV", tsw::Blue), 2.6 );
	qStar_CI_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarCI_M2900_7TeV_42X_20120918_zEffiTree.root", "CI, 2.9TeV", tsw::Blue), 2.9 );

	// SIGNAL DATASETS - 53X

	tsw::CompositeMC qStar_GI("q*, GI, 53X", tsw::Blue, "M_{q*}", "TeV");
	qStar_GI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M500_prodReco_zEffiTree.root", "GI, 0.5TeV", tsw::Green), 0.5 );
	qStar_GI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M600_prodReco_zEffiTree.root", "GI, 0.6TeV", tsw::Green), 0.6 );
	qStar_GI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M1500_prodReco_zEffiTree.root", "GI, 1.5TeV", tsw::Green), 1.5 );
	qStar_GI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M1600_prodReco_zEffiTree.root", "GI, 1.6TeV", tsw::Green), 1.6 );
	qStar_GI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M1900_prodReco_zEffiTree.root", "GI, 1.9TeV", tsw::Green), 1.9 );
	qStar_GI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M2000_prodReco_zEffiTree.root", "GI, 2.0TeV", tsw::Green), 2.0 );
	qStar_GI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M2500_prodReco_zEffiTree.root", "GI, 2.5TeV", tsw::Green), 2.5 );
	qStar_GI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M2700_prodReco_zEffiTree.root", "GI, 2.7TeV", tsw::Green), 2.7 );
	qStar_GI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M2900_prodReco_zEffiTree.root", "GI, 2.9TeV", tsw::Green), 2.9 );

	tsw::MCSample qStar_GI_53X_M500( BASE_NT_DIR+"int/QstarGI_M500_prodReco_zEffiTree.root",  "0.5TeV q*, 53X", tsw::Blue, 1.0);
	tsw::MCSample qStar_GI_53X_M1500(BASE_NT_DIR+"int/QstarGI_M1500_prodReco_zEffiTree.root", "1.5TeV q*, 53X", tsw::Blue, 2.0);
	tsw::MCSample qStar_GI_53X_M2000(BASE_NT_DIR+"int/QstarGI_M2000_prodReco_zEffiTree.root", "2.0TeV q*, 53X", tsw::Blue, 3.0);
	tsw::MCSample qStar_GI_53X_M2500(BASE_NT_DIR+"int/QstarGI_M2500_prodReco_zEffiTree.root", "2.5TeV q*, 53X", tsw::Blue, 4.0);

	tsw::CompositeMC qStar_CI("q*, CI, 53X", tsw::LightGreen, "M_{q*}", "TeV");
	qStar_CI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarCI_M1300_prodReco_zEffiTree.root", "CI, 1.3TeV", tsw::Blue), 1.3 );
	qStar_CI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarCI_M1500_prodReco_zEffiTree.root", "CI, 1.5TeV", tsw::Blue), 1.5 );
	qStar_CI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarCI_M1700_prodReco_zEffiTree.root", "CI, 1.7TeV", tsw::Blue), 1.7 );
	qStar_CI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarCI_M2600_prodReco_zEffiTree.root", "CI, 2.6TeV", tsw::Blue), 2.6 );
	qStar_CI.add( tsw::MCSample(BASE_NT_DIR+"int/QstarCI_M2900_prodReco_zEffiTree.root", "CI, 2.9TeV", tsw::Blue), 2.9 );


	/// *** MAKE PLOTS *** ///
	tsw::AxisDefn genHadronsDr04_eleA_nr("eleA_nGenHadronsDr04", 31, -0.5, +30.5, "num genHads, leading ele");
	tsw::AxisDefn genHadronsDr04_eleA_ptSum("eleA_ptSumGenHadronsDr04", 60, 0., +30., "genHad #Sigmap_{T}, leading ele [GeV]");
	tsw::AxisDefn genHadronsDr04_eleB_nr("eleB_nGenHadronsDr04", 31, -0.5, +30.5, "num genHads, sublead ele");
	tsw::AxisDefn genHadronsDr04_eleB_ptSum("eleB_ptSumGenHadronsDr04", 60, 0., +30., "genHad #Sigmap_{T}, sublead ele [GeV]");
	tsw::AxisDefn genHadronsDr04_tot_nr("eleA_nGenHadronsDr04", 31, -0.5, +30.5, "num genHads, total");
	tsw::AxisDefn genHadronsDr04_tot_ptSum("eleA_ptSumGenHadronsDr04", 60, 0., +30., "genHad #Sigmap_{T}, total [GeV]");

	tsw::DistPlotter sigMcPlotter_M500(true);
	sigMcPlotter_M500.setTree("zBosonEffiTree");
	sigMcPlotter_M500.setSelection(tsw::AndOfCuts("( (eleA_p4.Pt()>35.0 && abs(eleA_p4.Eta())<1.44 ) && (eleB_p4.Pt()>35.0 && abs(eleB_p4.Eta())<1.44) )",
															"bothRecod && (abs(ZdEta)>0.07 || abs(ZdPhi)>0.3) && ((eleA_stdHeep & 0x08ff)==0 && (eleB_stdHeep & 0x08ff)==0)"));
	sigMcPlotter_M500.rescaleMC();

	sigMcPlotter_M500.add(genHadronsDr04_eleA_nr);
	sigMcPlotter_M500.add(genHadronsDr04_eleA_ptSum);
	sigMcPlotter_M500.add(genHadronsDr04_eleB_nr);
	sigMcPlotter_M500.add(genHadronsDr04_eleB_ptSum);
	sigMcPlotter_M500.add(genHadronsDr04_tot_nr);
	sigMcPlotter_M500.add(genHadronsDr04_tot_ptSum);

	tsw::DistPlotter sigMcPlotter_M1500(sigMcPlotter_M500);
	tsw::DistPlotter sigMcPlotter_M2000(sigMcPlotter_M500);
	tsw::DistPlotter sigMcPlotter_M2500(sigMcPlotter_M500);
	tsw::DistPlotter sigMcPlotter_53X(sigMcPlotter_M500);
	tsw::DistPlotter sigMcPlotter_42X(sigMcPlotter_M500);

	sigMcPlotter_M500.add(qStar_GI_42X_M500);
	sigMcPlotter_M500.add(qStar_GI_53X_M500);

	sigMcPlotter_M1500.add(qStar_GI_42X_M1500);
	sigMcPlotter_M1500.add(qStar_GI_53X_M1500);

	sigMcPlotter_M2000.add(qStar_GI_42X_M2000);
	sigMcPlotter_M2000.add(qStar_GI_53X_M2000);

	sigMcPlotter_M2500.add(qStar_GI_42X_M2500);
	sigMcPlotter_M2500.add(qStar_GI_53X_M2500);

//	sigMcPlotter_M500.outFilePrefix("results/20121005/pythia6_investigations/qStarGI_M500GeV").run();
//	sigMcPlotter_M1500.outFilePrefix("results/20121005/pythia6_investigations/qStarGI_M1500GeV").run();
//	sigMcPlotter_M2000.outFilePrefix("results/20121005/pythia6_investigations/qStarGI_M2000GeV").run();
//	sigMcPlotter_M2500.outFilePrefix("results/20121005/pythia6_investigations/qStarGI_M2500GeV").run();

	sigMcPlotter_53X.add( tsw::MCSample( BASE_NT_DIR+"int/QstarGI_M500_prodReco_zEffiTree.root",  "0.5TeV q*, 53X", tsw::Black, 1.0) );
	sigMcPlotter_53X.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M1500_prodReco_zEffiTree.root", "1.5TeV q*, 53X", tsw::Blue, 2.0)  );
	sigMcPlotter_53X.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M2000_prodReco_zEffiTree.root", "2.0TeV q*, 53X", tsw::Red, 3.0)   );
	sigMcPlotter_53X.add( tsw::MCSample(BASE_NT_DIR+"int/QstarGI_M2500_prodReco_zEffiTree.root", "2.5TeV q*, 53X", tsw::Green, 4.0) );

	sigMcPlotter_42X.add( tsw::MCSample( BASE_NT_DIR+"int_42X/QstarGI_M500_7TeV_42X_20120918_zEffiTree.root",  "0.5TeV q*, 42X", tsw::Black, 1.0) );
	sigMcPlotter_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1000_7TeV_42X_20120918_zEffiTree.root", "1.5TeV q*, 42X", tsw::Blue, 2.0)  );
	sigMcPlotter_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M1500_7TeV_42X_20120918_zEffiTree.root", "2.0TeV q*, 42X", tsw::Red, 3.0)   );
	sigMcPlotter_42X.add( tsw::MCSample(BASE_NT_DIR+"int_42X/QstarGI_M2500_7TeV_42X_20120918_zEffiTree.root", "2.5TeV q*, 42X", tsw::Green, 4.0) );



	tsw::MCSample qStar_GI_42X_M500( BASE_NT_DIR+"int_42X/QstarGI_M500_7TeV_42X_20120918_zEffiTree.root",  "0.5TeV q*, 42X", tsw::Red, 0.5);
	tsw::MCSample qStar_GI_42X_M1500(BASE_NT_DIR+"int_42X/QstarGI_M1500_7TeV_42X_20120918_zEffiTree.root", "1.5TeV q*, 42X", tsw::Red, 1.0);
	tsw::MCSample qStar_GI_42X_M2000(BASE_NT_DIR+"int_42X/QstarGI_M2000_7TeV_42X_20120918_zEffiTree.root", "2.0TeV q*, 42X", tsw::Red, 1.5);
	tsw::MCSample qStar_GI_42X_M2500(BASE_NT_DIR+"int_42X/QstarGI_M2500_7TeV_42X_20120918_zEffiTree.root", "2.5TeV q*, 42X", tsw::Red, 2.0);


	sigMcPlotter_53X.outFilePrefix("results/20121005/pythia6_investigations/qStarGI_53X").run();
	sigMcPlotter_42X.outFilePrefix("results/20121005/pythia6_investigations/qStarGI_42X").run();

}
