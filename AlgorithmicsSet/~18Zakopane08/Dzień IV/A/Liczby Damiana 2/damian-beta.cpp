#include <bits/stdc++.h>
#ifdef _WIN32
typedef double lfloat;
#else
typedef long double lfloat;
#endif

using namespace std;

const size_t MAX = 1 << 6;

uint32_t popcount(uint32_t x) { return __builtin_popcount(x); }

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  uint32_t t;
  cin >> t;
  while(t --> 0)
  {
    static char I[MAX];
    cin >> I; uint32_t n = strlen(I);
    if(n >= MAX)
    {
        cout << "10.0";
        continue;
    }
    static uint32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        A[i] = I[i] - '0';

  }
}
