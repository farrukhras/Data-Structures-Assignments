#include <iostream>
#include <cmath>
using namespace std;

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

unsigned long bitHash(std::string value){
	unsigned long bitwise_hash = 0;
	for (int i=0; i<value.length(); i++)
	{
		int  x = value[i];
		bitwise_hash ^= (bitwise_hash << 5) + (bitwise_hash >> 2) + x;
	}

	return bitwise_hash;
}

int main()
{
    unsigned long hash_code = bitHash("random");
    cout<<hash_code<<endl;

    cout<<"Bitwise: "<<hash_code % 20;

    int y = 1637* hash_code + 1993;

    unsigned long x = abs(y);
    cout<< x % 20;
    return 0;
}
