#!/bin/bash
#GetYield.C(multMin, multMax, ptMin, ptMax, rapMin, rapMax, version)

version="v2"
root -l -b -q 'GetYield.C+(0, 300, 0, 3, -2.4, 2.4, '\"$version\"')'
root -l -b -q 'GetYield.C+(0, 300, 3, 5, -2.4, 2.4, '\"$version\"')'
root -l -b -q 'GetYield.C+(0, 300, 5, 7, -2.4, 2.4, '\"$version\"')'
root -l -b -q 'GetYield.C+(0, 300, 7, 9, -2.4, 2.4, '\"$version\"')'
root -l -b -q 'GetYield.C+(0, 300, 9, 11, -2.4, 2.4, '\"$version\"')'
root -l -b -q 'GetYield.C+(0, 300, 11, 15, -2.4, 2.4, '\"$version\"')'
root -l -b -q 'GetYield.C+(0, 300, 15, 30, -2.4, 2.4, '\"$version\"')'
