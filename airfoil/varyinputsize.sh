
API=opencl
architecture=nvidia
precision=single
vector=1
async=async

filename=inputsize_${API}_${architecture}_${precision}_vector$vector.csv

rm $filename

#make clean
#make 


for iter in `seq 3`
do
  for size in 101250 198450 299538 399618 496008 602802 698562 801378 903168 1002528 
  do
    rm ./new_grid.dat
    ln -fs "./naca/new_grid_$size.dat" ./new_grid.dat
    echo -ne "$size, $iter, $API, $architecture, $precision, $vector, " | tee -a  $filename
    /usr/bin/time -f "elapsed: %e" ./airfoil_${API} 2>&1 | awk '$1=="elapsed:"{printf("%.4f, ",$2);}' | tee -a $filename
    echo -ne "$async"
    echo ""
  done
done
