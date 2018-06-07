//Headers{{{
#include <Riostream.h> 
#include <TSystem.h> 
#include <TBrowser.h> 
#include <TROOT.h> 
#include <TStyle.h> 
#include <TFile.h> 
#include <TTree.h>
#include <TNtuple.h> 
#include <TCanvas.h> 
#include <TGraph.h> 
#include <TGraphAsymmErrors.h> 
#include <TGraphErrors.h> 
#include <TH1.h> 
#include <TH2.h> 
#include <TF1.h> 
#include <TProfile.h> 
#include <TMath.h> 
#include <TLegend.h> 
#include <TString.h> 
#include <TLatex.h> 
#include <TInterpreter.h> 
#include <fstream>
#include "Style_Upv2.h"
#include "Upsilon.h"
//}}}

void set_plot_style() {
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
}

void extV2(bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1")
{ 
	SetStyle();

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString dphiDIR = mainDIR + "/CorrDist/CorrDistdphi";
	TString v2DIR = mainDIR + "/CorrDist/V2Dist";

	void * dird = gSystem->OpenDirectory(dphiDIR.Data());
	if(dird) gSystem->FreeDirectory(dird);
	else gSystem->mkdir(dphiDIR.Data(), kTRUE);

	void * dirv = gSystem->OpenDirectory(v2DIR.Data());
	if(dirv) gSystem->FreeDirectory(dirv);
	else gSystem->mkdir(v2DIR.Data(), kTRUE);
//}}}

  // 0 : no draw, 1 : draw plots
	gStyle->SetOptFit(0);

//Define fitting function{{{
	TF1 *v2_1fine = new TF1("v2_1fine","[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
	v2_1fine->SetLineColor(kViolet+1);
	v2_1fine->SetLineStyle(2);
	v2_1fine->SetLineWidth(2);
	TF1 *v2_1coarse = new TF1("v2_1coarse","[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
	v2_1coarse->SetLineColor(kViolet+1);
	v2_1coarse->SetLineStyle(2);
	v2_1coarse->SetLineWidth(2);
	TF1 *v2_2fine = new TF1("v2_2fine","[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
	v2_2fine->SetLineColor(kViolet+1);
	v2_2fine->SetLineStyle(2);
	v2_2fine->SetLineWidth(2);
	TF1 *v2_2coarse = new TF1("v2_2coarse","[0]*(1+2*[1]*cos(2*x)+2*[2]*cos(x))",-6.28,6.28);
	v2_2coarse->SetLineColor(kViolet+1);
	v2_2coarse->SetLineStyle(2);
	v2_2coarse->SetLineWidth(2);
//}}}

	TFile* fin;

//Define canvas and histogram{{{

//Define canvas{{{
	TCanvas* cdphi1_fine = new TCanvas("cdphi1_fine", "", 0, 0, 600, 600);
	TCanvas* cdphi1_coarse = new TCanvas("cdphi1_coarse", "", 0, 0, 600, 600);
	TCanvas* cdphi2_fine = new TCanvas("cdphi2_fine", "", 0, 0, 600, 600);
	TCanvas* cdphi2_coarse = new TCanvas("cdphi2_coarse", "", 0, 0, 600, 600);
	TCanvas* cv2_1fine = new TCanvas("cv2_1fine", "", 0, 0, 600, 600);
	TCanvas* cv2_1coarse = new TCanvas("cv2_1coarse", "", 0, 0, 600, 600);
	TCanvas* cv2_2fine = new TCanvas("cv2_2fine", "", 0, 0, 600, 600);
	TCanvas* cv2_2coarse = new TCanvas("cv2_2coarse", "", 0, 0, 600, 600);
//}}}

//Define histogram{{{
	TH1D* hDeltaPhi1_fine;
	TH1D* hDeltaPhi1_coarse;
	TH1D* hDeltaPhi2_fine;
	TH1D* hDeltaPhi2_coarse;
	Double_t v2s_1fine[mass_narr-1], v2Es_1fine[mass_narr-1];
	Double_t v2s_1coarse[mass_narr-1], v2Es_1coarse[mass_narr-1];
	Double_t v2s_2fine[mass_narr-1], v2Es_2fine[mass_narr-1];
	Double_t v2s_2coarse[mass_narr-1], v2Es_2coarse[mass_narr-1];
	Double_t massCentArr[mass_narr-1];
	Double_t massValsArr[mass_narr];
	massCentArr[0] = 8;
//}}}

	TLatex *lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->SetNDC();
//}}}

	for(Int_t imass = 0; imass < mass_narr-1; imass++)
	{
		fin = new TFile(Form("CorrDist/CorrFiles/dphi_distribution_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "READ");

//Get dphiplot{{{
		hDeltaPhi1_fine = (TH1D*) fin->Get("hcut1Ratio_fine_py");
		hDeltaPhi1_coarse = (TH1D*) fin->Get("hcut1Ratio_fine_py");
		hDeltaPhi2_fine = (TH1D*) fin->Get("hcut1Ratio_fine_py");
		hDeltaPhi2_coarse = (TH1D*) fin->Get("hcut1Ratio_fine_py");
		hDeltaPhi1_fine->Sumw2();
      hDeltaPhi1_coarse->Sumw2();
      hDeltaPhi2_fine->Sumw2();
      hDeltaPhi2_coarse->Sumw2();
//}}}

//fit dphi with vn function{{{
		cdphi1_fine->cd();
		hDeltaPhi1_fine->Draw("pe");
		hDeltaPhi1_fine->Fit(v2_1fine,"rqm");
		v2s_1fine[imass] = v2_1fine->GetParameter(1);
		v2Es_1fine[imass] = v2_1fine->GetParError(1);
		lt1->DrawLatex(0.1,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N #geq %d", (int) multMin));
		lt1->DrawLatex(0.1,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		lt1->DrawLatex(0.1,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.1,0.75, "|#Delta#eta^{trk}| > 1.0");
		cdphi1_fine->SaveAs(Form("CorrDist/CorrDistdphi/fit_corr1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
		cdphi1_coarse->cd();
		hDeltaPhi1_coarse->Draw("pe");
		hDeltaPhi1_coarse->Fit(v2_1coarse,"rqm");
		v2s_1coarse[imass] = v2_1coarse->GetParameter(1);
		v2Es_1coarse[imass] = v2_1coarse->GetParError(1);
		lt1->DrawLatex(0.1,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N #geq %d", (int) multMin));
		lt1->DrawLatex(0.1,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		lt1->DrawLatex(0.1,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.1,0.75, "|#Delta#eta^{trk}| > 1.0");
		cdphi1_coarse->SaveAs(Form("CorrDist/CorrDistdphi/fit_corr1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
		cdphi2_fine->cd();
		hDeltaPhi2_fine->Draw("pe");
		hDeltaPhi2_fine->Fit(v2_2fine,"rqm");
		v2s_2fine[imass] = v2_2fine->GetParameter(1);
		v2Es_2fine[imass] = v2_2fine->GetParError(1);
		lt1->DrawLatex(0.1,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N #geq %d", (int) multMin));
		lt1->DrawLatex(0.1,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		lt1->DrawLatex(0.1,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.1,0.75, "|#Delta#eta^{trk}| > 2.0");
		cdphi2_fine->SaveAs(Form("CorrDist/CorrDistdphi/fit_corr2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
		cdphi2_coarse->cd();
		hDeltaPhi2_coarse->Draw("pe");
		hDeltaPhi2_coarse->Fit(v2_2coarse,"rqm");
		v2s_2coarse[imass] = v2_2coarse->GetParameter(1);
		v2Es_2coarse[imass] = v2_2coarse->GetParError(1);
		lt1->DrawLatex(0.1,0.9, Form("pPb #sqrt{s} = 8.16 TeV, N #geq %d", (int) multMin));
		lt1->DrawLatex(0.1,0.85, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		lt1->DrawLatex(0.1,0.8, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.1,0.75, "|#Delta#eta^{trk}| > 2.0");
		cdphi2_coarse->SaveAs(Form("CorrDist/CorrDistdphi/fit_corr2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

		massCentArr[imass] = 8 + massBinsArr[imass]*0.05 + (massBinsArr[imass+1]-massBinsArr[imass])*0.05/2.;
		massValsArr[imass+1] = 8 + massBinsArr[imass+1]*0.05;

		//TLatex *lt1 = new TLatex();
		//FormLatex(lt1, 12, 0.04);
		//lt1->SetNDC();
		//lt1->DrawLatex(0.4,0.4,Form("v_{2} : %0.3f #+- %0.4f",v2s,v2Errs));
		//lt1->DrawLatex(0.4,0.35, "|#Delta#eta^{trk}| > 1.0");
	}

//Define graph{{{
	TH1D* hRef = new TH1D("hRef", "", mass_narr, massValsArr);
	hRef->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
	hRef->GetYaxis()->SetTitle("v_{2}");
	hRef->SetMinimum(-0.1);
	hRef->SetMaximum(0.3);

	TGraphErrors* gv2_1fine = new TGraphErrors(mass_narr-1, massCentArr, v2s_1fine, 0, v2Es_1fine);
	gv2_1fine->SetName("gv2_1fine");
	TGraphErrors* gv2_1coarse = new TGraphErrors(mass_narr-1, massCentArr, v2s_1coarse, 0, v2Es_1coarse);
	gv2_1coarse->SetName("gv2_1coarse");
	TGraphErrors* gv2_2fine = new TGraphErrors(mass_narr-1, massCentArr, v2s_2fine, 0, v2Es_2fine);
	gv2_2fine->SetName("gv2_2fine");
	TGraphErrors* gv2_2coarse = new TGraphErrors(mass_narr-1, massCentArr, v2s_2coarse, 0, v2Es_2coarse);
	gv2_2coarse->SetName("gv2_2coarse");
//}}}

	cv2_1fine->cd();
	hRef->Draw();
	gv2_1fine->SetMarkerStyle(20);
	gv2_1fine->SetMarkerSize(1.2);
	gv2_1fine->Draw("pesame");
	cv2_1fine->SaveAs(Form("CorrDist/V2Dist/v2_dist_1fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));

	cv2_1coarse->cd();
	hRef->Draw();
	gv2_1coarse->SetMarkerStyle(20);
	gv2_1coarse->SetMarkerSize(1.2);
	gv2_1coarse->Draw("pesame");
	cv2_1coarse->SaveAs(Form("CorrDist/V2Dist/v2_dist_1coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));

	cv2_2fine->cd();
	hRef->Draw();
	gv2_2fine->SetMarkerStyle(20);
	gv2_2fine->SetMarkerSize(1.2);
	gv2_2fine->Draw("pesame");
	cv2_2fine->SaveAs(Form("CorrDist/V2Dist/v2_dist_2fine_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));

	cv2_2coarse->cd();
	hRef->Draw();
	gv2_2coarse->SetMarkerStyle(20);
	gv2_2coarse->SetMarkerSize(1.2);
	gv2_2coarse->Draw("pesame");
	cv2_2coarse->SaveAs(Form("CorrDist/V2Dist/v2_dist_2coarse_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));

	TFile* fout = new TFile(Form("CorrDist/CorrFiles/v2_dist_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()), "RECREATE");
	fout->cd();
	gv2_1fine->Write();
	gv2_1coarse->Write();
	gv2_2fine->Write();
	gv2_2coarse->Write();
/*
	gStyle->SetOptStat(0000);
	cmass->cd();
	hMass->SetMaximum(0.6);
	hMass->SetMinimum(-0.2);
	hMass->Draw("E");
	lt1->DrawLatex(0.16, 0.90, "CMS Preliminary");
	lt1->DrawLatex(0.64, 0.90, Form("%d < p_{T}^{trk} < %d GeV/c", (int)TrkptMin, (int)TrkptMax));
	lt1->DrawLatex(0.64, 0.83, "|#Delta#eta^{trk}| > 2.0");
	lt1->DrawLatex(0.16, 0.83, "p_{T}^{#mu} > 4.0 GeV/c");
	cmass->SaveAs(Form("plot_mass_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%dmbin.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), mass_narr));
*/
}
