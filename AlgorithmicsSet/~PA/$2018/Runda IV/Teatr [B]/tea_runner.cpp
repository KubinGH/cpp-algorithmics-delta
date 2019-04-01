#include <bits/stdc++.h>
#include <ext/numeric>

//#define TESTI
//#define TESTR
#define TEST1
//#define TEST2

using namespace std;
using __gnu_cxx::power;

template<typename T, T Divisor>
struct modulo_multiplies
{
    T operator() (T a, T b) { return (a*b) % Divisor; }
};
template<typename T, T Divisor>
T identity_element(modulo_multiplies<T, Divisor>) { return T(1); }

namespace teatr {

  bool initialized = false;
  int n;
  #ifdef TESTI
  vector <int> A;
  #endif
  #ifdef TESTR
  constexpr int seed = 15151515, prime = 999983;
  int base, lin;
  modulo_multiplies<int64_t, prime> M;
  #endif

  void init() {
    if(initialized) return;

    #ifdef TESTI
    cin >> n;
    A.resize(n);
    for(int i=0; i<n; i++) cin >> A[i];
    #endif

    #ifdef TESTR
    mt19937 gen = mt19937{seed};
    n = uniform_int_distribution<int>{int(1e7), int(1e8)}(gen);
    base = uniform_int_distribution<int>{1, 1234}(gen);
    lin = uniform_int_distribution<int>{1, 12}(gen);
    #endif

    #ifdef TEST1
    n = 1e8;
    #endif

    initialized = true;
  }

  int GetN() {
    init();
    return n;
  }

  int GetElement(int i) {
    init();
    assert(0 <= i and i < n);
    #ifdef TESTI
    return A[i];
    #endif
    #ifdef TESTR
    int64_t j = i;
    return (prime + (j*lin + j*j*base + power(base, j%127))%prime) % prime;
    #endif
    #ifdef TEST1
    //return (i * 1ll * i) % int(1e6) + 1;
    //return 1 + (((int64_t)i * 27) + i & (i %113) + ((i % 37) ^ (i % 20)) * 3571) % 1000000;
    return i < 100 * 1000 * 1000 - 3 ? 1 + i / 100 : 100 * 1000 * 1000 - i;
    #endif // TEST1
  }

}


#ifdef __cplusplus
extern "C" {
#endif
int GetN() {
  return teatr::GetN();
}
int GetElement(int i) {
  return teatr::GetElement(i);
}
#ifdef __cplusplus
}
#endif
