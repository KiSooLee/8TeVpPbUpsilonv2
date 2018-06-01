1. pPb v2 study is using track multiplicity instead of centrality.
	By running GetNtrack.C multiplicity distribution can be achieved.

2-1. With the track multiplicity binning onia tree is skimmed by dataskim.C in order to draw mass distribution. do_skim.sh is used to run dataskim.C

2-2. Mass distrinution is fitted by two Crystal ball.
	Initial parameters for the Crystal ball signal and Errfunction background should be defined in the SkimmedFiles/Parameter/ directory.
	Mass fitting is done by SkimmedFiles/GetYield.C. SkimmedFiles/do_GetYield.sh is used to run GetYield.C
	Final Parameters are also stored in SkimmedFiles/Parameter/ directory.

2-3. Mass fitting plot is stored in the SkimmedFiles/MassDist/ directory and yield is stored in the SkimmedFiles/Yield directory.

2-4. The Yield vs. pt, y, multiplicity distribution are drawn by SkimmedFiles/Yield/YieldDist.C.
	SkimmedFiles/Yield/do_YieldDist.sh is used to run YieldDist.C 

3. Because of the large events, correlation process takes too long time.
	In order to reduce process time, all processes are splited by HTCondor into 120 files.

3-1. Before correlate all variables should be rearranged by mSortpPb1.C, mSortpPb2.C, mSortPbp1.C, mSortPbp2.C.
	These macros run by do_mSortpPb1.sh, do_mSortpPb2.sh, do_mSortPbp1.sh, do_mSortPbp2.sh.
	Shell scripts are run by submit_Sort_pPb1.jds, submit_Sort_pPb2.jds, submit_Sort_Pbp1.jds, submit_Sort_Pbp2.jds. 
	And result files are moved to the storage by StoreSort.sh.

3-2. Rearranged root files are splited related to its multiplicity, pt, y, track pt range.
	Collect_pPb1.C, Collect_pPb2.C, Collect_Pbp1.C, Collect_Pbp2.C works this spliting.
	These macros run by same shell and jds with sorting process.

4. Correlation is processed separately for the signal and background.
	Files splited into 120 mass bin are merged to several bins to obtain enouph entry to correlate.

4-1. Signal correlation is processed by mCorrel_sig_pPb.C, mCorrel_sig_Pbp.C.
	Macro is run by do_mCorrel_sig_pPb.sh, do_mCorrel_sig_Pbp.sh.
	Condor file is submit_Corr_sig_pPb.jds, submit_Corr_sig_Pbp.jds.

4-2. Background correlation is processed by mCorrel_bkg_pPb.C, mCorrel_bkg_Pbp.C.
	Macro is run by do_mCorrel_bkg_pPb.sh, do_mCorrel_bkg_Pbp.sh.
	Condor file is submit_Corr_bkg_pPb.jds, submit_Corr_bkg_Pbp.jds.

5. Correlate results are projected to dphi axis.
	RatioNProjection.C project 2-D plot and store it.
	do_projection.sh runs the macro.

6. Fourier harmonic function is fitted to dphi projection distribution in the extV2.C.
	do_extV2.sh runs the macro.

7. In order to obtain v2 value for the signal, both yield and v2 distribution are fitted with SimultaneousFit.C.
