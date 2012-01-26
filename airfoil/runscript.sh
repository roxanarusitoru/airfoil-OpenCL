#!/bin/bash
for i in 4 8 16 32 64 128 258 512 1024 2048 
do
echo "Starting " $i
  make clean
  make all -e BLOCK_SIZE_0=$i -e BLOCK_SIZE_1=$i -e BLOCK_SIZE_2=$i -e BLOCK_SIZE_3=$i -e PART_SIZE_0=$i -e PART_SIZE_1=$i -e PART_SIZE_2=$i -e PART_SIZE_3=$i
./airfoil_opencl > ./outputs/output_allsize_$i.txt
  echo "Ending " $i
done
