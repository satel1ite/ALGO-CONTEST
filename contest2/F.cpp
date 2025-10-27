#include <algorithm>
#include <climits>
#include <iostream>
#include <stack>
#include <string>

void FillL(std::stack<int>& l, std::stack<int>& l_min, std::stack<int>& r,
           std::stack<int>& r_min) {
  while (!r.empty()) {
    int y = r.top();
    r.pop();
    r_min.pop();

    if (l.empty()) {
      l.push(y);
      l_min.push(y);
    } else {
      l.push(y);
      l_min.push(std::min(y, l_min.top()));
    }
  }
}

void EnqueueX(std::stack<int>& r, std::stack<int>& r_min, int x) {
  r.push(x);
  if (r_min.empty()) {
    r_min.push(x);
  } else {
    r_min.push(std::min(x, r_min.top()));
  }
  std::cout << "ok\n";
}

void Dequeue(std::stack<int>& l, std::stack<int>& l_min, std::stack<int>& r,
             std::stack<int>& r_min) {
  if (l.empty()) {
    FillL(l, l_min, r, r_min);
  }
  std::cout << l.top() << '\n';
  l.pop();
  l_min.pop();
}

void Front(std::stack<int>& l, std::stack<int>& l_min, std::stack<int>& r,
           std::stack<int>& r_min) {
  if (l.empty()) {
    FillL(l, l_min, r, r_min);
  }
  std::cout << l.top() << '\n';
}

void Size(std::stack<int>& l, std::stack<int>& r) {
  int answ;
  answ = (int)l.size() + (int)r.size();
  std::cout << answ << '\n';
}

void Clear(std::stack<int>& l, std::stack<int>& r, std::stack<int>& l_min,
           std::stack<int>& r_min) {
  while (!r.empty()) {
    r.pop();
  }
  while (!l.empty()) {
    l.pop();
  }
  while (!r_min.empty()) {
    r_min.pop();
  }
  while (!l_min.empty()) {
    l_min.pop();
  }
  std::cout << "ok" << '\n';
}

void Min(std::stack<int>& l_min, std::stack<int>& r_min) {
  if (l_min.empty() && r_min.empty()) {
    std::cout << "error\n";
  } else if (l_min.empty()) {
    std::cout << r_min.top() << '\n';
  } else if (r_min.empty()) {
    std::cout << l_min.top() << '\n';
  } else {
    int mini = std::min(l_min.top(), r_min.top());
    std::cout << mini << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::stack<int> l;
  std::stack<int> r;
  std::stack<int> l_min;
  std::stack<int> r_min;
  std::string request;
  for (int i = 0; i < n; i++) {
    std::cin >> request;
    if (request == "enqueue") {
      int x;
      std::cin >> x;
      EnqueueX(r, r_min, x);
    } else if (request == "dequeue") {
      if (l.empty() && r.empty()) {
        std::cout << "error" << '\n';
      } else {
        Dequeue(l, l_min, r, r_min);
      }
    } else if (request == "front") {
      if (l.empty() && r.empty()) {
        std::cout << "error" << '\n';
      } else {
        Front(l, l_min, r, r_min);
      }
    } else if (request == "size") {
      Size(l, r);
    } else if (request == "clear") {
      Clear(l, r, l_min, r_min);
    } else if (request == "min") {
      if (l.empty() && r.empty()) {
        std::cout << "error" << '\n';
      } else {
        Min(l_min, r_min);
      }
    }
  }
  return 0;
}
