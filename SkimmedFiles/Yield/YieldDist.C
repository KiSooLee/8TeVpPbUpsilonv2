//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <iostream>
#include <TString.h>
#include <TLegend.h>
#include <TMath.h>
#include "../../Upsilon.h"
#include "../../Style_Kisoo.h"
//}}}

void YieldDist(TString version = "v1")
{
	gStyle->SetOptStat(0000);

//Define canvas and histograms{{{
	TCanvas* c1S = new TCanvas("c1S", "", 0, 0, 600, 600);
	TCanvas* c2S = new TCanvas("c2S", "", 0, 0, 600, 600);
	TCanvas* c3S = new TCanvas("c3S", "", 0, 0, 600, 600);
	TCanvas* call = new TCanvas("call", "", 0, 0, 600, 600);
	TH1D* h1S;
	TH1D* h2S;
	TH1D* h3S;
	if(mult_narr > 2)
	{
		h1S = new TH1D("h1S", ";multiplicity;Counts", mult_narr-1, multBinsArr);
		h2S = new TH1D("h2S", ";multiplicity;Counts", mult_narr-1, multBinsArr);
		h3S = new TH1D("h3S", ";multiplicity;Counts", mult_narr-1, multBinsArr);
	}
	else if(pt_narr > 2)
	{
		h1S = new TH1D("h1S", ";p_{T} (GeV/c);Counts", pt_narr-1, ptBinsArr);
		h2S = new TH1D("h2S", ";p_{T} (GeV/c);Counts", pt_narr-1, ptBinsArr);
		h3S = new TH1D("h3S", ";p_{T} (GeV/c);Counts", pt_narr-1, ptBinsArr);
	}
	else if(rap_narr > 2)
	{
		h1S = new TH1D("h1S", ";y;Counts", rap_narr-1, rapBinsArr);
		h2S = new TH1D("h2S", ";y;Counts", rap_narr-1, rapBinsArr);
		h3S = new TH1D("h3S", ";y;Counts", rap_narr-1, rapBinsArr);
	}
	FormTH1Marker(h1S, 0, 1, 1);
	FormTH1Marker(h2S, 1, 1, 1);
	FormTH1Marker(h3S, 2, 1, 1);
//}}}

	for(Int_t imult = 0; imult < mult_narr-1; imult++)
	{
		for(Int_t ipt = 0; ipt < pt_narr-1; ipt++)
		{
			for(Int_t irap = 0; irap < rap_narr-1; irap++)
			{
				TFile* fin  = new TFile(Form("Yield_Mult_%d-%d_pt_%d-%d_rap_%d-%d_%s.root", (int)multBinsArr[imult], (int)multBinsArr[imult+1], (int)ptBinsArr[ipt], (int)ptBinsArr[ipt+1], (int)(10*rapBinsArr[irap]), (int)(10*rapBinsArr[irap+1]), version.Data()), "READ");
				TH1D* hin = (TH1D*) fin->Get("hYield");

				Double_t w1S = 0;
				Double_t w2S = 0;
				Double_t w3S = 0;

//Fill contents{{{
				if(mult_narr > 2)
				{
					w1S = h1S->GetBinWidth(imult+1);
					w2S = h2S->GetBinWidth(imult+1);
					w3S = h3S->GetBinWidth(imult+1);
					h1S->SetBinContent(imult+1, (double)hin->GetBinContent(1)/w1S);
					h1S->SetBinError(imult+1, hin->GetBinError(1)/TMath::Sqrt(w1S));
					h2S->SetBinContent(imult+1, (double)hin->GetBinContent(2)/w2S);
					h2S->SetBinError(imult+1, hin->GetBinError(2)/TMath::Sqrt(w2S));
					h3S->SetBinContent(imult+1, (double)hin->GetBinContent(3)/w3S);
					h3S->SetBinError(imult+1, hin->GetBinError(3)/TMath::Sqrt(w3S));
				}
				else if (pt_narr > 2)
				{
					w1S = h1S->GetBinWidth(ipt+1);
					w2S = h2S->GetBinWidth(ipt+1);
					w3S = h3S->GetBinWidth(ipt+1);
					h1S->SetBinContent(ipt+1, (double)hin->GetBinContent(1)/w1S);
					h1S->SetBinError(ipt+1, hin->GetBinError(1)/TMath::Sqrt(w1S));
					h2S->SetBinContent(ipt+1, (double)hin->GetBinContent(2)/w2S);
					h2S->SetBinError(ipt+1, hin->GetBinError(2)/TMath::Sqrt(w2S));
					h3S->SetBinContent(ipt+1, (double)hin->GetBinContent(3)/w3S);
					h3S->SetBinError(ipt+1, hin->GetBinError(3)/TMath::Sqrt(w3S));
				}
				else if(rap_narr > 2)
				{
					w1S = h1S->GetBinWidth(irap+1);
					w2S = h2S->GetBinWidth(irap+1);
					w3S = h3S->GetBinWidth(irap+1);
					h1S->SetBinContent(irap+1, (double)hin->GetBinContent(1)/w1S);
					h1S->SetBinError(irap+1, hin->GetBinError(1)/TMath::Sqrt(w1S));
					h2S->SetBinContent(irap+1, (double)hin->GetBinContent(2)/w2S);
					h2S->SetBinError(irap+1, hin->GetBinError(2)/TMath::Sqrt(w2S));
					h3S->SetBinContent(irap+1, (double)hin->GetBinContent(3)/w3S);
					h3S->SetBinError(irap+1, hin->GetBinError(3)/TMath::Sqrt(w3S));
				}
//}}}

				fin->Close();
			}
		}
	}
	h1S->SetMinimum(0);
	h2S->SetMinimum(0);
	h3S->SetMinimum(0);
	c1S->cd();
	h1S->Draw();
	c1S->SaveAs(Form("Yield_distribution_1S_%s.pdf", version.Data()));
	c2S->cd();
	h2S->Draw();
	c2S->SaveAs(Form("Yield_distribution_2S_%s.pdf", version.Data()));
	c3S->cd();
	h3S->Draw();
	c3S->SaveAs(Form("Yield_distribution_3S_%s.pdf", version.Data()));
	call->cd();
	h1S->Draw();
	h2S->Draw("same");
	h3S->Draw("same");
	TLegend* l1 = new TLegend(0.7, 0.7, 0.9, 0.9);
	FormLegend(l1, 0.04);
	l1->AddEntry(h1S, "1S", "pl");
	l1->AddEntry(h2S, "2S", "pl");
	l1->AddEntry(h3S, "3S", "pl");
	l1->Draw();
	call->SaveAs(Form("Yield_distribution_all_%s.pdf", version.Data()));
}
