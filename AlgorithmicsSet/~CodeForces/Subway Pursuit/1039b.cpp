#include <bits/stdc++.h>

using namespace std;

const size_t P = 8, B = 4;

struct communications
{
    uint64_t n, k, p;
    mt19937_64 gen;
    uint64_t counter = 0;

    communications(uint64_t _n, uint64_t _k)
        : n(_n), k(_k), p(P * k),
          gen(chrono::high_resolution_clock::now().time_since_epoch().count()) {}

    bool query(uint64_t L, uint64_t R)
    {
        counter++;
        L = max(L, (uint64_t)1); R = min(R, n);
        cout << L << " " << R << endl;
        string response;
        cin >> response;
        bool result = response == "Yes";
        if(result and L == R)
            exit(0);
        return result;
    }

    pair<uint64_t, uint64_t> find_approx()
    {
        uint64_t lo = 1, hi = n + 1;
        while(hi - lo > p)
        {
            uint64_t mid = (lo + hi) / 2;
            if(query(1, mid))
                hi = mid;
            else
                lo = mid+1;
        }
        return {lo > p ? lo - p : 1, lo+p < n ? lo + p : n};
    }

    bool bombard(uint64_t L, uint64_t R)
    {
        uint64_t i = uniform_int_distribution<uint64_t>{L, R}(gen);
        return query(i, i);
    }
};

int main()
{
    uint64_t n, k;
    cin >> n >> k;
    communications comm(n, k);
    while(comm.counter < 4444)
    {
        uint64_t L, R;
        tie(L, R) = comm.find_approx();
        for(size_t i = 0; i < B; i++)
            comm.bombard(L, R);
    }
    abort();
}
