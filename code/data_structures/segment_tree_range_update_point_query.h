#include <vector>
template<class T>
class SegmentTree {
	struct Node {
		T val;
		Node(T x) : val(x) {}
		Node () : val(0) {}
	};
	int N;
	std::vector<T> a;
	std::vector<Node> tr;
	Node neutral;
	inline Node join(const Node &a, const Node &b) {
		return Node();
	}
	void build(int node, int l, int r) {
		if (l == r) {
			tr[node] = Node(a[l]);
		} else {
			int mid = l+(r-l)/2, lc = (node << 1);
			build(lc, l, mid);
			build(lc+1, mid+1, r);
		}
	}
	T query(int node, int l, int r, int idx) {
		if (l == r) return tr[node].val;
		int mid = l+(r-l)/2, lc = (node << 1);
		if (idx <= mid) return tr[node].val + query(lc, l, mid, idx);
		else return tr[node].val + query(lc+1, mid+1, r, idx);
	}
	void update(int node, int l, int r, int ql, int qr, T x) {
		if (r < l or qr < l or r < ql) return;
		if (ql <= l and r <= qr) {
			tr[node].val += x;
		} else {
			int mid = l+(r-l)/2, lc = (node << 1);
			update(lc, l, mid, ql, std::min(qr, mid), x);
			update(lc+1, mid+1, r, std::max(mid+1, ql), qr, x);
		}
	}
public:
	template<class MyIterator>
	SegmentTree (MyIterator begin, MyIterator end) {
		N = end-begin-1;
		tr.assign(4*N, 0);
		a = std::vector<T>(begin, end);
		build(1, 1, N);
	}
	SegmentTree (int n) : N(n) {
		tr.assign(4*N, 0);
		a.assign(N+1, 0);
	}
	T query(int idx) {
		return query(1, 1, N, idx);
	}
	void update(int l, int r, T x) {
		update(1, 1, N, l, r, x);
	}
};