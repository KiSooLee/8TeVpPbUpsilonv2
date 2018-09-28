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

//{{{
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
//}}}

void RatioNProjection_trk(bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1"){ 

	SetStyle();
	gStyle->SetOptFit(0);

//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString dphiDIR = mainDIR + "/CorrDist/CorrDistdphi";
	TString fileDIR = mainDIR + "/CorrDist/CorrFiles";

	void * dird = gSystem->OpenDirectory(dphiDIR.Data());
	if(dird) gSystem->FreeDirectory(dird);
	else gSystem->mkdir(dphiDIR.Data(), kTRUE);

	void * dirfile = gSystem->OpenDirectory(fileDIR.Data());
	if(dirfile) gSystem->FreeDirectory(dirfile);
	else gSystem->mkdir(fileDIR.Data(), kTRUE);
//}}}

	TFile *sigPbp; TFile *sigpPb;
	TFile *bkgPbp; TFile *bkgpPb;

//Define histogram{{{

//2D plot{{{
	TH2D *hSig_cut1Pbp;
	TH2D *hSig_cut1pPb;
	TH2D *hBkg_cut1Pbp;
	TH2D *hBkg_cut1pPb;
	TH2D *hSig_cut1p5Pbp;
	TH2D *hSig_cut1p5pPb;
	TH2D *hBkg_cut1p5Pbp;
	TH2D *hBkg_cut1p5pPb;
	TH2D *hSig_cut2Pbp;
	TH2D *hSig_cut2pPb;
	TH2D *hBkg_cut2Pbp;
	TH2D *hBkg_cut2pPb;
//}}}

//1D projection{{{
	TH1D *hSigDeltaPhi1;
	TH1D *hBkgDeltaPhi1;
	TH1D *hSigDeltaPhi1p5;
	TH1D *hBkgDeltaPhi1p5;
	TH1D *hSigDeltaPhi2;
	TH1D *hBkgDeltaPhi2;
//}}}

//}}}

	TLatex* lt1 = new TLatex();
	FormLatex(lt1, 12, 0.04);
	lt1->SetNDC();

	for(Int_t imass = 0; imass < mass_narr-1; imass++)
	{

//Get files{{{
		sigPbp = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s/trk_deta-dphi_Pbp_distribution_sig_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "READ");
		sigpPb = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s/trk_deta-dphi_pPb_distribution_sig_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "READ");
		bkgPbp = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s/trk_deta-dphi_Pbp_distribution_bkg_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "READ");
		bkgpPb = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%s/trk_deta-dphi_pPb_distribution_bkg_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "READ");
//}}}

//Get |deta| > 2 range plot{{{

//get plot{{{
		hSig_cut2Pbp = (TH2D*)sigPbp->Get("hSigPbp2_1"); hSig_cut2Pbp->Sumw2();
		hSig_cut2pPb = (TH2D*)sigpPb->Get("hSigpPb2_1"); hSig_cut2pPb->Sumw2();
		hBkg_cut2Pbp = (TH2D*)bkgPbp->Get("hBkgPbp2_1"); hBkg_cut2Pbp->Sumw2();
		hBkg_cut2pPb = (TH2D*)bkgpPb->Get("hBkgpPb2_1"); hBkg_cut2pPb->Sumw2();
		hSig_cut2Pbp->Add(hSig_cut2pPb);
		hBkg_cut2Pbp->Add(hBkg_cut2pPb);
//}}}

//projection{{{
		hSigDeltaPhi2 = (TH1D*)hSig_cut2Pbp->ProjectionY();
		hBkgDeltaPhi2 = (TH1D*)hBkg_cut2Pbp->ProjectionY();

		hSigDeltaPhi2->SetName("hSigDeltaPhi2");
		hBkgDeltaPhi2->SetName("hBkgDeltaPhi2");

		FormTH1Marker(hSigDeltaPhi2, 0, 0, 1.4);
		FormTH1Marker(hBkgDeltaPhi2, 0, 0, 1.4);

		TH1D* hRatioDeltaPhi2 = (TH1D*) hSigDeltaPhi2->Clone("hRatioDeltaPhi2");

		hRatioDeltaPhi2->Divide(hBkgDeltaPhi2);
//}}}

//}}}

//Get |deta| > 1.5 range plot{{{

//get plot{{{
		hSig_cut1p5Pbp = (TH2D*)sigPbp->Get("hSigPbp3_1"); hSig_cut1p5Pbp->Sumw2();
		hSig_cut1p5pPb = (TH2D*)sigpPb->Get("hSigpPb3_1"); hSig_cut1p5pPb->Sumw2();
		hBkg_cut1p5Pbp = (TH2D*)bkgPbp->Get("hBkgPbp3_1"); hBkg_cut1p5Pbp->Sumw2();
		hBkg_cut1p5pPb = (TH2D*)bkgpPb->Get("hBkgpPb3_1"); hBkg_cut1p5pPb->Sumw2();
		hSig_cut1p5Pbp->Add(hSig_cut1p5pPb);
		hBkg_cut1p5Pbp->Add(hBkg_cut1p5pPb);
//}}}

//projection{{{
		hSigDeltaPhi1p5 = (TH1D*)hSig_cut1p5Pbp->ProjectionY();
		hBkgDeltaPhi1p5 = (TH1D*)hBkg_cut1p5Pbp->ProjectionY();

		FormTH1Marker(hSigDeltaPhi1p5, 0, 0, 1.4);
		FormTH1Marker(hBkgDeltaPhi1p5, 0, 0, 1.4);

		hSigDeltaPhi1p5->SetName("hSigDeltaPhi1p5");
		hBkgDeltaPhi1p5->SetName("hBkgDeltaPhi1p5");

		TH1D* hRatioDeltaPhi1p5 = (TH1D*) hSigDeltaPhi1p5->Clone("hRatioDeltaPhi1p5");

		hRatioDeltaPhi1p5->Divide(hBkgDeltaPhi1p5);
//}}}

//}}}

//Get |deta| > 1 range plot{{{

//get plot{{{
		hSig_cut1Pbp = (TH2D*)sigPbp->Get("hSigPbp4_1"); hSig_cut1Pbp->Sumw2();
		hSig_cut1pPb = (TH2D*)sigpPb->Get("hSigpPb4_1"); hSig_cut1pPb->Sumw2();
		hBkg_cut1Pbp = (TH2D*)bkgPbp->Get("hBkgPbp4_1"); hBkg_cut1Pbp->Sumw2();
		hBkg_cut1pPb = (TH2D*)bkgpPb->Get("hBkgpPb4_1"); hBkg_cut1pPb->Sumw2();
		hSig_cut1Pbp->Add(hSig_cut1pPb);
		hBkg_cut1Pbp->Add(hBkg_cut1pPb);
//}}}

//projection{{{
		hSigDeltaPhi1 = (TH1D*)hSig_cut1Pbp->ProjectionY();
		hBkgDeltaPhi1 = (TH1D*)hBkg_cut1Pbp->ProjectionY();

		FormTH1Marker(hSigDeltaPhi1, 0, 0, 1.4);
		FormTH1Marker(hBkgDeltaPhi1, 0, 0, 1.4);

		hSigDeltaPhi1->SetName("hSigDeltaPhi1");
		hBkgDeltaPhi1->SetName("hBkgDeltaPhi1");

		TH1D* hRatioDeltaPhi1 = (TH1D*) hSigDeltaPhi1->Clone("hRatioDeltaPhi1");

		hRatioDeltaPhi1->Divide(hBkgDeltaPhi1);
//}}}

//}}}

//Store dphi projection{{{
		TFile* fout = new TFile(Form("CorrDist/CorrFiles/trk_dphi_distribution_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), imass), "RECREATE");
		fout->cd();
		hSigDeltaPhi1->Write();
		hSigDeltaPhi1p5->Write();
		hSigDeltaPhi2->Write();
		hBkgDeltaPhi1->Write();
		hBkgDeltaPhi1p5->Write();
		hBkgDeltaPhi2->Write();
		hRatioDeltaPhi1->Write();
		hRatioDeltaPhi1p5->Write();
		hRatioDeltaPhi2->Write();
		fout->Close();
//}}}

	}
}
