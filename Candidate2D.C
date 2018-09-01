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
#include <TSystem.h>
#include "Style_Upv2.h"
#include "Upsilon.h"

using namespace std;
//}}}

void Candidate2D(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1")
{
	SetStyle();

//make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/CandDist");
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

//Get files{{{
	TString fname1, fname2, fname3, fname4;
	TChain* tin1 = new TChain("UpsilonTree");
	for(Int_t ibin = 0; ibin < 119; ibin++)
	{
		//fname1 = Form("root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d/Sort_OniaTree_Pbp1_PADoubleMuon_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, ibin);
		fname1 = Form("/xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d/Sort_OniaTree_Pbp1_PADoubleMuon_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, ibin);
		fname2 = Form("/xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/%d-%d_%d-%d_%d-%d_%d-%d/Sort_OniaTree_Pbp2_PADoubleMuon_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, ibin);
		fname3 = Form("/xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/%d-%d_%d-%d_%d-%d_%d-%d/Sort_OniaTree_pPb1_PADoubleMuon_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, ibin);
		fname4 = Form("/xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/%d-%d_%d-%d_%d-%d_%d-%d/Sort_OniaTree_pPb2_PADoubleMuon_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, ibin);
		tin1->Add(fname1.Data());
		tin1->Add(fname2.Data());
		tin1->Add(fname3.Data());
		tin1->Add(fname4.Data());
	}
//}}}

//Make plots{{{
	Int_t Netabin1 = 54;
	Int_t Nphibin1 = 32;
	TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
	TH2D* h1 = new TH2D("h1", ";#eta;#phi;", Netabin1,-8,8,Nphibin1,-5,5);
	FormTH2(h1);
	TH2D* h2 = new TH2D("h2", ";#eta;#phi;", Netabin1,-8,8,Nphibin1,-5,5);
	FormTH2(h2);
//}}}

//get variables{{{
	Int_t Ntrg;
	Int_t Nass;
	Double_t mult;
	TClonesArray* Vec_trg;
	TClonesArray* Vec_ass;
	Vec_trg = 0;
	Vec_ass = 0;

	TBranch* b_Ntrg;
	TBranch* b_Nass;
	TBranch* b_mult;
	TBranch* b_Vec_trg;
	TBranch* b_Vec_ass;

	tin1->SetBranchAddress("Ntrg", &Ntrg, &b_Ntrg);
	tin1->SetBranchAddress("Nass", &Nass, &b_Nass);
	tin1->SetBranchAddress("mult", &mult, &b_mult);
	tin1->SetBranchAddress("Vec_trg", &Vec_trg, &b_Vec_trg);
	tin1->SetBranchAddress("Vec_ass", &Vec_ass, &b_Vec_ass);

	TLorentzVector* vec_trg = new TLorentzVector;
	TLorentzVector* vec_ass = new TLorentzVector;
	vec_trg = 0;
	vec_ass = 0;
//}}}

	const Int_t Nevt = tin1->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt << " [" << Form("%.1f", ((double)ievt/(double)Nevt)*100) << " %]" << endl;
		tin1->GetEntry(ievt);

		for(Int_t itrg = 0; itrg < Ntrg; itrg++)
		{
			vec_trg = (TLorentzVector*) Vec_trg->At(itrg);
			if(vec_trg == 0) continue;
			Double_t trg_eta = vec_trg->Eta();
			Double_t trg_phi = vec_trg->Phi();
			h1->Fill(trg_eta, trg_phi);
			if(trg_eta < -5 || trg_eta > 5)
			{
				h2->Fill(trg_eta, trg_phi);
			}

		}
	}

	c1->cd();
	h1->Draw("colz");
	SetLine(1, -2.4, -5, -2.4, 5, 0, 2);
	SetLine(1, 2.4, -5, 2.4, 5, 0, 2);
	c1->SaveAs(Form("CandDist/Cand2D_Mult_%d-%d_pt_%d-%d_rap_%d-%d_neta_%d_nphi_%d_%s.pdf", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), Netabin1, Nphibin1, version.Data()));

cout << "high eta ratio = " << h2->GetEntries()*100/h1->GetEntries() << " %" << endl;
}
