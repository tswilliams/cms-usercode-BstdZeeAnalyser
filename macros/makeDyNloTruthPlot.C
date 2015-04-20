{

   std::string outPrefix = "results/2014xxxx";

   tsw::Samples2012 samples("zEffiTree");
   tsw::DistPlotter plotter(true);

   plotter.setTree("zBosonEffiTree");
   plotter.setWeight("genWeight * puWeight");
   //std::string selnString = "(abs(mcZ_ele1_p4.Eta())<1.44 && abs(mcZ_ele2_p4.Eta())<1.44) && (mcZ_ele1_p4.Et()>35.0 && mcZ_ele2_p4.Et()>35.0)";
   //plotter.setSelection("(Zmass<105 && Zmass>75) && (abs(dPhi)>=0.3 || abs(dEta)>=0.07) && (eleA_modHeepStdThr==0 && eleB_modHeepStdThr==0)");
   plotter.setSelection("(abs(mcZ_ele1_p4.Eta())<1.44) && (abs(mcZ_ele2_p4.Eta())<1.44) && (mcZ_ele1_p4.Et()>35.0) && (mcZ_ele2_p4.Et()>35.0)");

   plotter.outFilePrefix( outPrefix + "/dySamplesTruth_" );
   plotter.rescaleMC();

   plotter.add( tsw::AxisDefn("ZpT", "[250,300,350, 400,450,500,550, 600,650,700,750, 800,850,900,950, 1000,1050,1100,1150,1200]", "Z boson p_{T} [GeV]", 1.0) );

   //   plotter.add( tsw::AxisDefn("Zp4.P()", 100, 0.0, 2000, "Z boson momentum [GeV]") );
   //   plotter.add( tsw::AxisDefn("Zp4.Eta()", 50, -2.5, 2.5, "Z boson #eta") );
   //   plotter.add( tsw::AxisDefn("dR", 120, 0.0, 1.2, "#DeltaR_{ee}") );
   //   plotter.add( tsw::AxisDefn("eleA_p4.Eta()", 50, -2.5, 2.5, "Leading ele #eta") );
   //   plotter.add( tsw::AxisDefn("eleB_p4.Eta()", 50, -2.5, 2.5, "Sub-leading ele #eta") );


   plotter.add( samples.dyEE_mg_merged() );
   //plotter.add( samples.dyEE_sherpa() );
   //plotter.add( samples.dyEE_powheg() );
   //plotter.add( samples.dyEE_pythia() );

   plotter.run();

   std::string nloFileName( "data/ptV_CMS_250to1200.plot.txt" );
   std::vector<Float_t> binLims = tsw::GetColumnFromFile(nloFileName, 0);
   binLims.push_back(1200);
   size_t nBins = binLims.size() - 1;

   std::vector<Float_t> central_LO  = tsw::GetColumnFromFile(nloFileName, 1);
   std::vector<Float_t> central_NLO = tsw::GetColumnFromFile(nloFileName, 3);
   std::vector<Float_t> doubleQ_LO  = tsw::GetColumnFromFile(nloFileName, 7);
   std::vector<Float_t> doubleQ_NLO = tsw::GetColumnFromFile(nloFileName, 8);
   std::vector<Float_t> halfQ_LO    = tsw::GetColumnFromFile(nloFileName, 9);
   std::vector<Float_t> halfQ_NLO   = tsw::GetColumnFromFile(nloFileName, 10);

   std::vector<Float_t> central_LO_EWK = tsw::GetColumnFromFile(nloFileName, 5);


   TH1F* h_central_NLO = new TH1F("h_central_NLO", "central NLO", nBins, &binLims.at(0));
   TH1F* h_central_NLO_EWK = new TH1F("h_central_NLO_WEK", "central NLO, with EWK", nBins, &binLims.at(0));
   TH1F* h_doubleQ_NLO = new TH1F("h_doubleQ_NLO", "doubleQ NLO", nBins, &binLims.at(0));
   TH1F* h_halfQ_NLO = new TH1F("h_halfQ_NLO", "halfQ NLO", nBins, &binLims.at(0));

   for(size_t i=0; i<nBins; i++)
   {
     h_central_NLO->SetBinContent(i+1, central_LO.at(i) + central_NLO.at(i));
     h_central_NLO_EWK->SetBinContent(i+1, (central_LO.at(i) + central_NLO.at(i)) * (1 + central_LO_EWK.at(i)/central_LO.at(i)));
     h_doubleQ_NLO->SetBinContent(i+1, doubleQ_LO.at(i) + doubleQ_NLO.at(i));
     h_halfQ_NLO->SetBinContent(i+1, halfQ_LO.at(i) + halfQ_NLO.at(i));
   }

   // Re-scale to unity (values from file are fb/GeV)
   TH1* hists[] = {h_central_NLO, h_doubleQ_NLO, h_halfQ_NLO, h_central_NLO_EWK};
   for(size_t i=0; i<4; i++)
     hists[i]->Rebin(20);

   Float_t scFac = 1.0 / h_central_NLO->Integral("width");
   for(size_t i=0; i<4; i++)
     hists[i]->Scale( scFac );
   h_central_NLO_EWK->Scale( 1.0 / h_central_NLO_EWK->Integral("width") );

   for(size_t i=1; i<=nBins; i++)
     h_central_NLO->SetBinError(i, 0.1 * h_central_NLO->GetBinContent(i));

   h_central_NLO->SetMarkerColor(kGreen);
   h_central_NLO->SetLineColor(kGreen);
   h_central_NLO->SetFillColor(kGreen);
   h_central_NLO->SetFillStyle(3004);
   h_central_NLO_EWK->SetLineColor(kBlack);
   h_doubleQ_NLO->SetLineColor(kBlue);
   h_halfQ_NLO->SetLineColor(kMagenta);

   h_central_NLO->Draw("SAME E2 B");
   h_central_NLO_EWK->Draw("SAME");
   //   h_doubleQ_NLO->Draw("SAME");
   //   h_halfQ_NLO->Draw("SAME");

}
