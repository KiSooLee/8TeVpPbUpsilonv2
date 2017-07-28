1. pPb v2 study is using track multiplicity instead of centrality.
	By running GetNtrack.C multiplicity distribution can be achieved.

2. With the track multiplicity binning onia tree is skimmed by dataskim.C in order to draw mass distribution. do_skim.sh is used to run dataskim.C

3. Mass distrinution is fitted by two Crystal ball. Initial parameters for the Crystal ball are stored in the SkimmedFiles/Parameter/ directory. Mass fitting is done by SkimmedFiles/GetYield.C. SkimmedFiles/do_GetYield.sh is used to run GetYield.C

4. Mass fitting plot is stored in the SkimmedFiles/MassDist/ directory and yield is stored in the SkimmedFiles/Yield directory.

5. With the Yield pt, y, multiplicity distribution is drawn by SkimmedFiles/Yield/YieldDist.C. SkimmedFiles/Yield/do_YieldDist.sh is used to run YieldDist.C 

6. In each pt and multiplicity bin, dimuon candidates are correlated with track. To see the flow in each mass value dimuon candidates are separated in fine mass binnning. Sort.C store dimuons in the certain mass binning and tracks in the same event. do_Sort.sh is used to run Sort.C

7. Sorted results are stored in the SortFiles/ directory. Due to the large number of events all the events are separeted to the 10 root files.

7. To achieve signal dimuon is correlated with tracks in the same event. SortFiles/Correl_peak_sig.C is correlate signal. To get the background dimuon is correlated with tracks in the random 10 events. SortFiles/Correl_peak_bkg.C is correlate background.
	do_peak_sig.sh and do_peak_bkg.sh are used to run Correl_peak_sig.C and Correl_peak_bkg.C
	The correlation results are stored as dphi-deta distribution in the SortFiles/CorrDist/ directory.

v1
pt: 0, 30
mult: 0, 300

v2
pt: 0, 3, 5, 7, 9, 11, 15, 30
mult: 0, 300

v3
pt: 0, 30
mult: 0, 100, 150, 300
