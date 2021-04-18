#include "../data_structures/fenwick_tree.h"
using namespace std;
const int MAX = 2e5+5;

std::vector<int> gr[MAX];
int n, timer, cost[MAX];
int lf[MAX], rt[MAX];

/*
  Memory: O(2*N)
*/
void dfs(int u, int par, std::vector<int> &euler) {
	euler[timer++] = u;
	if (lf[u] == -1) lf[u] = timer-1;
	rt[u] = timer-1;
	for (int to : gr[u]) if (to != par) {
		dfs(to, u, euler);
	}
	euler[timer++] = u;
	rt[u] = timer-1;
}
std::vector<int> getEulerTour(int s) {
	std::vector<int> euler(2*n);
	timer = 0;
	for (int i = 0; i < n; ++i) lf[i] = -1;
	dfs(s, -1, euler);
	return euler;
}
/*
	Sum of subtree and add to nodes
	- To add:       FT.add(first(v), x)
	- To find sum:  FT.query(first(v), last(v))
*/
/*
	Sum of path from ancestor and add to nodes
	- To add:       FT.add(first(v), x) and FT.add(last(v), -x)
	- To find sum:  FT.query(first(ancestor), first(v))
*/
