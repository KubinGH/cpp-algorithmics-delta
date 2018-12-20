#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 1 << 17, MAX_Q = 1 << 17, MAX_A = 1 << 17;

struct mex_tree
{
    size_t w;
    vector<uint32_t> values;
    mex_tree(size_t n)
    {
        w = 1 << (31 - __builtin_clz(2*n-1));
        values.resize(2*w, -1u);
    }
    void set(size_t p, uint32_t v)
    {
        p += w;
        values[p] = v;
        while(p > 1)
            p /= 2, values[p] = min(values[2*p], values[2*p+1]);
    }
    uint32_t get() const { return values[1]; }
    void push(uint32_t p) { set(p, -1u); }
    void pop(uint32_t p) { set(p, p); }
};

struct query_t
{
    uint32_t L, R, i;
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    uint32_t n, q;
    cin >> n >> q;
    using pair_u32 = pair<uint32_t, uint32_t>;
    vector<uint32_t> A(n);
    static uint32_t mark[MAX_A];
    fill(mark, mark + MAX_A, -1u);
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        mark[A[i]] = i;
    }

    // Sieve
    bitset<MAX_A> is_prime; is_prime.set();
    is_prime[0] = is_prime[1] = false;
    vector<uint32_t> primes;
    static uint32_t prime_no[MAX_A];
    fill(prime_no, prime_no + MAX_A, -1u);
    static vector<uint32_t> prime_divs[MAX_A];
    vector<pair_u32> F;
    primes.reserve(1<<14);
    is_prime[0] = is_prime[1] = false;
    for(uint32_t i = 2; i < MAX_A; i += 2)
    {
        if(is_prime[i])
        {
            prime_no[i] = primes.size(), primes.push_back(i);
            if(mark[i] != -1u)
                prime_divs[i].push_back(i);
        }
        for(uint32_t x = 2*i; x < MAX_A; x += i)
        {
            if(mark[x] != -1u)
                prime_divs[x].push_back(i);
            is_prime[x] = false;
        }
        if(i == 2)
            i--;
    }
    vector<vector<pair_u32>> B(n);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t b = A[i];
        for(uint32_t p : prime_divs[A[i]])
        {
            B[i].emplace_back(prime_no[p], 0);
            while(b % p == 0)
                b /= p, B[i].back().second++;
        }
    }

    // Query preprocessing
    vector<query_t> queries(q);
    for(uint32_t i = 0; i < q; i++)
    {
        queries[i].i = i;
        cin >> queries[i].L >> queries[i].R;
        queries[i].L--; queries[i].R--;
    }
    const uint32_t nRT = 320; // = pV
    auto mo_cmp = [&](const query_t& lhs, const query_t& rhs)
    {
        if(lhs.L / nRT != rhs.L / nRT)
            return lhs.L / nRT < rhs.L / nRT;
        else
            return lhs.R < rhs.R or (lhs.R == rhs.R and lhs.i < rhs.i);
    };
    sort(queries.begin(), queries.end(), mo_cmp);

    // Solve
    vector<uint32_t> fcount(primes.size());
    mex_tree free(primes.size());
    for(uint32_t i = 0; i < primes.size(); i++)
        free.pop(i);
    auto push = [&](uint32_t i) {
        for(auto p : B[i])
        {
            if(fcount[p.first] == 0)
                free.push(p.first);
            fcount[p.first] += p.second;
        }
    };
    auto pop = [&](uint32_t i) {
        for(auto p : B[i])
        {
            fcount[p.first] -= p.second;
            if(fcount[p.first] == 0)
                free.pop(p.first);
        }
    };
    vector<uint32_t> result(q);
    uint32_t cL = 0, cR = 0;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        query_t cq = queries[qi]; cq.R++;
        while(cL > cq.L)
            push(--cL);
        while(cR < cq.R)
            push(cR++);
        while(cL < cq.L)
            pop(cL++);
        while(cR > cq.R)
            pop(--cR);
        result[cq.i] = free.get();
    }

    // Output
    for(uint32_t i = 0; i < q; i++)
        cout << primes[result[i]] << "\n";
}
