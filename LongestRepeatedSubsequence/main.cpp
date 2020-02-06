//https://www.techiedelight.com/longest-repeated-subsequence-problem/
//#include <iostream>
//#include <string>
//#include <algorithm>
//using namespace std;

//// Function to find the length of Longest repeated Subsequence
//// of substring X[0..m-1] and X[0..n-1]
//int LRSLength(string X, int m, int n)
//{
//	// return if we have reached the end of either string
//	if (m == 0 || n == 0)
//		return 0;
//
//	// if characters at index m and n matches and index is different
//	if (X[m - 1] == X[n - 1] && m != n)
//		return LRSLength(X, m - 1, n - 1) + 1;
//
//	// else if characters at index m and n don't match
//	return max (LRSLength(X, m, n - 1), LRSLength(X, m - 1, n));
//}
//
//// Longest Repeated Subsequence Problem
//int main()
//{
//	string X = "ATACTCGGA";
//	int m = X.length();
//
//	cout << "Length of Longest Repeating Subsequence is " <<
//			LRSLength(X, m, m);
//
//	return 0;
//}

//#include <iostream>
//#include <string>
//#include <algorithm>
//#include <unordered_map>
//using namespace std;
//
//// Function to find the length of Longest repeated Subsequence
//// of substring X[0..m-1] and X[0..n-1]
//int LRSLength(string X, int m, int n, auto &lookup)
//{
//	// return if we have reached the end of either string
//	if (m == 0 || n == 0)
//		return 0;
//
//	// construct an unique map key from dynamic elements of the input
//	string key = to_string(m) + "|" + to_string(n);
//
//	// if sub-problem is seen for the first time, solve it and
//	// store its result in a map
//	if (lookup.find(key) == lookup.end())
//	{
//		// if characters at index m and n matches and index is different
//		if (X[m - 1] == X[n - 1] && m != n)
//			lookup[key] = LRSLength(X, m - 1, n - 1, lookup) + 1;
//
//		else
//
//		// else if characters at index m and n don't match
//		lookup[key] = max (LRSLength(X, m, n - 1, lookup),
//						LRSLength(X, m - 1, n, lookup));
//	}
//
//	// return the subproblem solution from the map
//	return lookup[key];
//}
//
//// Longest Repeated Subsequence Problem
//int main()
//{
//	string X = "ATACTCGGA";
//	int m = X.length();
//
//	// create a map to store solutions of subproblems
//	unordered_map<string, int> lookup;
//
//	cout << "Length of Longest Repeating Subsequence is " <<
//			LRSLength(X, m, m, lookup);
//
//	return 0;
//}

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Function to find the length of Longest repeated Subsequence
// of substring X[0..n-1]
int LRSLength(string X, int n)
{
	// lookup table stores solution to already computed sub-problems

	// i.e. lookup[i][j] stores the length of LRS of substring
	// X[0..i-1] and X[0..j-1]
	int lookup[n + 1][n + 1];

	// first column of the lookup table will be all 0
	for (int i = 0; i <= n; i++)
		lookup[i][0] = 0;

	// first row of the lookup table will be all 0
	for (int j = 0; j <= n; j++)
		lookup[0][j] = 0;

	// fill the lookup table in bottom-up manner
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
	 
			// if characters at index i and j matches
			// and the index is different
			if (X[i - 1] == X[j - 1] && i != j)
				lookup[i][j] = lookup[i - 1][j - 1] + 1;

			// else if characters at index i and j are different
			else
				lookup[i][j] = max(lookup[i - 1][j], lookup[i][j - 1]);
	 
		}
	}

	// LRS will be last entry in the lookup table
	return lookup[n][n];
}

// Longest Repeated Subsequence Problem
int main()
{
	//string X = "ATACTCGGA";
	
	

	int n = X.length();

	cout << "Length of Longest Repeating Subsequence is " <<
			LRSLength(X, n);

	return 0;
}
