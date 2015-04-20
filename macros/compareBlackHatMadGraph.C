{
  #include <vector> 

  size_t nrBins = 18; 
  Double_t ptBinLims[nrBins+1] = {100, 110.957, 123.114, 136.604, 151.572,
                                  168.179, 186.607, 207.053, 229.74, 254.912,
                                  282.843, 313.834, 348.22, 386.375, 428.709,
                                  475.683, 527.803, 585.634, 800};

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
  histMadGraph->SetLineColor(kMagenta);
  histMadGraph->SetLineStyle(1);


  // Plot MadGraph and BlackHat histograms from SMP analysis 
  TCanvas* c = new TCanvas("canvas", "Drell-Yan: BH vs MG", 600, 400);
  c->cd(); gPad->SetLogy();

  histBlackHat->Draw("HIST");
  histMadGraph->Draw("SAME E0");
  histBoostedZeeMG->Draw("SAME E0");


  // Plot MadGraph/BlackHat ratios with and without k-factor
  tsw::SetStyle()->cd();
  TCanvas* cRatio = new TCanvas("ratioCanvas", "Drell-Yan: BH/MG ratio", 600, 400);
  cRatio->cd();
  TLegend* legend = new TLegend(0.17, 0.65, 0.45, 0.85);

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
  histRatioMGBH->GetXaxis()->SetRangeUser(200, 800); 
  histRatioMGBH->GetYaxis()->SetTitleOffset(0.8);
  histRatioMGBH->GetYaxis()->SetTitle("MadGraph / BlackHat");
  cRatio->Update();

  for(size_t i=0; i<kFactorHists.size(); i++)
  {
    TH1* hist = kFactorHists.at(i);
    hist->Multiply(histRatioMGBH);
    hist->Draw("SAME E0");
    legend->AddEntry(hist, hist->GetTitle(), "l");
    TF1 func("linearFunc", "[0] * x + [1]", 250, 800);
    TFitResultPtr fitResult = hist->Fit(&func, "SR", "SAME");
    std::cout << "k-factor " << hist->GetTitle() << "  -> ratio to BH: " << fitResult->Parameter(0) << "*pt + " << fitResult->Parameter(1) << std::endl; 
  }
  legend->Draw();


  // Plot the fractional uncertainties on BlackHat prediction ...
  TCanvas* cBlackHatUncert = new TCanvas("cBlackHatUncert", "BlackHat uncertainties", 600, 400);
//  TH1* histBlackHatPDFDown = (TH1*) smpHistFile->Get("h_band_BH_PDFDown_rebinned_total");
//  TH1* histBlackHatPDFUp   = (TH1*) smpHistFile->Get("h_band_BH_PDFUp_rebinned_total");
  histBlackHatPDFDown->Scale(-1.0);
  histBlackHatPDFDown->Draw();
  histBlackHatPDFDown->GetXaxis()->SetRangeUser(200, 800);
  histBlackHatPDFDown->GetYaxis()->SetRangeUser(-0.15,0.15);
  histBlackHatPDFUp->Draw("SAME");
  histBlackHatScaleDown->Scale(-1.0);
  histBlackHatScaleDown->Draw("SAME");
  histBlackHatScaleUp->Draw("SAME");
}

