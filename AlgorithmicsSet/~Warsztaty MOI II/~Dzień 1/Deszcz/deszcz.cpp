#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k, q;
    cin >> n >> k >> q;
    static array<pair<uint32_t, uint32_t>, MAX> A, B;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a, b, c;
        cin >> a >> b >> c; a--; b--;
        A[i].first = a; A[i].second = c;
        B[i].first = b+1; B[i].second = c;
    }
    sort(A.begin(), A.begin() + n);
    sort(B.begin(), B.begin() + n);
    uint32_t a = 0, b = 0;
    map<uint32_t, uint32_t> M;
    M[0] = 0;
    uint32_t t = 0;
    while(a < n or b < n)
    {
        if(b >= n or (a < n and A[a].first < B[b].first))
        {
            t += A[a].second;
            M[A[a].first] = t;
            a++;
        }
        else
        {
            t -= B[b].second;
            M[B[b].first] = t;
            b++;
        }
    }
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t x;
        cin >> x; x--;
        auto it = M.lower_bound(x);
        if(it != M.begin() and it->first != x) it--;
        cout << it->second << '\n';
    }
}
