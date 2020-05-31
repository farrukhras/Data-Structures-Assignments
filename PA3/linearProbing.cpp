#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"


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
    for (int i = 0; i<tableSize; i++)
    {
    	delete hashTable[i];
    }
}

unsigned long HashL :: hash(string value){
	unsigned long x = bitHash(value);
	return madCompression(x, tableSize);
}

void HashL::resizeTable(){
	int old_tablesize = tableSize;

	block** oldhashtable = hashTable;

	tableSize = tableSize*2;
	hashTable = new block*[tableSize];

	for (int i = 0; i < tableSize; i++)
	{
		hashTable[i] = NULL;
	}

	for (int i = 0; i<old_tablesize; i++)
	{
		if (oldhashtable[i] != NULL)
		{	
			insert(oldhashtable[i]->value);
		}	
	}
	delete [] oldhashtable;
}

void HashL::insert(string value){
	unsigned long index = hash(value);
	double load_factor = double(count)/double(tableSize);

	if (load_factor > 0.2)
	{
		resizeTable();
	}

	block* temp = new block(index, value);

	for (int i =0; i!=tableSize; i++)
	{
		if (hashTable[index] != NULL && hashTable[index]->key != -1)
		{
			index = (index+1) % tableSize;
		}
		else
		{
			hashTable[index] = temp;
			count++;
			return;
		}
	}
	delete temp;
}  

void HashL::deleteWord(string value){
	unsigned long index = hash(value);

	block* temp = lookup(value);

	if (temp != NULL)
	{
		temp->key = -1;
		temp->value = "-1";
	}
}

block* HashL::lookup(string value){
	unsigned long index = hash(value);

	while (hashTable[index] != NULL)
	{	
		if (index >= tableSize)
		{
			index = 0;
		}

		if (hashTable[index]->value == value)
		{
			return hashTable[index];
		}
		
		index++;
	}

	return NULL;

}
#endif
