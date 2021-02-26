#include <bits/stdc++.h>
using namespace std;
using i64 = long long int;

const int mod = 1e9+7;
const int D = 15;

int d = D;

struct M {
	i64 m[D][D];

	i64* operator[](int i) {
		return m[i];
	}

	M operator-(M oth) {
		M res;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				res[i][j] = m[i][j] - oth[i][j];
			}
		
		}return res;
	}

	M operator+(M oth) {
		M res;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				res[i][j] = m[i][j] + oth[i][j];
			}
		}
		return res;
	}

	M operator*(M oth) {
		M res;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				res[i][j] = 0;
				for (int k = 0; k < d; ++k) {
					res[i][j] = (res[i][j] + m[i][k] * oth[k][j] % mod + mod) % mod;
				}
			}
		}
		return res;
	}	

	M exp(i64 e) {
		M res;
		for (int i = 0; i < d; ++i)
			for (int j = 0; j < d; ++j)
				res[i][j] = (i==j);
		M base = *this;
		while (e > 0) {
			if (e & 1LL) res = res * base;
			base = base * base;
			e >>= 1LL;
		}
		return res;
	}
};

// O(n^(3)*log(k))
void apply_permutation(vector<int> &seq, vector<int> &perm, int k) {
	d = perm.size();
	M base;
	for (int i = 0; i < d; ++i) {
		for (int j = 0; j < d; ++j) {
			base[i][j] = 0;
		}
	}
	for (int i = 0; i < d; ++i) {
		base[i][perm[i]-1] = 1;
	}
	base = base.exp(k);
	vector<int> ans(d, 0);
	for (int i = 0; i < d; ++i) {
		for (int j = 0; j < d; ++j) {
			ans[i] += seq[j] * base[i][j];
		}
	}
	for (int i = 0; i < d; ++i) {
		seq[i] = ans[i];
	}
}

// O(n)
int dfs(int u, vector<vector<int>> &gr, vector<bool> &used, vector<int> &order) {
	int rs = 1;
	order.push_back(u);
	used[u] = true;
	if (!used[gr[u][0]]) {
		rs += dfs(gr[u][0], gr, used, order);
	}
	return rs;
}

// O(n)
void apply_permutation_with_graph(vector<int> &seq, vector<int> &perm, int k) {
	int n = seq.size();
	vector<vector<int>> gr(n+1);
	for (int i = 0; i < n; ++i) {
		gr[perm[i]].push_back(i+1);
	}

	vector<bool> used(n+1, false);
	vector<int> ans(n+1);
	vector<int> order;

	for (int i = 1; i <= n; ++i) {
		if (!used[i]) {
			order.clear();
			int sz = dfs(i, gr, used, order);
			int pos = k % sz;
			for (int j = 0; j < sz; ++j) {
				int u = order[j];
				int to = order[(j+pos)%sz];
				ans[to-1] = seq[u-1];
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		seq[i] = ans[i];
	}
}