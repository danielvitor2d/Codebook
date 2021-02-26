#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;

vector<int> gr[maxn];
int used[maxn], tin[maxn], low[maxn];
int n, timer;

void is_bridge(int u, int v) {
	return;
}

void dfs(int u, int p = -1) {
	used[u] = true;
	tin[u] = low[u] = timer++;
	for (int to : gr[u]) if (to != p) {
		if (used[to]) { //Is a back edge
			low[u] = min(low[u], tin[to]);
		} else {
			dfs(to, u);
			low[u] = min(low[u], low[to]);
			if (low[to] > tin[u]) {
				is_bridge(u, to);
			}
		}
	}
}

void find_bridges() {
	timer = 0;
	for (int i = 0; i < n; ++i) {
		used[i] = false;
		tin[i] = -1;
		low[i] = -1;
	}
	for (int i = 0; i < n; ++i)
		if (!used[i]) dfs(i);
}