1. pPb v2 study is using track multiplicity instead of centrality.
	By running GetNtrack.C multiplicity distribution can be achieved.

2. With the track multiplicity binning onia tree is skimmed by dataskim.C in order to draw mass distribution. do_skim.sh is used to run dataskim.C

3. Mass distrinution is fitted by two Cristal ball. Mass fitting is done by SkimmedFiles/GetYield.C. do_GetYield.sh is used to run GetYield.C

4. From the mass fitting sigma is achieved. Definition of the sigma is quadratic sum of sigma of two Cristal ball function.

5. Mass range within 2 sigma is selected as peak. And the rest range is selected as side.
	Peak and side for each multiplicity range are sorted by Sort.C

6. Peak and side are correlated with track and make signal and backgraound.
	deta-dphi distribution is achieved by following macros.
	Correl_peak_sig.C, Correl_peak_bkg.C, Correl_side_sig.C, Correl_side_bkg.C

v1
pt: 0~30
mult: 0~300

v2
pt: 0~3, 3~5, 5~7, 7~9, 9~11, 11~15, 15~40
mult: 0~300
