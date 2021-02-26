#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

const int maxn = 1e5+5;

struct SegmentTree {

	struct Node {
		vector<int> v;
	};

	Node join(const Node &a, const Node &b) {
		Node ans;
		merge(all(a.v), all(b.v), back_inserter(ans.v));
		return ans;
	}

	Node tree[4*maxn];
	Node neutral;

	void build(int node, int l, int r, vector<int> &v) {
		if (l == r) {
			tree[node].v.push_back(v[l]);
			return;
		}
		int mid = (l+r)/2;
		int lc = (node << 1);
		build(lc, l, mid, v);
		build(lc+1, mid+1, r, v);
		tree[node] = join(tree[lc], tree[lc+1]);
	}

	int query(int node, int l, int r, int ql, int qr, int x) { 
		if (r < l or qr < l or r < ql) return 0;
		if (ql <= l and r <= qr) return lower_bound(all(tree[node].v), x) - tree[node].v.begin(); //Count the numbers less than x in range [ql, qr]
		//if (ql <= l and r <= qr) return upper_bound(all(tree[node].v), x) - tree[node].v.begin(); //Count the numbers less or equal x in range [ql, qr]
		int mid = (l+r)/2;
		int lc = (node << 1);
		return query(lc, l, mid, ql, min(qr, mid), x) + 
			   query(lc+1, mid+1, r, max(ql, mid+1), qr, x);
	}
};

SegmentTree T;
int n, l, r, x, q;
vector<int> v;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n;

	v = vector<int>(n+1);

	for (int i = 1; i <= n; ++i) {
		cin >> v[i];
	}

	T.build(1, 1, n, v);

	cin >> q;

	while (q--) {
		cin >> l >> r >> x;
		cout << T.query(1, 1, n, l, r, x) << '\n';
	}

	return 0;
}