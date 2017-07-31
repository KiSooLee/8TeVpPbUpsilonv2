1. pPb v2 study is using track multiplicity instead of centrality.
	By running GetNtrack.C multiplicity distribution can be achieved.

2. With the track multiplicity binning onia tree is skimmed by dataskim.C in order to draw mass distribution. do_skim.sh is used to run dataskim.C

3. Mass distrinution is fitted by two Crystal ball. Initial parameters for the Crystal ball are stored in the SkimmedFiles/Parameter/ directory. Mass fitting is done by SkimmedFiles/GetYield.C. SkimmedFiles/do_GetYield.sh is used to run GetYield.C

4. Mass fitting plot is stored in the SkimmedFiles/MassDist/ directory and yield is stored in the SkimmedFiles/Yield directory.

5. With the Yield pt, y, multiplicity distribution is drawn by SkimmedFiles/Yield/YieldDist.C. SkimmedFiles/Yield/do_YieldDist.sh is used to run YieldDist.C 

6. Because of the large events correlation process takes too long time. In order to reduce running time root file is collected with Sort0.C ~ Sort9.C. 5000000 events are collected in a root file in each pt and multiplicity, rapidity bin. do_Sort0.sh ~do_Sort9.sh is used to run Sort?.C

7. The sorted files are stored in SortFiles/ directory. To correlate background two same file is needed. So the sorted root file is copied by Clone.sh

8. To see the Correlation distribution masses are separeted in 120 bins. And the tracks are correlated with dimuons. SortFiles/Correl_sig0.C ~ Correl_sig9.C is used to correlated signal and SortFiles/Correl_bkg0.C ~ Correl_bkg9.C is used to correlated background. To run the macros SortFiles/do_Corr_sig0.sh ~ do_Corr_sig9.sh and SortFiles/do_Corr_bkg0.sh ~ do_Corr_bkg9.sh are used. The result histograms are stored in the SigCorr/ and BkgCorr/ directories.

9. To achieve signal dimuon is correlated with tracks in the same event. SortFiles/Correl_peak_sig.C is correlate signal. To get the background dimuon is correlated with tracks in the random 10 events. SortFiles/Correl_peak_bkg.C is correlate background.

v1: integrated
mult: 0, 300
pt: 0, 30
y: -2.4, 2.4

v2: pt distribution
mult: 0, 300
pt: 0, 3, 5, 7, 9, 11, 15, 30
y: -2.4, 2.4

v3: multiplicity distribution
mult: 0, 100, 150, 300
pt: 0, 30
y: -2.4, 2.4

v4: rapidity distribution
mult: 0, 300
pt: 0, 30
y: -2.4, -1.2, 0.0, 1.2, 2.4
