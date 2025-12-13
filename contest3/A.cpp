#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int n;
int q;

std::pair<int, int> MergePairs(const std::pair<int, int>& l,
                               const std::pair<int, int>& r,
                               const std::vector<long long>& a) {
  std::vector<int> cand;
  if (l.first != -1) {
    cand.push_back(l.first);
  }
  if (l.second != -1) {
    cand.push_back(l.second);
  }
  if (r.first != -1) {
    cand.push_back(r.first);
  }
  if (r.second != -1) {
    cand.push_back(r.second);
  }

  if (cand.empty()) {
    return std::pair<int, int>{-1, -1};
  }

  std::sort(cand.begin(), cand.end());
  cand.erase(std::unique(cand.begin(), cand.end()), cand.end());

  std::sort(cand.begin(), cand.end(), [&](int i, int j) {
    if (a[i] != a[j]) {
      return a[i] < a[j];
    }
    return i < j;
  });

  if (cand.size() == 1) {
    return std::pair<int, int>{cand[0], -1};
  }
  return std::pair<int, int>{cand[0], cand[1]};
}

int main() {
  std::cin >> n >> q;

  std::vector<long long> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }

  std::vector<int> pw(n + 2);
  pw[1] = 0;
  for (int t = 2; t <= n; ++t) {
    pw[t] = pw[t - 1];
    if ((1 << (pw[t] + 1)) <= t) {
      pw[t]++;
    }
  }

  int log_max = 0;
  while ((1 << log_max) <= n) {
    ++log_max;
  }

  std::vector<std::vector<std::pair<int, int>>> sparse;
  sparse.assign(log_max, std::vector<std::pair<int, int>>(
                             n + 2, std::pair<int, int>{-1, -1}));

  for (int i = 1; i <= n; ++i) {
    sparse[0][i] = std::pair<int, int>{i, -1};
  }

  for (int k = 1; k < log_max; ++k) {
    int half = 1 << (k - 1);
    int len = 1 << k;
    for (int i = 1; i + len - 1 <= n; ++i) {
      sparse[k][i] = MergePairs(sparse[k - 1][i], sparse[k - 1][i + half], a);
    }
  }

  for (int i = 0; i < q; i++) {
    int l;
    int r;
    std::cin >> l >> r;
    int len = r - l + 1;
    int k = pw[len];

    std::pair<int, int> left = sparse[k][l];
    std::pair<int, int> right = sparse[k][r - (1 << k) + 1];
    std::pair<int, int> ans = MergePairs(left, right, a);

    if (ans.second == -1) {
      std::cout << a[ans.first] << '\n';
    } else {
      std::cout << a[ans.second] << '\n';
    }
  }

  return 0;
}
