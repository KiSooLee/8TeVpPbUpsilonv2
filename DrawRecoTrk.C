//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TString.h>
#include "Style_Kisoo.h"
//}}}

void DrawRecoTrk()
{
	//TString FileName[2] = {"OniaTree_PADoubleMuon_Pbp_Trk.root",
	//								"OniaTree_PADoubleMuon_pPb_Trk.root"};
	TString FileName[1] = {"OniaTree_PADoubleMuon_Pbp_Trk.root"};
	TChain* tin = new TChain("hionia/myTree");
	for(Int_t i = 0; i < 1; i++)
	{
		tin->Add(Form("%s", FileName[i].Data()));
	}

//Define plot{{{
	gStyle->SetOptStat(0000);
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 600);
	TCanvas* c3 = new TCanvas("c3", "", 0, 0, 600, 600);
	TCanvas* c4 = new TCanvas("c4", "", 0, 0, 600, 600);
	TCanvas* c5 = new TCanvas("c5", "", 0, 0, 600, 600);
	TCanvas* c6 = new TCanvas("c6", "", 0, 0, 600, 600);
	TH1D* hPt[3];
	TH1D* hDeltaR[3];
	for(Int_t i = 0; i < 3; i++)
	{
		hPt[i] = new TH1D(Form("hPt_%d", i), "", 400, 0, 400);
		hDeltaR[i] = new TH1D(Form("hDeltaR_%d", i), "", 20, 0, 20);
		FormTH1Marker(hPt[i], i, 0, 0.4);
		FormTH1Marker(hDeltaR[i], i, 0, 0.4);
	}
	TH1D* h1 = new TH1D("h1", "", 3, 0.15, 0.45);
	TH1D* h2 = new TH1D("h2", "", 3, 0.25, 0.55);
	FormTH1(h1, 0);
	FormTH1(h2, 0);
//}}}

//Fill histogram{{{
	for(Int_t i = 0; i < 3; i++)
	{
		tin->Draw(Form("Reco_QQ_NtrkPt0%d>>hPt_%d", i+2, i), "", "");
		tin->Draw(Form("Reco_QQ_NtrkDeltaR0%d>>hDeltaR_%d", i+3, i), "", "");
		h1->SetBinContent(i+1, hPt[i]->Integral());
		h2->SetBinContent(i+1, hDeltaR[i]->Integral());
	}
//}}}

//compare trk pt cut{{{
	c1->cd();
	TLegend* lPt = new TLegend(0.7, 0.7, 0.9, 0.85);
	FormLegend(lPt, 0.04);
	Double_t max_NPt1 = 0;
	Double_t max_NPt2 = 0;
	Double_t max_NPtf = 0;
	for(Int_t i = 0; i < 3; i++)
	{
		if(i == 0)
		{
			hPt[i]->SetXTitle("NtrkPt");
			hPt[i]->SetYTitle("Counts");
			max_NPt1 = hPt[i]->GetBinContent(hPt[i]->GetMaximumBin());
		}
		max_NPt2 = hPt[i]->GetBinContent(hPt[i]->GetMaximumBin());
		max_NPtf = max(max_NPt1, max_NPt2);
		hPt[0]->GetYaxis()->SetRangeUser(1, max_NPtf*1.2);
		max_NPt1 = max_NPtf;
		lPt->AddEntry(hPt[i], Form("p_{T} > 0.%d", i+2), "pe");
	}
	for(Int_t i = 0; i < 3; i++)
	{
		if(i == 0) hPt[i]->Draw("pe");
		else hPt[i]->Draw("same");
	}
	lPt->Draw();
	c1->SaveAs("NTrk_Pt_dist.pdf");

	c2->cd();
	c2->SetLogy();
	TLegend* lPtlog = new TLegend(0.7, 0.7, 0.9, 0.85);
	FormLegend(lPtlog, 0.04);
	for(Int_t i = 0; i < 3; i++)
	{
		if(i == 0) hPt[i]->Draw("pe");
		else hPt[i]->Draw("same");
		lPtlog->AddEntry(hPt[i], Form("p_{T} > 0.%d", i+2), "pe");
	}
	lPtlog->Draw();
	c2->SaveAs("NTrk_Pt_dist_log.pdf");

	c3->cd();
	h1->SetXTitle("NtrkPtCut");
	h1->SetYTitle("Counts");
	h1->Draw("text00");
	c3->SaveAs("NTrk_Pt_comp.pdf");
//}}}

//compare trk DeltaR cut{{{
	c4->cd();
	TLegend* lDeltaR = new TLegend(0.7, 0.7, 0.9, 0.85);
	FormLegend(lDeltaR, 0.04);
	Double_t max_DR1 = 0;
	Double_t max_DR2 = 0;
	Double_t max_DRf = 0;
	for(Int_t i = 0; i < 3; i++)
	{
		if(i == 0)
		{
			hDeltaR[i]->SetXTitle("NtrkDeltaR");
			hDeltaR[i]->SetYTitle("Counts");
			max_DR1 = hDeltaR[i]->GetBinContent(hDeltaR[i]->GetMaximumBin());
		}
		max_DR2 = hDeltaR[i]->GetBinContent(hDeltaR[i]->GetMaximumBin());
		max_DRf = max(max_DR1, max_DR2);
		hDeltaR[0]->GetYaxis()->SetRangeUser(1, max_DRf*1.2);
		max_DR1 = max_DRf;
		lDeltaR->AddEntry(hDeltaR[i], Form("#DeltaR < 0.%d", i+3), "pe");
	}
	for(Int_t i = 0; i < 3; i++)
	{
		if(i == 0) hDeltaR[i]->Draw("pe");
		else hDeltaR[i]->Draw("same");
	}
	lDeltaR->Draw();
	c4->SaveAs("NTrk_DeltaR_dist.pdf");

	c5->cd();
	c5->SetLogy();
	TLegend* lDeltaRlog = new TLegend(0.7, 0.7, 0.9, 0.85);
	FormLegend(lDeltaRlog, 0.04);
	for(Int_t i = 0; i < 3; i++)
	{
		if(i == 0) hDeltaR[i]->Draw("pe");
		else hDeltaR[i]->Draw("same");
		lDeltaRlog->AddEntry(hDeltaR[i], Form("#DeltaR < 0.%d", i+3), "pe");
	}
	lDeltaRlog->Draw();
	c5->SaveAs("Ntrk_DeltaR_dist_log.pdf");

	c6->cd();
	h2->SetXTitle("NtrkDeltaRCut");
	h2->SetYTitle("Counts");
	h2->Draw("text00");
	c6->SaveAs("Ntrk_DeltaR_comp.pdf");
//}}}
}
