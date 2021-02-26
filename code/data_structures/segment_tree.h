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
		return Node(a.val + b.val);
	}
	void build(int node, int l, int r) {
		if (l == r) {
			tr[node] = Node(a[l]);
			return;
		}
		int mid = l+(r-l)/2, lc = (node << 1);
		build(lc, l, mid);
		build(lc+1, mid+1, r);
		tr[node] = join(tr[lc], tr[lc+1]);
	}
	void update(int node, int l, int r, int idx, T x) {
		if (l == r) {
			tr[node] = Node(x);
			return;
		}
		int mid = l+(r-l)/2, lc = (node << 1);
		if(idx <= mid) update(lc, l, mid, idx, x);
		else update(lc+1, mid+1, r, idx, x);
		tr[node] = join(tr[lc], tr[lc+1]);
	}
	Node query(int node, int l, int r, int ql, int qr) {
		if (r < l or qr < l or r < ql) return neutral;
		if (ql <= l and r <= qr) return tr[node];
		int mid = l+(r-l)/2, lc = (node << 1);
		return join(query(lc, l, mid, ql, std::min(qr, mid)), 
			        query(lc+1, mid+1, r, std::max(ql, mid+1), qr));
	}
public:
	SegmentTree (int n) : N(n) {
		tr.assign(4*N, 0);
		a.assign(N+1, 0);
	}
	void build(T *v) {
		a = std::vector<T>(v, v+N+1);
		build(1, 1, N);
	}
	T query(int l, int r) {
		return query(1, 1, N, l, r).val;
	}
	void update(int idx, T x) {
		update(1, 1, N, idx, x);
	}
};