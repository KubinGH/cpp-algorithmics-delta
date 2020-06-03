#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

map<int, int> factorize(int a)
{
    map<int, int> f;
    for(int x = 2; x * x <= a; x++)
        while(a % x == 0)
            f[x]++, a /= x;
    if(a > 1) f[a]++;
    return f;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    map<int, vector<int>> E;
    for(size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        for(auto [p, e] : factorize(x))
            E[p].push_back(e);
    }

    int64_t result = 1;
    for(auto& [p, es] : E)
    {
        if(es.size() <= n - 2)
            continue;
        else if(es.size() == n - 1)
            es.insert(es.begin(), 0);
        else
            iter_swap(es.begin(), min_element(es.begin(), es.end()));
        result *= power(p, *min_element(es.begin() + 1, es.end()));
    }

    cout << result;
}
