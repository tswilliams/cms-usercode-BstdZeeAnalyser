{

   std::string outPrefix = "results/2014xxxx";

   tsw::Samples2012 samples("zEffiTree");
   tsw::SetStyle()->cd();

   std::string treeName("zBosonEffiTree");
   tsw::AxisDefn axisDefn("ZpT", "[0,2,4,6,8,10, 12.5,15,17.5,20,30, 40,50,70,90,110, 150,190,250,350,550, 750,1000,1250,1500,1750, 2000]", "Z boson p_{T} [GeV]", 1.0);
   std::string boostedZeeSeln("(abs(mcZ_ele1_p4.Eta())<2.1) && (abs(mcZ_ele2_p4.Eta())<2.1) && (mcZ_ele1_p4.Et()>20.0) && (mcZ_ele2_p4.Et()>20.0)");
   TH1* histBoostedZeeMG = samples.dyEE_mg_merged().getFilledHist("hBoostedZee_MG_ZpT", treeName, axisDefn, boostedZeeSeln, "exp(-4.8 * ZpT / 10000.0)");
   histBoostedZeeMG->Scale( 1.0 / histBoostedZeeMG->Integral(19,23,"width") );


   TCanvas* c = new TCanvas("canvas", "Z boson pT", 600, 400);
   c->cd();
   c->SetLogy();
   histBoostedZeeMG->Draw();
   histBoostedZeeMG->GetXaxis()->SetRangeUser(250, 1249);
   histBoostedZeeMG->GetYaxis()->SetTitle("Fraction / 1 GeV");

   Float_t binLims[] = {0,2,4,6,8,10, 12.5,15,17.5,20,30, 40,50,70,90,110, 150,190,250,350,550, 750,1000,1250,1500,1750, 2000};
   TH1F* hist = new TH1F("expertPowhegZpt", "expertPowhegZpt", 26, binLims);

   for(Int_t i=1; i<=26; i++)
   {
     hist->SetBinContent(i, 0.1);
     hist->SetBinError(i, 0.0);
   }
   /*hist->SetBinContent(1,  2.144295e-02);
   hist->SetBinContent(2,  4.814757e-02);
   hist->SetBinContent(3,  5.069378e-02);
   hist->SetBinContent(4,  4.591795e-02);
   hist->SetBinContent(5,  3.922000e-02);
   hist->SetBinContent(6,  3.250507e-02);
   hist->SetBinContent(7,  2.688241e-02);
   hist->SetBinContent(8,  2.239995e-02);
   hist->SetBinContent(9,  1.885164e-02);
   hist->SetBinContent(10, 1.268952e-02);
   hist->SetBinContent(11, 7.311480e-03);
   hist->SetBinContent(12, 4.462025e-03);
   hist->SetBinContent(13, 2.385283e-03);
   hist->SetBinContent(14, 1.084726e-03);
   hist->SetBinContent(15, 5.273478e-04);
   hist->SetBinContent(16, 2.147773e-04);
   hist->SetBinContent(17, 7.452128e-05);
   hist->SetBinContent(18, 2.173190e-05);
   hist->SetBinContent(19, 4.779814e-06);
   hist->SetBinContent(20, 5.250174e-07);*/

   hist->SetBinContent(1,  9.2664);
   hist->SetBinContent(2,  20.532);
   hist->SetBinContent(3,  21.80219);
   hist->SetBinContent(4,  19.41193);
   hist->SetBinContent(5,  16.65929);

   hist->SetBinContent(6,  13.8955);
   hist->SetBinContent(7,  11.41830);
   hist->SetBinContent(8,  9.551316);
   hist->SetBinContent(9,  7.976880);
   hist->SetBinContent(10, 5.420055);

   hist->SetBinContent(11, 3.076209);
   hist->SetBinContent(12, 1.888153);
   hist->SetBinContent(13, 1.013663);
   hist->SetBinContent(14, 0.4633540);
   hist->SetBinContent(15, 0.2273508);

   hist->SetBinContent(16, 9.205043e-02);
   hist->SetBinContent(17, 3.048947e-02);
   hist->SetBinContent(18, 8.660911e-03);
   hist->SetBinContent(19, 1.899264e-03);
   hist->SetBinContent(20, 2.173050e-04);

   hist->SetBinContent(21, 1.349220e-05);
   hist->SetBinContent(22, 1.396244e-06);
   hist->SetBinContent(23, 1.269979e-07);
   hist->SetBinContent(24, 1.339855e-08);
   hist->SetBinContent(25, 1.404013e-09);
   hist->SetBinContent(26, 1.534835e-10);


   std::cout << " integral, expertPowhegZpt : " << hist->Integral("width") << std::endl;
   std::cout << "   ... now re-norm to 1 ... " << std::endl;

   Double_t scaleFactor = 1.0 / hist->Integral(19, 23, "width");
   hist->Scale( scaleFactor);

   std::cout << " integral, expertPowhegZpt : " << hist->Integral("width") << std::endl;

   hist->Draw("SAME");


   TCanvas* cRatio = new TCanvas("cRatio", "POWHEG / MadGraph ratio", 600, 400); 
   cRatio->cd();


   TH1* hRatio = (TH1*) hist->Clone("h_zpt_ratio");

   hRatio->Divide(histBoostedZeeMG);

   hRatio->Draw();
   hRatio->GetXaxis()->SetRangeUser(250, 1249);
   hRatio->GetYaxis()->SetTitle("Ratio");
   cRatio->Update();

}
