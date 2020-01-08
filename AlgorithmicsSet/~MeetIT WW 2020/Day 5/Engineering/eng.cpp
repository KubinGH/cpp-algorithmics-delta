#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<size_t> A(n);
    vector<int> B(n);
    for(auto& a : A)
        cin >> a, a--;
    for(auto& b : B)
        cin >> b;

    vector<vector<int>> want(k);
    for(size_t i = 0; i < n; i++)
        want[A[i]].push_back(B[i]);

    size_t req = 0;
    vector<int> unbound;
    unbound.reserve(n);
    for(auto& w : want)
    {
        if(w.empty())
        {
            req++;
            continue;
        }
        iter_swap(--w.end(), max_element(w.begin(), w.end()));
        for(size_t j = 0; j + 1 < w.size(); j++)
            unbound.push_back(w[j]);
    }

    nth_element(unbound.begin(), unbound.begin() + req, unbound.end());

    int64_t cost = 0;
    for(size_t i = 0; i < req; i++)
        cost += unbound[i];

    cout << cost;
}
