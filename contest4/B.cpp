#include <iostream>
#include <string>
#include <vector>

using Ll = long long;
const Ll cInfVal = 2000000000000000000LL;

class RedBlackTree {
  struct Node {
    Node *l = nullptr, *r = nullptr, *parent = nullptr;
    Ll key = 0;
    bool color = false;
    int size = 1;

    Node(Ll k) : key(k), color(true), size(1) {}
  };

  Node* root_ = nullptr;

  static void UpdateSize(Node* n) {
    if (n == nullptr) {
      return;
    }
    n->size = 1;
    if (n->l != nullptr) {
      n->size += n->l->size;
    }
    if (n->r != nullptr) {
      n->size += n->r->size;
    }
  }

  void RotateLeft(Node* x) {
    Node* y = x->r;
    x->r = y->l;
    if (y->l != nullptr) {
      y->l->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      root_ = y;
    } else if (x == x->parent->l) {
      x->parent->l = y;
    } else {
      x->parent->r = y;
    }
    y->l = x;
    x->parent = y;

    UpdateSize(x);
    UpdateSize(y);
  }

  void RotateRight(Node* x) {
    Node* y = x->l;
    x->l = y->r;
    if (y->r != nullptr) {
      y->r->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      root_ = y;
    } else if (x == x->parent->r) {
      x->parent->r = y;
    } else {
      x->parent->l = y;
    }
    y->r = x;
    x->parent = y;

    UpdateSize(x);
    UpdateSize(y);
  }

  void FixInsert(Node* n) {
    while (n != root_ && n->parent->color) {
      if (n->parent == n->parent->parent->l) {
        Node* uncle = n->parent->parent->r;
        if ((uncle != nullptr) && uncle->color) {
          n->parent->color = false;
          uncle->color = false;
          n->parent->parent->color = true;
          n = n->parent->parent;
        } else {
          if (n == n->parent->r) {
            n = n->parent;
            RotateLeft(n);
          }
          n->parent->color = false;
          n->parent->parent->color = true;
          RotateRight(n->parent->parent);
        }
      } else {
        Node* uncle = n->parent->parent->l;
        if ((uncle != nullptr) && uncle->color) {
          n->parent->color = false;
          uncle->color = false;
          n->parent->parent->color = true;
          n = n->parent->parent;
        } else {
          if (n == n->parent->l) {
            n = n->parent;
            RotateRight(n);
          }
          n->parent->color = false;
          n->parent->parent->color = true;
          RotateLeft(n->parent->parent);
        }
      }
    }
    root_->color = false;
  }

  void Transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
      root_ = v;
    } else if (u == u->parent->l) {
      u->parent->l = v;
    } else {
      u->parent->r = v;
    }
    if (v != nullptr) {
      v->parent = u->parent;
    }
  }

  static Node* Minimum(Node* n) {
    while (n->l != nullptr) {
      n = n->l;
    }
    return n;
  }

  Node* FixDeleteLeft(Node* parent) {
    Node* s = parent->r;
    if ((s != nullptr) && s->color) {
      s->color = false;
      parent->color = true;
      RotateLeft(parent);
      s = parent->r;
    }
    if ((s != nullptr) && ((s->l == nullptr) || !s->l->color) &&
        ((s->r == nullptr) || !s->r->color)) {
      s->color = true;
      return parent;
    }
    if ((s != nullptr) && ((s->r == nullptr) || !s->r->color)) {
      if (s->l != nullptr) {
        s->l->color = false;
      }
      s->color = true;
      RotateRight(s);
      s = parent->r;
    }
    if (s != nullptr) {
      s->color = parent->color;
      parent->color = false;
      if (s->r != nullptr) {
        s->r->color = false;
      }
      RotateLeft(parent);
    }
    return root_;
  }

  Node* FixDeleteRight(Node* parent) {
    Node* s = parent->l;
    if ((s != nullptr) && s->color) {
      s->color = false;
      parent->color = true;
      RotateRight(parent);
      s = parent->l;
    }
    if ((s != nullptr) && ((s->r == nullptr) || !s->r->color) &&
        ((s->l == nullptr) || !s->l->color)) {
      s->color = true;
      return parent;
    }
    if ((s != nullptr) && ((s->l == nullptr) || !s->l->color)) {
      if (s->r != nullptr) {
        s->r->color = false;
      }
      s->color = true;
      RotateLeft(s);
      s = parent->l;
    }
    if (s != nullptr) {
      s->color = parent->color;
      parent->color = false;
      if (s->l != nullptr) {
        s->l->color = false;
      }
      RotateRight(parent);
    }
    return root_;
  }

  void FixDelete(Node* x) {
    while (x != root_ && ((x == nullptr) || !x->color)) {
      Node* parent = (x != nullptr) ? x->parent : nullptr;
      if ((x == nullptr) && (parent == nullptr)) {
        return;
      }

      if (x == nullptr) {
        break;
      }

      parent = x->parent;
      if (parent == nullptr) {
        break;
      }

      if (x == parent->l) {
        x = FixDeleteLeft(parent);
      } else {
        x = FixDeleteRight(parent);
      }
    }
    if (x != nullptr) {
      x->color = false;
    }
  }

  void DestroyTree(Node* n) {
    if (n != nullptr) {
      DestroyTree(n->l);
      DestroyTree(n->r);
      delete n;
    }
  }

 public:
  ~RedBlackTree() { DestroyTree(root_); }

  bool Exists(Ll key) {
    Node* cur = root_;
    while (cur != nullptr) {
      if (key == cur->key) {
        return true;
      }
      if (key < cur->key) {
        cur = cur->l;
      } else {
        cur = cur->r;
      }
    }
    return false;
  }

  void Insert(Ll key) {
    Node* z = new Node(key);
    Node* y = nullptr;
    Node* x = root_;

    while (x != nullptr) {
      y = x;
      if (z->key < x->key) {
        x = x->l;
      } else {
        x = x->r;
      }
    }

    z->parent = y;
    if (y == nullptr) {
      root_ = z;
    } else if (z->key < y->key) {
      y->l = z;
    } else {
      y->r = z;
    }

    Node* temp = z;
    while (temp != nullptr) {
      UpdateSize(temp);
      temp = temp->parent;
    }

    FixInsert(z);
  }

  void Erase(Ll key) {
    Node* z = root_;
    while (z != nullptr) {
      if (key == z->key) {
        break;
      }
      z = (key < z->key) ? z->l : z->r;
    }

    if (z == nullptr) {
      return;
    }

    Node* y = z;
    Node* x = nullptr;
    bool y_original_color = y->color;

    if (z->l == nullptr) {
      x = z->r;
      Transplant(z, z->r);
    } else if (z->r == nullptr) {
      x = z->l;
      Transplant(z, z->l);
    } else {
      y = Minimum(z->r);
      y_original_color = y->color;
      x = y->r;

      if (y->parent == z) {
        if (x != nullptr) {
          x->parent = y;
        }
      } else {
        Transplant(y, y->r);
        y->r = z->r;
        if (y->r != nullptr) {
          y->r->parent = y;
        }
      }

      Transplant(z, y);
      y->l = z->l;
      y->l->parent = y;
      y->color = z->color;
    }

    Node* t = (x != nullptr) ? x : y;
    if (t == nullptr) {
      t = z->parent;
    }
    while (t != nullptr) {
      UpdateSize(t);
      t = t->parent;
    }

    delete z;

    if (!y_original_color) {
      if (x != nullptr) {
        FixDelete(x);
      }
    }

    if (root_ != nullptr) {
      UpdateSize(root_);
    }
  }

  Ll Next(Ll x) {
    Node* cur = root_;
    Node* succ = nullptr;
    while (cur != nullptr) {
      if (cur->key > x) {
        succ = cur;
        cur = cur->l;
      } else {
        cur = cur->r;
      }
    }
    return (succ != nullptr) ? succ->key : cInfVal;
  }

  Ll Prev(Ll x) {
    Node* cur = root_;
    Node* pred = nullptr;
    while (cur != nullptr) {
      if (cur->key < x) {
        pred = cur;
        cur = cur->r;
      } else {
        cur = cur->l;
      }
    }
    return (pred != nullptr) ? pred->key : -cInfVal;
  }

  Ll Kth(int k) {
    if ((root_ == nullptr) || k < 0 || k >= root_->size) {
      return cInfVal;
    }
    Node* cur = root_;
    while (cur != nullptr) {
      int left_s = (cur->l != nullptr) ? cur->l->size : 0;
      if (left_s == k) {
        return cur->key;
      }
      if (k < left_s) {
        cur = cur->l;
      } else {
        k -= (left_s + 1);
        cur = cur->r;
      }
    }
    return cInfVal;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  RedBlackTree tree;
  std::string op;
  Ll x;

  while (std::cin >> op >> x) {
    if (op == "insert") {
      if (!tree.Exists(x)) {
        tree.Insert(x);
      }
    } else if (op == "delete") {
      tree.Erase(x);
    } else if (op == "exists") {
      if (tree.Exists(x)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    } else if (op == "next") {
      Ll res;
      res = tree.Next(x);
      if (res == cInfVal) {
        std::cout << "none\n";
      } else {
        std::cout << res << "\n";
      }
    } else if (op == "prev") {
      Ll res;
      res = tree.Prev(x);
      if (res == -cInfVal) {
        std::cout << "none\n";
      } else {
        std::cout << res << "\n";
      }
    } else if (op == "kth") {
      Ll res;
      res = tree.Kth((int)x);
      if (res == cInfVal) {
        std::cout << "none\n";
      } else {
        std::cout << res << "\n";
      }
    }
  }

  return 0;
}
