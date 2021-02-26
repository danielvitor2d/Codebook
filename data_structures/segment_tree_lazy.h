#include <bits/stdc++.h>
using namespace std;

typedef long long int i64;
typedef vector<i64> vi64;
typedef long long ftype;

const int maxn = 1e5+5;

namespace SegmentTree {

	struct Node {
		ftype val;
		Node(ftype x) : val(x) {}
		Node () : val(0LL) {}
	};

	inline Node join(const Node &a, const Node &b) {
		return Node(a.val + b.val);
	}

	int n;
	ftype lazy[4*maxn];
	Node tree[4*maxn];
	Node neutral;
	ftype lazyNeutral = -1LL;

	inline void upLazy(int node, int l, int r) {
		if (lazy[node] == lazyNeutral) return;

		tree[node].val += lazy[node] * (r - l + 1LL); //To increment value
		// tree[node].val = lazy[node] * (r - l + 1LL);  //To set value

		if (l != r) {
			int lc = (node << 1);
			// lazy[lc] = lazy[node];     //To set value
			// lazy[lc+1] = lazy[node];   //To set value
			lazy[lc] = (lazy[lc] == lazyNeutral ? lazy[node] : lazy[lc] + lazy[node]);        //To increment value
			lazy[lc+1] = (lazy[lc+1] == lazyNeutral ? lazy[node] : lazy[lc+1] + lazy[node]);  //To increment value
		}

		lazy[node] = lazyNeutral;
	}

	void build(int node, int l, int r, int *v) {
		lazy[node] = lazyNeutral;
		if (l == r) { tree[node].val = v[l]; return; }
		int mid = l+(r-l)/2, lc = (node << 1);
		build(lc, l, mid, v);
		build(lc+1, mid+1, r, v);
		tree[node] = join(tree[lc], tree[lc+1]);
	}

	void update(int node, int l, int r, int ul, int ur, ftype val) {
		upLazy(node, l, r);
		if (r < l or ur < ul or ur < l or r < ul) return;
		if (ul <= l and r <= ur) {
			// lazy[node] = val; // To set value
			lazy[node] = (lazy[node] == lazyNeutral ? val : lazy[node] + val); //To increment value
			upLazy(node, l, r);
			return;
		}
		int mid = l+(r-l)/2, lc = (node << 1);
		update(lc, l, mid, ul, min(mid, ur), val);
		update(lc+1, mid+1, r, max(mid+1, ul), ur, val);
		tree[node] = join(tree[lc], tree[lc+1]);
	}

	Node query(int node, int l, int r, int ql, int qr) {
		upLazy(node, l, r);
		if (r < l or qr < ql or qr < l or r < ql) return neutral;
		if (ql <= l and r <= qr) return tree[node];
		int mid = l+(r-l)/2, lc = (node << 1);
		return join(query(lc, l, mid, ql, min(mid, qr)), query(lc+1, mid+1, r, max(mid+1, ql), qr));
	}

	void build(int _n, int *v) {
		n = _n;
		build(1, 1, n, v);
	}

	ftype query(int l, int r) {
		return query(1, 1, n, l, r).val;
	}

	void update(int l, int r, ftype val) {
		update(1, 1, n, l, r, val);
	}
};
