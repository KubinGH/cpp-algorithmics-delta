#include <bits/stdc++.h>
using namespace std;

int random_int(int a, int b) { return a + rand() % (b - a + 1); }

void random_tree(int n) {

  vector<int> l1, l2;
  vector<pair<int, int>> edges;

  for (int i = 0; i < n - 2; i++)
    l1.push_back(random_int(1, n));
  for (int i = 0; i < n; i++)
    l2.push_back(i + 1);

  while ((int)l2.size() > 2) {
    for (int i : l2) {
      if (find(l1.begin(), l1.end(), i) != l1.end()) {
        continue;
      }

      edges.push_back({i, l1[0]});
      l1.erase(l1.begin());
      l2.erase(find(l2.begin(), l2.end(), i));
      break;
    }
  }
  edges.push_back({l2[0], l2[1]});
  for (int i = 0; i < (int)edges.size(); ++i) {
    swap(edges[i], edges[random_int(0, i)]);
  }
  for (pair<int, int> i : edges) {
    if (random_int(0, 1) == 1)
      swap(i.first, i.second);
    printf("%d %d\n", i.first, i.second);
  }
}

int main() {
  int seed;
  cin >> seed;
  srand(seed);

  int t;
  cin >> t;
  assert(1 <= t && t <= 10);

  int min_n, max_n;
  cin >> min_n >> max_n;
  assert(2 <= min_n && min_n <= max_n && max_n <= 300);

  int max_a_i;
  cin >> max_a_i;
  assert(1 <= max_a_i && max_a_i <= 1000 * 1000);

  printf("%d\n", t);
  while (t--) {

    int n = random_int(min_n, max_n);
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
      printf("%d%c", random_int(1, max_a_i), " \n"[i == n]);
    random_tree(n);
  }
  return 0;
}
