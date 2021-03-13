#include <vector>
const int MAXN = 1e5+5;
std::vector<int> gr[MAXN];
int used[MAXN], tin[MAXN], low[MAXN];
int n, timer;

void is_cutpoint(int u) {
	return;
}

void dfs(int u, int p = -1) {
	used[u] = true;
	tin[u] = low[u] = timer++;
	int children = 0;
	for (int to : gr[u]) if (to != p) {
		if (used[to]) { //Is a back edge
			low[u] = std::min(low[u], tin[to]);
		} else {
			dfs(to, u);
			low[u] = std::min(low[u], low[to]);
			if (low[to] >= tin[u] and p != -1) {
				is_cutpoint(u);
			}
			++children;
		}
	}
	if (p == -1 and children > 1)
		is_cutpoint(u);
}

void find_cutpoints() {
	timer = 0;
	for (int i = 0; i < n; ++i) {
		used[i] = false;
		tin[i] = -1;
		low[i] = -1;
	}
	for (int i = 0; i < n; ++i)
		if (!used[i]) dfs(i);
}