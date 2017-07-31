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
#include <TSystem.h>
#include "Style_Kisoo.h"
#include "Upsilon.h"

using namespace std;
//}}}

bool InAcc(Double_t muPt, Double_t muEta);

void Sort3(bool isMC = false, const Int_t MultMin = 0, const Int_t MultMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1")
{
//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + "/SortFiles";
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}

	TString DM;
	if(isMC) DM = "MC";
	else DM = "RD";

	const Int_t SortN = 3;

//Get files{{{
	TString fname1, fname2;
	TChain* tin = new TChain("hionia/myTree");
	fname1 = "oniaTree_pPb_20170504.root";
	fname2 = "oniaTree_Pbp_20170504.root";
	tin->Add(fname1.Data());
	tin->Add(fname2.Data());
//}}}

	const Int_t MaxQQ = 250;
	const Int_t MaxTrk = 1500;

//tree variables{{{
	UInt_t eventNb;
	ULong64_t HLTriggers;
	Int_t Reco_QQ_size;
	Int_t Reco_QQ_type[MaxQQ];
	Int_t Reco_QQ_sign[MaxQQ];
	Float_t Reco_QQ_VtxProb[MaxQQ];
	ULong64_t Reco_QQ_trig[MaxQQ];
	Bool_t Reco_QQ_mupl_highPurity[MaxQQ];
	Bool_t Reco_QQ_mumi_highPurity[MaxQQ];
	Float_t Reco_QQ_mupl_dxy[MaxQQ];
	Float_t Reco_QQ_mumi_dxy[MaxQQ];
	Float_t Reco_QQ_mupl_dz[MaxQQ];
	Float_t Reco_QQ_mumi_dz[MaxQQ];
	Int_t Reco_QQ_mupl_nTrkWMea[MaxQQ];
	Int_t Reco_QQ_mumi_nTrkWMea[MaxQQ];
	Bool_t Reco_QQ_mupl_TMOneStaTight[MaxQQ];
	Bool_t Reco_QQ_mumi_TMOneStaTight[MaxQQ];
	Int_t Reco_QQ_mupl_nPixWMea[MaxQQ];
	Int_t Reco_QQ_mumi_nPixWMea[MaxQQ];
	Int_t Reco_QQ_NtrkPt04[MaxQQ];
	TClonesArray* Reco_QQ_4mom;
	TClonesArray* Reco_QQ_mupl_4mom;
	TClonesArray* Reco_QQ_mumi_4mom;
	Reco_QQ_4mom = 0;
	Reco_QQ_mupl_4mom = 0;
	Reco_QQ_mumi_4mom = 0;
	Int_t Reco_trk_size;
	Int_t Reco_trk_charge[MaxTrk];
	Float_t Reco_trk_dxyError[MaxTrk];
	Float_t Reco_trk_dzError[MaxTrk];
	Bool_t Reco_isgoodTrk[MaxTrk];
	Bool_t Reco_isMuTrk[MaxTrk];
	TClonesArray* Reco_trk_4mom;
	Reco_trk_4mom = 0;
//}}}

//Branches{{{
	TBranch* b_eventNb;
	TBranch* b_HLTriggers;
	TBranch* b_Reco_QQ_size;
	TBranch* b_Reco_QQ_type;
	TBranch* b_Reco_QQ_sign;
	TBranch* b_Reco_QQ_VtxProb;
	TBranch* b_Reco_QQ_trig;
	TBranch* b_Reco_QQ_mupl_highPurity;
	TBranch* b_Reco_QQ_mumi_highPurity;
	TBranch* b_Reco_QQ_mupl_dxy;
	TBranch* b_Reco_QQ_mumi_dxy;
	TBranch* b_Reco_QQ_mupl_dz;
	TBranch* b_Reco_QQ_mumi_dz;
	TBranch* b_Reco_QQ_mupl_nTrkWMea;
	TBranch* b_Reco_QQ_mumi_nTrkWMea;
	TBranch* b_Reco_QQ_mupl_TMOneStaTight;
	TBranch* b_Reco_QQ_mumi_TMOneStaTight;
	TBranch* b_Reco_QQ_mupl_nPixWMea;
	TBranch* b_Reco_QQ_mumi_nPixWMea;
	TBranch* b_Reco_QQ_NtrkPt04;
	TBranch* b_Reco_QQ_4mom;
	TBranch* b_Reco_QQ_mupl_4mom;
	TBranch* b_Reco_QQ_mumi_4mom;
	TBranch* b_Reco_trk_size;
	TBranch* b_Reco_trk_charge;
	TBranch* b_Reco_trk_dxyError;
	TBranch* b_Reco_trk_dzError;
	TBranch* b_Reco_isgoodTrk;
	TBranch* b_Reco_isMuTrk;
	TBranch* b_Reco_trk_4mom;
//}}}

//Branche address{{{
	tin->SetBranchAddress("eventNb", &eventNb, &b_eventNb);
	tin->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);
	tin->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
	tin->SetBranchAddress("Reco_QQ_type", &Reco_QQ_type, &b_Reco_QQ_type);
	tin->SetBranchAddress("Reco_QQ_sign", &Reco_QQ_sign, &b_Reco_QQ_sign);
	tin->SetBranchAddress("Reco_QQ_VtxProb", Reco_QQ_VtxProb, &b_Reco_QQ_VtxProb);
	tin->SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig, &b_Reco_QQ_trig);
	tin->SetBranchAddress("Reco_QQ_mupl_highPurity", Reco_QQ_mupl_highPurity, &b_Reco_QQ_mupl_highPurity);
	tin->SetBranchAddress("Reco_QQ_mumi_highPurity", Reco_QQ_mumi_highPurity, &b_Reco_QQ_mumi_highPurity);
	tin->SetBranchAddress("Reco_QQ_mupl_dxy", Reco_QQ_mupl_dxy, &b_Reco_QQ_mupl_dxy);
	tin->SetBranchAddress("Reco_QQ_mumi_dxy", Reco_QQ_mumi_dxy, &b_Reco_QQ_mumi_dxy);
	tin->SetBranchAddress("Reco_QQ_mupl_dz", Reco_QQ_mupl_dz, &b_Reco_QQ_mupl_dz);
	tin->SetBranchAddress("Reco_QQ_mumi_dz", Reco_QQ_mumi_dz, &b_Reco_QQ_mumi_dz);
	tin->SetBranchAddress("Reco_QQ_mupl_nTrkWMea", Reco_QQ_mupl_nTrkWMea, &b_Reco_QQ_mupl_nTrkWMea);
	tin->SetBranchAddress("Reco_QQ_mumi_nTrkWMea", Reco_QQ_mumi_nTrkWMea, &b_Reco_QQ_mumi_nTrkWMea);
	tin->SetBranchAddress("Reco_QQ_mupl_TMOneStaTight", Reco_QQ_mupl_TMOneStaTight, &b_Reco_QQ_mupl_TMOneStaTight);
	tin->SetBranchAddress("Reco_QQ_mumi_TMOneStaTight", Reco_QQ_mumi_TMOneStaTight, &b_Reco_QQ_mumi_TMOneStaTight);
	tin->SetBranchAddress("Reco_QQ_mupl_nPixWMea", Reco_QQ_mupl_nPixWMea, &b_Reco_QQ_mupl_nPixWMea);
	tin->SetBranchAddress("Reco_QQ_mumi_nPixWMea", Reco_QQ_mumi_nPixWMea, &b_Reco_QQ_mumi_nPixWMea);
	tin->SetBranchAddress("Reco_QQ_NtrkPt04", Reco_QQ_NtrkPt04, &b_Reco_QQ_NtrkPt04);
	tin->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
	tin->SetBranchAddress("Reco_QQ_mupl_4mom", &Reco_QQ_mupl_4mom, &b_Reco_QQ_mupl_4mom);
	tin->SetBranchAddress("Reco_QQ_mumi_4mom", &Reco_QQ_mumi_4mom, &b_Reco_QQ_mumi_4mom);
	tin->SetBranchAddress("Reco_trk_size", &Reco_trk_size, &b_Reco_trk_size);
	tin->SetBranchAddress("Reco_trk_charge", Reco_trk_charge, &b_Reco_trk_charge);
	tin->SetBranchAddress("Reco_trk_dxyError", Reco_trk_dxyError, &b_Reco_trk_dxyError);
	tin->SetBranchAddress("Reco_trk_dzError", Reco_trk_dzError, &b_Reco_trk_dzError);
	tin->SetBranchAddress("Reco_isgoodTrk", Reco_isgoodTrk, &b_Reco_isgoodTrk);
	tin->SetBranchAddress("Reco_isMuTrk", Reco_isMuTrk, &b_Reco_isMuTrk);
	tin->SetBranchAddress("Reco_trk_4mom", &Reco_trk_4mom, &b_Reco_trk_4mom);
//}}}

//Define LorentzVector{{{
	TLorentzVector* Up_Reco_4mom = new TLorentzVector;
	TLorentzVector* mupl_Reco_4mom = new TLorentzVector;
	TLorentzVector* mumi_Reco_4mom = new TLorentzVector;
	TLorentzVector* Trk_Reco_4mom = new TLorentzVector;
	Up_Reco_4mom = 0;
	mupl_Reco_4mom = 0;
	mumi_Reco_4mom = 0;
	Trk_Reco_4mom = 0;
//}}}

//initialize dataset{{{
	DiMuon DMset;

	TTree* tout = new TTree("UpsilonTree", "");
	tout->SetMaxTreeSize(10000000000000);
	DMset.BuildBranch(tout);
//}}}

	const Int_t Nevt = tin->GetEntries();
	Int_t EventNb = 0;

//output file{{{
	TFile* fout = new TFile(Form("SortFiles/Sort_OniaTree_PADoubleMuon_%s_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s_%d.root", DM.Data(), MultMin, MultMax, (int)ptMin, (int)ptMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data(), SortN), "RECREATE");
//}}}

	for(Int_t ievt = Numbin[SortN]; ievt < Numbin[SortN+1]; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Numbin[SortN+1] << " [" << Form("%.1f", ((double)(ievt-Numbin[SortN])/(double)(Numbin[SortN+1]-Numbin[SortN])*100)) << " %]" << endl;
		tin->GetEntry(ievt);

		DMset.clear();
		Int_t Ntrg = 0;
		Int_t Nass = 0;

		if( (HLTriggers&1)!=1 ) continue;

//Get track multiplicity{{{
		Int_t Tot_Ntrk = 0;
		for(Int_t itrk = 0; itrk < Reco_trk_size; itrk++)
		{
			if( Reco_isgoodTrk[itrk] && !Reco_isMuTrk[itrk] ) Tot_Ntrk++;
		}
//}}}

		if(Tot_Ntrk >= MultMin && Tot_Ntrk < MultMax)
		{
//Get trigger vector{{{
			for(Int_t iqq = 0; iqq < Reco_QQ_size; iqq++)
			{
				Up_Reco_4mom = (TLorentzVector*) Reco_QQ_4mom->At(iqq);
				mupl_Reco_4mom = (TLorentzVector*) Reco_QQ_mupl_4mom->At(iqq);
				mumi_Reco_4mom = (TLorentzVector*) Reco_QQ_mumi_4mom->At(iqq);

//Cuts for muon and Upsilon{{{
				if( Reco_QQ_sign[iqq] != 0 ) continue;
				if( Up_Reco_4mom->M() < 8 || Up_Reco_4mom->M() > 14) continue;
				if( (Reco_QQ_trig[iqq]&1)!=1 ) continue;
				if( !InAcc(mupl_Reco_4mom->Pt(), mupl_Reco_4mom->Eta()) ) continue;
				if( !InAcc(mumi_Reco_4mom->Pt(), mumi_Reco_4mom->Eta()) ) continue;
				bool muplSoft = ( (Reco_QQ_mupl_TMOneStaTight[iqq]) &&
										(Reco_QQ_mupl_nTrkWMea[iqq] > 5) &&
										(Reco_QQ_mupl_nPixWMea[iqq] > 0) &&
										(Reco_QQ_mupl_dxy[iqq] < 0.3) &&
										(Reco_QQ_mupl_dz[iqq] < 20.) );
				bool mumiSoft = ( (Reco_QQ_mumi_TMOneStaTight[iqq]) &&
										(Reco_QQ_mumi_nTrkWMea[iqq] > 5) &&
										(Reco_QQ_mumi_nPixWMea[iqq] > 0) &&
										(Reco_QQ_mumi_dxy[iqq] < 0.3) &&
										(Reco_QQ_mumi_dz[iqq] < 20.) );
				if( !(muplSoft && mumiSoft) ) continue;
				if( Reco_QQ_VtxProb[iqq] < 0.01 ) continue;
//}}}

				Double_t tmp_eta = Up_Reco_4mom->Eta();
				Double_t tmp_pt = Up_Reco_4mom->Pt();
				Double_t tmp_y = Up_Reco_4mom->Rapidity();
				Double_t tmp_phi = Up_Reco_4mom->Phi();
				Double_t tmp_mass = Up_Reco_4mom->M();

//get trg for each pt bin{{{
				if(tmp_eta >= -2.4 && tmp_eta <= 2.4 && tmp_pt >= ptMin && tmp_pt < ptMax && tmp_y > rapMin && tmp_y < rapMax)
				{
//peak{{{
					if( (tmp_mass >= 8) && (tmp_mass <= 14) )
					//if( (tmp_mass >= mean-peakFactor*sigma) && (tmp_mass <= mean+peakFactor*sigma) )
					{
						new( (*DMset.Vec_trg_peak)[Ntrg] )TLorentzVector(*Up_Reco_4mom);
						Ntrg++;
					}
//}}}

				}
//}}}
				}
//}}}

//Get associator vector{{{
			for(Int_t itrk = 0; itrk < Reco_trk_size; itrk++)
			{
				Trk_Reco_4mom = (TLorentzVector*) Reco_trk_4mom->At(itrk);
				TVector3 Trk_vector;

				if(Trk_Reco_4mom->Eta() <= 2.4 && Trk_Reco_4mom->Eta() >= -2.4 && Reco_isgoodTrk[itrk] && !Reco_isMuTrk[itrk] && Trk_Reco_4mom->Pt() >= TrkptMin && Trk_Reco_4mom->Pt() < TrkptMax)
				{
					new( (*DMset.Vec_ass)[Nass] )TLorentzVector(*Trk_Reco_4mom);
					Nass++;
				}
			}
//}}}

			EventNb++;
		}
		DMset.eventNb = EventNb;
		DMset.Ntrg = Ntrg;
		DMset.Nass = Nass;
		DMset.weight = 1.;
		tout->Fill();
	}
	tout->Write();
	fout->Close();
}

//External function{{{
bool InAcc(Double_t muPt, Double_t muEta)
{
	return ( TMath::Abs(muEta) < 2.4 && muPt >= 4);
}
//}}}
