#!/bin/bash

#mode='GI'
#masses=`seq 1500 100 3000`
mode='CI'
masses=`seq 2400 50 3200`

for mass in $masses; do
  echo "Creating generator file: python/Qstar${mode}ToQZ_M_${mass}_8TeV_pythia6_cff.py"
  sed "s/.*PMAS.343.*/            'PMAS\(343,1\) = $mass  \!mass of d*',/" python/Qstar${mode}ToQZ_M_XXXX_8TeV_pythia6_cff.py \
    | sed "s/.*PMAS.344.*/            'PMAS\(344,1\) = $mass  \!mass of u*',/" \
    | sed "s/.*RTCM.41.*/            'RTCM\(41\)    = $mass  \!Lambda = mass ',/" \
    > python/Qstar${mode}ToQZ_M_${mass}_8TeV_pythia6_cff.py 
done

echo; echo
scram b 

for mass in $masses; do
  echo; echo; echo "-> Calculating cross section at mass $mass"
  cmsDriver.py TSWilliams/BstdZeeAnalyser/python/Qstar${mode}ToQZ_M_${mass}_8TeV_pythia6_cff.py -s GEN --conditions auto:mc --datatier 'GEN-SIM-RAW' --eventcontent RAWSIM --fileout /opt/ppd/newscratch/williams/tmp.root -n 10000 \
    2>&1 | grep "All included subprocesses"
done

