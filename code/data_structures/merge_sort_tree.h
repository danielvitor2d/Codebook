#include <vector>
#define all(x) (x).begin(), (x).end()
const int64_t INF = 0x3f3f3f3f;
template<class T>
class MergeSortTree {
	typedef std::vector<T> Node;
	inline Node join(const Node &a, const Node &b) {
		Node ans;
		merge(all(a), all(b), std::back_inserter(ans));
		return ans;
	}
	int N;
	std::vector<Node> tr;
	std::vector<T> a;
	Node neutral;
	inline int szEq(int node, int k) {
		return upper_bound(all(tr[node]), k)-lower_bound(all(tr[node]), k); }
	inline int szLe(int node, int k) {
		return upper_bound(all(tr[node]), k)-tr[node].begin(); }
	inline int szLt(int node, int k) {
		return lower_bound(all(tr[node]), k)-tr[node].begin(); }
	void build(int node, int l, int r) {
		if (l == r) return (void)tr[node].push_back(a[l]);
		int mid = l+(r-l)/2, lc = (node << 1);
		build(lc, l, mid);
		build(lc+1, mid+1, r);
		tr[node] = join(tr[lc], tr[lc+1]);
	}
	// Find the amount of value (lower, lower or equal, equal) than x
	int query(int node, int l, int r, int ql, int qr, int k, int op) { 
		if (r < l or qr < l or r < ql) return 0;
		if (ql <= l and r <= qr) return (op == -1 ? szLt(node, k) : op == 1 ? szLe(node, k): szEq(node, k));
		int mid = l+(r-l)/2, lc = (node << 1);
		return query(lc, l, mid, ql, std::min(qr, mid), k, op) + 
			   query(lc+1, mid+1, r, std::max(ql, mid+1), qr, k, op);
	}
	//Find the smallest number greater or equal to x
	T query(int node, int l, int r, int ql, int qr, T x) {
		if (r < l or qr < l or r < ql) return INF;
		if (ql <= l and r <= qr) {
			auto pos = lower_bound(all(tr[node]), x);
			if (pos != tr[node].end()) return *pos;
			return INF;
		}
		int mid = l+(r-l)/2, lc = (node << 1);
		return std::min(query(lc, l, mid, ql, std::min(mid, qr), x), 
			            query(lc+1, mid+1, r, std::max(ql, mid+1), qr, x));
	}
public:
	template<class MyIterator>
	MergeSortTree(MyIterator begin, MyIterator end) {
		N = end-begin-1;
		a = std::vector<T>(begin, end);
		tr.assign(4*N, std::vector<T>());
		build(1, 1, N);
	}
	int lt(int l, int r, int k) {
		return query(1, 1, N, l, r, k, -1);
	}
	int le(int l, int r, int k) {
		return query(1, 1, N, l, r, k, 1);
	}
	int eq(int l, int r, int k) {
		return query(1, 1, N, l, r, k, 0);
	}
	T query(int l, int r, T x) {
		return query(1, 1, N, l, r, x);
	}
};
