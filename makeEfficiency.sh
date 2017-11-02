#!/bin/bash

for cent in $( seq 0 8 ); do
  echo centrality $cent
  root efficiency.C'+('$cent')'
done
