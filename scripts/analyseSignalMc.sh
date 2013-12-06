#!/bin/bash

for Type in GI CI ; do
   for MassTag in `seq 500 50 3500` 500Fs01 500Fs05 1000Fs01 1000Fs05 1500Fs01 1500Fs05 2000Fs01 2000Fs05 2500Fs01 2500Fs05 3000Fs01 3000Fs05 ; do
   #for MassTag in `seq 500 50 3500` ; do
      if [ $MassTag == "500" -o $MassTag == "1000" ]; then
         continue
      elif [ $MassTag == "1500" -o $MassTag == "2000" ]; then
         continue
      elif [ $MassTag == "2500" -o $MassTag == "3000" ]; then
         continue
      fi

      inputFileName="/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_53X_20130207/int_signal/${Type}/qStar${Type}_M${MassTag}_53X-v2pre4_modIsoV000203_20130207.root"
      outputFileName="/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_53X_20130212/int_signal/${Type}/Qstar${Type}_M${MassTag}_20130424.root"
      outputLogFile="/opt/ppd/newscratch/williams/Datafiles/AnaTuples/bstdZeeAna_8TeV_53X_20130212/int_signal/${Type}/Qstar${Type}_M${MassTag}_20130424.log"

      if [ -f $inputFileName ]; then
         echo 
         echo " * Now doing cmsRun (at `date` )..."
         echo "    + input  = " $inputFileName
         echo "    + output = " $outputFileName
         BstdZeeFirstAnalyser --mc -i $inputFileName -o $outputFileName >& $outputLogFile
         if [ "$?" != "0" ] ; then
            echo
            echo "   *** ERROR : Non-zero exit code. Please see log file."
            echo 
         fi
      fi

   done
done
