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

void DrawRatio(bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1"){ 

	SetStyle();
	gStyle->SetOptFit(0);

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString fullDIR = mainDIR + "/CorrDist/CorrDistFull";
	TString fullsigDIR = mainDIR + "/CorrDist/CorrDistFullSig";
	TString fullbkgDIR = mainDIR + "/CorrDist/CorrDistFullBkg";
	TString cut1DIR = mainDIR + "/CorrDist/CorrDistCut1";
	TString cut1sigDIR = mainDIR + "/CorrDist/CorrDistCut1Sig";
	TString cut1bkgDIR = mainDIR + "/CorrDist/CorrDistCut1Bkg";
	TString cut1p5DIR = mainDIR + "/CorrDist/CorrDistCut1p5";
	TString cut1p5sigDIR = mainDIR + "/CorrDist/CorrDistCut1p5Sig";
	TString cut1p5bkgDIR = mainDIR + "/CorrDist/CorrDistCut1p5Bkg";
	TString cut2DIR = mainDIR + "/CorrDist/CorrDistCut2";
	TString cut2sigDIR = mainDIR + "/CorrDist/CorrDistCut2Sig";
	TString cut2bkgDIR = mainDIR + "/CorrDist/CorrDistCut2Bkg";

	void * dirf = gSystem->OpenDirectory(fullDIR.Data());
	if(dirf) gSystem->FreeDirectory(dirf);
	else gSystem->mkdir(fullDIR.Data(), kTRUE);

	void * dirfs = gSystem->OpenDirectory(fullsigDIR.Data());
	if(dirfs) gSystem->FreeDirectory(dirfs);
	else gSystem->mkdir(fullsigDIR.Data(), kTRUE);

	void * dirfb = gSystem->OpenDirectory(fullbkgDIR.Data());
	if(dirfb) gSystem->FreeDirectory(dirfb);
	else gSystem->mkdir(fullbkgDIR.Data(), kTRUE);

	void * dirc1 = gSystem->OpenDirectory(cut1DIR.Data());
	if(dirc1) gSystem->FreeDirectory(dirc1);
	else gSystem->mkdir(cut1DIR.Data(), kTRUE);

	void * dirc1s = gSystem->OpenDirectory(cut1sigDIR.Data());
	if(dirc1s) gSystem->FreeDirectory(dirc1s);
	else gSystem->mkdir(cut1sigDIR.Data(), kTRUE);

	void * dirc1b = gSystem->OpenDirectory(cut1bkgDIR.Data());
	if(dirc1b) gSystem->FreeDirectory(dirc1b);
	else gSystem->mkdir(cut1bkgDIR.Data(), kTRUE);

	void * dirc1p5 = gSystem->OpenDirectory(cut1p5DIR.Data());
	if(dirc1p5) gSystem->FreeDirectory(dirc1p5);
	else gSystem->mkdir(cut1p5DIR.Data(), kTRUE);

	void * dirc1p5s = gSystem->OpenDirectory(cut1p5sigDIR.Data());
	if(dirc1p5s) gSystem->FreeDirectory(dirc1p5s);
	else gSystem->mkdir(cut1p5sigDIR.Data(), kTRUE);

	void * dirc1p5b = gSystem->OpenDirectory(cut1p5bkgDIR.Data());
	if(dirc1p5b) gSystem->FreeDirectory(dirc1p5b);
	else gSystem->mkdir(cut1p5bkgDIR.Data(), kTRUE);

	void * dirc2 = gSystem->OpenDirectory(cut2DIR.Data());
	if(dirc2) gSystem->FreeDirectory(dirc2);
	else gSystem->mkdir(cut2DIR.Data(), kTRUE);

	void * dirc2s = gSystem->OpenDirectory(cut2sigDIR.Data());
	if(dirc2s) gSystem->FreeDirectory(dirc2s);
	else gSystem->mkdir(cut2sigDIR.Data(), kTRUE);

	void * dirc2b = gSystem->OpenDirectory(cut2bkgDIR.Data());
	if(dirc2b) gSystem->FreeDirectory(dirc2b);
	else gSystem->mkdir(cut2bkgDIR.Data(), kTRUE);
//}}}

	TFile *sigPbp; TFile *sigpPb;
	TFile *bkgPbp; TFile *bkgpPb;

//Define canvas and histogram{{{

//Define canvas{{{

//fine{{{
	TCanvas* cfull_fine = new TCanvas("cfull_fine", "", 0, 0, 600, 600);
	TCanvas* cfull_sig_fine = new TCanvas("cfull_sig_fine", "", 0, 0, 600, 600);
	TCanvas* cfull_bkg_fine = new TCanvas("cfull_bkg_fine", "", 0, 0, 600, 600);
	TCanvas* ccut1_fine = new TCanvas("ccut1_fine", "", 0, 0, 600, 600);
	TCanvas* ccut1_sig_fine = new TCanvas("ccut1_sig_fine", "", 0, 0, 600, 600);
	TCanvas* ccut1_bkg_fine = new TCanvas("ccut1_bkg_fine", "", 0, 0, 600, 600);
	TCanvas* ccut1p5_fine = new TCanvas("ccut1p5_fine", "", 0, 0, 600, 600);
	TCanvas* ccut1p5_sig_fine = new TCanvas("ccut1p5_sig_fine", "", 0, 0, 600, 600);
	TCanvas* ccut1p5_bkg_fine = new TCanvas("ccut1p5_bkg_fine", "", 0, 0, 600, 600);
	TCanvas* ccut2_fine = new TCanvas("ccut2_fine", "", 0, 0, 600, 600);
	TCanvas* ccut2_sig_fine = new TCanvas("ccut2_sig_fine", "", 0, 0, 600, 600);
	TCanvas* ccut2_bkg_fine = new TCanvas("ccut2_bkg_fine", "", 0, 0, 600, 600);
//}}}

//coarse{{{
	TCanvas* cfull_coarse = new TCanvas("cfull_coarse", "", 0, 0, 600, 600);
	TCanvas* cfull_sig_coarse = new TCanvas("cfull_sig_coarse", "", 0, 0, 600, 600);
	TCanvas* cfull_bkg_coarse = new TCanvas("cfull_bkg_coarse", "", 0, 0, 600, 600);
	TCanvas* ccut1_coarse = new TCanvas("ccut1_coarse", "", 0, 0, 600, 600);
	TCanvas* ccut1_sig_coarse = new TCanvas("ccut1_sig_coarse", "", 0, 0, 600, 600);
	TCanvas* ccut1_bkg_coarse = new TCanvas("ccut1_bkg_coarse", "", 0, 0, 600, 600);
	TCanvas* ccut1p5_coarse = new TCanvas("ccut1p5_coarse", "", 0, 0, 600, 600);
	TCanvas* ccut1p5_sig_coarse = new TCanvas("ccut1p5_sig_coarse", "", 0, 0, 600, 600);
	TCanvas* ccut1p5_bkg_coarse = new TCanvas("ccut1p5_bkg_coarse", "", 0, 0, 600, 600);
	TCanvas* ccut2_coarse = new TCanvas("ccut2_coarse", "", 0, 0, 600, 600);
	TCanvas* ccut2_sig_coarse = new TCanvas("ccut2_sig_coarse", "", 0, 0, 600, 600);
	TCanvas* ccut2_bkg_coarse = new TCanvas("ccut2_bkg_coarse", "", 0, 0, 600, 600);
//}}}

//}}}

//Define histogram{{{

//fine{{{

//2D ratio{{{
	TH2D* hfullRatio_fine = new TH2D("hfullRatio_fine", ";#Delta#eta;#Delta#phi", Netabin1-4, -9.9*(Netabin1-4)/(2*Netabin1), 9.9*(Netabin1-4)/(2*Netabin1), Nphibin1,-(0.5-1.0/(Nphibin1+1))*TMath::Pi(),(1.5-1.0/(Nphibin1+1))*TMath::Pi());
	TH2D* hcut1Ratio_fine = new TH2D("hcut1Ratio_fine", ";#Delta#eta;#Delta#phi", Netabin1-4, -9.9*(Netabin1-4)/(2*Netabin1), 9.9*(Netabin1-4)/(2*Netabin1), Nphibin1,-(0.5-1.0/(Nphibin1+1))*TMath::Pi(),(1.5-1.0/(Nphibin1+1))*TMath::Pi());
	TH2D* hcut1p5Ratio_fine = new TH2D("hcut1p5Ratio_fine", ";#Delta#eta;#Delta#phi", Netabin1-4, -9.9*(Netabin1-4)/(2*Netabin1), 9.9*(Netabin1-4)/(2*Netabin1), Nphibin1,-(0.5-1.0/(Nphibin1+1))*TMath::Pi(),(1.5-1.0/(Nphibin1+1))*TMath::Pi());
	TH2D* hcut2Ratio_fine = new TH2D("hcut2Ratio_fine", ";#Delta#eta;#Delta#phi", Netabin1-4, -9.9*(Netabin1-4)/(2*Netabin1), 9.9*(Netabin1-4)/(2*Netabin1), Nphibin1,-(0.5-1.0/(Nphibin1+1))*TMath::Pi(),(1.5-1.0/(Nphibin1+1))*TMath::Pi());
	FormTH2(hfullRatio_fine);
	FormTH2(hcut1Ratio_fine);
	FormTH2(hcut1p5Ratio_fine);
	FormTH2(hcut2Ratio_fine);
//}}}

//2D plot{{{
	TH2D *hSigPbp_fine;
	TH2D *hSigpPb_fine;
	TH2D *hBkgPbp_fine;
	TH2D *hBkgpPb_fine;
	TH2D *hSig_cut1Pbp_fine;
	TH2D *hSig_cut1pPb_fine;
	TH2D *hBkg_cut1Pbp_fine;
	TH2D *hBkg_cut1pPb_fine;
	TH2D *hSig_cut1p5Pbp_fine;
	TH2D *hSig_cut1p5pPb_fine;
	TH2D *hBkg_cut1p5Pbp_fine;
	TH2D *hBkg_cut1p5pPb_fine;
	TH2D *hSig_cut2Pbp_fine;
	TH2D *hSig_cut2pPb_fine;
	TH2D *hBkg_cut2Pbp_fine;
	TH2D *hBkg_cut2pPb_fine;
//}}}

//}}}

//coarse{{{

//2D ratio{{{
	TH2D* hfullRatio_coarse = new TH2D("hfullRatio_coarse", ";#Delta#eta;#Delta#phi", Netabin2-2, -9.9*(Netabin2-2)/(2*Netabin2), 9.9*(Netabin2-2)/(2*Netabin2), Nphibin2,-(0.5-1.0/(Nphibin2+1))*TMath::Pi(),(1.5-1.0/(Nphibin2+1))*TMath::Pi());
	TH2D* hcut1Ratio_coarse = new TH2D("hcut1Ratio_coarse", ";#Delta#eta;#Delta#phi", Netabin2-2, -9.9*(Netabin2-2)/(2*Netabin2), 9.9*(Netabin2-2)/(2*Netabin2), Nphibin2,-(0.5-1.0/(Nphibin2+1))*TMath::Pi(),(1.5-1.0/(Nphibin2+1))*TMath::Pi());
	TH2D* hcut1p5Ratio_coarse = new TH2D("hcut1p5Ratio_coarse", ";#Delta#eta;#Delta#phi", Netabin2-2, -9.9*(Netabin2-2)/(2*Netabin2), 9.9*(Netabin2-2)/(2*Netabin2), Nphibin2,-(0.5-1.0/(Nphibin2+1))*TMath::Pi(),(1.5-1.0/(Nphibin2+1))*TMath::Pi());
	TH2D* hcut2Ratio_coarse = new TH2D("hcut2Ratio_coarse", ";#Delta#eta;#Delta#phi", Netabin2-2, -9.9*(Netabin2-2)/(2*Netabin2), 9.9*(Netabin2-2)/(2*Netabin2), Nphibin2,-(0.5-1.0/(Nphibin2+1))*TMath::Pi(),(1.5-1.0/(Nphibin2+1))*TMath::Pi());
	FormTH2(hfullRatio_coarse);
	FormTH2(hcut1Ratio_coarse);
	FormTH2(hcut1p5Ratio_coarse);
	FormTH2(hcut2Ratio_coarse);
//}}}

//2D plot{{{
	TH2D *hSigPbp_coarse;
	TH2D *hSigpPb_coarse;
	TH2D *hBkgPbp_coarse;
	TH2D *hBkgpPb_coarse;
	TH2D *hSig_cut1Pbp_coarse;
	TH2D *hSig_cut1pPb_coarse;
	TH2D *hBkg_cut1Pbp_coarse;
	TH2D *hBkg_cut1pPb_coarse;
	TH2D *hSig_cut1p5Pbp_coarse;
	TH2D *hSig_cut1p5pPb_coarse;
	TH2D *hBkg_cut1p5Pbp_coarse;
	TH2D *hBkg_cut1p5pPb_coarse;
	TH2D *hSig_cut2Pbp_coarse;
	TH2D *hSig_cut2pPb_coarse;
	TH2D *hBkg_cut2Pbp_coarse;
	TH2D *hBkg_cut2pPb_coarse;
//}}}

//}}}

//}}}

//}}}

	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->SetNDC();

	for(Int_t imass = 0; imass < mass_narr-1; imass++)
	{

//Get files{{{
		sigPbp = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s/deta-dphi_Pbp_distribution_sig_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "READ");
		sigpPb = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s/deta-dphi_pPb_distribution_sig_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "READ");
		bkgPbp = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s/deta-dphi_Pbp_distribution_bkg_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "READ");
		bkgpPb = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s/deta-dphi_pPb_distribution_bkg_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "READ");
//}}}

//Get full range plot{{{

//get plot{{{
		hSigPbp_fine = (TH2D*)sigPbp->Get("hSigPbp1_1"); hSigPbp_fine->Sumw2();
		hSigPbp_coarse = (TH2D*)sigPbp->Get("hSigPbp1_2"); hSigPbp_coarse->Sumw2();
		hSigpPb_fine = (TH2D*)sigpPb->Get("hSigpPb1_1"); hSigpPb_fine->Sumw2();
		hSigpPb_coarse = (TH2D*)sigpPb->Get("hSigpPb1_2"); hSigpPb_coarse->Sumw2();
		hBkgPbp_fine = (TH2D*)bkgPbp->Get("hBkgPbp1_1"); hBkgPbp_fine->Sumw2();
		hBkgPbp_coarse = (TH2D*)bkgPbp->Get("hBkgPbp1_2"); hBkgPbp_coarse->Sumw2();
		hBkgpPb_fine = (TH2D*)bkgpPb->Get("hBkgpPb1_1"); hBkgpPb_fine->Sumw2();
		hBkgpPb_coarse = (TH2D*)bkgpPb->Get("hBkgpPb1_2"); hBkgpPb_coarse->Sumw2();
		hSigPbp_fine->Add(hSigpPb_fine);
		hSigPbp_coarse->Add(hSigpPb_coarse);
		hBkgPbp_fine->Add(hBkgpPb_fine);
		hBkgPbp_coarse->Add(hBkgpPb_coarse);
//}}}

//Draw sig & bkg{{{
		cfull_sig_fine->cd();
		hSigPbp_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		cfull_sig_fine->SaveAs(Form("CorrDist/CorrDistFullSig/plot_corr_full_sig_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
		cfull_bkg_fine->cd();
		hBkgPbp_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		cfull_bkg_fine->SaveAs(Form("CorrDist/CorrDistFullBkg/plot_corr_full_bkg_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
		cfull_sig_coarse->cd();
		hSigPbp_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		cfull_sig_coarse->SaveAs(Form("CorrDist/CorrDistFullSig/plot_corr_full_sig_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
		cfull_bkg_coarse->cd();
		hBkgPbp_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		cfull_bkg_coarse->SaveAs(Form("CorrDist/CorrDistFullBkg/plot_corr_full_bkg_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

//Draw ratio{{{
		hSigPbp_fine->Divide(hBkgPbp_fine);
		//hSigPbp->Scale(hBkgPbp->GetBinContent(7,7)); // multiply B(0,0) 
		for(Int_t j = 0; j < Netabin1-4; j++)
		{
			for(Int_t k = 0; k < Nphibin1; k++)
			{
				hfullRatio_fine->SetBinContent(j+1, k+1, hSigPbp_fine->GetBinContent(j+3, k+1));
			}
		}
		cfull_fine->cd();
		hfullRatio_fine->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#delta#phi}");
		hfullRatio_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		cfull_fine->SaveAs(Form("CorrDist/CorrDistFull/plot_corr_full_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));

		hSigPbp_coarse->Divide(hBkgPbp_coarse);
		for(Int_t j = 0; j < Netabin2-2; j++)
		{
			for(Int_t k = 0; k < Nphibin2; k++)
			{
				hfullRatio_coarse->SetBinContent(j+1, k+1, hSigPbp_coarse->GetBinContent(j+2, k+1));
			}
		}
		cfull_coarse->cd();
		hfullRatio_coarse->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#delta#phi}");
		hfullRatio_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		cfull_coarse->SaveAs(Form("CorrDist/CorrDistFull/plot_corr_full_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

//}}}

//Get |deta| > 2 range plot{{{

//get plot{{{
		hSig_cut2Pbp_fine = (TH2D*)sigPbp->Get("hSigPbp2_1"); hSig_cut2Pbp_fine->Sumw2();
		hSig_cut2Pbp_coarse = (TH2D*)sigPbp->Get("hSigPbp2_2"); hSig_cut2Pbp_coarse->Sumw2();
		hSig_cut2pPb_fine = (TH2D*)sigpPb->Get("hSigpPb2_1"); hSig_cut2pPb_fine->Sumw2();
		hSig_cut2pPb_coarse = (TH2D*)sigpPb->Get("hSigpPb2_2"); hSig_cut2pPb_coarse->Sumw2();
		hBkg_cut2Pbp_fine = (TH2D*)bkgPbp->Get("hBkgPbp2_1"); hBkg_cut2Pbp_fine->Sumw2();
		hBkg_cut2Pbp_coarse = (TH2D*)bkgPbp->Get("hBkgPbp2_2"); hBkg_cut2Pbp_coarse->Sumw2();
		hBkg_cut2pPb_fine = (TH2D*)bkgpPb->Get("hBkgpPb2_1"); hBkg_cut2pPb_fine->Sumw2();
		hBkg_cut2pPb_coarse = (TH2D*)bkgpPb->Get("hBkgpPb2_2"); hBkg_cut2pPb_coarse->Sumw2();
		hSig_cut2Pbp_fine->Add(hSig_cut2pPb_fine);
		hSig_cut2Pbp_coarse->Add(hSig_cut2pPb_coarse);
		hBkg_cut2Pbp_fine->Add(hBkg_cut2pPb_fine);
		hBkg_cut2Pbp_coarse->Add(hBkg_cut2pPb_coarse);
//}}}

//Draw sig & bkg{{{
		ccut2_sig_fine->cd();
		hSig_cut2Pbp_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 2.0");
		ccut2_sig_fine->SaveAs(Form("CorrDist/CorrDistCut2Sig/plot_corr_sig_cut2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
		ccut2_bkg_fine->cd();
		hBkg_cut2Pbp_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 2.0");
		ccut2_bkg_fine->SaveAs(Form("CorrDist/CorrDistCut2Bkg/plot_corr_bkg_cut2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
		ccut2_sig_coarse->cd();
		hSig_cut2Pbp_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 2.0");
		ccut2_sig_coarse->SaveAs(Form("CorrDist/CorrDistCut2Sig/plot_corr_sig_cut2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
		ccut2_bkg_coarse->cd();
		hBkg_cut2Pbp_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 2.0");
		ccut2_bkg_coarse->SaveAs(Form("CorrDist/CorrDistCut2Bkg/plot_corr_bkg_cut2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

//Draw ratio{{{
		hSig_cut2Pbp_fine->Divide(hBkg_cut2Pbp_fine);
	//	hSig_cut2Pbp->Scale(hBkgPbp->GetBinContent(7,7)); // multiply B(0,0) 
		for(Int_t j = 0; j < Netabin1-4; j++)
		{
			for(Int_t k = 0; k < Nphibin1; k++)
			{
				hcut2Ratio_fine->SetBinContent(j+1, k+1, hSig_cut2Pbp_fine->GetBinContent(j+3, k+1));
				hcut2Ratio_fine->SetBinError(j+1, k+1, hSig_cut2Pbp_fine->GetBinError(j+3, k+1));
			}
		}
		ccut2_fine->cd();
		hcut2Ratio_fine->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#delta#phi}");
		hcut2Ratio_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 2.0");
		ccut2_fine->SaveAs(Form("CorrDist/CorrDistCut2/plot_corr_cut2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));

		hSig_cut2Pbp_coarse->Divide(hBkg_cut2Pbp_coarse);
		for(Int_t j = 0; j < Netabin2-2; j++)
		{
			for(Int_t k = 0; k < Nphibin2; k++)
			{
				hcut2Ratio_coarse->SetBinContent(j+1, k+1, hSig_cut2Pbp_coarse->GetBinContent(j+2, k+1));
				hcut2Ratio_coarse->SetBinError(j+1, k+1, hSig_cut2Pbp_coarse->GetBinError(j+2, k+1));
			}
		}
		ccut2_coarse->cd();
		hcut2Ratio_coarse->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#delta#phi}");
		hcut2Ratio_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 2.0");
		ccut2_coarse->SaveAs(Form("CorrDist/CorrDistCut2/plot_corr_cut2_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

//}}}

//Get |deta| > 1.5 range plot{{{

//get plot{{{
		hSig_cut1p5Pbp_fine = (TH2D*)sigPbp->Get("hSigPbp3_1"); hSig_cut1p5Pbp_fine->Sumw2();
		hSig_cut1p5Pbp_coarse = (TH2D*)sigPbp->Get("hSigPbp3_2"); hSig_cut1p5Pbp_coarse->Sumw2();
		hSig_cut1p5pPb_fine = (TH2D*)sigpPb->Get("hSigpPb3_1"); hSig_cut1p5pPb_fine->Sumw2();
		hSig_cut1p5pPb_coarse = (TH2D*)sigpPb->Get("hSigpPb3_2"); hSig_cut1p5pPb_coarse->Sumw2();
		hBkg_cut1p5Pbp_fine = (TH2D*)bkgPbp->Get("hBkgPbp3_1"); hBkg_cut1p5Pbp_fine->Sumw2();
		hBkg_cut1p5Pbp_coarse = (TH2D*)bkgPbp->Get("hBkgPbp3_2"); hBkg_cut1p5Pbp_coarse->Sumw2();
		hBkg_cut1p5pPb_fine = (TH2D*)bkgpPb->Get("hBkgpPb3_1"); hBkg_cut1p5pPb_fine->Sumw2();
		hBkg_cut1p5pPb_coarse = (TH2D*)bkgpPb->Get("hBkgpPb3_2"); hBkg_cut1p5pPb_coarse->Sumw2();
		hSig_cut1p5Pbp_fine->Add(hSig_cut1p5pPb_fine);
		hSig_cut1p5Pbp_coarse->Add(hSig_cut1p5pPb_coarse);
		hBkg_cut1p5Pbp_fine->Add(hBkg_cut1p5pPb_fine);
		hBkg_cut1p5Pbp_coarse->Add(hBkg_cut1p5pPb_coarse);
//}}}

//Draw sig & bkg{{{
		ccut1p5_sig_fine->cd();
		hSig_cut1p5Pbp_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.5");
		ccut1p5_sig_fine->SaveAs(Form("CorrDist/CorrDistCut1p5Sig/plot_corr_sig_cut1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
		ccut1p5_bkg_fine->cd();
		hBkg_cut1p5Pbp_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.5");
		ccut1p5_bkg_fine->SaveAs(Form("CorrDist/CorrDistCut1p5Bkg/plot_corr_bkg_cut1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
		ccut1p5_sig_coarse->cd();
		hSig_cut1p5Pbp_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.5");
		ccut1p5_sig_coarse->SaveAs(Form("CorrDist/CorrDistCut1p5Sig/plot_corr_sig_cut1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
		ccut1p5_bkg_coarse->cd();
		hBkg_cut1p5Pbp_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.5");
		ccut1p5_bkg_coarse->SaveAs(Form("CorrDist/CorrDistCut1p5Bkg/plot_corr_bkg_cut1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

//Draw ratio{{{
		hSig_cut1p5Pbp_fine->Divide(hBkg_cut1p5Pbp_fine);
	//	hSig_cut2Pbp->Scale(hBkgPbp->GetBinContent(7,7)); // multiply B(0,0) 
		for(Int_t j = 0; j < Netabin1-4; j++)
		{
			for(Int_t k = 0; k < Nphibin1; k++)
			{
				hcut1p5Ratio_fine->SetBinContent(j+1, k+1, hSig_cut1p5Pbp_fine->GetBinContent(j+3, k+1));
				hcut1p5Ratio_fine->SetBinError(j+1, k+1, hSig_cut1p5Pbp_fine->GetBinError(j+3, k+1));
			}
		}
		ccut1p5_fine->cd();
		hcut1p5Ratio_fine->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#delta#phi}");
		hcut1p5Ratio_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.5");
		ccut1p5_fine->SaveAs(Form("CorrDist/CorrDistCut1p5/plot_corr_cut1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));

		hSig_cut1p5Pbp_coarse->Divide(hBkg_cut1p5Pbp_coarse);
		for(Int_t j = 0; j < Netabin2-2; j++)
		{
			for(Int_t k = 0; k < Nphibin2; k++)
			{
				hcut1p5Ratio_coarse->SetBinContent(j+1, k+1, hSig_cut1p5Pbp_coarse->GetBinContent(j+2, k+1));
				hcut1p5Ratio_coarse->SetBinError(j+1, k+1, hSig_cut1p5Pbp_coarse->GetBinError(j+2, k+1));
			}
		}
		ccut1p5_coarse->cd();
		hcut1p5Ratio_coarse->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#delta#phi}");
		hcut1p5Ratio_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.5");
		ccut1p5_coarse->SaveAs(Form("CorrDist/CorrDistCut1p5/plot_corr_cut1p5_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

//}}}

//Get |deta| > 1 range plot{{{

//get plot{{{
		hSig_cut1Pbp_fine = (TH2D*)sigPbp->Get("hSigPbp4_1"); hSig_cut1Pbp_fine->Sumw2();
		hSig_cut1Pbp_coarse = (TH2D*)sigPbp->Get("hSigPbp4_2"); hSig_cut1Pbp_coarse->Sumw2();
		hSig_cut1pPb_fine = (TH2D*)sigpPb->Get("hSigpPb4_1"); hSig_cut1pPb_fine->Sumw2();
		hSig_cut1pPb_coarse = (TH2D*)sigpPb->Get("hSigpPb4_2"); hSig_cut1pPb_coarse->Sumw2();
		hBkg_cut1Pbp_fine = (TH2D*)bkgPbp->Get("hBkgPbp4_1"); hBkg_cut1Pbp_fine->Sumw2();
		hBkg_cut1Pbp_coarse = (TH2D*)bkgPbp->Get("hBkgPbp4_2"); hBkg_cut1Pbp_coarse->Sumw2();
		hBkg_cut1pPb_fine = (TH2D*)bkgpPb->Get("hBkgpPb4_1"); hBkg_cut1pPb_fine->Sumw2();
		hBkg_cut1pPb_coarse = (TH2D*)bkgpPb->Get("hBkgpPb4_2"); hBkg_cut1pPb_coarse->Sumw2();
		hSig_cut1Pbp_fine->Add(hSig_cut1pPb_fine);
		hSig_cut1Pbp_coarse->Add(hSig_cut1pPb_coarse);
		hBkg_cut1Pbp_fine->Add(hBkg_cut1pPb_fine);
		hBkg_cut1Pbp_coarse->Add(hBkg_cut1pPb_coarse);
//}}}

//Draw sig & bkg{{{
		ccut1_sig_fine->cd();
		hSig_cut1Pbp_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.0");
		ccut1_sig_fine->SaveAs(Form("CorrDist/CorrDistCut1Sig/plot_corr_sig_cut1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
		ccut1_bkg_fine->cd();
		hBkg_cut1Pbp_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.0");
		ccut1_bkg_fine->SaveAs(Form("CorrDist/CorrDistCut1Bkg/plot_corr_bkg_cut1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));
		ccut1_sig_coarse->cd();
		hSig_cut1Pbp_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.0");
		ccut1_sig_coarse->SaveAs(Form("CorrDist/CorrDistCut1Sig/plot_corr_sig_cut1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
		ccut1_bkg_coarse->cd();
		hBkg_cut1Pbp_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.0");
		ccut1_bkg_coarse->SaveAs(Form("CorrDist/CorrDistCut1Bkg/plot_corr_bkg_cut1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

//Draw ratio{{{
		hSig_cut1Pbp_fine->Divide(hBkg_cut1Pbp_fine);
	//	hSig_cut1Pbp->Scale(hBkgPbp->GetBinContent(7,7)); // multiply B(0,0) 
		for(Int_t j = 0; j < Netabin1-4; j++)
		{
			for(Int_t k = 0; k < Nphibin1; k++)
			{
				hcut1Ratio_fine->SetBinContent(j+1, k+1, hSig_cut1Pbp_fine->GetBinContent(j+3, k+1));
				hcut1Ratio_fine->SetBinError(j+1, k+1, hSig_cut1Pbp_fine->GetBinError(j+3, k+1));
			}
		}
		ccut1_fine->cd();
		hcut1Ratio_fine->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#delta#phi}");
		hcut1Ratio_fine->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.0");
		ccut1_fine->SaveAs(Form("CorrDist/CorrDistCut1/plot_corr_cut1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin1, Nphibin1, version.Data(), imass));

		hSig_cut1Pbp_coarse->Divide(hBkg_cut1Pbp_coarse);
		for(Int_t j = 0; j < Netabin2-2; j++)
		{
			for(Int_t k = 0; k < Nphibin2; k++)
			{
				hcut1Ratio_coarse->SetBinContent(j+1, k+1, hSig_cut1Pbp_coarse->GetBinContent(j+2, k+1));
				hcut1Ratio_coarse->SetBinError(j+1, k+1, hSig_cut1Pbp_coarse->GetBinError(j+2, k+1));
			}
		}
		ccut1_coarse->cd();
		hcut1Ratio_coarse->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^{2}N^{pair}}{d#Delta#etad#delta#phi}");
		hcut1Ratio_coarse->Draw("Surf1");
		lt1->DrawLatex(0.15,0.95, Form("pPb #sqrt{s} = 8.16 TeV, N^{trk} #geq %d", (int) multMin));
		lt1->DrawLatex(0.15,0.9, Form("%d < p_{T}^{trig} < %d GeV/c", (int) ptMin, (int) ptMax));
		if((int) TrkptMin == 0) lt1->DrawLatex(0.15,0.85, Form("0.3 < p_{T}^{assoc} < %d GeV/c", (int) TrkptMax));
		else lt1->DrawLatex(0.15,0.85, Form("%d < p_{T}^{assoc} < %d GeV/c", (int) TrkptMin, (int) TrkptMax));
		lt1->DrawLatex(0.15,0.8, "|#Delta#eta| < 1.0");
		ccut1_coarse->SaveAs(Form("CorrDist/CorrDistCut1/plot_corr_cut1_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_neta_%d_nphi_%d_%s_%d.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, Netabin2, Nphibin2, version.Data(), imass));
//}}}

//}}}

	}
}
