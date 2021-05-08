#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n; int x;
    cin >> n >> x;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    unordered_map<int, size_t> where;
    where.reserve(16 * n);

    auto done = [&](size_t i, size_t j, size_t k) {
        cout << i+1 << ' ' << j+1 << ' ' << k+1;
        exit(0);
    };

    where[A[n-1]] = n-1;
    for(size_t j = n-1; j --> 0; )
    {
        for(size_t i = j; i --> 0; )
        {
            if(where.count(x - A[i] - A[j]))
                done(i, j, where[x - A[i] - A[j]]);
        }
        where[A[j]] = j;
    }
    cout << "IMPOSSIBLE" << endl;
}
