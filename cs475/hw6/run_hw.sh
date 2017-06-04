#! /bin/bash

localSizes=(32 64 128 256)
globalSizes=(1 2 3 4 5 6 7 8)

for i in ${globalSizes[@]}; do
    for j in ${localSizes[@]}; do
        make -s LOCAL_SIZE=$j NUM_ELEMENTS=$((1024*1024*${i}))
        ./first | tee -a data/multred-${i}.tmp
    done
    column -t data/multred-${i}.tmp > data/multred-${i}.dat
    rm data/multred-${i}.tmp
done
