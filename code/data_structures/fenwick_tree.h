#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;

namespace FenwickTree {

	int tree[maxn], a[maxn];
	int n;

	void build(int _n) {
		n = _n;
		for (int i = 0; i < maxn; ++i) {
			tree[i] = 0;
		}
	}

	void updateI(int idx, int x) {   //increment a[idx] by x
		a[idx] = x;
		for (; idx <= n; idx += (idx & -idx)) {
			tree[idx] += x;
		}
	}

	void updateS(int idx, int x) {   //set a[idx] = x
		int delta = x - a[idx];
		a[idx] = x;
		for (; idx <= n; idx += (idx & -idx)) {
			tree[idx] += delta;
		}
	}

	int query(int idx) {            //return sum of a[1..idx]
		int rs = 0;
		for (; idx > 0; idx -= (idx & -idx)) {
			rs += tree[idx];
		}
		return rs;
	}

	int query(int l, int r) {       //return sum of a[l..r]
		return query(r) - query(l - 1);
	}

};