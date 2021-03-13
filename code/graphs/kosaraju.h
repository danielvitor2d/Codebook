#include <vector>
const int MAXN = 1e5+5;
namespace SCC {
	std::vector<int> gr[MAXN], gt[MAXN];
	std::vector<int> order;
	int comp[MAXN], used[MAXN];
	int n, timer, scc;

	void init(int _n) {
		n = _n;
		scc = 0;
		order.clear();
		for (int i = 0; i < n; ++i) {
			used[i] = false;
			comp[i] = 0;
			gr[i].clear();
			gt[i].clear();
		}
	}

	void addEdge(int u, int v) {
		gr[u].push_back(v);
		// gt[v].push_back(u);
	}

	void dfs1(int u) {
		used[u] = timer;
		for (int to : gr[u]) if (used[to] != timer) {
			dfs1(to);
		}
		order.push_back(u);
	}

	void dfs2(int u) {
		used[u] = timer;
		comp[u] = scc;
		for (int to : gt[u]) if (used[to] != timer) {
			dfs2(to);
		}
	}

	int get_scc() {
		++timer;
		for (int u = 0; u < n; ++u) {
			if (used[u] != timer) {
				dfs1(u);
			}
		}

		++timer;
		for (int i = n-1; i >= 0; --i) {
			if (used[order[i]] != timer) {
				dfs2(order[i]);
				++scc;
			}
		}
		return scc;
	}
};
