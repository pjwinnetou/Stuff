#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"
 
TCanvas* example_plot( int iPeriod, int iPos );
 
void myMacro_Z()
{
  //  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  //  gROOT->LoadMacro("CMS_lumi.C");

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  //lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
  //lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
//  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

  int iPeriod = 106;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)

  // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
  // iPos=11 : top-left, left-aligned
   //iPos=33; // top-right, right-aligned
  // iPos=22 : center, centered
  // mode generally : 
  //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)

  //example_plot( iPeriod, 0 );   // out of frame (in exceptional cases)
  //  example_plot( iPeriod, 11 );  // left-aligned
    example_plot( iPeriod, 33 );  // right-aligned

  //  writeExtraText = false;       // remove Preliminary
  
  //  example_plot( iPeriod, 0 );   // out of frame (in exceptional cases)

  //  example_plot( iPeriod, 11 );  // default: left-aligned
  //  example_plot( iPeriod, 22 );  // centered
  //  example_plot( iPeriod, 33 );  // right-aligned  
}

TCanvas* example_plot( int iPeriod, int iPos )
{ 
  //  if( iPos==0 ) relPosX = 0.12;

  int W = 600;
  int H = 600;

  int RUNNUM_1 = 285480;
  int RUNNUM_2 = 285539;
  // 
  // Simple example of macro: plot with CMS name and lumi text
  //  (this script does not pretend to work in all configurations)
  // iPeriod = 1*(0/1 7 TeV) + 2*(0/1 8 TeV)  + 4*(0/1 13 TeV) 
  // For instance: 
  //               iPeriod = 3 means: 7 TeV + 8 TeV
  //               iPeriod = 7 means: 7 TeV + 8 TeV + 13 TeV 
  // Initiated by: Gautier Hamel de Monchenault (Saclay)
  // Updated by:   Dinko Ferencek (Rutgers)
  //
  int H_ref = 600; 
  int W_ref = 800; 

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  TString canvName = "Figure_Z_RUN";
  canvName += RUNNUM_1;
  canvName += "-";
  canvName += RUNNUM_2;
  canvName += iPeriod;
  if( writeExtraText ) canvName += "-prelim";
  if( iPos%10==0 ) canvName += "-out";
  else if( iPos%10==1 ) canvName += "-left";
  else if( iPos%10==2 )  canvName += "-center";
  else if( iPos%10==3 )  canvName += "-right";

  TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);

  TH1* h = new TH1F("h","h",40,80,110);
  h->GetXaxis()->SetNdivisions(6,5,0);
  h->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}} (GeV)");  
  h->GetXaxis()->SetTitleSize(0.053);
  h->GetXaxis()->SetTitleOffset(1.);
  h->GetYaxis()->SetNdivisions(6,5,0);
  h->GetYaxis()->SetTitleOffset(1.4);
  h->GetYaxis()->SetTitleSize(0.053);
  h->GetYaxis()->SetTitle("Events / 0.83 GeV");  
  h->SetMarkerStyle(kRed);

  h->SetMaximum( 700 );
  if( iPos==1 ) h->SetMaximum( 300 );
  h->Draw();
  drawText("Soft Muon",0.17,0.7);    
  drawText("p_{T}^{#mu} > 10 GeV/c",0.17,0.62);    

  int histLineColor = kOrange+7;
  int histFillColor = kOrange-2;
  float markerSize  = 1.0;

  {
    TLatex latex;
				
    int n_ = 2;

    float x1_l = 0.92;
    float y1_l = 0.60;

    float dx_l = 0.30;
    float dy_l = 0.18;
    float x0_l = x1_l-dx_l;
    float y0_l = y1_l-dy_l;

    TPad* legend = new TPad("legend_0","legend_0",x0_l,y0_l,x1_l, y1_l );
    //    legend->SetFillColor( kGray );
    legend->Draw();
    legend->cd();
		
    float ar_l = dy_l/dx_l;
		
    float x_l[1];
    float ex_l[1];
    float y_l[1];
    float ey_l[1];
		
    //    float gap_ = 0.09/ar_l;
    float gap_ = 1./(n_+1);
		
    float bwx_ = 0.12;
    float bwy_ = gap_/1.5;
		
    x_l[0] = 1.2*bwx_;
    //    y_l[0] = 1-(1-0.10)/ar_l;
    y_l[0] = 1-gap_;
    ex_l[0] = 0;
    ey_l[0] = 0.04/ar_l;
		
    TGraph* gr_l = new TGraphErrors(1, x_l, y_l, ex_l, ey_l );
		
    gStyle->SetEndErrorSize(0);
    gr_l->SetMarkerSize(0.9);
    gr_l->SetMarkerColor(kBlack);
    gr_l->Draw("0P");
	

    latex.SetTextFont(42);
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    
    latex.SetTextSize(0.25);    
    latex.SetTextAlign(12); 
		
    TLine line_;
    TBox  box_;
    float xx_ = x_l[0];
    float yy_ = y_l[0];
    latex.DrawLatex(xx_+1.*bwx_,yy_,"Z #rightarrow #mu^{+}#mu^{-}");
 
    yy_ -= gap_;
    box_.SetLineStyle( kSolid );
    box_.SetLineWidth( 1 );
//    		box_.SetLineColor( kRed );
    box_.SetLineColor( histLineColor );
    box_.SetFillColor( histFillColor );
//    box_.DrawBox( xx_-bwx_/2, yy_-bwy_/2, xx_+bwx_/2, yy_+bwy_/2 );
//    box_.SetFillStyle(0);
//    box_.DrawBox( xx_-bwx_/2, yy_-bwy_/2, xx_+bwx_/2, yy_+bwy_/2 );
//    latex.DrawLatex(xx_+1.*bwx_,yy_,"Z #rightarrow #mu^{+}#mu^{-} (MC)");

    canv->cd();
  }

  {
    // Observed data
    TFile file_(Form("histo_%d_%d.root",RUNNUM_1,RUNNUM_2),"READ");

    TH1F *data = static_cast<TH1F*>(file_.Get(Form("hMass_Z_%d_%d",RUNNUM_1,RUNNUM_2))->Clone());
    data->SetDirectory(0);
    data->SetMarkerStyle(20);
    data->SetMarkerSize(markerSize);
    data->SetMarkerColor(kBlack);

    /*TH1F *MC   = static_cast<TH1F*>(file_.Get("MC")->Clone());
    MC->SetDirectory(0);
    MC->SetLineColor(histLineColor);
    MC->SetFillColor(histFillColor);

    MC->Draw("histsame");
    */
    data->Draw("esamex0");
    TF1 *f = new TF1("f","gaus(0)+pol2(3)",80,110);
    f->SetParName(0,"norm");
    f->SetParName(1,"mass");
    f->SetParName(2,"width");
    //f->SetParameters(0.16028e+02,9.07785e+01,10.11556e+00, 1.7600e+00);
    f->SetParameters(0.16028e+02,9.07785e+01,10.11556e+00, 1.7600e+00,9.67443e-01,-6.98382e-03);
    f->SetParLimits(0,0,1e07);
    f->SetParLimits(1,0,201);
    f->SetParLimits(2,0.5,100);
    data->Fit("f","RL");
    data->GetYaxis()->SetRangeUser(0,200);

    TF1 *f2 = new TF1("f2","gaus(0)",80,110);
    f2->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2));
    int integral = (int) (f2->Integral(80,110) / h->GetBinWidth(2));
    cout << "integral : " << integral << endl;

    file_.Close();
  }

  // writing the lumi information and the CMS "logo"
  CMS_lumi( canv, iPeriod, iPos );

  canv->Update();
  canv->RedrawAxis();
  canv->GetFrame()->Draw();

  canv->Print(canvName+".pdf",".pdf");
  canv->Print(canvName+".png",".png");

  return canv;
}
