#include <cassert>
#include <iostream>
#include <vector>

namespace {

bool zakonczone = false;
bool is_initialized = false;
int krawedz_cnt;
int n, m;
std::vector<bool> wybrane;

void Init() {
  if (!is_initialized) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    is_initialized = true;
    std::cin >> n >> m;
    wybrane.resize(m);
  }
  if (zakonczone) {
    std::cout << "Po użyciu funkcji Zakoncz(), nie wolno używać innych funkcji."
              << std::endl;
    std::exit(1);
  }
}

}  // namespace

int LiczbaWierzcholkow() {
  Init();
  return n;
}

int LiczbaKrawedzi() {
  Init();
  return m;
}

void NastepnaKrawedz(int* u, int* v, long long* w) {
  if (krawedz_cnt++ >= m) {
    std::cout << "NastepnaKrawedz() wywołana m+1-wszy raz." << std::endl;
    std::exit(1);
  }
  Init();
  std::cin >> *u >> *v >> *w;
}

void WybierzKrawedz(int i) {
  Init();
  if (!(0 <= i and i < m)) {
    std::cout << "WybierzKrawedz(): i poza zakresem." << std::endl;
    std::exit(1);
  }
  wybrane[i] = true;
}

void Zakoncz() {
  Init();
  for (int i = 0; i < m; i++) {
    if (wybrane[i]) {
      std::cout << '1';
    } else {
      std::cout << '0';
    }
  }
  std::cout << std::endl;
  zakonczone = true;
}
