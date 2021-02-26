#include <bits/stdc++.h>
using namespace std;

int lis(vector<int> &aux) {
	vector<int> d;
	for (int &x : aux) {
		auto it = upper_bound(d.begin(), d.end(), x); //for repeated values
		//auto it = lower_bound(d.begin(), d.end(), x); //for non repeated values
		if (it == d.end()) d.pb(x);
		else *it = x;
	}
	return (int)d.size();
}