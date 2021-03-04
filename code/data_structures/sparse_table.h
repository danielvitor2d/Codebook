#include <vector>
template<class T>
class SparseTable {
	std::vector<std::vector<T>> st;
	std::vector<int> log2;
	T neutral = 0x3f3f3f3f;
	const int nLog = 20;
	T join(T a, T b) {
		return std::min(a, b);
	}
public:
	template<class MyIterator>
	SparseTable(MyIterator begin, MyIterator end) {
		int n = end-begin;
		log2.resize(n+1);
		log2[1] = 0;
		for (int i = 2; i <= n; ++i)
			log2[i] = log2[i/2]+1;
		st.resize(n, std::vector<T>(nLog, neutral));
		for (int i = 0; i < n; ++i, ++begin)
			st[i][0] = *begin;
		for (int j = 1; j < nLog; ++j)
			for (int i = 0; i+(1<<(j-1)) < n; ++i)
				st[i][j] = join(st[i][j-1], st[i+(1<<(j-1))][j-1]);
	}
	T query(int l, int r) {
		int sz = r-l+1;
		T ans = neutral;
		for (int j = nLog-1; j >= 0; --j) {
			if (sz & (1 << j)) {
				neutral = join(neutral, st[l][j]);
				l += (1 << j);
			}
		}
		return ans;
	}
	T queryRMQ(int l, int r) {
		int j = log2[r-l+1];
		return join(st[l][j], st[r-(1 << j)+1][j]);
	}
};