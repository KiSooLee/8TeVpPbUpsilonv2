#!/bin/bash
#GetYield.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, version)

#version="v13"
#root -l -b -q 'GetYield.C+(110, 300, 0, 4, -2.4, 2.4, '\"$version\"')'
root -l -b -q 'GetYield.C+(110, 300, 0, 4, -2.4, 2.4, "v13")'
root -l -b -q 'GetYield.C+(110, 300, 4, 6, -2.4, 2.4, "v13")'
root -l -b -q 'GetYield.C+(110, 300, 6, 10, -2.4, 2.4, "v13")'
root -l -b -q 'GetYield.C+(110, 300, 10, 30, -2.4, 2.4, "v13")'
