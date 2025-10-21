#include <iostream>
#include <vector>
using namespace std;

const int cMOD = 10004321;
const int cOne = 123;
const int cTwo = 45;

void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int Min(int a, int b) { return a < b ? a : b; }

void SSort(vector<int>& arr, int start, int end) {
  for (int i = start; i <= end; i++) {
    for (int j = i + 1; j <= end; j++) {
      if (arr[j] < arr[i]) {
        Swap(arr[i], arr[j]);
      }
    }
  }
}

int QuickSelect(vector<int>& arr, int l, int r, int k);

int MedianOfMedians(vector<int>& arr, int l, int r) {
  int write = l;
  for (int i = l; i <= r; i += 5) {
    int end = Min(i + 4, r);
    SSort(arr, i, end);
    int mid = (i + end) / 2;
    Swap(arr[write], arr[mid]);
    write++;
  }
  int num = write - l;
  return QuickSelect(arr, l, l + num - 1, l + num / 2);
}

int QuickSelect(vector<int>& arr, int l, int r, int k) {
  while (true) {
    if (l == r) {
      return arr[l];
    }
    if (r - l + 1 <= 5) {
      SSort(arr, l, r);
      return arr[k];
    }

    int pivot = MedianOfMedians(arr, l, r);

    int i = l;
    int j = l;
    int t = r;

    while (j <= t) {
      if (arr[j] < pivot) {
        Swap(arr[i], arr[j]);
        i++;
        j++;
      } else if (arr[j] > pivot) {
        Swap(arr[j], arr[t]);
        t--;
      } else {
        j++;
      }
    }

    if (k < i) {
      r = i - 1;
    } else if (k <= t) {
      return pivot;
    } else {
      l = t + 1;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  int k;
  int a0;
  int a1;
  cin >> n >> k >> a0 >> a1;

  vector<int> arr(n);
  arr[0] = a0;
  arr[1] = a1;

  for (int i = 2; i < n; i++) {
    arr[i] = (1LL * arr[i - 1] * cOne + 1LL * arr[i - 2] * cTwo) % cMOD;
  }

  int result = QuickSelect(arr, 0, n - 1, k - 1);
  cout << result;

  return 0;
}
