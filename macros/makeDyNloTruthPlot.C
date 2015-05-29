{
   std::string outDateStamp = "2015xxxx";
   std::string outPrefix = "results/"+outDateStamp+"/dyTruthPtSpectra_madgraphVsDittmaierNlo_"+outDateStamp;

   tsw::Samples2012 samples("zEffiTree");
   tsw::SetStyle();

   std::string treeName("zBosonEffiTree");
   tsw::AxisDefn axisDefn("ZpT", "[250,300,350, 400,450,500,550, 600,650,700,750, 800,850,900,950, 1000,1050,1100,1150,1200]", "Z boson p_{T} [GeV]", 1.0);
   std::string boostedZeeSeln("(abs(mcZ_ele1_p4.Eta())<1.44) && (abs(mcZ_ele2_p4.Eta())<1.44) && (mcZ_ele1_p4.Et()>35.0) && (mcZ_ele2_p4.Et()>35.0)");
   std::string weight("exp(-4.8 * mcZ_p4.Pt() / 10000.0)");

   TH1* histBoostedZeeMG = samples.dyEE_mg_merged().getFilledHist("hBoostedZee_MG_ZpT", treeName, axisDefn, boostedZeeSeln, weight);
   histBoostedZeeMG->Scale( 1.0 / histBoostedZeeMG->Integral("width") );


   TCanvas* c = new TCanvas("canvas", "Z boson pT spectra", 600, 400);
   c->cd(); c->SetLogy();
   histBoostedZeeMG->Draw();
   histBoostedZeeMG->GetYaxis()->SetTitle("Fraction / 1 GeV");
   TLegend* leg = new TLegend(0.55, 0.62, 0.9, 0.88);
   leg->SetFillColor(kWhite);
   leg->AddEntry(histBoostedZeeMG, "MadGraph with k-factor", "L");

   // Extract NLO calculation from file ...
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
   leg->AddEntry(h_central_NLO, "NLO QCD, LO EWK", "F");
   h_central_NLO_EWK->Draw("SAME");
   leg->AddEntry(h_central_NLO_EWK, "NLO QCD and EWK", "L");
   //   h_doubleQ_NLO->Draw("SAME");
   //   h_halfQ_NLO->Draw("SAME");

   leg->Draw();


   TCanvas* cRatio = new TCanvas("cRatio", "Z boson pT: Ratio Dittmaier / MadGraph", 600, 400);
   cRatio->cd();

   TH1* h_ratio_NLO = (TH1*) h_central_NLO->Clone("h_ratio_NLO");
   TH1* h_ratio_NLO_EWK = (TH1*) h_central_NLO_EWK->Clone("h_ratio_NLO_EWK");
   TH1* h_ratio_MG = (TH1*) histBoostedZeeMG->Clone("h_ratio_MG"); // For MG stat uncert band
   for(size_t i=0; i<=h_ratio_NLO_EWK->GetNbinsX(); i++)
   {
     h_ratio_MG->SetBinError(i, 0.0);
   }

   h_ratio_NLO->Divide(h_ratio_MG);
   h_ratio_NLO_EWK->Divide(histBoostedZeeMG);
   h_ratio_MG->Divide(histBoostedZeeMG);

   // Must set errors to be non-zero in order for ROOT to 
   // display the histogram correctly (i.e. point with 
   // horizontal error lines, rather than like a bar chart)
   for(size_t i=0; i<=h_ratio_NLO_EWK->GetNbinsX(); i++)
   {
     //h_ratio_NLO->SetBinError(i, 0.0001);
     h_ratio_NLO_EWK->SetBinError(i, 0.0001);
   }

   h_ratio_MG->SetFillStyle(3002);
   h_ratio_MG->SetFillColor(7);
   h_ratio_MG->SetMarkerSize(0);
   h_ratio_MG->Draw("E2 B");
   h_ratio_MG->GetXaxis()->SetTitle("Z boson p_{T} [GeV]");
   h_ratio_MG->GetYaxis()->SetRangeUser(0.2,1.8);
   h_ratio_MG->GetYaxis()->SetTitle("Ratio");

   TLine* lineAtOne = new TLine(250, 1.0, 1200, 1.0);
   lineAtOne->SetLineStyle(3);
   lineAtOne->Draw();

   h_ratio_NLO->SetMarkerColor(kGreen);
   h_ratio_NLO->SetLineColor(kGreen);
   h_ratio_NLO->SetFillColor(kGreen);
   h_ratio_NLO->SetFillStyle(3004);
   h_ratio_NLO->Draw("SAME E2 B");
   h_ratio_NLO_EWK->Draw("SAME E");

   cRatio->Update();


   // Save canvases to file
   c->SaveAs( (outPrefix+".pdf").c_str() );
   cRatio->SaveAs( (outPrefix+"_ratio.pdf").c_str() );
}
