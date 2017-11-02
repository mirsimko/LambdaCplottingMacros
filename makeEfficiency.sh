#!/bin/bash

for cent in $( seq 0 8 ); do
  echo centrality $cent
  root -b -q -l efficiency.C'+('$cent')'
done
