#include <bits/stdc++.h>

using namespace std;

struct query_t { uint32_t L, R, i; };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    uint32_t n, q;
    cin >> n >> q;
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    uint32_t max_a = max(4 * (*max_element(A.begin(), A.end()) + 1), 32u);
    vector<bool> mark(max_a);
    for(uint32_t i = 0; i < n; i++)
        mark[A[i]] = true;

    // Sieve
    vector<bool> is_prime(max_a, true);
    is_prime[0] = is_prime[1] = false;
    vector<uint32_t> primes; primes.reserve(1<<16);
    vector<uint32_t> prime_no(max_a, -1u);
    vector<vector<uint32_t>> prime_divs(max_a);
    is_prime[0] = is_prime[1] = false;
    for(uint32_t i = 2; i < max_a; i += 2)
    {
        if(not is_prime[i])
            continue;
        prime_no[i] = primes.size();
        primes.push_back(i);
        if(mark[i])
            prime_divs[i].push_back(i);
        for(uint32_t x = 2*i; x < max_a; x += i)
        {
            if(mark[x])
                prime_divs[x].push_back(i);
            is_prime[x] = false;
        }
        if(i == 2)
            i--;
    }
    // Occurences
    vector<vector<uint32_t>> prime_occ(primes.size());
    for(uint32_t p = 0; p < primes.size(); p++)
        prime_occ[p].push_back(0);
    for(uint32_t i = 0; i < n; i++)
        for(uint32_t p : prime_divs[A[i]])
            prime_occ[prime_no[p]].push_back(i+1);
    for(uint32_t p = 0; p < primes.size(); p++)
        prime_occ[p].push_back(n+1);

    // Query preprocessing
    vector<query_t> Q(q);
    for(uint32_t i = 0; i < q; i++)
        cin >> Q[i].L >> Q[i].R, Q[i].i = i;
    sort(Q.begin(), Q.end(), [&](const query_t& lhs, const query_t& rhs) {
        return lhs.R > rhs.R or (lhs.R == rhs.R and make_pair(lhs.L, lhs.i) < make_pair(rhs.L, rhs.i));
    });
    // Build tree
    uint32_t w = 1 << (31 - __builtin_clz(2*(n+2)-1));
    vector<vector<query_t>> T(2*w);
    for(auto p : Q)
    {
        uint32_t v = p.L + w;
        T[v].push_back(p);
        while(v > 1)
            v /= 2, T[v].push_back(p);
    }

    // Solve
    vector<uint32_t> result(q, -1u);
    for(uint32_t p = 0; p < primes.size(); p++)
    {
        for(uint32_t pi = 0; pi+1 < prime_occ[p].size(); pi++)
        {
            uint32_t qL = prime_occ[p][pi]+1, qR = prime_occ[p][pi+1]-1;
            if(qL > qR) continue;
            uint32_t pL = qL, pR = qR;
            auto handle_node = [&](vector<query_t>& bucket) {
                while(not bucket.empty() and pL <= bucket.back().L and bucket.back().R <= pR)
                {
                    result[bucket.back().i] = min(result[bucket.back().i], primes[p]);
                    bucket.pop_back();
                }
            };
            for(qL += w, qR += w+1; qL < qR; qL /= 2, qR /= 2)
            {
                if(qL % 2) handle_node(T[qL++]);
                if(qR % 2) handle_node(T[--qR]);
            }
        }
    }
    for(uint32_t i = 0; i < q; i++)
        cout << result[i] << "\n";
}
