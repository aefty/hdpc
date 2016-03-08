#!/bin/sh
echo "RUNNING TESTING"

METHOD='hdmr'
PROCESSPERGROUP=1
DIM=3
SGLEVEL=$2
GRIDTYPE=$1
HDMRmaxOrder=2
HDMRcutOff=0.1

echo 'mpirun -n' 4 './main' $METHOD $PROCESSPERGROUP $DIM $SGLEVEL $GRIDTYPE $HDMRmaxOrder $HDMRcutOff
#make clean
#make

mpirun -n 2 ./main $METHOD $PROCESSPERGROUP $DIM $SGLEVEL $GRIDTYPE $HDMRmaxOrder $HDMRcutOff
