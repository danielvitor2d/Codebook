#include <bits/stdc++.h>
using namespace std;
typedef long long int i64;
const int maxn = 1e5+5;
struct SegmentTree {
	struct Node {
		i64 ans, pref, suff, sum;
		Node(i64 x = 0LL) { //0 if can take empty set, -linf if not
			ans = pref = suff = max(0LL, x);  // max(0, x) if can take empty set, x if not
			sum = x; //always x
		}
	};
	inline Node join(const Node& a, const Node& b) {
		Node ans;
		ans.pref = max(a.pref, a.sum + b.pref);
		ans.suff = max(a.suff + b.sum, b.suff);
		ans.sum = a.sum + b.sum;
		ans.ans = max(a.suff + b.pref, max(a.ans, b.ans));
		return ans;
	}
	int n;
	Node tree[4*maxn];
	Node neutral;
	void build(int node, int l, int r, int *v) {
		if (l == r) { tree[node] = Node(v[l]); return; }
		int mid = l+(r-l)/2, lc = (node << 1);
		build(lc, l, mid, v);
		build(lc+1, mid+1, r, v);
		tree[node] = join(tree[lc], tree[lc+1]);
	}
	void update(int node, int l, int r, int idx, int val) {
		if (l == r) { tree[node] = Node(val); return; }
		int mid = l+(r-l)/2, lc = (node << 1);
		if(idx <= mid) update(lc, l, mid, idx, val);
		else update(lc+1, mid+1, r, idx, val);
		tree[node] = join(tree[lc], tree[lc+1]);
	}
	Node query(int node, int l, int r, int ql, int qr) {
		if (r < l or qr < l or r < ql) return neutral;
		if (ql <= l and r <= qr) return tree[node];
		int mid = l+(r-l)/2, lc = (node << 1);
		return join(query(lc, l, mid, ql, min(qr, mid)), query(lc+1, mid+1, r, max(ql, mid+1), qr));
	}
	void build(int _n, int *v) {
		n = _n;
		build(1, 1, n, v);
	}
	i64 query(int l, int r) {
		return query(1, 1, n, l, r).ans;
	}
	void update(int idx, int val) {
		update(1, 1, n, idx, val);
	}
};