{
	tsw::Samples2012 anaTuples("heepTpTree");
	std::string OUT_DIR = "results/20130815/ChargeScaleFactor/";

	//-> 0) Setup objects
	/*  ---  AXES  ---  */
	tsw::AxisDefn axis_probePt("probe_p4.Pt()", "[35,36,37,38,39,40,41,43,45,47.5,50,  55,60,65,70,80,90,100,  150,200,300,500,1000]", "p_{T,lead} [GeV]", 1.0, true);
	tsw::AxisDefn axis_probePt2("probe_p4.Pt()", "[35,40,45,50,70,100,200,1000]", "p_{T,lead} [GeV]", 1.0, true);
	tsw::AxisDefn axis_mass("pair_p4.M()", 50, 65., 115., "M_{tag-probe} [GeV]");
	tsw::AxisDefn axis_nVtx("nVtx", 30, 0.5, 30.5, "N_{vtx}");
	tsw::AxisDefn axis_zPt("pair_p4.Pt()", "[0,5,10,15,20,25,30,35,40,50, 60,70,80,90,100, 120,140,160,180,200, 300,500,1000]", "p_{T,ee} [GeV]", 1.0, true);
	tsw::AxisDefn axis_zPt2("pair_p4.Pt()", "[0,10,20,30,40,60,80,100,200,1000]", "p_{T,ee} [GeV]", 1.0, true);
	tsw::AxisDefn axis_zMom("pair_p4.P()", "[0,5,10,15,20,25,30,35,40,50, 60,70,80,90,100, 120,140,160,180,200, 300,500,1000]", "p_{ee} [GeV]", 1.0, true);
	tsw::AxisDefn axis_zMom2("pair_p4.P()", "[0,10,20,30,40,60,80,100,200,1000]", "p_{ee} [GeV]", 1.0, true);

	/*  ---  TAGS  ---  */
	tsw::TagProbeEffiCalc::TagDefn tag_heepStdIso("EB StdHeep, Z peak, probe EB");
	tag_heepStdIso.mSelectionCuts_tag   = pass_elefull("tag_stdHeep");
	tag_heepStdIso.mSelectionCuts_event = "probe_p4.Pt()>tag_p4.Pt() && pair_p4.M()<105 && pair_p4.M()>75 && abs(tag_scEta)<1.44 && abs(probe_scEta)<1.44";
	tag_heepStdIso.mFakeRateFunc = "tsw::fr_heepV41_full";

	/*  ---  PROBES  ---  */

	tsw::TagProbeEffiCalc::ProbeCutDefn prb_oppCharge;
	prb_oppCharge.mEffiDefn = tsw::EffiDefn("abs(probe_scEta)<1.44 && "+pass_elefull("probe_stdHeep"), "probe_charge != tag_charge", "Opposite sign", tsw::Black);
	prb_oppCharge.mFakeRateFunc_allProbe = "zero";
	prb_oppCharge.mFakeRateFunc_passProbe = "zero";

	tsw::TagProbeEffiCalc::ProbeCutDefn prb_sameCharge;
	prb_sameCharge.mEffiDefn = tsw::EffiDefn("abs(probe_scEta)<1.44 && "+pass_elefull("probe_stdHeep"), "probe_charge == tag_charge", "Same sign", tsw::Black);
	prb_sameCharge.mFakeRateFunc_allProbe = "zero";
	prb_sameCharge.mFakeRateFunc_passProbe = "zero";
  
	/* --- TAG-PROBE CALCULATORS --- */

	tsw::TagProbeEffiCalc tpCalc("tagProbeTree", "qcdGsfGsfTree", true);
	tpCalc.baselineSelection("trgDecision");
	tpCalc.eventWeight("genWeight * puWeight *  * tsw::totalClusEtTurnOn(tag_p4.Pt(),tag_p4.Eta()) * tsw::totalClusEtTurnOn(probe_p4.Pt(),probe_p4.Eta())");
	tpCalc.stdFakeRate("tsw::fr_heepV41_full", pass_elefull("tag_stdHeep") );
	tpCalc.fakeRatePreSeln("tag_fakePreCutCode==0");
	tpCalc.effiAxis( tsw::Range(0.85, 1.0), "OS fraction");
  	//tpCalc.qcdSysUncertScaleRange( tsw::Range(0.6, 1.4) );

	tpCalc.drellYan( anaTuples.dyEE_mg_merged() );
	tpCalc.add_background( anaTuples.wJets() );
	tpCalc.add_background( anaTuples.dyTauTau_powheg() );
	tpCalc.add_background( anaTuples.topBkgds() );
	tpCalc.add_background( anaTuples.vzBkgds()  );

	tpCalc.data( anaTuples.data2012() );

	tpCalc.outFilePrefix(OUT_DIR+"/chargeTagPrb_dyMG");
	tsw::TagProbeEffiCalc tpCalc_powheg(tpCalc);
	tpCalc_powheg.drellYan( anaTuples.dyEE_powheg() );
	tpCalc_powheg.outFilePrefix(OUT_DIR+"/chargeTagPrb_dyPowheg");
	tsw::TagProbeEffiCalc tpCalc_pythia(tpCalc);
	tpCalc_pythia.drellYan( anaTuples.dyEE_pythia() );
	tpCalc_pythia.outFilePrefix(OUT_DIR+"/chargeTagPrb_dyPythia");

	// A) Plots for full standard HEEP [cross-check with Z'(ee) note]
	//	tpCalc
	  //	  .effiLegendPos( tsw::LOWER_LEFT )
	  //	  .run(tag_heepStdIso, prb_oppCharge, axis_probePt )
	  //.run(tag_heepStdIso, prb_oppCharge, axis_nVtx)
	  //.run(tag_heepStdIso, prb_oppCharge, axis_mass)
	  //	  .run(tag_heepStdIso, prb_oppCharge, axis_zPt)
	  //	  .run(tag_heepStdIso, prb_oppCharge, axis_zMom);

	tpCalc
	  .effiLegendPos( tsw::UPPER_LEFT )
	  .effiAxis( tsw::Range(0.0, 0.05), "SS fraction")
	  .run(tag_heepStdIso, prb_sameCharge, axis_probePt2 )
	  .run(tag_heepStdIso, prb_sameCharge, axis_zPt2 )
	  .run(tag_heepStdIso, prb_sameCharge, axis_zMom2 );

	/*tpCalc_powheg
	  .run(tag_heepStdIso, prb_oppCharge, axis_probePt)
	  .run(tag_heepStdIso, prb_oppCharge, axis_zPt)
	  ;
	//        throw std::exception();
	tpCalc_pythia
	  .run(tag_heepStdIso, prb_oppCharge, axis_probePt )
	  .run(tag_heepStdIso, prb_oppCharge, axis_probePt );*/

//	
}
