#include <iostream>
using std::cout;

#define NUM_BITS_IN_BYTE 8

int main()
{
	cout <<"A char take up " <<(sizeof(char) * NUM_BITS_IN_BYTE)<<" bytes of memory \n";
	cout <<"An int takes up "<<(sizeof(int) * NUM_BITS_IN_BYTE)<<" bytes of memory \n";
        cout <<"A float takes up " <<(sizeof(float) * NUM_BITS_IN_BYTE)<<" bytes of memory \n";
	cout <<"A long takes up " <<(sizeof(long) * NUM_BITS_IN_BYTE) <<" bytes of memory \n";
	cout <<"A short takes up " <<(sizeof(short) * NUM_BITS_IN_BYTE) <<" bytes of memory \n";
	cout <<"A double takes up " <<(sizeof(double) * NUM_BITS_IN_BYTE) <<" bytes of memory \n";;
	cout <<"A bool takes up " <<(sizeof(bool) * NUM_BITS_IN_BYTE) <<" bytes of memory \n";
	return 0;
}

