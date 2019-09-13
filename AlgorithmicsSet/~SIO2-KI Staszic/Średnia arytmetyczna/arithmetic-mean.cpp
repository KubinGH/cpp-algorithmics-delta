#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n, a;
    cin >> n >> a;

    vector<size_t> W(n);
    for(size_t i = 0; i < n; i++)
        cin >> W[i];
    sort(W.begin(), W.end());

    vector<size_t> sums(n+1);
    partial_sum(W.begin(), W.end(), sums.begin() + 1);
    auto sum = [&](size_t i, size_t j) {
        return sums[j] - sums[i];
    };

    auto done = [&](vector<size_t> used) {
        cout << "TAK\n" << used.size() << '\n';
        for(auto i : used)
            cout << i << " ";
        exit(0);
    };

    if(a == 0)
        done({});

    for(size_t i = 0; i < n; i++)
        if(W[i] == a)
            done({W[i]});
    for(size_t i = 0; i < n; i++)
        for(size_t j = i+1; j < n; j++)
            if(W[i] + W[j] == 2*a)
                done({W[i], W[j]});
    for(size_t i = 0; i < n; i++)
        for(size_t j = i+1; j < n; j++)
            for(size_t k = j+1; k < n; k++)
                if(W[i] + W[j] + W[k] == 3*a)
                    done({W[i], W[j], W[k]});

    vector<size_t> knapsack((n+1)*(n*a+1), SIZE_MAX);
    auto K = [&](size_t k, size_t u) -> size_t& {
        return knapsack[k*(n*a+1) + u];
    };

    K(0, 0) = 0;

    for(size_t i = 1; i <= n; i++)
    {
        auto w = W[i - 1];

        for(size_t k = i+1; k --> 1; )
        {
            size_t lo = max(sum(i-k, i-1), w), hi = min(sum(i-k, i), k*a);
            for(size_t u = hi+1; u --> lo; )
                if(K(k-1, u-w) != SIZE_MAX)
                    K(k, u) = w;
        }
    }

    for(size_t k = 1; k <= n; k++)
    {
        if(K(k, k*a) != SIZE_MAX)
        {
            vector<size_t> used;
            size_t curr = k * a;
            for(size_t l = k+1; l --> 1; )
                used.push_back(K(l, curr)), curr -= K(l, curr);
            done(used);
        }
    }

    cout << "NIE" << endl;
}
