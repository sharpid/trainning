#include <numeric>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


typedef int position;

template<typename T>
inline T abs( const T& _v )
{
	return _v >= 0 ? _v : -_v;
}

inline position LongestNonNegativePos( const int sumv, vector<int>& vecSum, int &lastSum )
{
	int sum = sumv;

	if( sum >= 0 )
	{
		lastSum = sum;
		return 0;
	}

	int i = 0;
	int vecSize = vecSum.size();

	while( 1 )
	{
		i += abs( sum );

		if( i < vecSize )
		{
			sum = sumv - vecSum.at( i - 1 );

			if( sum >= 0 )
			{
				lastSum = sum;
				return i;
			}
		}
		else
		{
			lastSum = 0;
			return -1;
		}

	}

	lastSum = 0;
	return -1;
}



int solution( vector<int> &A )
{

	int maxLength = 0;
	int sum = 0;

	vector<int> vecSum;

	vector<int> vecNegativePos;
	vecSum.reserve( A.size() );
	vecNegativePos.reserve( A.size() );

	int lastLength = 0;
	int lastPos = -1;
	int lastSum = 0;

	for( int i = 0; i < ( int ) A.size(); ++i )
	{
		auto value = A[ i ];

		sum += value;
		vecSum.push_back( sum );

		if( value == 0 && lastLength > 0 )
		{
			lastLength++;
			if( lastLength >= maxLength )
				maxLength = lastLength;
		}
		else if( value == 1 && lastLength > 0 )
		{
			// lastPos Moving
			lastPos = GetLongestLength( A, lastPos, -1 );

			lastLength = i - lastPos + 1;

			if( lastLength >= maxLength )
				maxLength = lastLength;
		}
		else// if ( value == -1)
		{

			lastPos = LongestNonNegativePos( sum, vecSum, lastSum );

			if( lastPos >= 0 )
			{
				lastLength = i - lastPos + 1;

				if( lastLength >= maxLength )
					maxLength = lastLength;
			}
			else
			{
				lastLength = 0;
				lastPos = -1;
			}
		}
	}


	return maxLength;
}


int main()
{
	vector<int> temp;

	//temp = { 0,0,0,0,0 };

	//for( int i = 0; i < 100000; i++ )
	//{
	//	temp.push_back( rand() % 3 - 1 );
	//	//temp.push_back( i% 3 -1 );
	//}
	//solution( temp );

	//solution( temp );

	//vector<int> temp2 = { -1, -1, 0, 0, 1, 1, -1, -1, 0, 1, 1, 1, 1 };
	//solution( temp2 );

	//vector<int> temp3 = { 1, 1, -1, -1, -1, -1, -1, 1, 1 };
	//solution( temp3 );

	vector<int> temp3 = { 0, -1, 0, 0, 1, 0, -1, -1 };
	solution( temp3 );
};