#include <bits/stdc++.h>
using namespace std;
typedef intmax_t I;
const I inf = 1e18;
typedef pair<I, I> II;
typedef double F;

template <typename T>
ostream &operator<<(ostream &o, const vector<T> &v) {
  o << "[";
  for (auto i = v.begin(); i != v.end(); ++i) {
    o << setw(2) << *i;
    if (i != prev(v.end())) o << ", ";
  }
  o << "]";
  return o;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  I n;
  cin >> n;

  vector<I> v(3 * n);
  for (I y = 0; y < 3; ++y) {
    for (I x = 0; x < n; ++x) {
      cin >> v[3 * x + y];
    }
  }

  vector<vector<I>> w = {v};

  map<vector<I>, vector<I>> pre;
  pre[v];

  for (;;) {
    I m = w.size();

    for (I i = 0; i < m; ++i) {
      for (I x = 0; x + 2 < n; ++x) {
        w.push_back(w[i]);

        auto &c = w.back();
        I o = 3 * x;

        swap(c[o + 0], c[o + 8]);
        swap(c[o + 1], c[o + 7]);
        swap(c[o + 2], c[o + 6]);
        swap(c[o + 3], c[o + 5]);

        // cout << w[i] << " -> " << c << "\n";
        if (pre.find(c) == pre.end()) pre[c] = w[i];
      }
    }

    sort(w.begin(), w.end());
    w.erase(unique(w.begin(), w.end()), w.end());

    if (w.size() == m) break;
  }

  // cout << w << "\n";
  // for (auto i : w) cout << i << "\n";

  vector<I> needed(3 * n);
  iota(needed.begin(), needed.end(), 1);

  auto h = needed;
  while (pre.find(h) != pre.end()) {
    cout << pre[h] << "\n";
    h = pre[h];
  }

  // bool ok = binary_search(w.begin(), w.end(), needed);
  bool ok = w[0] == needed;

  cout << (ok ? "TAK" : "NIE") << "\n";

#ifdef UNITEST
  cout.flush();
  system("pause");
#endif
  return 0;
}
