#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 9){

	unsigned long sum = 0;
	int k = value.length();

	for (int i=0; i < k; i++)
	{
		int x = value[i];
		sum += x * pow(a, k-(i+1));
	}

	return sum;
}

//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
	unsigned long bitwise_hash = 0;
	for (int i=0; i<value.length(); i++)
	{
		int  x = value[i];
		bitwise_hash ^= (bitwise_hash << 5) + (bitwise_hash >> 2) + x;
	}

	return bitwise_hash;
}

// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){

	return hash % size;
}

// multiplication addition and division compression. 
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){

	int x = (a*hash) + m;
	return abs(x) % size;
}
#endif

// you may write your own program to test these functions.
