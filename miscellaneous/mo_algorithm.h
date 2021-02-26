#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

const int BLOCK_SIZE = 800;
const int maxn = 5e5+5;

int v[maxn], f[maxn];
int ans;

void remove(int idx) {
	--f[v[idx]];
	if (f[v[idx]] == 0) --ans;
}

void add(int idx) {
	++f[v[idx]];
	if (f[v[idx]] == 1) ++ans;
}

int get_answer() {
	return ans;
}

struct Query {
	int l, r, idx;
	bool operator < (const Query oth) const {
		if (l / BLOCK_SIZE != oth.l / BLOCK_SIZE) return l < oth.l;
		return (l / BLOCK_SIZE & 1) ? (r < oth.r) : (r > oth.r); 
	}
};

vi mo_s_algorithm(vector<Query> queries) {
	vi answers(queries.size());
	sort(queries.begin(), queries.end());
	int l = 0, r = 0;
	for (Query q : queries) {
		while (q.l < l) add(--l);
		while (r < q.r) add(++r);
		while (l < q.l) remove(l++);
		while (q.r < r) remove(r--);
		answers[q.idx] = get_answer();
	}
	return answers;
}
