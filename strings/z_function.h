#include <bits/stdc++.h>
using namespace std;

/*
	z[i] is the length of the largest common prefix 
	between s[0..n-1] and s[i..n-1]
*/
vector<int> z_function(const string &s) {
	int n = (int)s.size();
	vector<int> z(n);
	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n and s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}
