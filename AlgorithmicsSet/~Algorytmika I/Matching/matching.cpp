#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<uint> P(n);
    vector<size_t> I(n + 1);

    I[0] = SIZE_MAX;
    for(size_t i = 1; i <= n; i++)
        cin >> I[i], P[--I[i]] = i - 1;

    vector<size_t> upper(n, SIZE_MAX), lower(n, SIZE_MAX);

    list<size_t> L;
    vector<list<size_t>::iterator> where(n);
    for(size_t i = 0; i < n; i++)
        L.push_back(i), where[i] = prev(L.end());
    L.push_front(SIZE_MAX); L.push_back(SIZE_MAX);
    for(size_t i = n; i --> 0; )
    {
        auto it = where[P[i]];
        lower[i] = I[*prev(it) + 1]; upper[i] = I[*next(it) + 1];
        L.erase(it);
    }

    auto extends = [&](const vector<uint>& S, size_t i, size_t k) {
        return k < n and
              (lower[k] == SIZE_MAX or S[i - k + lower[k]] < S[i]) and
              (upper[k] == SIZE_MAX or S[i - k + upper[k]] > S[i]);
    };

    vector<size_t> F(n);
    for(size_t i = 1; i < n; i++)
    {
        F[i] = F[i - 1];
        while(F[i] and not extends(P, i, F[i]))
            F[i] = F[F[i] - 1];
        F[i] += extends(P, i, F[i]);
    }

    vector<uint> T(m);
    for(auto& x : T) cin >> x;

    vector<size_t> occ;
    for(size_t i = 0, k = 0; i < m; i++)
    {
        while(k and not extends(T, i, k))
            k = F[k - 1];
        k += extends(T, i, k);
        if(k == n)
            occ.push_back(i - n + 1);
    }

    cout << occ.size() << endl;
    for(auto i : occ)
        cout << i + 1 << ' ';
    cout << endl;
}
