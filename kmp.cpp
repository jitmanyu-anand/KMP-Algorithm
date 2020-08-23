/*
* @Author: jitmanyu
* @Date:   2020-08-23 10:52:04
* @Last Modified by:   jitmanyu
* @Last Modified time: 2020-08-23 21:03:58
*/
#include<bits/stdc++.h>
using namespace std;

vector<int> createAux(string s) {
	int n = s.length();

	// initialize each index with 0

	vector<int> aux(n, 0);

	// the value at first index is 0
	// so we start traversal from index 1
	int i = 1;

	// m can be viewed as the index of first mismatch
	int m = 0;

	while (i < n) {

		// if prefix = suffix till m-1
		if (s[i] == s[m]) {
			m++;
			aux[i] = m;
			i++;
		}
		
		// if prefix is not same as suffix till m-1
		// we will check the index of previous possible prefix
		else {

			// if m is not equal to zero
			// check for the pre
			if (m > 0) {
				// we do not increment i here
				m = aux[m - 1];
			} 
			// if m is equal to zero
			// there was no prefix equal to suffix
			// for index i
			else {

				// increment i here
				aux[i] = 0;
				i++;
			}
		}

	}

	return aux;

}



vector<int> matchingIndex(string text, string pat) {

	// array to store the indices of matching
	vector<int> matches;

	// get the aux array using the above function
	vector<int> aux = createAux(pat);

	int n = text.length();
	int m = pat.length();

	// pointer for text
	int i = 0;

	// pointer for pattern
	int j = 0;

	while (i < n) {

		// if mismatch
		if (text[i] != pat[j]) {

			// if we are on the first letter of the pattern
			if (j == 0) {
				i++;
			}
			// if we were on some position greater then zero
			else {
				// we use aux to check the prefix
				// and tell, from where to compare next
				// as the common part will match anyway
				j = aux[j - 1];
			}
		}
		// if matches
		else {
			// increment both pointers
			i++;
			j++;

			// if we found the pattern
			if (j == m) {
				// push the index of match
				// to the result array
				matches.push_back(i - m);
				// to find more patterns,
				// we can continue as if
				// no patterns were found at this point
				j = aux[j - 1];
			}
		}

	}

	return matches;
}

int main() {
	string text = "abcdabcdabfqab";
	string pat = "ab";

	for (int i : matchingIndex(text, pat)) {
		cout << "found at " << i << endl;
	}
}
