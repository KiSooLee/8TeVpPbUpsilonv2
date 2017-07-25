//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include "Upsilon.h"
#include "Style_Kisoo.h"
//}}}

void DrawdEtadPhi()
{
	TFile* fin = new TFile("", "READ");
	TTree* tin = (TTree*) fin->Get("");
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH2D* h1 = new TH2D("h1", "", 20, -2, 4, 20, -4, 4);
	tin->Draw("dphi:deta>>h1", "", "");
	gStyle->SetOptStat(0000);
	c1->cd();
	h1->Draw("colz");
	c1->SaveAs("dEtadPhi_dist.pdf");
}
