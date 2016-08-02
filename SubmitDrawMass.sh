#!/bin/bash

prodPath=/global/project/projectdirs/star/pwg/starhf/simkomir/LambdaC/histProd1


mkdir -d $prodPath
cp SubmitDrawMass.xml DrawMass.C $prodPath

pushd $prodPath >> /dev/null
star-submit SubmitDrawMass.xml
popd >> /dev/null
