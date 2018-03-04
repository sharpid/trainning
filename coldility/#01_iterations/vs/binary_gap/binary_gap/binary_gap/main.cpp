// you can use includes, for example:
#include <algorithm>
#include <iostream>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
#define BIT(X) ( 1<< (X))
const int BYTE_SIZE = 8;

int solution( int N )
{
	int maxGap = 0;
	int temp = 0;
	bool isStart = false;

	for( unsigned int i = 0; i < sizeof( N ) * BYTE_SIZE; ++i )
	{
		if( N & BIT( i ) )
		{
			isStart = true;
			if( temp > maxGap )
				maxGap = temp;

			temp = 0;
		}
		else
		{
			if( isStart )
				temp++;
		}
	}

	return maxGap;
}

int main()
{
	std::cout << solution( 6 ) << std:: endl;

}