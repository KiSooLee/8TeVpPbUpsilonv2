#!/bin/bash

multMin=("110")
multMax=("300")
#multMin=("40" "100" "200" "300")
#multMax=("100" "200" "300" "1500")
ptMin=("10")
ptMax=("30")
rapMin=("-24")
rapMax=("24")
TrkptMin=("1")
TrkptMax=("3")
version="v1"

#rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/total/
#rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/total/
#rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/total/
#rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/total/

for((i=0; i<"${#multMin[@]}"; i++))
do
	for((j=0; j<"${#ptMin[@]}"; j++))
	do
		for((k=0; k<"${#rapMin[@]}"; k++))
		do
			for((l=0; l<"${#TrkptMin[@]}"; l++))
			do
				#cp ${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}_Pbp1/* /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/total/
				#cp ${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}_Pbp2/* /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/total/
				#cp ${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}_pPb1/* /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/total/
				#cp ${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}_pPb2/* /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/total/

				rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}/*
				cp ${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}_Pbp1/* /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}/
				rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}/*
				cp ${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}_Pbp2/* /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}/
				rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}/*
				cp ${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}_pPb1/* /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}/
				rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}/*
				cp ${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}_pPb2/* /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/${multMin[$i]}-${multMax[$i]}_${ptMin[$j]}-${ptMax[$j]}_${rapMin[$k]}-${rapMax[$k]}_${TrkptMin[$l]}-${TrkptMax[$l]}/
			done
		done
	done
done
