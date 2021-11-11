#include <stack>
#include <utility>
#include <vector>

std::vector<std::vector<int>> gr;

void dfs(int u) {
  // antes

  for (int i : gr[u]) {
    // filho i antes
    dfs(i)
    // filho i depois
  }

  // depois
}

void dfs_iterative(int u) {
  std::stack<std::pair<int, int>> st;
  st.push({u, 0});
  while (!st.empty()) {
    auto [u, c] = st.top(); st.pop();
    if (c == 0) {
      // antes
    }
    if (c == (int)gr[u].size()) {
      for (int i = 0; i < (int)gr[u].size(); ++i) {
        // filho i depois
      }
      // depois
    } else {
      st.push({u, c+1});
      // filho i antes
      st.push({gr[u][c], 0});
    }
  }
}