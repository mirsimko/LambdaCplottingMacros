#!/bin/bash

prodPath=/global/project/projectdirs/star/pwg/starhf/simkomir/LambdaC/histProd1

mkdir -p $prodPath
cp SubmitDrawMass.xml DrawMass.C $prodPath

pushd $prodPath >> /dev/null
if [ -e LocalLibraries.zip ]; then
  rm LocalLibraries.zip
fi

if [ -d LocalLibraries.package ]; then
  rm -rf LocalLibraries.package
fi 
star-submit SubmitDrawMass.xml
popd >> /dev/null
