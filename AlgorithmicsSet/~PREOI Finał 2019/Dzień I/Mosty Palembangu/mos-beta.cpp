#include <bits/stdc++.h>

using namespace std;

struct gather_t { uint64_t forced; vector<pair<uint32_t, uint32_t>> pos; };

gather_t gather(uint32_t n)
{
    gather_t G = {0, {}};
    G.pos.reserve(n);
    for(uint32_t i = 0; i < n; i++)
    {
        char p, q; uint32_t s, t;
        cin >> p >> s >> q >> t;
        if(s > t)
            swap(s, t);
        if(p != q)
            G.pos.emplace_back(s, t), G.forced++;
        else
            G.forced += t - s;
    }
    return G;
}

uint64_t median_dist(vector<uint32_t> A)
{
    sort(A.begin(), A.end());
    uint64_t x = accumulate(A.begin(), A.begin() + A.size()/2, 0llu),
             y = accumulate(A.begin() + (A.size()+1)/2, A.end(), 0llu);
    return y - x;

}

uint64_t solve_case1(const vector<pair<uint32_t, uint32_t>>& pos)
{
    vector<uint32_t> A; A.reserve(2*pos.size());
    for(auto p : pos)
        A.push_back(p.first), A.push_back(p.second);
    return median_dist(A);
}

uint64_t solve_case2(const vector<pair<uint32_t, uint32_t>>& pos)
{
    if(pos.empty()) return 0;
    const uint32_t n = pos.size();
    vector<uint32_t> A; A.reserve(2*n);
    for(auto p : pos)
        A.push_back(p.first), A.push_back(p.second);
    uint64_t result = -1llu;
    for(uint32_t split : A)
    {
        vector<uint32_t> L, R;
        L.reserve(2*n); R.reserve(2*n);
        for(auto p : pos)
            if((p.first+p.second)/2 < split)
                L.push_back(p.first), L.push_back(p.second);
            else
                R.push_back(p.first), R.push_back(p.second);
        result = min(result, median_dist(L) + median_dist(R));
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t k, n;
    cin >> k >> n;
    auto G = gather(n);
    if(k == 1)
        cout << G.forced + solve_case1(G.pos);
    else if(k == 2)
        cout << G.forced + solve_case2(G.pos);
}

