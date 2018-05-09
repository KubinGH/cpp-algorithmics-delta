#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 19;

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  uint32_t z;
  cin >> z;
  for(uint32_t zi = 0; zi < z; zi++)
  {
    uint32_t m, n;
    cin >> m >> n;
    static tuple<uint32_t, bool, uint32_t> events[2*MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a, b;
        cin >> a >> b;
        events[2*i]   = make_tuple(a, 1, i);
        events[2*i+1] = make_tuple(b, 0, i);
    }
    sort(events, events + 2*n);
    set<uint32_t> active;
    uint32_t r = 0;
    static array<bool, MAX> A;
    for(uint32_t e = 0; e < 2*n; e++)
    {
        uint32_t a, i; bool t;
        tie(a, t, i) = events[e];
        if(t == 1)
        {
            active.insert(i);
            A[i] = true;
        }
        else if(t == 0)
        {
            if(A[i])
            {
                for(uint32_t j : active)
                    A[j] = false;
                active.clear();
                r++;
            }
        }
    }
    cout << r << " " << 1 << "\n";
  }
}
