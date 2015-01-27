/************************************************************************************************************
**Program: CS 161 Assignment 1
**Author: Taylor Fahlman
**Date Due: 01/18/2013
**Description: Prints hex,dec and oct versions of the max and min longs, int and shorts, signed and unsigned
**Input: None
**Output: In addition to printing hex.dec and oct values of max and min long,ints and shorts, also adds and 
**subtracts one from mins and maxes. 
*************************************************************************************************************/

#include<iostream>
#include<climits>
#include<cmath>
using std::cout;
using std::endl;
using std::hex;
using std::oct;
using std::dec;

int main()
{
	int si_max = INT_MAX;
	int si_min = INT_MIN;
	unsigned int ui_max = UINT_MAX;
	short ss_max = SHRT_MAX;
	short ss_min = SHRT_MIN;
	unsigned short us_max = USHRT_MAX;
	long sl_max = LONG_MAX;
	long sl_min = LONG_MIN;
	unsigned long ul_max = ULONG_MAX;

	cout << "Decimal: " << dec << si_max << " Hexidecimal: " << hex << si_max << " Octal: " << oct << si_max << endl;
	cout << "Decimal: " << dec << si_min << " Hexidecimal: " << hex << si_min << " Octal: " << oct << si_min << endl;
	cout << "Decimal: " << dec << ui_max << " Hexidecimal: " << hex << ui_max << " Octal: " << oct << ui_max << endl;
	cout << "Decimal: " << dec << ss_max << " Hexidecimal: " << hex << ss_max << " Octal: " << oct << ss_max << endl;
	cout << "Deciaml: " << dec << ss_min << " Hexidecimal: " << hex << ss_min << " Octal: " << oct << ss_min << endl;
	cout << "Decimal: " << dec << us_max << " Hexidecimal: " << hex << us_max << " Octal: " << oct << us_max << endl;
	cout << "Decimal: " << dec << sl_max << " Hexidecimal: " << hex << sl_max << " Octal: " << oct << sl_max << endl;
	cout << "Decimal: " << dec << sl_min << " Hexidecimal: " << hex << sl_min << " Octal: " << oct << sl_min << endl;
	cout << "Decimal: " << dec << ul_max << " Hexidecimal: " << hex << ul_max << " Octal: " << oct << ul_max << endl;
	
	cout << "Signed int max plus one " << (si_max++) << endl;
	cout << "Signed int min minus one " << (si_min--) << endl;
	cout << "Unsigned int max plus one " << (ui_max++)<< endl;
	cout << "Signed short max plus one " << (ss_max++) << endl;
	cout << "Signed short min minus one " << (ss_min--) << endl;
	cout << "Unsigned short max plus one " << (us_max++) << endl;
	cout << "Signed long max plus one " << (sl_max++) << endl;
	cout << "Signed long min minus one " << (sl_min--) << endl;
	cout << "Unsigned long max plus one " << (ul_max++) << endl;

	cout << "Signed int max by powers is " << dec << (unsigned int) pow(2, sizeof(int) * 8 - 1) - 1 << endl;
	cout << "Signed int min by powers is " << dec << (unsigned int) pow(2, sizeof(int) * 8 - 1) << endl; 
	cout << "Unsigned int max by powers is " << dec << (unsigned int) pow(2, sizeof(int)*8) - 1 << endl;
	cout << "Signed short max by powers is " << dec << (unsigned short)pow(2, sizeof(short) * 8 - 1) - 1<< endl;
	cout << "Signed short min by powers is " << dec << (unsigned short) pow(2, sizeof(short) * 8 -1) << end;
	cout << "Unsigned short max by powers is " << dec << (unsigned short) pow(2, sizeof(short) * 8) - 1 << endl;
	cout << "Signed long max by powers is " << dec << (unsigned long) pow(2, sizeof(long) * 8 - 1) -1 << endl;
	cout << "Signed long min by powers is " << dec << (unsigned long) pow(2, sizeof(long) * 8 - 1) << endl;
	cout << "Unsigned long max by powers is " << dec << (unsigned long) pow(2, sizeof(long) * 8) - 1 << endl;

	return 0;
}
