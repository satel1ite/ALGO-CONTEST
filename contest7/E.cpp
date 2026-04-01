#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

const int cWhite = 0;
const int cGray = 1;
const int cBlack = 2;

int n;
int m;
int timer = 0;
std::vector<std::vector<std::pair<int, int>>> g;
std::vector<int> color;
std::vector<int> tin;
std::vector<int> ret;
std::vector<int> bridges;

void Dfs(int v, int edge_id) {
  color[v] = cGray;
  timer++;
  tin[v] = timer;
  ret[v] = timer;
  for (size_t i = 0; i < g[v].size(); ++i) {
    int to;
    int id;
    to = g[v][i].first;
    id = g[v][i].second;
    if (id == edge_id) {
      continue;
    }
    if (color[to] == cWhite) {
      Dfs(to, id);
      ret[v] = std::min(ret[v], ret[to]);
      if (ret[to] == tin[to]) {
        bridges.push_back(id);
      }
    } else {
      ret[v] = std::min(ret[v], tin[to]);
    }
  }
  color[v] = cBlack;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  g.resize(n + 1);
  color.assign(n + 1, cWhite);
  tin.assign(n + 1, 0);
  ret.assign(n + 1, 0);
  for (int i = 1; i <= m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    g[u].push_back(std::make_pair(v, i));
    g[v].push_back(std::make_pair(u, i));
  }
  for (int i = 1; i <= n; ++i) {
    if (color[i] == cWhite) {
      Dfs(i, -1);
    }
  }
  std::sort(bridges.begin(), bridges.end());
  std::cout << bridges.size() << "\n";
  for (size_t i = 0; i < bridges.size(); ++i) {
    std::cout << bridges[i] << (i == bridges.size() - 1 ? "" : " ");
  }
  std::cout << "\n";
  return 0;
}
