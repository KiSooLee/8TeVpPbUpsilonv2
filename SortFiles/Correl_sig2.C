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
#include "../Style_Kisoo.h"
#include "../Upsilon.h"

using namespace std;
//}}}

void Correl_sig2(bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1")
{
//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + "/SigCorr";
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

	TString DM;
	if(isMC) DM = "MC";
	else DM = "RD";

	const Int_t SortN = 2;

//Get files{{{
	TString fname1;
	TChain* tin1 = new TChain("UpsilonTree");
	fname1 = Form("Sort_OniaTree_PADoubleMuon_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%d.root", DM.Data(), (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), SortN);
	tin1->Add(fname1.Data());
//}}}

	const Int_t MaxQQ = 250;
	const Int_t MaxTrk = 1500;

//Make plots{{{
	TCanvas* c1[120];
	TH2D* h1[120];
	for(Int_t imass = 0; imass < 120; imass++)
	{
		c1[imass] = new TCanvas(Form("c1_%d", imass), "", 0, 0, 600, 600);
		h1[imass] = new TH2D(Form("h1_%d", imass), ";#Delta#eta;#Delta#phi", 33,-4.95,4.95,31,-(0.5-1.0/32)*TMath::Pi(),(1.5-1.0/32)*TMath::Pi());
		FormTH2(h1[imass]);
	}
//}}}

//get variables{{{
	Int_t Ntrg;
	Int_t Nass;
	TClonesArray* Vec_trg;
	TClonesArray* Vec_ass;
	Vec_trg = 0;
	Vec_ass = 0;

	TBranch* b_Ntrg;
	TBranch* b_Nass;
	TBranch* b_Vec_trg;
	TBranch* b_Vec_ass;

	tin1->SetBranchAddress("Ntrg", &Ntrg, &b_Ntrg);
	tin1->SetBranchAddress("Nass", &Nass, &b_Nass);
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

//peak Correlate{{{
		for(Int_t itrg = 0; itrg < Ntrg; itrg++)
		{
			vec_trg = (TLorentzVector*) Vec_trg->At(itrg);
			Double_t trg_eta = vec_trg->Eta();
			Double_t trg_phi = vec_trg->Phi();
			Double_t trg_m = vec_trg->M();

			for(Int_t imass = 0; imass < 120; imass++)
			{
				if(trg_m > 8+imass*0.05 && trg_m <= 8+(imass+1)*0.05)
				{
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
						h1[imass]->Fill(deta, dphi, 1/(double)Ntrg);
					}
//}}}
				}
			}
		}
//}}}
	}

	for(Int_t imass = 0; imass < 120; imass++)
	{
		c1[imass]->cd();
		h1[imass]->Draw("LEGO");
	}

	TFile* fout = new TFile(Form("SigCorr/deta-dphi_%s_distribution_sig_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%d.root", DM.Data(), (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), SortN), "RECREATE");
	fout->cd();
	for(Int_t imass = 0; imass < 120; imass++)
	{
		h1[imass]->Write();
	}
	fout->Close();
}
