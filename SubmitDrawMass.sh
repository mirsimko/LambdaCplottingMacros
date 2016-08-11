#!/bin/bash

prodPath=/global/project/projectdirs/star/pwg/starhf/simkomir/LambdaC/histProd2/

mkdir -p $prodPath
cp SubmitDrawMass.xml DrawMass.C $prodPath

pushd $prodPath >> /dev/null
if [ -e LocalLibraries.zip ]; then
  rm LocalLibraries.zip
fi

if [ -d LocalLibraries.package ]; then
  rm -rf LocalLibraries.package
fi 
star-submit-template -template SubmitDrawMass.xml -entities prodPath=$prodPath
popd >> /dev/null
