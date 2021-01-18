// Jakub Bachurski
// Cukiernia - O((n + q) log n)

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    string sa, sb;
    cin >> sa >> sb;

    set<size_t> carries, notnines;
    vector<int> A(n), B(n);
    for(size_t i = 0; i < n - 1; i++)
        A[i] = sa[n-i-2] - '0', B[i] = sb[n-i-2] - '0';

    auto update = [&](size_t i) {
        notnines.erase(i);
        if(A[i] + B[i] != 9)
            notnines.insert(i);
        carries.erase(i+1);
        if(A[i] + B[i] >= 10)
            carries.insert(i+1);
    };
    auto get = [&](size_t i) {
        if(auto it = carries.upper_bound(i); i and it != carries.begin())
        {
            auto c = *prev(it);
            auto d = *notnines.lower_bound(c);
            return (A[i] + B[i] + (i <= d)) % 10;
        }
        return (A[i] + B[i]) % 10;
    };
    for(size_t i = 0; i < n; i++)
        update(i);

    while(q --> 0)
    {
        char c;
        cin >> c;

        if(c == 'W')
        {
            size_t i; int v;
            cin >> i >> v; i--;
            A[i] = v; update(i);
        }
        else if(c == 'Z')
        {
            size_t i; int v;
            cin >> i >> v; i--;
            B[i] = v; update(i);
        }
        else if(c == 'S')
        {
            size_t i;
            cin >> i; i--;
            cout << get(i) << '\n';
        }
        else if(c == 's')
        {
            for(size_t k = n; k --> 0; )
                cout << get(k);
            cout << '\n';
        }
    }
}
