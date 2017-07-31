#!/bin/bash
#Correl_bkg2.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version)

version="v1"

root -l -b -q 'Correl_bkg2.C+(false, 0, 300, 0, 30, -2.4, 2.4, 0, 1, '\"$version\"')'
#root -l -b -q 'Correl_bkg2.C+(false, 0, 300, 0, 30, -2.4, 2.4, 1, 3, '\"$version\"')'
#root -l -b -q 'Correl_bkg2.C+(false, 0, 300, 0, 30, -2.4, 2.4, 3, 10, '\"$version\"')'
