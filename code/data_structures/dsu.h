#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;

namespace DSU {
	int n, link[maxn], sz[maxn];
	inline void init(int _n) {
		n = _n;
		for (int i = 0; i <= n; ++i) {
			link[i] = i;
			sz[i] = 1;
		}		
	}
	int id(int x) { return link[x] = (link[x] == x ? x : id(link[x])); }
	int same(int x, int y) { return (id(x) == id(y)); }
	void unite(int x, int y) {
		x = id(x); y = id(y);
		if (x == y) return;
		if (sz[x] < sz[y]) swap(x,y);
		link[y] = x;
		sz[x] += sz[y];
	}
	int size(int x) { return sz[id(x)]; }
};
