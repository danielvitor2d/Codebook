#include <vector>
template<class T>
class SegmentTreeLazy {
	struct Node {
		T val;
		Node(T x) : val(x) {}
		Node () : val(0) {}
	};
	int N;
	std::vector<T> a, lazy;
	std::vector<Node> tr;
	Node neutral;
	inline Node join(const Node &a, const Node &b) {
		return Node(a.val + b.val);
	}
	inline void upLazy(int node, int l, int r) {
		if (lazy[node] == 0) return;
		tr[node].val += lazy[node]*(r-l+1);
		int lc = (node << 1);
		(l != r ? lazy[lc] += lazy[node], lazy[lc+1] += lazy[node] : 0);
		lazy[node] = 0;
	}
	void build(int node, int l, int r) {
		if (l == r) tr[node] = Node(a[l]);
		else {
			int mid = l+(r-l)/2, lc = (node << 1);
			build(lc, l, mid);
			build(lc+1, mid+1, r);
			tr[node] = join(tr[lc], tr[lc+1]);
		}
	}
	void update(int node, int l, int r, int ul, int ur, T x) {
		upLazy(node, l, r);
		if (r < r or ur < ul or ur < l or r < ul) return;
		if (ul <= l and r <= ur) {
			lazy[node] += x;
			upLazy(node, l, r);
		} else {
			int mid = l+(r-l)/2, lc = (node << 1);
			update(lc, l, mid, ul, std::min(ur, mid), x);
			update(lc+1, mid+1, r, std::max(mid+1, ul), ur, x);
			tr[node] = join(tr[lc], tr[lc+1]);
		}
	}
	Node query(int node, int l, int r, int ql, int qr) {
		upLazy(node, l, r);
		if (r < l or qr < ql or qr < l or r < ql) return neutral;
		if (ql <= l and r <= qr) return tr[node];
		int mid = l+(r-l)/2, lc = (node << 1);
		return join(query(lc, l, mid, ql, std::min(qr, mid)), 
			        query(lc+1, mid+1, r, std::max(mid+1, ql), qr));
	}
public:
	template<class MyIterator>
	SegmentTreeLazy (MyIterator begin, MyIterator end) {
		N = end-begin-1;
		tr.assign(4*N, 0);
		lazy.assign(4*N, 0);
		a = std::vector<T>(begin, end);
		build(1, 1, N);
	}
	SegmentTreeLazy (int n) : N(n) {
		tr.assign(4*N, 0);
		lazy.assign(4*N, 0);
		a.assign(N+1, 0);
	}
	T query(int l, int r) {
		return query(1, 1, N, l, r).val;
	}
	void update(int l, int r, T x) {
		update(1, 1, N, l, r, x);
	}
};