#include <vector>
#include <numeric>

class DSU {
	int N;
	std::vector<int> link, sz;
public:
	int id(int x) { return link[x] = (link[x] == x ? x : id(link[x])); }
	int same(int x, int y) { return (id(x) == id(y)); }
	void unite(int x, int y) {
		x = id(x); y = id(y);
		if (x == y) return;
		if (sz[x] < sz[y]) std::swap(x,y);
		link[y] = x;
		sz[x] += sz[y];
	}
	int size(int x) { return sz[id(x)]; }
	DSU (int n) : N(n) {
		sz.assign(N+1, 1);
		link.resize(N+1);
		iota(link.begin(), link.end(), 0);
	}
};
