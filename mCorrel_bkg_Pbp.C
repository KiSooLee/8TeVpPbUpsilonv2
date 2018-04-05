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

void mCorrel_bkg_Pbp(bool isMC = false, const Int_t multMin = 0, const Int_t multMax = 300, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v1", const Int_t imass = 0, const Int_t nmbin = 20)
{
/*
//Make directory{{{
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + "/BkgCorr";
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);
//}}}
*/
	TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
	TString saveDIR = mainDIR + Form("/%d-%d_%d-%d_%d-%d_%d-%d_%d", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, nmbin);
	void * dirp = gSystem->OpenDirectory(saveDIR.Data());
	if(dirp) gSystem->FreeDirectory(dirp);
	else gSystem->mkdir(saveDIR.Data(), kTRUE);

//Get files{{{
	TString fname1, fname2;
	TChain* tin1 = new TChain("UpsilonTree");
	TChain* tin2 = new TChain("UpsilonTree");
	for(Int_t ibin = 0; ibin < 120/nmbin; ibin++)
	{
		fname1 = Form("root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/%d-%d_%d-%d_%d-%d_%d-%d/Sort_OniaTree_Pbp1_PADoubleMuon_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, imass*(120/nmbin)+ibin);
		fname2 = Form("root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/%d-%d_%d-%d_%d-%d_%d-%d/Sort_OniaTree_Pbp2_PADoubleMuon_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, imass*(120/nmbin)+ibin);
		tin1->Add(fname1.Data());
		tin2->Add(fname2.Data());
	}
//}}}

//Make plots{{{
	const Int_t Netabin1 = 32;
	const Int_t Nphibin1 = 32;
	const Int_t Netabin2 = 16;
	const Int_t Nphibin2 = 16;
	TCanvas* c1_1 = new TCanvas("c1_1", "", 0, 0, 600, 600);
	TCanvas* c1_2 = new TCanvas("c1_2", "", 0, 0, 600, 600);
	TCanvas* c2_1 = new TCanvas("c2_1", "", 0, 0, 600, 600);
	TCanvas* c2_2 = new TCanvas("c2_2", "", 0, 0, 600, 600);
	TCanvas* c3_1 = new TCanvas("c3_1", "", 0, 0, 600, 600);
	TCanvas* c3_2 = new TCanvas("c3_2", "", 0, 0, 600, 600);
	TH2D* h1_1 = new TH2D("h1_1", ";#Delta#eta;#Delta#phi", Netabin1,-4.95,4.95,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* h1_2 = new TH2D("h1_2", ";#Delta#eta;#Delta#phi", Netabin2,-4.95,4.95,Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* h2_1 = new TH2D("h2_1", ";#Delta#eta;#Delta#phi", Netabin1,-4.95,4.95,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* h2_2 = new TH2D("h2_2", ";#Delta#eta;#Delta#phi", Netabin2,-4.95,4.95,Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	TH2D* h3_1 = new TH2D("h3_1", ";#Delta#eta;#Delta#phi", Netabin1,-4.95,4.95,Nphibin1,-(0.5-1.0/((double)(Nphibin1+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin1+1)))*TMath::Pi());
	TH2D* h3_2 = new TH2D("h3_2", ";#Delta#eta;#Delta#phi", Netabin2,-4.95,4.95,Nphibin2,-(0.5-1.0/((double)(Nphibin2+1)))*TMath::Pi(),(1.5-1.0/((double)(Nphibin2+1)))*TMath::Pi());
	FormTH2(h1_1);
	FormTH2(h1_2);
	FormTH2(h2_1);
	FormTH2(h2_2);
	FormTH2(h3_1);
	FormTH2(h3_2);
//}}}

//tree variables{{{
	Int_t Ntrg1;
	Int_t Ntrg2;
	Int_t Nass1;
	Int_t Nass2;
	Double_t mult1;
	Double_t mult2;
	TClonesArray* Vec_trg1;
	TClonesArray* Vec_trg2;
	TClonesArray* Vec_ass1;
	TClonesArray* Vec_ass2;
	Vec_trg1 = 0;
	Vec_trg2 = 0;
	Vec_ass1 = 0;
	Vec_ass2 = 0;

	TBranch* b_Ntrg1;
	TBranch* b_Ntrg2;
	TBranch* b_Nass1;
	TBranch* b_Nass2;
	TBranch* b_mult1;
	TBranch* b_mult2;
	TBranch* b_Vec_trg1;
	TBranch* b_Vec_trg2;
	TBranch* b_Vec_ass1;
	TBranch* b_Vec_ass2;

	tin1->SetBranchAddress("Ntrg", &Ntrg1, &b_Ntrg1);
	tin1->SetBranchAddress("Nass", &Nass1, &b_Nass1);
	tin1->SetBranchAddress("mult", &mult1, &b_mult1);
	tin1->SetBranchAddress("Vec_trg", &Vec_trg1, &b_Vec_trg1);
	tin1->SetBranchAddress("Vec_ass", &Vec_ass1, &b_Vec_ass1);
	tin2->SetBranchAddress("Ntrg", &Ntrg2, &b_Ntrg2);
	tin2->SetBranchAddress("Nass", &Nass2, &b_Nass2);
	tin2->SetBranchAddress("mult", &mult2, &b_mult2);
	tin2->SetBranchAddress("Vec_trg", &Vec_trg2, &b_Vec_trg2);
	tin2->SetBranchAddress("Vec_ass", &Vec_ass2, &b_Vec_ass2);
//}}}

//Define lorentz vector{{{
	TLorentzVector* vec_trg1 = new TLorentzVector;
	TLorentzVector* vec_trg2 = new TLorentzVector;
	TLorentzVector* vec_ass1 = new TLorentzVector;
	TLorentzVector* vec_ass2 = new TLorentzVector;
	vec_trg1 = 0;
	vec_trg2 = 0;
	vec_ass1 = 0;
	vec_ass2 = 0;
//}}}

	const Int_t Nevt1 = tin1->GetEntries();
	const Int_t Nevt2 = tin2->GetEntries();

	for(Int_t ievt = 0; ievt < Nevt1; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt1 << " [" << Form("%.1f", ((double)ievt/(double)Nevt1)*100) << " %]" << endl;
		tin1->GetEntry(ievt);

//		if(multMin <= mult1 && mult1 < multMax)
//		{
/*
//Get true Ntrig{{{
			Double_t TrueNtrg = 0;
			for(Int_t itrg = 0; itrg < Ntrg1; itrg++)
			{
				vec_trg1 = (TLorentzVector*) Vec_trg1->At(itrg);
				if(vec_trg1 == 0) continue;
				Double_t trg_pt = vec_trg1->Pt();
				Double_t trg_y = vec_trg1->Rapidity();

				if(ptMin <= trg_pt && trg_pt < ptMax && rapMin <= trg_y && trg_y < rapMax)
				{
					TrueNtrg++;
				}
			}
//}}}
*/
//background{{{
			for(Int_t itrg = 0; itrg < Ntrg1; itrg++)
			{
				vec_trg1 = (TLorentzVector*) Vec_trg1->At(itrg);
				if(vec_trg1 == 0) continue;
				Double_t trg_eta = vec_trg1->Eta();
				Double_t trg_phi = vec_trg1->Phi();
				Double_t trg_pt = vec_trg1->Pt();
				Double_t trg_y = vec_trg1->Rapidity();

//				if(ptMin <= trg_pt && trg_pt < ptMax && rapMin <= trg_y && trg_y < rapMax)
//				{
//correlation{{{
					for(Int_t irand = 0; irand < 10; irand++)
					{
						Int_t rNum = gRandom->Integer(Nevt2);
						tin2->GetEntry(rNum);
/*
//multiplicity cut for associator{{{
						if(!(multMin <= mult2 && mult2 < multMax))
						{
							irand--;
							continue;
						}
//}}}

//dimuon pt cut for associator{{{
						Int_t Nass_dimu = 0;
						for(Int_t itrg2 = 0; itrg2 < Ntrg2; itrg2++)
						{
							vec_trg2 = (TLorentzVector*) Vec_trg2->At(itrg2);
							Double_t ass_dimu_pt = vec_trg2->Pt();
							Double_t ass_dimu_y = vec_trg2->Rapidity();
							if(ptMin <= ass_dimu_pt && ass_dimu_pt < ptMax && rapMin <= ass_dimu_y && ass_dimu_y < rapMax) Nass_dimu++;
						}
						if(Nass_dimu == 0)
						{
							irand--;
							continue;
						}
//}}}
*/
						for(Int_t itrk = 0; itrk < Nass2; itrk++)
						{
							vec_ass2 = (TLorentzVector*) Vec_ass2->At(itrk);
							if(vec_ass2 == 0) continue;
							Double_t ass_eta = vec_ass2->Eta();
							Double_t ass_phi = vec_ass2->Phi();
							Double_t ass_pt = vec_ass2->Pt();

//							if(TrkptMin <= ass_pt && ass_pt < TrkptMax)
//							{
								Double_t deta = ass_eta - trg_eta;
								Double_t dphi = ass_phi - trg_phi;
								if(dphi > TMath::Pi()) dphi = dphi - 2*TMath::Pi();
								if(dphi < -TMath::Pi()) dphi = dphi + 2*TMath::Pi();
								if(dphi > -TMath::Pi() && dphi < -TMath::Pi()/2.) dphi = dphi + 2*TMath::Pi();
								h1_1->Fill(deta, dphi, 1/(double)(10*Ntrg1));
								h1_2->Fill(deta, dphi, 1/(double)(10*Ntrg1));
								if(fabs(deta) > 2.0)
								{
									h2_1->Fill(deta, dphi, 1/(double)(10*Ntrg1));
									h2_2->Fill(deta, dphi, 1/(double)(10*Ntrg1));
								}
								if(fabs(deta) > 1.0)
								{
									h3_1->Fill(deta, dphi, 1/(double)(10*Ntrg1));
									h3_2->Fill(deta, dphi, 1/(double)(10*Ntrg1));
								}
//							}
						}
					}
//}}}
//				}
			}
//}}}
//		}
	}

	for(Int_t ievt = 0; ievt < Nevt2; ievt++)
	{
		if(ievt%100000 == 0) cout << "Events: " << ievt << " / " << Nevt2 << " [" << Form("%.1f", ((double)ievt/(double)Nevt2)*100) << " %]" << endl;
		tin2->GetEntry(ievt);

//		if(multMin <= mult2 && mult2 < multMax)
//		{
/*
//Get true Ntrig{{{
			Double_t TrueNtrg = 0;
			for(Int_t itrg = 0; itrg < Ntrg2; itrg++)
			{
				vec_trg2 = (TLorentzVector*) Vec_trg2->At(itrg);
				if(vec_trg2 == 0) continue;
				Double_t trg_pt = vec_trg2->Pt();
				Double_t trg_y = vec_trg2->Rapidity();

				if(ptMin <= trg_pt && trg_pt < ptMax && rapMin <= trg_y && trg_y < rapMax)
				{
					TrueNtrg++;
				}
			}
//}}}
*/

//background{{{
			for(Int_t itrg = 0; itrg < Ntrg2; itrg++)
			{
				vec_trg2 = (TLorentzVector*) Vec_trg2->At(itrg);
				if(vec_trg2 == 0) continue;
				Double_t trg_eta = vec_trg2->Eta();
				Double_t trg_phi = vec_trg2->Phi();
				Double_t trg_pt = vec_trg2->Pt();
				Double_t trg_y = vec_trg2->Rapidity();

//				if(ptMin <= trg_pt && trg_pt < ptMax && rapMin <= trg_y && trg_y < rapMax)
//				{
//correlation{{{
					for(Int_t irand = 0; irand < 10; irand++)
					{
						Int_t rNum = gRandom->Integer(Nevt1);
						tin1->GetEntry(rNum);

/*
//multiplicity cut for associator{{{
						if(!(multMin <= mult1 && mult1 < multMax))
						{
							irand--;
							continue;
						}
//}}}

//dimuon pt cut for associator{{{
						Int_t Nass_dimu = 0;
						for(Int_t itrg1 = 0; itrg1 < Ntrg1; itrg1++)
						{
							vec_trg1 = (TLorentzVector*) Vec_trg1->At(itrg1);
							Double_t ass_dimu_pt = vec_trg1->Pt();
							Double_t ass_dimu_y = vec_trg1->Rapidity();
							if(ptMin <= ass_dimu_pt && ass_dimu_pt < ptMax && rapMin <= ass_dimu_y && ass_dimu_y < 2.4) Nass_dimu++;
						}
						if(Nass_dimu == 0)
						{
							irand--;
							continue;
						}
//}}}
*/

						for(Int_t itrk = 0; itrk < Nass1; itrk++)
						{
							vec_ass1 = (TLorentzVector*) Vec_ass1->At(itrk);
							if(vec_ass1 == 0) continue;
							Double_t ass_eta = vec_ass1->Eta();
							Double_t ass_phi = vec_ass1->Phi();
							Double_t ass_pt = vec_ass1->Pt();
							Double_t deta = ass_eta - trg_eta;
							Double_t dphi = ass_phi - trg_phi;
//							if(TrkptMin <= ass_pt && ass_pt < TrkptMax)
//							{
								if(dphi > TMath::Pi()) dphi = dphi - 2*TMath::Pi();
								if(dphi < -TMath::Pi()) dphi = dphi + 2*TMath::Pi();
								if(dphi > -TMath::Pi() && dphi < -TMath::Pi()/2.) dphi = dphi + 2*TMath::Pi();
								h1_1->Fill(deta, dphi, 1/(double)(10*Ntrg2));
								h1_2->Fill(deta, dphi, 1/(double)(10*Ntrg2));
								if(fabs(deta) > 2.0)
								{
									h2_1->Fill(deta, dphi, 1/(double)(10*Ntrg2));
									h2_2->Fill(deta, dphi, 1/(double)(10*Ntrg2));
								}
								if(fabs(deta) > 1.0)
								{
									h3_1->Fill(deta, dphi, 1/(double)(10*Ntrg2));
									h3_2->Fill(deta, dphi, 1/(double)(10*Ntrg2));
								}
//							}
						}
					}
//}}}
//				}
			}
//}}}

//		}
	}

//draw{{{
	gStyle->SetOptStat(0000);
	c1_1->cd();
	h1_1->Draw("Surf1");
	c1_2->cd();
	h1_2->Draw("Surf1");
	c2_1->cd();
	h2_1->Draw("Surf1");
	c2_2->cd();
	h2_2->Draw("Surf1");
	c3_1->cd();
	h3_1->Draw("Surf1");
	c3_2->cd();
	h3_2->Draw("Surf1");
//}}}

//store{{{
	TFile* fout = new TFile(Form("%d-%d_%d-%d_%d-%d_%d-%d_%d/deta-dphi_Pbp_distribution_bkg_%d.root", (int)multMin, (int)multMax, (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), (int)TrkptMin, (int)TrkptMax, nmbin, imass), "RECREATE");
	fout->cd();
	h1_1->Write();
	h1_2->Write();
	h2_1->Write();
	h2_2->Write();
	h3_1->Write();
	h3_2->Write();
	fout->Close();
//}}}
}
