all: non one eight simd cl

non: proj7-non-par.cpp
	g++ -o par-non -fopenmp proj7-non-par.cpp


one: proj7-par1.cpp
	g++ -o par1 -fopenmp proj7-par1.cpp

eight: proj7-par8.cpp
	g++ -o par8 -fopenmp proj7-par8.cpp

simd.p7.o:	simd.p7.h  simd.p7.cpp
			g++ -c  simd.p7.cpp -o simd.p7.o
simd: simd.p7.o
	g++ -o par-simd -fopenmp proj7-simd.cpp simd.p7.o

cl: 
	g++ -w -o par-cl proj7-opencl.cpp /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp

clean:
	rm -rf par1 par8 par-non par-simd par-cl *.o
