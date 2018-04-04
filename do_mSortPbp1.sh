#!/bin/bash
#Sort0.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version)

#source /cvmfs/cms.cern.ch/cmsset_default.sh
#scram p CMSSW CMSSW_8_0_26_patch2
#cd CMSSW_8_0_26_patch2
#eval `scramv1 runtime -sh`
#cd -

version="v1"
#root -l -b -q 'mSortPbp1.C+(false, 0, 1500, 0, 30, -2.4, 2.4, 0, 10, '\"$version\"', '$1')'
#root -l -b -q 'Collect_Pbp1.C+(false, 120, 1500, 0, 6, -2.4, 2.4, 1, 3, '$1')'
root -l -b -q 'Collect_Pbp1.C+(false, 120, 1500, 0, 6, -2.4, 2.4, 1, 3, 109)'
