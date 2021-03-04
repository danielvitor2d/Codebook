#include <vector>
#include <queue>
const int INF = 0x3f3f3f3f;
namespace MaxFlow {
	std::vector<std::vector<int>> capacity;
	std::vector<std::vector<int>> gr;
	int N;
	void init(int n) { N = n;
		capacity.assign(N, std::vector<int>(N));
		gr.assign(N, std::vector<int>());
	}
	void addEdge(int u, int v, int cap) {
		gr[u].push_back(v);
		gr[v].push_back(u);
		capacity[u][v] += cap;
		capacity[v][u] += 0;
	}
	int bfs(int s, int t, std::vector<int> &parent) {
		fill(parent.begin(), parent.end(), -1);
		parent[s] = -2;
		std::queue<std::pair<int, int>> q;
		q.push({s, INF});
		while (!q.empty()) {
			auto [cur, flow] = q.front(); q.pop();
			for (int next : gr[cur]) {
				if (parent[next] == -1 and capacity[cur][next]) {
					parent[next] = cur;
					int new_flow = std::min(flow, capacity[cur][next]);
					if (next == t)
						return new_flow;
					q.push({next, new_flow});
				}
			}
		}
		return 0;
	}
	int maxflow(int s, int t) {
		int flow = 0;
		std::vector<int> parent(N);
		int new_flow;
		while (new_flow = bfs(s, t, parent)) {
			flow += new_flow;
			int cur = t;
			while (cur != s) {
				int prev = parent[cur];
				capacity[prev][cur] -= new_flow;
				capacity[cur][prev] += new_flow;
				cur = prev;
			}
		}
		return flow;
	}
};
