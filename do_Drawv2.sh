#!/bin/bash
#extV2fromCor.C()

version="v16"

multMin=("110")
multMax=("300")
rapMin=("-2.4")
rapMax=("2.4")
TrkptMin=("0")
TrkptMax=("3")

for((i=0; i<"${#multMin[@]}"; i++))
do
	for((k=0; k<"${#rapMin[@]}"; k++))
	do
		for((l=0; l<"${#TrkptMin[@]}"; l++))
		do
			root -l -b -q 'DrawSigv2.C+('${multMin[$i]}', '${multMax[$i]}', '${rapMin[$k]}', '${rapMax[$k]}', '${TrkptMin[$l]}', '${TrkptMax[$l]}', '\"$version\"')'
		done
	done
done
