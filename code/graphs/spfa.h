#include <vector>
#include <queue>
typedef std::pair<int, int> ii;
const int INF = 0x3f3f3f3f;
namespace SPFA {
	std::vector<std::vector<ii>> gr;
	std::vector<int> d;
	int N;
	void init(int n) {
		N = n;
		d.assign(N, INF);
		gr.assign(N, std::vector<ii>());
	}
	inline void addEdge(int a, int b, int c) {
		gr[a].push_back({b, c});
	}
	bool spfa(int s) {
		std::vector<int> cnt(N, 0);
		std::vector<bool> inqueue(N, false);
		std::queue<int> q;

		d[s] = 0;
		q.push(s);
		inqueue[s] = true;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			inqueue[u] = false;
			for (auto [to, w] : gr[u]) {
				if (d[u] + w < d[to]) {
					d[to] = d[u] + w;
					if (!inqueue[to]) {
						inqueue[to] = true;
						q.push(to);
						++cnt[to];
						if (cnt[to] > N)
							return false;         //Negative cycle
					}
				}
			}
		}

		return true;
	}
};