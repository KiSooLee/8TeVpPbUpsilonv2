#!/bin/bash
#Sort0.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version)

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_8_0_26_patch2
cd CMSSW_8_0_26_patch2
eval `scramv1 runtime -sh`
cd -

root -l -b -q 'mCorrel_sig_pPb.C+(false, 110, 300, 0, 4, -2.4, 2.4, 1, 3, "v13", '$1')'
#ls
#root -l -b -q 'mCorrel_sig_pPb.C+(false, 120, 1500, 10, 30, -2.4, 2.4, 1, 3, "v13", 0)'
