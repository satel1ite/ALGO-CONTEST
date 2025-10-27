#include <iostream>
#include <vector>

int BinSearch(std::vector<std::pair<int, int>>& req, int n) {
  int l = 0;
  int r = (int)req.size() - 1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (req[m].first == n) {
      return req[m].second;
    }
    if (req[m].first < n) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return -1;
}

void SwapElements(std::vector<std::pair<long long, int>>& heap,
                  std::vector<std::pair<int, int>>& requests, int i, int j) {
  int a = heap[i].second;
  int b = heap[j].second;
  std::swap(heap[i], heap[j]);
  requests[a].second = j;
  requests[b].second = i;
}

void SiftUp(std::vector<std::pair<long long, int>>& heap,
            std::vector<std::pair<int, int>>& requests, int index) {
  if (index != 0) {
    int parent = (index - 1) / 2;
    if (heap[index].first < heap[parent].first) {
      SwapElements(heap, requests, index, parent);
      SiftUp(heap, requests, parent);
    }
  }
}

void SiftDown(std::vector<std::pair<long long, int>>& heap,
              std::vector<std::pair<int, int>>& requests, int index) {
  if (2 * index + 1 < (int)heap.size()) {
    int child = index * 2 + 1;
    if (child + 1 < (int)heap.size() &&
        heap[child + 1].first < heap[child].first) {
      child++;
    }
    if (heap[child].first < heap[index].first) {
      SwapElements(heap, requests, child, index);
      SiftDown(heap, requests, child);
    }
  }
}

void InsertElement(std::vector<std::pair<long long, int>>& heap,
                   std::vector<std::pair<int, int>>& requests, long long value,
                   int request_id) {
  int heap_index = (int)heap.size();
  int request_index = (int)requests.size();
  requests.push_back(std::make_pair(request_id, heap_index));
  heap.push_back(std::make_pair(value, request_index));
  SiftUp(heap, requests, (int)heap.size() - 1);
}

void DecreaseKey(std::vector<std::pair<long long, int>>& heap,
                 std::vector<std::pair<int, int>>& requests, int id,
                 long long delta) {
  int index = BinSearch(requests, id);
  if (index == -1) {
    return;
  }
  heap[index].first -= delta;
  SiftUp(heap, requests, index);
}

void ExtractMin(std::vector<std::pair<long long, int>>& heap,
                std::vector<std::pair<int, int>>& requests) {
  if (!heap.empty()) {
    int last_index = (int)heap.size() - 1;
    int request_index_removed = heap[0].second;
    SwapElements(heap, requests, 0, last_index);
    requests[request_index_removed].second = -1;
    heap.pop_back();
    if (!heap.empty()) {
      SiftDown(heap, requests, 0);
    }
  }
}

void GetMin(std::vector<std::pair<long long, int>>& heap) {
  if (!heap.empty()) {
    std::cout << heap[0].first << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> q;

  std::vector<std::pair<long long, int>> heap;
  std::vector<std::pair<int, int>> requests;
  std::string command;

  for (int i = 0; i < q; i++) {
    std::cin >> command;
    if (command == "insert") {
      long long value;
      std::cin >> value;
      InsertElement(heap, requests, value, i + 1);
    } else if (command == "decreaseKey") {
      int id;
      long long delta;
      std::cin >> id >> delta;
      DecreaseKey(heap, requests, id, delta);
    } else if (command == "getMin") {
      GetMin(heap);
    } else if (command == "extractMin") {
      ExtractMin(heap, requests);
    }
  }

  return 0;
}
