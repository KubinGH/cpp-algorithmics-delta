#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5 + 16, MAX_E = 1 << 20;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    uint32_t n;
    cin >> n;
    uint32_t m = 0;
    static uint32_t A[MAX], at_idx[MAX_E], result_idx[MAX], first[MAX_E], dist[MAX_E], result[MAX];
    fill(result, result + n, -1u); fill(result_idx, result_idx + n, -1u);
    queue<pair<uint32_t, uint32_t>> Q;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        if(A[i] > m) m = A[i];
    }
    fill(dist, dist + m, -1u); fill(first, first + m+1, -1u);
    fill(at_idx, at_idx + m+1, -1u);
    for(uint32_t i = 0; i < n; i++)
    {
        if(at_idx[A[i]] != -1u)
        {
            if(result[at_idx[A[i]]])
            {
                result[at_idx[A[i]]] = 0;
                result_idx[at_idx[A[i]]] = i;
            }
            result[i] = 0;
            result_idx[i] = at_idx[A[i]];
        }
        else
        {
            at_idx[A[i]] = i;
            dist[A[i]] = 0;
            first[A[i]] = i;
            Q.emplace(A[i], i);
            Q.emplace(A[i], i | (1<<30));
        }
    }
    static bitset<MAX_E> is_composite;
    static vector<uint32_t> prime_divs[MAX_E];
    static uint32_t primes[MAX_E]; uint32_t jp = 0;
    primes[jp++] = 2; prime_divs[2].push_back(2);
    for(uint32_t i = 1; i <= m; i++)
        prime_divs[i].reserve(7);
    for(uint32_t i = 4; i <= m; i += 2)
        prime_divs[i].push_back(2), is_composite[i] = true;
    for(uint32_t i = 3; i <= m; i += 2)
    {
        if(not is_composite[i])
        {
            primes[jp++] = i;
            prime_divs[i].push_back(i);
            for(uint32_t x = 2*i; x <= m; x += i)
            {
                prime_divs[x].push_back(i);
                is_composite[x] = true;
            }
        }
    }
    primes[jp] = -1u;

    vector<pair<uint32_t, uint32_t>> edges;
    edges.reserve(m*5);
    while(not Q.empty())
    {
        uint32_t a, i; tie(a, i) = Q.front(); Q.pop();
        if(not (i & (1<<30))) for(uint32_t p : prime_divs[a])
        {
            uint32_t k = a / p;
            if(dist[k] == -1u)
            {
                first[k] = i;
                dist[k] = dist[a] + 1;
                Q.emplace(k, i);
                Q.emplace(k, i|(1<<30));
            }
        }
        else for(uint32_t j = 0, p = primes[0]; a * (p = primes[j]) <= m; j++)
        {
            uint32_t k = a * p;
            if(dist[k] == -1u)
            {
                first[k] = i^(1<<30);
                dist[k] = dist[a] + 1;
                Q.emplace(k, i|(1<<30));
            }
            edges.emplace_back(a, k);
        }
    }

    for(uint32_t ph = 0; ph < 2; ph++) for(auto e : edges)
    {
        uint32_t ux, vx; tie(ux, vx) = e;
        if(ph) swap(ux, vx);
        uint32_t u = first[ux], v = first[vx];
        if(u != v)
        {
            uint32_t d = dist[ux] + dist[vx] + 1;
            if(d < result[u] or (d == result[u] and v < result_idx[u]))
            {
                result[u] = d;
                result_idx[u] = v;
            }
        }
    }
    for(uint32_t i = 0; i < n; i++)
        cout << result_idx[i]+1 << "\n";
}
