#!/bin/bash
#Sort0.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version)

version="v11"

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_8_0_26_patch2
cd CMSSW_8_0_26_patch2
eval `scramv1 runtime -sh`
cd -

root -l -b -q 'mCorrel_sig_Pbp.C+(false, 120, 1500, 0, 4, -2.4, 2.4, 1, 3, '\"$version\"', '$1', 20)'
#ls
#root -l -b -q 'mCorrel_sig_Pbp.C+(false, 120, 1500, 0, 6, -2.4, 2.4, 1, 3, '\"$version\"', 13, 20)'
#root -l -b -q 'mCorrel_sig_Pbp_test.C+(false, 1, 40, 10, 30, 1.2, 2.4, 6, 10, '\"$version\"', 14, 20)'
