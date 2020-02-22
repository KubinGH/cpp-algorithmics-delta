#include <bits/stdc++.h>

using namespace std;

struct max_monoqueue
{
    size_t l = 0, r = 0;
    deque<pair<int, size_t>> Q;

    pair<int, size_t> max() const
    {
        return Q.empty() ? make_pair(0, SIZE_MAX) : Q.front();
    }

    void push_back(int v)
    {
        pair<int, size_t> x = {v, r++};
        while(not Q.empty() and Q.back() < x)
            Q.pop_back();
        Q.push_back(x);
    }

    void pop_front()
    {
        if(l++ == Q.front().second)
            Q.pop_front();
    }
};
struct min_monoqueue
{
    max_monoqueue Q;
    pair<int, size_t> min() const { auto [x, i] = Q.max(); return {-x, i}; }
    void push_back(int v) { return Q.push_back(-v); }
    void pop_front() { return Q.pop_front(); }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int t;
    cin >> t >> n;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    max_monoqueue Q; min_monoqueue P;
    auto ok = [&]() {
        return Q.max().first - P.min().first <= t;
    };

    size_t result = 0;

    for(size_t l = 0, r = 0; l < n; l++)
    {
        while(r < n and ok())
        {
            Q.push_back(A[r]); P.push_back(A[r]);
            r++;
        }

        result = max(result, r - l - (not ok()));

        Q.pop_front();
        P.pop_front();
    }

    cout << result;
}
