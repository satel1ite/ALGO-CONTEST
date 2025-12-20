#include <cassert>
#include <iostream>
#include <vector>

using Ll = long long;

Ll CustomMax(Ll a, Ll b) { return (a > b) ? a : b; }

class AVLtree {
  struct Node {
    Node *l = nullptr, *r = nullptr;
    Ll key = 0;
    unsigned char h = 1;

    Node(Node* left, Node* right, Ll k, unsigned char height)
        : l(left), r(right), key(k), h(height) {}
  };
  Node* root_ = nullptr;

  int static Height(Node* n) { return (n != nullptr) ? n->h : 0; }

  int static GetBalance(Node* n) {
    return (n != nullptr) ? Height(n->l) - Height(n->r) : 0;
  }

  Node static* RightRotate(Node* y) {
    if (y == nullptr || y->l == nullptr) {
      return y;
    }
    Node* x = y->l;
    Node* t2 = x->r;
    x->r = y;
    y->l = t2;
    y->h = CustomMax(Height(y->l), Height(y->r)) + 1;
    x->h = CustomMax(Height(x->l), Height(x->r)) + 1;
    return x;
  }

  Node static* LeftRotate(Node* x) {
    if (x == nullptr || x->r == nullptr) {
      return x;
    }
    Node* y = x->r;
    Node* t2 = y->l;
    y->l = x;
    x->r = t2;
    x->h = CustomMax(Height(x->l), Height(x->r)) + 1;
    y->h = CustomMax(Height(y->l), Height(y->r)) + 1;
    return y;
  }

  Node static* Balance(Node* n) {
    if (n == nullptr) {
      return n;
    }
    n->h = CustomMax(Height(n->l), Height(n->r)) + 1;
    int balance = GetBalance(n);
    if (balance > 1 && GetBalance(n->l) >= 0) {
      return RightRotate(n);
    }
    if (balance > 1 && GetBalance(n->l) < 0) {
      n->l = LeftRotate(n->l);
      return RightRotate(n);
    }
    if (balance < -1 && GetBalance(n->r) <= 0) {
      return LeftRotate(n);
    }
    if (balance < -1 && GetBalance(n->r) > 0) {
      n->r = RightRotate(n->r);
      return LeftRotate(n);
    }
    return n;
  }

  Node* InsertNode(Node* n, Ll key) {
    if (n == nullptr) {
      return new Node(nullptr, nullptr, key, 1);
    }

    if (key < n->key) {
      n->l = InsertNode(n->l, key);
    } else if (key > n->key) {
      n->r = InsertNode(n->r, key);
    } else {
      return n;
    }
    return Balance(n);
  }

  Node static* MinValueNode(Node* n) {
    Node* current = n;
    while ((current != nullptr) && ((current->l) != nullptr)) {
      current = current->l;
    }
    return current;
  }

  Node* DeleteNode(Node* n, Ll key) {
    if (n == nullptr) {
      return n;
    }

    if (key < n->key) {
      n->l = DeleteNode(n->l, key);
    } else if (key > n->key) {
      n->r = DeleteNode(n->r, key);
    } else {
      if (n->l == nullptr || n->r == nullptr) {
        Node* temp = ((n->l) != nullptr) ? n->l : n->r;
        delete n;
        return temp;
      }
      Node* temp = MinValueNode(n->r);
      n->key = temp->key;
      n->r = DeleteNode(n->r, temp->key);
    }
    return Balance(n);
  }

  void DestroyTree(Node* n) {
    if (n != nullptr) {
      DestroyTree(n->l);
      DestroyTree(n->r);
      delete n;
    }
  }

 public:
  ~AVLtree() { DestroyTree(root_); }

  bool Exists(Ll key) {
    Node* cur = root_;
    while (cur != nullptr) {
      if (key == cur->key) {
        return true;
      }
      cur = (key < cur->key) ? cur->l : cur->r;
    }
    return false;
  }
  Ll LowerBound(Ll x) {
    Node* cur = root_;
    Ll res = -1;

    while (cur != nullptr) {
      if (cur->key >= x) {
        res = cur->key;
        cur = cur->l;
      } else {
        cur = cur->r;
      }
    }
    return res;
  }
  void Insert(Ll key) { root_ = InsertNode(root_, key); }
  void Erase(Ll key) { root_ = DeleteNode(root_, key); }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int q;
  std::cin >> q;

  AVLtree tree;
  bool last_op_was_query = false;
  Ll last_y;
  last_y = 0;
  const Ll cMod = 1000000000;

  while ((q--) != 0) {
    char type;
    Ll x;
    x = 0;
    std::cin >> type >> x;
    if (type == '+') {
      if (last_op_was_query) {
        x = (x + last_y) % cMod;
      }
      tree.Insert(x);
      last_op_was_query = false;
    } else if (type == '?') {
      last_y = tree.LowerBound(x);
      std::cout << last_y << "\n";
      last_op_was_query = true;
    }
  }
  return 0;
}
