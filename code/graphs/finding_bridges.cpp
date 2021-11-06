#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5+5;

int n, m;
vector<int> gr[MAX];
bool used[MAX];
int dp[MAX], in[MAX], timer;

void find_bridge(int u, int par = -1) {
  in[u] = timer++;
  used[u] = true;
  for (int to : gr[u]) if (to != par) {
    if (!used[to]) {
      find_bridge(to, u);
      dp[u] += dp[to];
      cout << "span-edge: " << u << " -> " << to << '\n';
    } else {
      if (in[u] > in[to]) {
        cout << "back-edge: " << u << " -> " << to << '\n';
        ++dp[u];
      } else {
        cout << "forward-edge: " << u << " -> " << to << '\n';
        --dp[u];
      }
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> m;

  for (int i = 0, u, v; i < m; ++i) {
    cin >> u >> v;
    gr[u].push_back(v);
    gr[v].push_back(u);
  }

  find_bridge(0);

  for (int i = 0; i < n; ++i) {
    if (i) cout << ' ';
    cout << dp[i];
  }
  cout << '\n';
}
/*
6 7
0 1
1 2
0 2
3 4
3 5
4 5
1 3

*/