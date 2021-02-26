#include <bits/stdc++.h>
using namespace std;

/*
	p[i] is the length of the longest proper prefix of s[0..i]
	which is also a suffix of this string
	Run in O(|s|)
*/
vector<int> prefix_function(const string &s) {
	int n = s.size();
	vector<int> pi(n);
	for (int i = 1, j = 0; i < n; ++i) {
		while (j > 0 and s[i] != s[j]) j = pi[j-1];
		if (s[i] == s[j]) ++j;
		pi[i] = j;
	}
	return pi;
}

/*
	Returns a vector with the initial positions of 
	all occurrences of s in t
	Using O(|s|) memory
	Run in O(|s|+|t|)
*/
vector<int> kmp(const string &s, const string &t) {
	vector<int> p = prefix_function(s+'$'), match;
	for (int i = 0, j = 0; i < (int)t.size(); ++i) {
		while (j > 0 and s[j] != t[i]) j = p[j-1];
		if (s[j] == t[i]) ++j;
		if (j == (int)s.size()) match.push_back(i-j+1);
	}
	return match;
}

/*
	ans[i] is the amount of occurrences of the prefix s[0..i] in s
*/
vector<int> prefix_occurrences(const string &s) {
	vector<int> pi = prefix_function(s);
	int n = pi.size();
	vector<int> ans(n+1);
	for (int i = 0; i < n; i++)
	    ans[pi[i]]++;
	for (int i = n-1; i > 0; i--)
	    ans[pi[i-1]] += ans[i];
	for (int i = 0; i <= n; i++)
	    ans[i]++;
	return ans;
}

inline int getInt(char c) {
	return c-'a';
}

/*
	Run in O(26*|s|)
*/
struct autKMP {
	vector<vector<int>> nxt;
	autKMP (const string &s) : nxt(26, vector<int>(s.size()+1)) {
		vector<int> p = prefix_function(s);
		nxt[getId(d[0])][0] = 1;
		for (char c = 0; c < 26; ++c) {
			for (int i = 1; i <= (int)s.size(); ++i) {
				nxt[c][i] = (getId(s[i-1]) == c ? i+1 : nxt[c][p[i-1]]);
			}
		}
	}
};

/*
	Returns a vector with the initial positions of 
	all occurrences of s in t
	Run in O(|t|)
*/
vector<int> matching_aut(const string& s, const string& t) {
	auto aut = autKMP(s);
	vector<int> match;
	int at = 0;
	for (int i = 0; i < (int)t.size(); ++i) {
		at = aut.nxt[getId(t[i])][at];
		if (at == (int)s.size()) match.push_back(i-at+1);
	}
	return match;
}