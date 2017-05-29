//Headers{{{
#include <TROOT.h>
#include <TTree.h>
#include <TString.h>
#include <TClonesArray.h>
//}}}

//Basic info{{{
//Double_t rapBinsArr[] = {0, 1.2, 2.4};
Double_t rapBinsArr[] = {0, 2.4};
//Double_t ptBinsArr[] = {0, 6, 30};
Double_t ptBinsArr[] = {0, 30};
//Double_t multBinsArr[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 95, 100, 105, 110, 120, 130, 140, 150, 160, 300};
//Double_t multBinsArr[] = {0, 10, 20, 30, 100, 300};
Double_t multBinsArr[] = {0, 300};

const Int_t rap_narr = sizeof(rapBinsArr)/sizeof(double);
const Int_t pt_narr = sizeof(ptBinsArr)/sizeof(double);
const Int_t mult_narr = sizeof(multBinsArr)/sizeof(double);

const Double_t U1S_mass = 9.460;
const Double_t U2S_mass = 10.023;
const Double_t U3S_mass = 10.355;
const Double_t U1S_sigma = 0.00026;
const Double_t U2S_sigma = 0.00031;
const Double_t U3S_sigma = 0.0005;
const Double_t peakFactor = 2.;
const Double_t sideFactor = 2.;
//}}}

class DiMuon
{
//{{{
	public:

	UInt_t eventNb, LS;
	Double_t zVtx, dphi, deta;
	Double_t mass, y, pt, phi;
	Double_t mupl_eta, mupl_pt, mupl_phi;
	Double_t mumi_eta, mumi_pt, mumi_phi;
	Double_t trk_eta, trk_pt, trk_phi;
	Double_t weight;
	Double_t mult;
	Int_t Npeak, Nside, Nass;
	TClonesArray* Vec_trg_peak;
	TClonesArray* Vec_trg_side;
	TClonesArray* Vec_ass;

	void clear()
	{
		eventNb = -99; LS = -99; zVtx = -99; dphi = -99, deta = -99;
		mass = -99; y = -99; pt = -99; phi = -99;
		mupl_eta = -99; mupl_pt = -99; mupl_phi = -99;
		mumi_eta = -99; mumi_pt = -99; mumi_phi = -99;
		trk_eta = -99; trk_pt = -99; trk_phi = -99;
		weight = -99; mult = -99;
		Npeak = -99; Nside = -99; Nass = -99;
		Vec_trg_peak->Clear();
		Vec_trg_side->Clear();
		Vec_ass->Clear();
	}

	void BuildBranch(TTree* tout)
	{
		tout->Branch("eventNb", &eventNb);
		tout->Branch("LS", &LS);
		tout->Branch("zVtx", &zVtx);
		tout->Branch("dphi", &dphi);
		tout->Branch("deta", &deta);
		tout->Branch("mass", &mass);
		tout->Branch("y", &y);
		tout->Branch("pt", &pt);
		tout->Branch("phi", &phi);
		tout->Branch("mupl_eta", &mupl_eta);
		tout->Branch("mupl_pt", &mupl_pt);
		tout->Branch("mupl_phi", &mupl_phi);
		tout->Branch("mumi_eta", &mumi_eta);
		tout->Branch("mumi_pt", &mumi_pt);
		tout->Branch("mumi_phi", &mumi_phi);
		tout->Branch("trk_eta", &trk_eta);
		tout->Branch("trk_pt", &trk_pt);
		tout->Branch("trk_phi", &trk_phi);
		tout->Branch("weight", &weight);
		tout->Branch("mult", &mult);
		tout->Branch("Npeak", &Npeak);
		tout->Branch("Nside", &Nside);
		tout->Branch("Nass", &Nass);
		Vec_trg_peak = new TClonesArray("TLorentzVector", 250);
		Vec_trg_side = new TClonesArray("TLorentzVector", 250);
		Vec_ass = new TClonesArray("TLorentzVector", 1500);
		tout->Branch("Vec_trg_peak", "TClonesArray", &Vec_trg_peak, 32000, 0);
		tout->Branch("Vec_trg_side", "TClonesArray", &Vec_trg_side, 32000, 0);
		tout->Branch("Vec_ass", "TClonesArray", &Vec_ass, 32000, 0);
	}
//}}}
};
