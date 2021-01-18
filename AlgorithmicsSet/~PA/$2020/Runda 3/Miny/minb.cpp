#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> A(n), R(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i] >> R[i];

    set<size_t> got;

    for(size_t mask = 0; mask < (1u << n); mask++)
    {
        size_t cmask = mask;

        bool any;
        do {
            any = false;

            for(size_t i = 0; i < n; i++)
              if(cmask >> i & 1)
            {
                size_t l = lower_bound(A.begin(), A.end(), A[i]-R[i]) - A.begin(),
                       r = upper_bound(A.begin(), A.end(), A[i]+R[i]) - A.begin();
                for(size_t j = l; j < r; j++)
                {
                    if(not (cmask >> j & 1))
                        any = true;
                    cmask |= 1 << j;
                }
            }
        } while(any);


        got.insert(cmask);
    }

    cout << got.size() << endl;
}
