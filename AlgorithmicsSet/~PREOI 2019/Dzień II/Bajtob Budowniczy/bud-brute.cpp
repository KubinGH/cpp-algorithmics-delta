#include <bits/stdc++.h>

using namespace std;

struct brute_worker
{
    uint32_t n;
    vector<uint32_t> A, mutate;
    brute_worker(uint32_t _n) : n(_n), A(n) {}
    void set(uint32_t i, uint32_t x)
    {
        A[i] = x;
    }
    void build() {}
    uint32_t get(uint32_t a, uint32_t b)
    {
        uint32_t r = 0;
        for(uint32_t i = a; i <= b; i++)
            r ^= A[i];
        return r;
    }
    void mut(uint32_t a, uint32_t b, uint32_t x)
    {
        for(uint32_t i = a; i <= b; i++)
            A[i] = x;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    brute_worker T(n);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t x;
        cin >> x;
        T.set(i, x);
    }
    T.build();
    while(q --> 0)
    {
        uint32_t t;
        cin >> t;
        if(t == 0)
        {
            uint32_t a, b, x;
            cin >> a >> b >> x; a--; b--;
            T.mut(a, b, x);
        }
        else if(t == 1)
        {
            uint32_t a, b;
            cin >> a >> b; a--; b--;
            cout << T.get(a, b) << "\n";
        }
    }
}
