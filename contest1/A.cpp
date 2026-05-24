#include <iostream>
#include <vector>

using namespace std;

void Merge(vector<pair<int, int>>& a, int l, int m, int r) {
  vector<pair<int, int>> temp;
  int i = l;
  int j = m + 1;

  while (i <= m && j <= r) {
    if (a[i].first < a[j].first ||
        (a[i].first == a[j].first && a[i].second <= a[j].second)) {
      temp.push_back(a[i]);
      i++;
    } else {
      temp.push_back(a[j]);
      j++;
    }
  }

  while (i <= m) {
    temp.push_back(a[i]);
    i++;
  }

  while (j <= r) {
    temp.push_back(a[j]);
    j++;
  }

  for (int k = l; k <= r; k++) {
    a[k] = temp[k - l];
  }
}

void MergeSort(vector<pair<int, int>>& a, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;

    MergeSort(a, l, m);
    MergeSort(a, m + 1, r);

    Merge(a, l, m, r);
  }
}

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> segs(n);
    for (int i = 0; i < n; i++) {
        cin >> segs[i].first >> segs[i].second;
    }

    MergeSort(segs, 0, n - 1);

    vector<pair<int, int>> res;
    int start = segs[0].first;
    int end = segs[0].second;

    for (int i = 1; i < n; i++) {
        if (segs[i].first <= end) {
            if (segs[i].second > end) {
                end = segs[i].second;
            }
        } else {
            res.push_back({start, end});
            start = segs[i].first;
            end = segs[i].second;
        }
    }
    res.push_back({start, end});

    cout << res.size() << endl;
    for (auto seg : res) {
        cout << seg.first << " " << seg.second << endl;
    }

    return 0;
}
