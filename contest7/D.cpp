#include <algorithm>
#include <iostream>
#include <vector>

const int cWhite = 0;
const int cGray = 1;
const int cBlack = 2;

int n;
int m;
std::vector<std::vector<int>> g;
std::vector<std::vector<int>> g_rev;
std::vector<int> color;
std::vector<int> order;
std::vector<int> comp;
int current_comp = 0;

void Dfs1(int v) {
  color[v] = cGray;
  for (int to : g[v]) {
    if (color[to] == cWhite) {
      Dfs1(to);
    }
  }
  color[v] = cBlack;
  order.push_back(v);
}

void Dfs2(int v) {
  color[v] = cGray;
  comp[v] = current_comp;
  for (int to : g_rev[v]) {
    if (color[to] == cWhite) {
      Dfs2(to);
    }
  }
  color[v] = cBlack;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  g.resize(n + 1);
  g_rev.resize(n + 1);
  color.assign(n + 1, cWhite);
  comp.assign(n + 1, 0);
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    g[u].push_back(v);
    g_rev[v].push_back(u);
  }

  for (int i = 1; i <= n; ++i) {
    if (color[i] == cWhite) {
      Dfs1(i);
    }
  }

  std::reverse(order.begin(), order.end());
  color.assign(n + 1, cWhite);
  for (size_t i = 0; i < order.size(); ++i) {
    int v;
    v = order[i];

    if (color[v] == cWhite) {
      current_comp++;
      Dfs2(v);
    }
  }
  std::cout << current_comp << "\n";
  for (int i = 1; i <= n; ++i) {
    std::cout << comp[i] << (i == n ? "" : " ");
  }
  std::cout << "\n";
  return 0;
}
