#include <algorithm>
#include <vector>
typedef std::pair<int, int> ii;
template<bool dir=false>
struct EulerianPath {
	std::vector<std::vector<ii>> gr;
	std::vector<int> ans, ng;
	std::vector<bool> used;
	int N, m;
	EulerianPath(int n) : N(n) {
		m = 0;
		gr.assign(N, std::vector<ii>());
	}
	inline void addEdge(int a, int b) {
		int eg = m++;
		gr[a].push_back({b, eg});
		if (!dir) gr[b].push_back({a, eg});
	}
	void dfs(int u) {
		while (ng[u] < (int)gr[u].size()) {
			auto [to, id] = gr[u][ng[u]++];
			if (!used[id]) {
				used[id] = true;
				dfs(to);
			}
		}
		ans.push_back(u);
	}
	std::vector<int> getPath(int s) {
		ng.assign(N, 0);
		used.assign(m, false);
		ans.clear();
		dfs(s);
		std::reverse(ans.begin(), ans.end());
		return ans;
	}
};