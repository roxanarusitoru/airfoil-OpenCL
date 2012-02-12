#!/bin/bash

for i in {1..100..1}
do
  echo "try $i"
  ./airfoil_opencl > intel_noncoalescing_single$i.txt
done
