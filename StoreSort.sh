#!/bin/bash

multMin=("110")
multMax=("1500")
#multMin=("40" "100" "200" "300")
#multMax=("100" "200" "300" "1500")
ptMin=("0" "4" "6" "10")
ptMax=("4" "6" "10" "30")
rapMin=("-24")
rapMax=("24")
TrkptMin=("1")
TrkptMax=("3")
version="v1"

#rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp1/
#rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/
#rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/Sort_OniaTree_pPb1_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_*.root
#rm /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/Sort_OniaTree_pPb2_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_*.root

for((i=0; i<"${#multMin[@]}"; i++))
do
	for((j=0; j<"${#ptMin[@]}"; j++))
	do
		for((k=0; k<"${#rapMin[@]}"; k++))
		do
			for((l=0; l<"${#TrkptMin[@]}"; l++))
			do
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
#	cp Sort_OniaTree_Pbp2_PADoubleMuon_$i.root /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultPbp2/Sort_OniaTree_Pbp2_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_$i.root
#	cp Sort_OniaTree_pPb1_PADoubleMuon_$i.root /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb1/Sort_OniaTree_pPb1_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_$i.root
#	cp Sort_OniaTree_pPb2_PADoubleMuon_$i.root /xrootd/store/user/kilee/pPb_8TeV_OniaTrkTree/resultpPb2/Sort_OniaTree_pPb2_PADoubleMuon_RD_Mult_$multMin-$multMax\_pt_$ptMin-$ptMax\_rap_$rapMin-$rapMax\_Trkpt_$TrkptMin-$TrkptMax\_$version\_$i.root
#done
