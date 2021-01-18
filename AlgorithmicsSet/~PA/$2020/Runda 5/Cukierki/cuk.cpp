#include <bits/stdc++.h>

using namespace std;

const uint mod = 1e9 + 7;

uint M(uint x) { return x >= mod ? x - mod : x; }

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    uint m = 0;
    vector<uint> A(n);
    for(auto& a : A)
        cin >> a, m = max(a, m);
    sort(A.begin(), A.end());

    vector<uint> P(m), Q(m);
    P[0] = 1;
    for(auto a : A)
    {
        copy(P.begin(), P.end(), Q.begin());
        for(uint z = a-1; z < m; z++)
        {
            auto zz = min(a+z, m-1);
            Q[zz] += P[z]; Q[zz] = M(Q[zz]);
        }
        swap(P, Q);
    }

    uint result = 0;
    for(uint z = 0; z < m; z++)
        result += P[z], result = M(result);
    cout << result - 1 << '\n';
}
