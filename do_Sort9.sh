#!/bin/bash
#Sort9.C(isMC, multMin, multMax, ptMin, ptMax, rapMin, rapMax, trkptMin, trkptMax, version)

version="v1"
root -l -b -q 'Sort9.C+(false, 0, 300, 0, 30, -2.4, 2.4, 0, 1, '\"$version\"')'
root -l -b -q 'Sort9.C+(false, 0, 300, 0, 30, -2.4, 2.4, 1, 3, '\"$version\"')'
root -l -b -q 'Sort9.C+(false, 0, 300, 0, 30, -2.4, 2.4, 3, 6, '\"$version\"')'
