#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  if (!(cin >> n)) {
    return 0;
  }

  vector<double> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  vector<double> preflogs(n);
  if (n > 0) {
    preflogs[0] = log(a[0]);
  }
  for (int i = 1; i < n; ++i) {
    preflogs[i] = preflogs[i - 1] + log(a[i]);
  }

  int q;
  cin >> q;

  const int cPrec = 10;

  for (int i = 0; i < q; ++i) {
    int l;
    int r;
    cin >> l >> r;

    int count = r - l + 1;
    double sumlog;
    if (l > 0) {
      sumlog = preflogs[r] - preflogs[l - 1];
    } else {
      sumlog = preflogs[r];
    }

    double otvet = exp(sumlog / count);

    cout << fixed << setprecision(cPrec) << otvet << "\n";
  }

  return 0;
}

