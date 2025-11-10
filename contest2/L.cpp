#include <iostream>
#include <vector>

using Item = std::pair<int, int>;

void SiftUpMin(std::vector<Item>& v, int x) {
  if (x == 0) {
    return;
  }
  int p = (x - 1) / 2;
  if ((v[x].first < v[p].first) ||
      (v[x].first == v[p].first && v[x].second < v[p].second)) {
    std::swap(v[p], v[x]);
    SiftUpMin(v, p);
  }
}

void SiftUpMax(std::vector<Item>& v, int x) {
  if (x == 0) {
    return;
  }
  int p = (x - 1) / 2;
  if ((v[x].first > v[p].first) ||
      (v[x].first == v[p].first && v[x].second < v[p].second)) {
    std::swap(v[p], v[x]);
    SiftUpMax(v, p);
  }
}

void SiftDownMin(std::vector<Item>& v, int x) {
  int n = (int)(v.size());
  while (true) {
    int l = 2 * x + 1;
    if (l >= n) {
      break;
    }
    int r = l + 1;
    int smallest = l;
    if (r < n) {
      if ((v[r].first < v[l].first) ||
          (v[r].first == v[l].first && v[r].second < v[l].second)) {
        smallest = r;
      }
    }
    if ((v[smallest].first < v[x].first) ||
        (v[smallest].first == v[x].first && v[smallest].second < v[x].second)) {
      std::swap(v[smallest], v[x]);
      x = smallest;
    } else {
      break;
    }
  }
}

void SiftDownMax(std::vector<Item>& v, int x) {
  int n = (int)(v.size());
  while (true) {
    int l = 2 * x + 1;
    if (l >= n) {
      break;
    }
    int r = l + 1;
    int best = l;
    if (r < n) {
      if ((v[r].first > v[l].first) ||
          (v[r].first == v[l].first && v[r].second < v[l].second)) {
        best = r;
      }
    }
    if ((v[best].first > v[x].first) ||
        (v[best].first == v[x].first && v[best].second < v[x].second)) {
      std::swap(v[best], v[x]);
      x = best;
    } else {
      break;
    }
  }
}

void MinPop(std::vector<Item>& v) {
  int n = (int)(v.size());
  if (n == 0) {
    return;
  }
  std::swap(v[0], v[n - 1]);
  v.pop_back();
  if (!v.empty()) {
    SiftDownMin(v, 0);
  }
}

void MaxPop(std::vector<Item>& v) {
  int n = (int)(v.size());
  if (n == 0) {
    return;
  }
  std::swap(v[0], v[n - 1]);
  v.pop_back();
  if (!v.empty()) {
    SiftDownMax(v, 0);
  }
}

void CleanMin(std::vector<Item>& heap_min, const std::vector<int>& alive) {
  while (!heap_min.empty()) {
    int id = heap_min[0].second;
    if (id >= 0 && id < (int)(alive.size()) && alive[id] == 1) {
      break;
    }
    MinPop(heap_min);
  }
}

void CleanMax(std::vector<Item>& heap_max, const std::vector<int>& alive) {
  while (!heap_max.empty()) {
    int id = heap_max[0].second;
    if (id >= 0 && id < (int)(alive.size()) && alive[id] == 1) {
      break;
    }
    MaxPop(heap_max);
  }
}

void Insert(std::vector<Item>& heap_min, std::vector<Item>& heap_max, int x,
            std::vector<int>& alive, int id, int& cur_size) {
  alive.push_back(1);
  heap_min.push_back({x, id});
  heap_max.push_back({x, id});
  SiftUpMin(heap_min, (int)(heap_min.size()) - 1);
  SiftUpMax(heap_max, (int)(heap_max.size()) - 1);
  ++cur_size;
}

void ExtractMin(std::vector<Item>& heap_min, std::vector<Item>& /* heap_max */,
                std::vector<int>& alive, int& cur_size) {
  CleanMin(heap_min, alive);
  if (heap_min.empty()) {
    std::cout << "error\n";
    return;
  }
  Item p = heap_min[0];
  MinPop(heap_min);
  if (p.second < (int)(alive.size())) {
    alive[p.second] = 0;
  }
  --cur_size;
  std::cout << p.first << '\n';
}

void GetMin(std::vector<Item>& heap_min, const std::vector<int>& alive) {
  CleanMin(heap_min, alive);
  if (heap_min.empty()) {
    std::cout << "error\n";
    return;
  }
  std::cout << heap_min[0].first << '\n';
}

void ExtractMax(std::vector<Item>& heap_max, std::vector<Item>& /* heap_min */,
                std::vector<int>& alive, int& cur_size) {
  CleanMax(heap_max, alive);
  if (heap_max.empty()) {
    std::cout << "error\n";
    return;
  }
  Item p = heap_max[0];
  MaxPop(heap_max);
  if (p.second < (int)(alive.size())) {
    alive[p.second] = 0;
  }
  --cur_size;
  std::cout << p.first << '\n';
}

void GetMax(std::vector<Item>& heap_max, const std::vector<int>& alive) {
  CleanMax(heap_max, alive);
  if (heap_max.empty()) {
    std::cout << "error\n";
    return;
  }
  std::cout << heap_max[0].first << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  if (!(std::cin >> q)) {
    return 0;
  }

  std::vector<Item> heap_min;
  std::vector<Item> heap_max;
  std::vector<int> alive;
  int next_id = 0;
  int cur_size = 0;

  const int cClearArType = 6;

  for (int i = 0; i < q; ++i) {
    int type;
    std::cin >> type;
    if (type == 0) {
      int x;
      std::cin >> x;
      Insert(heap_min, heap_max, x, alive, next_id, cur_size);
      ++next_id;
      std::cout << "ok\n";
    } else if (type == 1) {
      ExtractMin(heap_min, heap_max, alive, cur_size);
    } else if (type == 2) {
      GetMin(heap_min, alive);
    } else if (type == 3) {
      ExtractMax(heap_max, heap_min, alive, cur_size);
    } else if (type == 4) {
      GetMax(heap_max, alive);
    } else if (type == 5) {
      std::cout << cur_size << '\n';
    } else if (type == cClearArType) {
      heap_min.clear();
      heap_max.clear();
      alive.clear();
      next_id = 0;
      cur_size = 0;
      std::cout << "ok\n";
    }
  }
  return 0;
}
