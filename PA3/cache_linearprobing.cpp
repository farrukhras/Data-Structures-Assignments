#ifndef CACHE_LINEARPROBING_CPP
#define CACHE_LINEARPROBING_CPP

#include "cache_linearprobing.h"
#include "hashfunctions.cpp"
#include <sstream>


string convert_to_string(unsigned long key)
{
	ostringstream string_converted ;
	string_converted << key ;
	string new_key = string_converted.str() ;
	return new_key ;
}

HashL::HashL(){
    tableSize = 1000; // you cant change this
    count = 0;
    hashTable = new block*[tableSize];

    for (int i =0; i<tableSize; i++)
    {
    	hashTable[i] = NULL;
    }
}

HashL::~HashL(){
    /*for (int i = 0; i<tableSize; i++)
    {
    	delete hashTable[i];
    }*/
}

unsigned long HashL :: hash(string value){
	unsigned long x = bitHash(value);
	return madCompression(x, tableSize);
}

void HashL::insert(unsigned long key, string value)
{
    if (count == tableSize)
    {
        string new_key = convert_to_string(key);
        unsigned long index = hash(new_key);
        unsigned min_index = index;
        int freq = hashTable[0]->frequency;
        for (int i = 0; i < tableSize; i++)
        {
            if (hashTable[i]->frequency < freq)
            {
                freq = hashTable[i]->frequency;
                min_index = i;
            }
        }
        hashTable[min_index] = NULL;
        hashTable[min_index] = new block(key , value);
        return;
    }

    string new_key = convert_to_string(key);
    unsigned long index = hash(new_key);

	for (int i =0; i!=tableSize; i++)
	{
		if (hashTable[index] != NULL)
		{
			index++;
			index = index % tableSize;
		}
		else
		{
			hashTable[index] = new block(key , value);
			count++;
			return;
		}
	}
}

block* HashL::lookup(unsigned long key){
	string new_key = convert_to_string(key);
    unsigned long index = hash(new_key);

    int counter = 0;

	while (hashTable[index] != NULL)
	{
		if(counter++ > count)
            return NULL;

		if (hashTable[index]->key == key)
		{
			hashTable[index]->frequency = hashTable[index]->frequency + 1 ;
            return hashTable[index];
		}

		index++;
		index = index % tableSize;
	}

	return NULL;
}

#endif
