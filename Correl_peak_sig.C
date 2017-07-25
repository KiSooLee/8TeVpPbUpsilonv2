//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TBranch.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TVector.h>
#include <TLorentzVector.h>
#include <iostream>
#include <fstream>
#include <TString.h>
#include <TH1.h>
#include <TF1.h>
#include <TRandom3.h>
#include "Style_Kisoo.h"
#include "Upsilon.h"

using namespace std;
//}}}

void Correl_peak_sig(bool isMC = false, const Int_t MultMin = 0, const Int_t MultMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1")
{
	TString DM;
	if(isMC) DM = "MC";
	else DM = "RD";

//Get files{{{
	TString fname1, fname2, fname3, fname4;
	TChain* tin1 = new TChain("UpsilonTree");
	fname1 = Form("SkimmedFiles/Sort_OniaTree_PADoubleMuon_%s_Mult_%d-%d_pt_%d-%d_Trkpt_%d-%d_%s.root", DM.Data(), MultMin, MultMax, (int)ptMin, (int)ptMax, (int)TrkptMin, (int)TrkptMax, version.Data());
	tin1->Add(fname1.Data());
//}}}

	const Int_t MaxQQ = 250;
	const Int_t MaxTrk = 1500;

//Make plots{{{
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH2D* h1 = new TH2D("h1", ";#Delta#eta;#Delta#phi", 33,-4.95,4.95,31,-(0.5-1.0/32)*TMath::Pi(),(1.5-1.0/32)*TMath::Pi());
	FormTH2(h1);
//}}}

//tree variables{{{
	Int_t Npeak;
	Int_t Nass;
	TClonesArray* Vec_trg_peak;
	TClonesArray* Vec_ass;
	Vec_trg_peak = 0;
	Vec_ass = 0;
//}}}

//Branches{{{
	TBranch* b_Npeak;
	TBranch* b_Nass;
	TBranch* b_Vec_trg_peak;
	TBranch* b_Vec_ass;
//}}}

//Branche address{{{
	tin1->SetBranchAddress("Npeak", &Npeak, &b_Npeak);
	tin1->SetBranchAddress("Nass", &Nass, &b_Nass);
	tin1->SetBranchAddress("Vec_trg_peak", &Vec_trg_peak, &b_Vec_trg_peak);
	tin1->SetBranchAddress("Vec_ass", &Vec_ass, &b_Vec_ass);
//}}}

//Define lorentz vector{{{
	TLorentzVector* vec_trg_peak = new TLorentzVector;
	TLorentzVector* vec_ass = new TLorentzVector;
	vec_trg_peak = 0;
	vec_ass = 0;
//}}}

	const Int_t Nevt = tin1->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin1->GetEntry(ievt);

//peak Correlate{{{
		for(Int_t itrg = 0; itrg < Npeak; itrg++)
		{
			vec_trg_peak = (TLorentzVector*) Vec_trg_peak->At(itrg);
			Double_t trg_eta = vec_trg_peak->Eta();
			Double_t trg_phi = vec_trg_peak->Phi();

//signal{{{
			for(Int_t itrk = 0; itrk < Nass; itrk++)
			{
				vec_ass = (TLorentzVector*) Vec_ass->At(itrk);
				Double_t ass_eta = vec_ass->Eta();
				Double_t ass_phi = vec_ass->Phi();
				Double_t deta = ass_eta - trg_eta;
				Double_t dphi = ass_phi - trg_phi;
				if(dphi > TMath::Pi()) dphi = dphi - 2*TMath::Pi();
				if(dphi < -TMath::Pi()) dphi = dphi + 2*TMath::Pi();
				if(dphi > -TMath::Pi() && dphi < -TMath::Pi()/2.) dphi = dphi + 2*TMath::Pi();
				h1->Fill(deta, dphi, 1/(double)Npeak);
			}
//}}}
		}
//}}}
	}

	gStyle->SetOptStat(0000);
	c1->cd();
	h1->Draw("LEGO");
	c1->SaveAs(Form("deta-dphi_%s_distribution_peak_sig_Mult_%d-%d_pt_%d-%d_Trkpt_%d-%d_%s.pdf", DM.Data(), MultMin, MultMax, (int)ptMin, (int)ptMax, (int)TrkptMin, (int)TrkptMax, version.Data()));

	TFile* fout = new TFile(Form("deta-dphi_%s_distribution_peak_sig_Mult_%d-%d_pt_%d-%d_Trkpt_%d-%d_%s.root", DM.Data(), MultMin, MultMax, (int)ptMin, (int)ptMax, (int)TrkptMin, (int)TrkptMax, version.Data()), "RECREATE");
	fout->cd();
	h1->Write();
	fout->Close();
}
