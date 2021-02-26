#include <vector>
template<class T>
class FenwickTree {
	int N;
	std::vector<T> tr, a;
public:
	void add(int idx, T x){
		a[idx] = x;
		for (; idx <= N; idx += (idx & -idx))
			tr[idx] += x;
	}
	void set(int idx, T x){
		T delta = x-a[idx];
		a[idx] = x;
		for (; idx <= N; idx += (idx & -idx))
			tr[idx] += delta;
	}
	T query(int idx){
		T res = 0;
		for (; idx > 0; idx -= (idx & -idx))
			res += tr[idx];
		return res;
	}
	T query(int l, int r){
		return query(r)-query(l-1);
	}
	FenwickTree(int n) : N(n) {
		tr.resize(N+1, 0);
		a.resize(N+1, 0);
	}
};