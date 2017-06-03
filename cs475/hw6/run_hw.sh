#! /bin/bash

localSizes=(1 2 4 8 16 32 64 128 256 512)
globalSizes=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)

for i in ${globalSizes[@]}; do
    for j in ${localSizes[@]}; do
        make -s LOCAL_SIZE=$j NUM_ELEMENTS=$((1024*1024*${i}))
        ./first | tee -a data/mult-${i}.tmp
    done
    column -t data/mult-${i}.tmp > data/mult-${i}.dat
    rm data/mult-${i}.tmp
done
