//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TString.h>
#include <iostream>
#include <fstream>

#include "Upsilon.h"
#include "Style_Upv2.h"
//}}}

void DrawSigv2(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v13")
{
	SetStyle();

	TFile* fin = new TFile(Form("CorrDist/CorrFiles/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_pol2_No23.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()), "READ");
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH1D* htmp = new TH1D("htmp", ";p_{T};v_{2}", 10, 0, 30);
	FormTH1(htmp, 0);

	TGraphErrors *gin = (TGraphErrors*) fin->Get(Form("v2vspt"));
	TGraphErrors *g1 = (TGraphErrors*) gin->Clone("g1");
	FormGraph(g1, 0, 0, 1);

	c1->cd();
	htmp->SetMinimum(-0.02);
	htmp->SetMaximum(0.02);
	htmp->Draw();
	g1->Draw("samepe");
	c1->SaveAs(Form("CorrDist/V2Dist/V2Dist_sig_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_No23_pol2_%s.pdf", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
}
