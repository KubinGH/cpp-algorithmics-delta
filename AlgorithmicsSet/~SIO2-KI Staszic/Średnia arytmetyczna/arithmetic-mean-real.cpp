#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n; int a;
    cin >> n >> a;

    if(a == 0)
    {
        cout << "TAK\n0" << endl;
        return 0;
    }

    vector<int> W(n);
    for(auto& w : W)
        cin >> w, w -= a;
    sort(W.begin(), W.end());
    int lo = 0, hi = 0;
    for(auto w : W)
    {
        if(w < 0) lo += w;
        else hi += w;
    }
    if(W.front() < 0) lo += W.front();
    if(W.back()  > 0) hi += W.back();

    vector<vector<size_t>> knapsack(hi - lo + 1);
    auto K = [&](int x) -> vector<size_t>& {
        return knapsack[size_t(x - lo)];
    };

    for(size_t i = 0; i < n; i++)
    {
        auto w = W[i];
        #define ITER { \
            if(K(u).empty() and (not K(u - w).empty() or u - w == 0)) \
                K(u) = K(u - w), K(u).push_back(w); \
        }
        if(w >= 0) { for(int u = hi+1; u --> lo+w; )
            ITER;
        } else { for(int u = lo; u <= hi+w; u++)
            ITER;
        }
        #undef ITER
    }

    if(not K(0).empty())
    {
        cout << "TAK\n" << K(0).size() << '\n';
        for(auto x : K(0))
            cout << x+a << " ";
        cout << endl;
    }
    else
        cout << "NIE" << endl;
}
