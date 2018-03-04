#include <numeric>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

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



position GetLongestLength( vector<int>& A, position _pos, int _value )
{
	int sum = 0;
	while( _pos >= 0 )
	{
		sum += A[ _pos ];

		if( sum < _value )
		{
			_pos++;
			break;
		}

		_pos--;
	}

	if( _pos < 0 ) _pos = 0;

	return _pos;
}
// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solutionB( vector<int> &A )
{
	int maxLength = 0;
	int curLength = 0;

	int negativeIndex = -1;
	int positiveIndex = -1;

	vector<int> vecNegativePos;
	vector<int> vecPositivePos;
	vecNegativePos.reserve( A.size() );
	vecPositivePos.reserve( A.size() );

	auto IncreaseLen = [ &maxLength, &curLength ]()
	{
		maxLength = max( maxLength, ++curLength );
	};

	for( int i = 0; i < ( int ) A.size(); ++i )
	{
		switch( A[ i ] )
		{
		case -1:
			if( !vecPositivePos.empty() )
			{
				vecPositivePos.pop_back();
				IncreaseLen();
			}
			else
			{
				vecNegativePos.push_back( i );
				curLength = 0;
			}
			break;

		case 0:
			// 순열 길이만 증가, 
			IncreaseLen();
			break;

		case 1:
			// A[i] 가 가장 우측에 위치한 부분 순열중 가장 긴 non-negative sum 
			// 
			if( !vecNegativePos.empty() )
			{
				vecNegativePos.pop_back();
				if( vecNegativePos.empty() )
					curLength = i - 0 + 1;
				else
					curLength = i - ( vecNegativePos.back() + 1 ) + 1;
				maxLength = max( maxLength, curLength );
			}
			else
			{
				vecPositivePos.push_back( i );
				IncreaseLen();
			}
			break;
		}

	}

	return maxLength;
}



int solutionC( vector<int> &A )
{
	int maxLength = 0;
	int curLength = 0;

	int negativeIndex = -1;
	int positiveIndex = -1;

	vector<int> vecNegativePos;
	vector<int> vecPositivePos;
	vecNegativePos.reserve( A.size() );
	vecPositivePos.reserve( A.size() );

	auto IncreaseLen = [ &maxLength, &curLength ]()
	{
		maxLength = max( maxLength, ++curLength );
	};

	for( int i = 0; i < ( int ) A.size(); ++i )
	{
		switch( A[ i ] )
		{
		case -1:
			if( positiveIndex >= 0 )
			{
				positiveIndex--;
				IncreaseLen();
			}
			else
			{
				vecNegativePos.push_back( i );
				negativeIndex++;
				curLength = 0;
			}
			break;

		case 0:
			// 순열 길이만 증가, 
			IncreaseLen();
			break;

		case 1:
			// A[i] 가 가장 우측에 위치한 부분 순열중 가장 긴 non-negative sum 
			// 
			if( negativeIndex >= 0 )
			{
				negativeIndex--;
				if( negativeIndex < 0 )
					curLength = i;
				else
					curLength = i - vecNegativePos[ negativeIndex ];
				maxLength = max( maxLength, ++curLength );
			}
			else
			{
				vecPositivePos.push_back( i );
				positiveIndex++;
				IncreaseLen();
			}
			break;
		}

	}

	return maxLength;
}


int solution( vector<int> &A )
{

	int maxLength = 0;
	int sum = 0;

	vector<int> vecSum;
	vecSum.reserve( A.size() );

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

		else
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

	vector<int> temp3 = { -1,-1,1,-1,1,0,1,-1,-1 };

	temp3.back();
	temp3.back();
	temp3.back();
	temp3.back();
	temp3.back();

	solutionB( temp3 );
};