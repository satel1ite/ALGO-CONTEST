#include <iostream>
#include <queue>

void Add(std::deque<int>& deq, int value) { deq.push_back(value); }

void Remove(std::deque<int>& deq) {
  std::cout << deq.front() << '\n';
  deq.pop_front();
}

void InsertMid(std::deque<int>& deq, int value) {
  size_t mid = deq.size() / 2;
  if (deq.size() % 2 != 0) {
    mid++;
  }
  deq.insert(deq.begin() + mid, value);
}

int main() {
  int n;
  int value;
  std::cin >> n;
  std::deque<int> deq;
  std::string operation;
  for (int i = 0; i < n; i++) {
    std::cin >> operation;
    if (operation == "+") {
      std::cin >> value;
      Add(deq, value);
    } else if (operation == "-") {
      Remove(deq);
    } else {
      std::cin >> value;
      InsertMid(deq, value);
    }
  }
  return 0;
}
