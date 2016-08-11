#!/bin/bash

# Make a list of root files in a directory
# author Miroslav Simko (msimko@bnl.gov)

# The structure must be dir/dayNumber/runNumber
# usage: ./makeList.sh <dir> <list location>
startDir=${1:-/global/project/projectdirs/star/pwg/starhf/simkomir/LambdaC/production/LambdaC.kPionKaonProton.picoHFtree/}
listDir=${2:-LambdaC.kPionKaonProton.picoHFtree}

if [ ! -d $startDir ]; then
  echo $startDir is not a directory
  exit
fi
# creating diretrories for the lists
echo creating directory \"$listDir\"
mkdir $listDir
mkdir $listDir/runs

list=$listDir/list_temp.list
echo Creating temporary list $list
touch $list 

# give reading permissions
chmod a+r $startDir
chmod a+x $startDir

for day in $( ls $startDir ); do
  # if day is a directory
  if [ -d $startDir/$day ]; then
    echo Running in $startDir/$day

    # give reading permissions
    chmod a+r $startDir/$day
    chmod a+x $startDir/$day

    for  run in $( ls $startDir/$day ); do
      # if run is a directory
      if [ -d $startDir/$day/$run ]; then

	# give reading permissions
	chmod a+r $startDir/$day/$run
	chmod a+x $startDir/$day/$run

	# list for the runs
	runList=$listDir'/runs/picoList_'$day'_'$run'.list'
	# put all root files in the list without double slashes
	ls $startDir/$day/$run/*.root | sed 's|//|/|g' > $runList
	cat $runList >> $list
	# grant permissions to the root files
	chmod a+r $startDir/$day/$run/*.root
      else
	echo $startDir/$day/$run is not a directory
      fi # run
    done # run
  else
    echo $startDir/$day is not a directory
  fi # day
done # day

# remove all double slashes
echo Copying to $listDir/listAll.list
sed 's|//|/|g' $list > $listDir/listAll.list
# delete temporary list
echo Removing temporary list $list
rm -f $list

echo Done
