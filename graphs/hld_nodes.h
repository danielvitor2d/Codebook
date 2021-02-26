#include <bits/stdc++.h>
using namespace std;
using i64 = long long int;
using vi64 = vector<i64>;

const int maxn = 1e5+5;

namespace SegmentTree {

	struct Node {
		i64 val;
		Node(i64 x) : val(x) {}
		Node () : val(0LL) {}
	};

	inline Node join(const Node &a, const Node &b) {
		return Node(a.val + b.val);
	}

	int n;
	i64 lazy[4*maxn];
	Node tree[4*maxn];
	Node neutral;
	i64 lazyNeutral = -1LL;

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

	void update(int node, int l, int r, int ul, int ur, i64 val) {
		upLazy(node, l, r);
		if (r < l or ur < ul or ur < l or r < ul) return;
		if (ul <= l and r <= ur) {
			// lazy[node] = val; // To set value
			lazy[node] = (lazy[node] == lazyNeutral ? val : lazy[node] + val); // To increment value
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

	i64 query(int l, int r) {
		return query(1, 1, n, l, r).val;
	}

	void update(int l, int r, i64 val) {
		update(1, 1, n, l, r, val);
	}
};


namespace HLD {
	struct edge {
		int a; i64 w;
		edge () {}
		edge (int to, i64 ww) : a(to), w(ww) {}
	};

	vector<edge> gr[maxn];
	int pos[maxn], st[maxn], pai[maxn];
	int h[maxn], v[maxn], val[maxn], timer;
	int deep[maxn], hei[maxn];

	inline void addEdge(int a, int b, i64 w = 1LL) {
		gr[a].push_back(edge(b, w));
	}

 	//O(n)
	void dfs(int u, int p = -1) {
		st[u] = 1;
		for (auto &e : gr[u]) if (e.a != p) {
			pai[e.a] = u;
			deep[e.a] = deep[u] + 1;
			hei[e.a] = hei[u] + e.w;
			dfs(e.a, u);
			st[u] += st[e.a];
			if (st[e.a] > st[gr[u][0].a] or gr[u][0].a == p) swap(e, gr[u][0]);
		}
	}

	//O(n)
	void build_hld(int u, int p = -1) {
		pos[u] = ++timer;
		v[pos[u]] = val[u];
		for (auto e : gr[u]) if (e.a != p) {
			h[e.a] = (e.a == gr[u][0].a ? h[u] : e.a);
			build_hld(e.a, u);
		}
	}

	void build(int root = 0) {
		timer = 0;
		h[root] = 0;
		hei[root] = 0;
		deep[root] = 0;
		dfs(root);
		build_hld(root);
		SegmentTree::build(timer, v);
	}

	//O(log^2 (n))
	i64 query_path(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		if (h[a] == h[b]) return SegmentTree::query(pos[b], pos[a]);
		return SegmentTree::query(pos[h[a]], pos[a]) + query_path(pai[h[a]], b);
	}
	
	//O(log^2 (n))
	void update_path(int a, int b, i64 x) {
		if (pos[a] < pos[b]) swap(a, b);
		if (h[a] == h[b]) return (void) SegmentTree::update(pos[b], pos[a], x);
		SegmentTree::update(pos[h[a]], pos[a], x);
		update_path(pai[h[a]], b, x);
	}

	//O(log(n))
	inline i64 query_subtree(int a) {
		return SegmentTree::query(pos[a], pos[a]+st[a]-1);
	}

	//O(log(n))
	inline void update_subtree(int a, i64 x) {
		SegmentTree::update(pos[a], pos[a]+st[a]-1, x);
	}

	//O(log(n))
	int lca(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		return (h[a] == h[b] ? b : lca(pai[h[a]], b));
	}

	//O(log(n))
	i64 distw(int a, int b) {
		return hei[a] + hei[b] - 2 * hei[lca(a, b)];
	}

	//O(log(n))
	int dist(int a, int b) {
		return deep[a] + deep[b] - 2 * deep[lca(a, b)];
	}
};
