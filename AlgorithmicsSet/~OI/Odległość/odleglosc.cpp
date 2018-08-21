#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5 + 16, MAX_E = 1 << 20;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    uint32_t n;
    cin >> n;
    uint32_t m = 0;
    static uint32_t A[MAX], result[MAX], at_idx[MAX_E],
                    dist[MAX_E], first[MAX_E], result_idx[MAX];
    fill(result, result + n, -1u); fill(at_idx, at_idx + MAX_E, -1u);
    fill(dist, dist + MAX_E, -1u); fill(first, first + MAX_E, -1u);
    fill(result_idx, result_idx + n, -1u);
    queue<pair<uint32_t, uint32_t>> Q;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        m = max(m, A[i]);
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
        }
    }
    static bitset<MAX_E> is_composite;
    static vector<uint32_t> prime_divs[MAX_E];
    vector<uint32_t> primes; primes.reserve(m);
    for(uint32_t i = 2; i <= m; i += 2)
    {
        if(not is_composite[i])
        {
            primes.push_back(i);
            prime_divs[i].push_back(i);
            if(i < (1u << 11)) for(uint32_t x = 2*i; x <= m; x += i)
            {
                prime_divs[x].push_back(i);
                is_composite[x] = true;
            }
        }
        if(i == 2) i--;
    }


    set<pair<uint32_t, uint32_t>> edges;
    while(not Q.empty())
    {
        uint32_t a, i; tie(a, i) = Q.front(); Q.pop();
        for(uint32_t p : prime_divs[a])
        {
            uint32_t k = a / p;
            if(dist[k] == -1u)
            {
                first[k] = i;
                dist[k] = dist[a] + 1;
                Q.emplace(k, i);
            }
            edges.emplace(a, k);
            edges.emplace(k, a);
        }
        for(uint32_t p : primes)
        {
            if(a * p > m)
                break;
            uint32_t k = a * p;
            if(dist[k] == -1u)
            {
                first[k] = i;
                dist[k] = dist[a] + 1;
                Q.emplace(k, i);
            }
            edges.emplace(a, k);
            edges.emplace(k, a);
        }
    }

    for(auto e : edges)
    {
        uint32_t ux, vx; tie(ux, vx) = e;
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
