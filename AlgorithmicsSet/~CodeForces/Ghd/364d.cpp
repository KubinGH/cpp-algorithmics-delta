#include <bits/stdc++.h>
#define gcd __gcd

using namespace std;

const size_t TRIES = 15;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;
    vector<uint64_t> A(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];

    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<size_t> dis(0, n - 1);
    uint64_t result = 0;
    unordered_map<uint64_t, size_t> cnt;
    cnt.reserve(4*n);
    for(size_t t = 0; t < TRIES; t++)
    {
        size_t p = dis(gen);
        cnt.clear();
        for(size_t i = 0; i < n; i++)
            cnt[gcd(A[p], A[i])]++;
        for(const auto& e : cnt)
        {
            if(e.first < result)
                continue;
            size_t c = 0;
            for(const auto& f : cnt)
                if(f.first % e.first == 0)
                    c += f.second;
            if(2*c >= n)
                result = max(result, e.first);
        }
    }
    cout << result;
}
