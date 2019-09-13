#include <bits/stdc++.h>

using namespace std;

const size_t RANGE = 1 << 18;

int main()
{
    size_t n, a;
    cin >> n >> a;

    vector<size_t> w(n);
    for(size_t i = 0; i < n; i++)
        cin >> w[i];
    sort(w.begin(), w.end());

    auto done = [&](vector<size_t> used) {
        cout << "TAK\n" << used.size() << '\n';
        for(auto i : used)
            cout << i << " ";
        exit(0);
    };

    if(a == 0)
        done({});

    auto maybe = [&](int cost, size_t target) {
        vector<size_t> B(target+1, SIZE_MAX);
        vector<int> Q(target+1, INT_MAX/2);
        Q[0] = 0;
        for(size_t i = 0, sum = 0; i < n; i++)
        {
            size_t ww = w[i]; sum += ww; sum = min(sum, target);
            for(size_t u = sum+1; u --> w[i]; )
                if(Q[u - ww] + cost < Q[u])
                    Q[u] = Q[u - ww] + cost, B[u] = ww;
        }
        vector<size_t> used;
        size_t curr = target;
        if(B[curr] == SIZE_MAX)
            return vector<size_t>{};
        while(curr)
        {
            used.push_back(B[curr]);
            curr -= B[curr];
        }
        return used;
    };

    for(size_t k = 1; k <= n; k++)
    {
        cerr << "k = " << k << endl;
        size_t lo = 0, hi = 2*RANGE;
        while(lo < hi)
        {
            size_t mid = (lo + hi) / 2;
            int cost = int(mid) - RANGE;
            auto used = maybe(cost, k * a);
            if(used.size() < k)
                hi = mid;
            else
                lo = mid+1;
        }
        auto used = maybe(int(lo) - RANGE, k * a);
        if(used.size() == k)
            done(used);
    }

    cout << "NIE" << endl;
}
