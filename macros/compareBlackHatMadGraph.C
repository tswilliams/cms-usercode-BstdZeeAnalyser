{
  #include <vector> 

  std::string outDateStamp = "2015xxxx";
  std::string outPrefix = "results/"+outDateStamp+"/dyTruthPtSpectra_madgraphVsBlackHat_"+outDateStamp;

  size_t nrBins = 18; 
  Double_t ptBinLims[nrBins+1] = {100, 110.957, 123.114, 136.604, 151.572,
                                  168.179, 186.607, 207.053, 229.74, 254.912,
                                  282.843, 313.834, 348.22, 386.375, 428.709,
                                  475.683, 527.803, 585.634, 800};

  tsw::SetStyle()->cd();

  tsw::Samples2012 samples("zEffiTree");
 
/* tsw::DistPlotter plotter(true);

  plotter.setTree("zBosonEffiTree");
//  plotter.setWeight("genWeight * puWeight");
  //std::string selnString = "(abs(mcZ_ele1_p4.Eta())<1.44 && abs(mcZ_ele2_p4.Eta())<1.44) && (mcZ_ele1_p4.Et()>35.0 && mcZ_ele2_p4.Et()>35.0)";
  //plotter.setSelection("(Zmass<105 && Zmass>75) && (abs(dPhi)>=0.3 || abs(dEta)>=0.07) && (eleA_modHeepStdThr==0 && eleB_modHeepStdThr==0)");
  plotter.setSelection("(abs(mcZ_ele1_p4.Eta())<2.4) && (abs(mcZ_ele2_p4.Eta())<2.4) && (mcZ_ele1_p4.Et()>20.0) && (mcZ_ele2_p4.Et()>20.0) && (mcZ_p4.M()>71) && (mcZ_p4.M()<111)");

  std::string outPrefix("results/2015xxxx");
  plotter.outFilePrefix( outPrefix + "/dyBHvsMG_" );
  plotter.rescaleMC();

  //   plotter.add( tsw::AxisDefn("ZpT", "[0,2,4,6,8,10,12.5,15,17.5,20,30,40,50,70,90,110,150,190,250,350,550, 750,1000,1250,1500,1750,2000]", "Z boson p_{T} [GeV]", 1.0) );
  plotter.add( tsw::AxisDefn("mcZ_p4.Pt()", nrBins, ptBinLims, "Z boson p_{T} [GeV]", 1.0) );

  plotter.add( samples.dyEE_mg_merged() );

//  plotter.run();
*/
  // Determine k-factor histograms from trees in boosted Z(ee)
  std::string treeName("zBosonEffiTree");
  tsw::AxisDefn axisDefn("mcZ_p4.Pt()", nrBins, ptBinLims, "Z boson p_{T} [GeV]", 1.0);
  std::string boostedZeeSeln("(abs(mcZ_ele1_p4.Eta())<2.4) && (abs(mcZ_ele2_p4.Eta())<2.4) && (mcZ_ele1_p4.Et()>20.0) && (mcZ_ele2_p4.Et()>20.0) && (mcZ_p4.M()>71) && (mcZ_p4.M()<111)");
  TH1* histBoostedZeeMG = samples.dyEE_mg_merged().getFilledHist("hBoostedZee_MG_orig", treeName, axisDefn, boostedZeeSeln, "1");
  histBoostedZeeMG->Scale( 1.0 / histBoostedZeeMG->GetBinContent(10) );  // histBoostedZeeMG->Integral("width") );

  std::vector<std::string> kFactors; // % per 100GeV 
  //kFactors.push_back("-4.0");
  kFactors.push_back("-4.8");
  //kFactors.push_back("-6.0");

  std::vector<TH1*> kFactorHists;
  for(size_t i=0; i<kFactors.size(); i++)
  {
    std::string kFactorWeight = "exp(";
    kFactorWeight += kFactors.at(i);
    kFactorWeight += " * mcZ_p4.Pt() / 10000)";
    TH1* hist = samples.dyEE_mg_merged().getFilledHist(std::string("hBoostedZee_MG_kFactor")+kFactors.at(i), treeName, axisDefn, boostedZeeSeln, kFactorWeight);
    hist->Scale( 1.0 / hist->GetBinContent(10) );  // hist->Integral("width") );
    hist->Divide(histBoostedZeeMG);
    for(size_t j=0; j <= hist->GetNbinsX(); j++)
      hist->SetBinError(j, 0.0);

    hist->SetTitle((kFactors.at(i)+"% per 100GeV").c_str());
    hist->SetLineColor(i+2);
    hist->SetMarkerColor(i+2);

    kFactorHists.push_back(hist);
  }

  // Extract histograms from SMP analysis histogram file (c.f. Eric Takasugi)
  TFile* smpHistFile = TFile::Open("data/BlackHatDYhists_Zpt_hist_Zpt100_BY_Inf_jet30_njets1plus_18_Feb_test.root", "READ");

  TH1* histBlackHat = (TH1*) smpHistFile->Get("h_BH_rebinned_total");
  TH1* histBlackHatPDFDown = (TH1*) smpHistFile->Get("h_band_BH_PDFDown_rebinned_total");
  TH1* histBlackHatPDFUp   = (TH1*) smpHistFile->Get("h_band_BH_PDFUp_rebinned_total");
  TH1* histBlackHatScaleDown = (TH1*) smpHistFile->Get("h_band_BH_scaleDown_rebinned_total");
  TH1* histBlackHatScaleUp   = (TH1*) smpHistFile->Get("h_band_BH_scaleUp_rebinned_total");
  for(size_t i=1; i<=histBlackHat->GetNbinsX(); i++)
  {
    histBlackHat->SetBinError(i, 0.0);
    histBlackHatPDFDown->SetBinError(i, 0.0);
    histBlackHatPDFUp->SetBinError(i, 0.0);
    histBlackHatScaleDown->SetBinError(i, 0.0);
    histBlackHatScaleUp->SetBinError(i, 0.0);
  }
  histBlackHatPDFDown->Divide(histBlackHat);
  histBlackHatPDFUp->Divide(histBlackHat);
  histBlackHatScaleDown->Divide(histBlackHat);
  histBlackHatScaleUp->Divide(histBlackHat);
  histBlackHat->Scale( 1.0 / histBlackHat->GetBinContent(10) );  // histBlackHat->Integral("width") );

  TH1* histMadGraph = (TH1*) smpHistFile->Get("h_MG_GEN_leptons_combined");
  histMadGraph->Scale( 1.0 / histMadGraph->GetBinContent(10) );  // histMadGraph->Integral("width") );
  histMadGraph->SetMarkerColor(kCyan);
  histMadGraph->SetLineColor(kCyan);
  histMadGraph->SetLineStyle(1);


  // Plot MadGraph and BlackHat histograms from SMP analysis 
  TCanvas* c = new TCanvas("canvas", "Drell-Yan: BH vs MG", 600, 400);
  c->cd(); gPad->SetLogy();
  TLegend* leg1 = new TLegend(0.65, 0.65, 0.88, 0.85);


  histBlackHat->Draw("HIST");
  histBlackHat->GetXaxis()->SetTitle("Z boson p_{T} [GeV]");
  histBlackHat->GetXaxis()->SetRangeUser(240, 800); 
  histBlackHat->GetYaxis()->SetTitleOffset(0.8);
  histBlackHat->GetYaxis()->SetTitle("Events (A.U.)");
  histMadGraph->Draw("SAME E0");

  leg1->AddEntry(histBlackHat, "BlackHat", "L");
  leg1->AddEntry(histMadGraph, "MadGraph", "L");
  leg1->SetFillColor(kWhite);
  leg1->Draw();
  //histBoostedZeeMG->Draw("SAME E0");


  // Plot MadGraph/BlackHat ratios with and without k-factor
  TCanvas* cRatio = new TCanvas("ratioCanvas", "Drell-Yan: BH/MG ratio", 600, 400);
  cRatio->cd();
  TLegend* legend = new TLegend(0.17, 0.15, 0.45, 0.35);
  legend->SetFillColor(kWhite);

  TH1* histRatioMGBH = (TH1*) histMadGraph->Clone("h_MG_BH_ratio");
  histRatioMGBH->Divide(histBlackHat);
  std::cout << std::endl;
  for(size_t i=1; i<=histRatioMGBH->GetNbinsX() ; i++)
  {
    std::cout << "   " << histRatioMGBH->GetBinContent(i) << " +/- " << histRatioMGBH->GetBinError(i) << std::endl;
  }

  legend->AddEntry(histRatioMGBH, "No k factor", "l");
  histRatioMGBH->Draw("E0");
  histRatioMGBH->GetXaxis()->SetTitle("Z boson p_{T} [GeV]");
  histRatioMGBH->GetXaxis()->SetRangeUser(240, 800); 
  histRatioMGBH->GetYaxis()->SetTitleOffset(0.9);
  histRatioMGBH->GetYaxis()->SetTitle("MadGraph / BlackHat");
  histRatioMGBH->GetYaxis()->SetRangeUser(0.8, 1.2);
  cRatio->Update();

  TLine* lineAtOne = new TLine(250, 1.0, 800, 1.0);
  lineAtOne->SetLineStyle(3);
  lineAtOne->Draw();

  for(size_t i=0; i<kFactorHists.size(); i++)
  {
    TH1* hist = kFactorHists.at(i);
    hist->Multiply(histRatioMGBH);
    hist->Draw("SAME E0");
    legend->AddEntry(hist, hist->GetTitle(), "l");
    TF1 func("linearFunc", "[0] * x + [1]", 250, 800);
    TFitResultPtr fitResult = hist->Fit(&func, "NSR"); // "SR", "SAME");
    std::cout << "k-factor " << hist->GetTitle() << "  -> ratio to BH: " << fitResult->Parameter(0) << "*pt + " << fitResult->Parameter(1) << std::endl; 
  }
  legend->Draw();


  // Plot the fractional uncertainties on BlackHat prediction ...
  TCanvas* cBlackHatUncert = new TCanvas("cBlackHatUncert", "BlackHat uncertainties", 600, 400);
  TLegend* legUncert = new TLegend(0.17, 0.16, 0.35, 0.3);
  legUncert->SetFillColor(kWhite);

//  TH1* histBlackHatPDFDown = (TH1*) smpHistFile->Get("h_band_BH_PDFDown_rebinned_total");
//  TH1* histBlackHatPDFUp   = (TH1*) smpHistFile->Get("h_band_BH_PDFUp_rebinned_total");
  histBlackHatPDFDown->Scale(-1.0);
  histBlackHatPDFDown->SetLineColor(kBlack);
  histBlackHatPDFDown->Draw();
  histBlackHatPDFDown->GetXaxis()->SetTitle("Z boson p_{T} [GeV]");
  histBlackHatPDFDown->GetXaxis()->SetRangeUser(240, 800);
  histBlackHatPDFDown->GetYaxis()->SetTitleOffset(0.9);
  histBlackHatPDFDown->GetYaxis()->SetTitle("Fractional uncertainty");
  histBlackHatPDFDown->GetYaxis()->SetRangeUser(-0.2, 0.2);
  histBlackHatPDFUp->SetLineColor(kBlack);
  histBlackHatPDFUp->Draw("SAME");
  legUncert->AddEntry(histBlackHatPDFUp, "PDF", "L");

  TLine* lineAtZero = new TLine(250, 0.0, 800, 0.0);
  lineAtZero->SetLineStyle(3);
  lineAtZero->Draw();

  histBlackHatScaleDown->Scale(-1.0);
  histBlackHatScaleDown->SetLineColor(kRed);
  histBlackHatScaleDown->Draw("SAME");
  histBlackHatScaleUp->SetLineColor(kRed);
  histBlackHatScaleUp->Draw("SAME");
  legUncert->AddEntry(histBlackHatScaleUp, "Scale", "L");
  legUncert->Draw();

  c->SaveAs( (outPrefix+".pdf").c_str() );  
  cRatio->SaveAs( (outPrefix+"_ratio.pdf").c_str() );
  cBlackHatUncert->SaveAs( (outPrefix+"_bhUncert.pdf").c_str() );

}

