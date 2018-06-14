//Headers{{{
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TH1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <TMath.h>

#include <Fit/Fitter.h>
#include <Fit/BinData.h>
#include <Fit/Chi2FCN.h>
#include <Math/WrappedMultiTF1.h>
#include <HFitInterface.h>

#include "Upsilon.h"
#include "Style_Upv2.h"
//}}}

//external function{{{

//Chi2 calculation{{{
Int_t iparmass[8] = {0, 1, 2, 3, 4, 5, 6, 7};
Int_t iparvn[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

struct GlobalChi2_width
{
	GlobalChi2_width(ROOT::Math::IMultiGenFunction & f1,
						ROOT::Math::IMultiGenFunction & f2):
	fChi2_1(&f1), fChi2_2(&f2) {}

	Double_t operator() (const double *par) const
	{
		Double_t p1[13];
		for(Int_t i = 0; i < 8; i++) p1[i] = par[iparmass[i]];
		Double_t p2[16];
		for(Int_t i = 0; i < 11; i++) p2[i] = par[iparvn[i]];
		return (*fChi2_1)(p1) + (*fChi2_2)(p2);
	}
	const ROOT::Math::IMultiGenFunction * fChi2_1;
	const ROOT::Math::IMultiGenFunction * fChi2_2;
};
//}}}

//Yield fitting function{{{
Double_t YieldFunc(TF1* f1, TF1* f2, TF1* f3, Double_t* x, Double_t* p)
{
	return p[0]*f1->Eval(x[0]) + p[1]*f2->Eval(x[0]) + p[2]*f3->Eval(x[0]) + TMath::Exp(-x[0]/p[5])*(TMath::Erf((x[0]-p[3])/(TMath::Sqrt(2)*p[4]))+1)*0.5;
}
//}}}

//vn fitting function{{{
Double_t vnFunc(TF1* f1, TF1* f2, TF1* f3, Double_t* x, Double_t* p)
{
	return p[6]*( p[0]*f1->Eval(x[0]) + p[1]*f2->Eval(x[0]) + p[2]*f3->Eval(x[0]) )/( p[0]*f1->Eval(x[0]) + p[1]*f2->Eval(x[0]) + p[2]*f3->Eval(x[0]) + TMath::Exp(-x[0]/p[5])*(TMath::Erf((x[0]-p[3])/(TMath::Sqrt(2)*p[4]))+1)*0.5 ) + (p[7]+p[8]*x[0])*( 1 - ( p[0]*f1->Eval(x[0]) + p[2]*f2->Eval(x[0]) + p[3]*f3->Eval(x[0]) )/( p[0]*f1->Eval(x[0]) + p[1]*f2->Eval(x[0]) + p[2]*f3->Eval(x[0]) + TMath::Exp(-x[0]/p[5])*(TMath::Erf((x[0]-p[3])/(TMath::Sqrt(2)*p[4]))+1)*0.5 ) );
}
//}}}

//}}}

void SimultaneousFit(const Int_t multMin = 0, const Int_t multMax = 300, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const Double_t TrkptMin = 0, const Double_t TrkptMax = 1, TString version = "v13")
{
	SetStyle();
	const Int_t npt = 4;
	TFile* fout = new TFile(Form("CorrDist/CorrFiles/Combine_fit_Mult_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.root", (int)multMin, (int)multMax, (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()), "RECREATE");
	fout->cd();
	TF1* fyieldtot[npt];
	TF1* fvntot[npt];
	Double_t v2[npt];
	Double_t v2e[npt];
	Double_t v2_bkg[npt];
	Double_t a[npt];
	Double_t b[npt];
	Double_t pt[npt] = {2, 5, 8, 20};

//Define canvas for yield and vn dist{{{
	TCanvas* c1[npt];
	for(Int_t ipt = 0; ipt < npt; ipt++)
	{
		c1[ipt] = new TCanvas(Form("c1_%d", ipt), "", 0, 0, 1200, 600);
		c1[ipt]->Divide(2, 1);
	}
	TH1D* hist = new TH1D("hist", "", 20, 8, 14);
	hist->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
	hist->GetYaxis()->SetTitle("v_{2}");
	hist->SetMinimum(-0.1);
	hist->SetMaximum(0.3);
//}}}

	for(Int_t ipt = 0; ipt < npt; ipt++)
	{
//Get yield distribution{{{
		TFile* fyield = new TFile(Form("SkimmedFiles/Yield/Yield_Mult_%d-%d_pt_%d-%d_rap_%d-%d_%s.root", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), version.Data() ), "READ");
		TH1D* hyield = (TH1D*) fyield->Get(Form("hmass"));
		hyield->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
		hyield->GetYaxis()->SetTitle("Entries");
		TF1* tf1S = (TF1*) fyield->Get(Form("twoCB1S"));
		TF1* tf2S = (TF1*) fyield->Get(Form("twoCB2S"));
		TF1* tf3S = (TF1*) fyield->Get(Form("twoCB3S"));
		TF1* tf1SC = (TF1*) tf1S->Clone("tf1SC");
		TF1* tf2SC = (TF1*) tf2S->Clone("tf2SC");
		TF1* tf3SC = (TF1*) tf3S->Clone("tf3SC");
		gROOT->GetListOfFunctions()->Add(tf1SC);
		gROOT->GetListOfFunctions()->Add(tf2SC);
		gROOT->GetListOfFunctions()->Add(tf3SC);

		tf1SC->Print();

		//tf1S->SetTitle("tf1S");
		//tf2S->SetTitle("tf2S");
		//tf3S->SetTitle("tf3S");

		c1[ipt]->cd(1);
		hyield->Draw();
//}}}

//Get fitting parameter{{{
		string char1, char2, char3, char4, char5, char6, char7, char8, char9; 
		string char10, char11, char12, char13, char14, char15, char16; 
		string char17, char18, char19, char20, char21, char22, char23; 
		string char24, char25, char26, char27, char28, char29, char30;
		string char31; 
		Double_t var1, var2, var3, var4, var5, var6, var7, var8, var9;
		Double_t var10, var11, var12, var13, var14, var15, var16, var17;
		Double_t var18, var19, var20, var21, var22, var23, var24, var25;
		Double_t var26, var27, var28, var29, var30, var31;

		ifstream in;
		in.open(Form("SkimmedFiles/Parameter/Result_parameters_mult_110-300_pt_%d-%d_rap_-24-24_v13.txt", (int)(ptBinsArr[ipt]*10), (int)(ptBinsArr[ipt+1]*10)));
		if(in.is_open())
		{
			in >> char1 >> char2 >> char3 >> char4 >> char5 >> char6 >> 
					char7 >> char8 >> char9 >> char10 >> char11 >> char12; 
			in >> var1 >> var2 >> var3 >> var4 >> var5 >> var6 >> 
					var7 >> var8 >> var9 >> var10 >> var11 >> var12;
			in >> char13 >> char14 >> char15 >> char16 >> char17 >> 
					char18 >> char19 >> char20 >> char21 >> char22 >> 
					char23 >> char24 >> char25;
			in >> var13 >> var14 >> var15 >> var16 >> var17 >> var18 >> 
					var19 >> var20 >> var21 >> var22 >> var23 >> var24 >> 
					var25;
			in >> char26 >> char27 >> char28 >> char29 >> char30 >> char31;
			in >> var26 >> var27 >> var28 >> var29 >> var30 >> var31;
		}
		in.close();
//}}}

//Get vn distribution{{{
		TFile* fvn = new TFile(Form("CorrDist/CorrFiles/v2_dist_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.root", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]), (int)(ptBinsArr[ipt+1]), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()), "READ");
		TGraphErrors* gvn_1fine = (TGraphErrors*) fvn->Get("gv2_1fine");
		TGraphErrors* gvn_1coarse = (TGraphErrors*) fvn->Get("gv2_1coarse");
		TGraphErrors* gvn_2fine = (TGraphErrors*) fvn->Get("gv2_2fine");
		TGraphErrors* gvn_2coarse = (TGraphErrors*) fvn->Get("gv2_2coarse");

		c1[ipt]->cd(2);
		//gvn_1fine->Draw();
//}}}

		//fit function for yield
//{{{
/*
//define individual crystalball function{{{
		TF1* f1S1 = new TF1("f1S1", "ROOT::Math::crystalball_function(x, var21, var22, var14, var13)", 8, 14);
		TF1* f1S2 = new TF1("f1S2", "ROOT::Math::crystalball_function(x, var21, var22, var15, var13)", 8, 14);
		TF1* f2S1 = new TF1("f2S1", "ROOT::Math::crystalball_function(x, var21, var22, var16, var13*U2S_mass/U1S_mass)", 8, 14);
		TF1* f2S2 = new TF1("f2S2", "ROOT::Math::crystalball_function(x, var21, var22, var17, var13*U2S_mass/U1S_mass)", 8, 14);
		TF1* f3S1 = new TF1("f3S1", "ROOT::Math::crystalball_function(x, var21, var22, var18, var13*U3S_mass/U1S_mass)", 8, 14);
		TF1* f3S2 = new TF1("f3S2", "ROOT::Math::crystalball_function(x, var21, var22, var19, var13*U3S_mass/U1S_mass)", 8, 14);
//}}}

		TF1* fbkg = new TF1("fbkg", "TMath::Exp(-x/[0])*(TMath::Erf((x-[1])/(TMath::Sqrt(2)*[2]))+1)*0.5", );
		fbkg->SetParameter(0, var25);
		fbkg->SetParameter(1, var23);
		fbkg->SetParameter(2, var24);
*/
//}}}

		//parameters
		//p0 = mean
		//p1 = sigma1
		//fit function for yield
//{{{
		//TF1* fyield_simul = new TF1(Form("fyield_simul_%d", ipt), "[13]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [1], [0])+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [2], [0])) + [14]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [3], [0]*U2S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [4], [0]*U2S_mass/U1S_mass)) + [15]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [5], [0]*U3S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [6], [0]*U3S_mass/U1S_mass)) + TMath::Exp(-x/[12])*(TMath::Erf((x-[10])/(TMath::Sqrt(2)*[11]))+1)*0.5", 8, 14);
//}}}

		auto Addfyield = [&](Double_t* x, Double_t* p)->Double_t
		{
			return YieldFunc(tf1SC, tf2SC, tf3SC, x, p);
		};
		TF1* fyield_simul = new TF1(Form("fyield_simul_%d", ipt), Addfyield, 8, 14, 6);

		auto Addfvn = [&](Double_t* x, Double_t* p)->Double_t
		{
			return vnFunc(tf1SC, tf2SC, tf3SC, x, p);
		};
		TF1* fvn_simul = new TF1(Form("fyield_simul_%d", ipt), Addfvn, 8, 14, 9);

//{{{
		//TF1* fyield_simul = new TF1(Form("fyield_simul_%d", ipt), "[0]*(tf1SC) + [1]*(tf2SC) + [2]*(tf3SC) + TMath::Exp(-x/[5])*(TMath::Erf((x-[3])/(TMath::Sqrt(2)*[4]))+1)*0.5", 8, 14);
		//TF1* fvn_simul = new TF1(Form("fyield_simul_%d", ipt), "[6]*([0]*(tf1SC)+[1]*(tf2SC)+[2]*(tf3SC))/([0]*(tf1SC)+[1]*(tf2SC)+[2]*(tf3SC) + TMath::Exp(-x/[5])*(TMath::Erf((x-[3])/(TMath::Sqrt(2)*[4]))+1)*0.5) + ([7]+[8]*x)*(1 - ([0]*(tf1SC)+[2]*(tf2SC)+[3]*(tf3SC))/([0]*(tf1SC)+[1]*(tf2SC)+[2]*(tf3SC) + TMath::Exp(-x/[5])*(TMath::Erf((x-[3])/(TMath::Sqrt(2)*[4]))+1)*0.5))", 8, 14);
		//TF1* fvn_simul = new TF1(Form("fvn_simul_%d", ipt), "[16]*([13]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [1], [0])+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [2], [0])) + [14]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [3], [0]*U2S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [4], [0]*U2S_mass/U1S_mass)) + [15]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [5], [0]*U3S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [6], [0]*U3S_mass/U1S_mass)))/([13]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [1], [0])+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [2], [0])) + [14]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [3], [0]*U2S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [4], [0]*U2S_mass/U1S_mass)) + [15]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [5], [0]*U3S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [6], [0]*U3S_mass/U1S_mass)) + TMath::Exp(-x/[12])*(TMath::Erf((x-[10])/(TMath::Sqrt(2)*[11]))+1)*0.5) + ([17]+[18]*x)*(([13]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [1], [0])+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [2], [0])) + [14]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [3], [0]*U2S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [4], [0]*U2S_mass/U1S_mass)) + [15]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [5], [0]*U3S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [6], [0]*U3S_mass/U1S_mass)))/([13]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [1], [0])+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [2], [0])) + [14]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [3], [0]*U2S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [4], [0]*U2S_mass/U1S_mass)) + [15]*([7]*ROOT::Math::crystalball_function(x, [8], [9], [5], [0]*U3S_mass/U1S_mass)+(1-[7])*ROOT::Math::crystalball_function(x, [8], [9], [6], [0]*U3S_mass/U1S_mass)) + TMath::Exp(-x/[12])*(TMath::Erf((x-[10])/(TMath::Sqrt(2)*[11]))+1)*0.5))", 8, 14);
//}}}
		//fit function for v2
//{{{
		//TF1* fvn_simul = new TF1(Form("fvn_simul_%d", ipt), "[&](Double_t* x, Double_t* p){return p[5]*(p[0]*(p[4]*f1S1(x)+(1-p[4])*f1S2(x))+p[1]*(p[4]*f2S1(x)+(1-p[4])*f2S2(x))+p[2]*(p[4]*f3S1(x)+(1-p[4])*f3S2(x)))/(p[0]*(p[4]*f1S1(x)+(1-p[4])*f1S2(x))+p[1]*(p[4]*f2S1(x)+(1-p[4])*f2S2(x))+p[2]*(p[4]*f3S1(x)+(1-p[4])*f3S2(x))+p[3]*fbkg) + (p[6]+p[7]*x)*(1 - (p[0]*(p[4]*f1S1(x)+(1-p[4])*f1S2(x))+p[1]*(p[4]*f2S1(x)+(1-p[4])*f2S2(x))+p[2]*(p[4]*f3S1(x)+(1-p[4])*f3S2(x)))/(p[0]*(p[4]*f1S1(x)+(1-p[4])*f1S2(x))+p[1]*(p[4]*f2S1(x)+(1-p[4])*f2S2(x))+p[2]*(p[4]*f3S1(x)+(1-p[4])*f3S2(x))+p[3]*fbkg));}", 8, 14);
//}}}

//combine functions{{{
		fyield_simul->SetLineColor(2);
		fyield_simul->SetLineWidth(1);

		fvn_simul->SetLineColor(2);
		fvn_simul->SetLineWidth(1);

		ROOT::Math::WrappedMultiTF1 wmass(*fyield_simul, 1);
		ROOT::Math::WrappedMultiTF1 wvn(*fvn_simul, 1);

		ROOT::Fit::DataOptions opt;
		ROOT::Fit::DataRange massrange;

		massrange.SetRange(8, 16);
		ROOT::Fit::BinData datamass(opt, massrange);
		ROOT::Fit::FillData(datamass, hyield);

		ROOT::Fit::DataRange vnrange;
		vnrange.SetRange(8, 16);
		ROOT::Fit::BinData datavn(opt, vnrange);
		ROOT::Fit::FillData(datavn, gvn_1fine);

		ROOT::Fit::Chi2Function mass_chi2(datamass, wmass);
		ROOT::Fit::Chi2Function vn_chi2(datavn, wvn);

		GlobalChi2_width globalChi2(mass_chi2, vn_chi2);

		ROOT::Fit::Fitter fitter;
//}}}

//parameter setting{{{
		//parameters
		//par0[0] = 1S const
		//par0[1] = 2S const
		//par0[2] = 3S const
		//par0[3] = Erf mean
		//par0[4] = Erf sigma
		//par0[5] = Erf p0
		//par0[6] = sig ratio
		//par0[7] = linear b
		//par0[8] = linear a

		const Int_t Npar = 10;
		Double_t par0[Npar];
		par0[0] = var26/var29;
		par0[1] = var27/var30;
		par0[2] = var28/var31;
		par0[3] = var23;
		par0[4] = var24;
		par0[5] = var25;
		par0[6] = 0.01;
		par0[7] = 0.10;
		par0[8] = 0.05;
//}}}

//fit{{{
		c1[ipt]->cd(2);
		hist->Draw();
		fitter.Config().SetParamsSettings(Npar, par0);
		//fitter.Config().ParSettings(1).Fix();
		fitter.Config().MinimizerOptions().SetPrintLevel(0);
		fitter.Config().SetMinimizer("Minuit2","Migrad");

		fitter.FitFCN(Npar, globalChi2, 0, datamass.Size()+datavn.Size(), true);
		ROOT::Fit::FitResult result = fitter.Result();
		result.Print(std::cout);

		fyield_simul->SetFitResult(result, iparmass);
		fyield_simul->SetRange(massrange().first, massrange().second);
		fyield_simul->SetLineColor(kRed);
		hyield->GetListOfFunctions()->Add(fyield_simul);

		fvn_simul->SetFitResult(result, iparvn);
		fvn_simul->SetRange(vnrange().first, vnrange().second);
		fvn_simul->SetLineColor(2);

		gvn_1fine->GetListOfFunctions()->Add(fvn_simul);
		gvn_1fine->SetTitle("");
		gvn_1fine->SetMarkerSize(0.8);
		gvn_1fine->SetLineWidth(1);
		gvn_1fine->Draw("PESAME");
//}}}

//store individual function{{{
		fout->cd();

		fvntot[ipt] = (TF1*) fvn_simul->Clone();
		fvntot[ipt]->SetName(Form("vnfit_pt%d", ipt));
		fvntot[ipt]->Write();

		fyieldtot[ipt] = (TF1*) fyield_simul->Clone();
		fyieldtot[ipt]->SetName(Form("massfit_pt%d", ipt));
		fyieldtot[ipt]->Write();

		v2[ipt] = fvn_simul->GetParameter(6);
		v2e[ipt] = fvn_simul->GetParError(6);
		v2_bkg[ipt] = fvn_simul->GetParameter(7) + fvn_simul->GetParameter(8) * U1S_mass;
		a[ipt] = fvn_simul->GetParameter(8);
		b[ipt] = fvn_simul->GetParameter(7);

		TF1* fvn_bkg = new TF1(Form("fvn_bkg_%d", 1), "([0]+[1]*x)", 8, 14);
		fvn_bkg->FixParameter(0, b[ipt]);
		fvn_bkg->FixParameter(1, a[ipt]);
		fvn_bkg->SetName(Form("fvnbkg_%d", ipt));
		fvn_bkg->Write();
//}}}

//get Chi2{{{
		Double_t xmass[200];
		Double_t pullmass[200];

		Float_t Chi2 = 0;
		Int_t ndf = (14-8)/0.3 - 8;

		for(Int_t ibin = 0; ibin < hyield->GetNbinsX(); ibin++)
		{
			xmass[ibin] = hyield->GetBinCenter(ibin);
			pullmass[ibin] = (hyield->GetBinContent(ibin) - fyield_simul->Eval(xmass[ibin]))/hyield->GetBinError(ibin);
			if(fabs(pullmass[ibin]) < 5)
			{
				Chi2 += pullmass[ibin]*pullmass[ibin];
			}
		}

		Double_t xv2[200];
		Double_t pullv2[200];
		Double_t v2y[200];

		Float_t Chi2v2 = 0;
		Int_t ndfv2 = 8-2;

		for(Int_t ibin = 0; ibin < gvn_1fine->GetN(); ibin++)
		{
			gvn_1fine->GetPoint(ibin, xv2[ibin], v2y[ibin]);
			pullv2[ibin] = (v2y[ibin] - fvn_simul->Eval(xv2[ibin]))/gvn_1fine->GetErrorY(ibin);
			if(fabs(pullv2[ibin]) < 100)
			{
				Chi2v2 += pullv2[ibin]*pullv2[ibin];
			}
		}
//}}}
	}

	for(Int_t ipt = 0; ipt < npt; ipt++)
	{
		cout << "pt" << ipt << ", a: " << a[ipt] << ", b: " << b[ipt] << endl;
		c1[ipt]->SaveAs(Form("CorrDist/V2Dist/Combine_fit_Mult_%d-%d_pt_%d-%d_rap_%d-%d_Trkpt_%d-%d_%s.pdf", (int)multMin, (int)multMax, (int)(ptBinsArr[ipt]*10), (int)(ptBinsArr[ipt+1]*10), (int)(10*rapMin), (int)(10*rapMax), (int)TrkptMin, (int)TrkptMax, version.Data()));
	}

	TGraphErrors* v2plot = new TGraphErrors(npt, pt, v2, 0, v2e);
	v2plot->SetTitle("");
	TGraphErrors* v2bkgplot = new TGraphErrors(npt, pt, v2_bkg, 0, 0);

	v2plot->SetName("v2vspt");
	v2bkgplot->SetName("v2bkgvspt");

	v2plot->Write();
	v2bkgplot->Write();
//}}}
}
