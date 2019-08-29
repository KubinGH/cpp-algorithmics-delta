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
    o << *i;
    if (i != prev(v.end())) o << ", ";
  }
  o << "]";
  return o;
}
template <typename T>
ostream &operator<<(ostream &o, const pair<T, T> &p) {
  o << "(" << p.first << ", " << p.second << ")";
  return o;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  I w, h, k, b;
  cin >> w >> h >> k >> b;

  vector<vector<I>> v(w, vector<I>(h));
  for (I y = 0; y < h; ++y) {
    for (I x = 0; x < w; ++x) cin >> v[x][y];
    // for (I x = 0; x < w; ++x) v[x][y] = rand() % 4;
  }

  auto get_partial = [&](function<I(I)> f) {
    vector<vector<I>> partial(w, vector<I>(h));
    partial[0][0] = f(v[0][0]);
    for (I x = 1; x < w; ++x) partial[x][0] = partial[x - 1][0] + f(v[x][0]);
    for (I y = 1; y < h; ++y) partial[0][y] = partial[0][y - 1] + f(v[0][y]);
    for (I y = 1; y < h; ++y)
      for (I x = 1; x < w; ++x)
        partial[x][y] = partial[x - 1][y] + partial[x][y - 1] -
                        partial[x - 1][y - 1] + f(v[x][y]);
    return partial;
  };
  auto v_sum = get_partial([&](I x) { return x; });
  auto v_n_divisible = get_partial([&](I x) { return x % b == 0; });

  auto read_partial = [&](const vector<vector<I>> &partial,  //
                          I x_start, I y_start, I x_stop, I y_stop) {
    I c = partial[x_stop][y_stop];
    if (x_start > 0) c -= partial[x_start - 1][y_stop];
    if (y_start > 0) c -= partial[x_stop][y_start - 1];
    if (x_start > 0 && y_start > 0) c += partial[x_start - 1][y_start - 1];
    return c;
  };

  bool any_found = false;
  for (I area = h * w; area >= 1; --area) {
    vector<II> possible_dimensions;
    for (I i = 1; i <= area; ++i) {
      if (area % i != 0) continue;
      possible_dimensions.push_back({i, area / i});
    }

    // cout << area << ": " << possible_dimensions << endl;

    I max_sum = -1;
    I best_ax = -1, best_ay = -1, best_bx = -1, best_by = -1;

    for (I ax = 0; ax < w; ++ax) {
      for (I ay = 0; ay < h; ++ay) {
        for (II wh : possible_dimensions) {
          I bx = ax + wh.first - 1, by = ay + wh.second - 1;
          if (by >= h) continue;
          if (bx >= w) break;

          if (area - read_partial(v_n_divisible, ax, ay, bx, by) > k) continue;

          I sum = read_partial(v_sum, ax, ay, bx, by);
          if (sum > max_sum) {
            max_sum = sum;
            best_ax = ax, best_ay = ay, best_bx = bx, best_by = by;
          }
        }
      }
    }
    if (max_sum > -1) {
      cout << area << " " << (best_bx - best_ax + 1) << " "
           << (best_by - best_ay + 1) << " " << fixed << setprecision(3)
           << (F)(max_sum * 1000 / area) / (F)1000 << "\n";
      for (I y = best_ay; y <= best_by; ++y) {
        for (I x = best_ax; x <= best_bx; ++x) {
          cout << v[x][y] << " ";
        }
        cout << "\n";
      }
      any_found = true;
      break;
    }
  }

  if (!any_found) {
    cout << "NYET"
         << "\n";
  }

#ifdef UNITEST
  cout.flush();
  system("pause");
#endif
  return 0;
}
