LOCAL_SIZE=64
NUM_ELEMENTS=65536


default:
	g++ -w -DLOCAL_SIZE=${LOCAL_SIZE} -DNUM_ELEMENTS=${NUM_ELEMENTS} -o first first.cpp /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp

clean:
	rm -f first *.o
