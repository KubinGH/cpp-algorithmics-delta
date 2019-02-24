#include <bits/stdc++.h>

using namespace std;

struct bauble { uint32_t r, q; };

unordered_map<uint64_t, uint32_t> cache;
uint32_t solve(const vector<bauble>& B, uint32_t i, uint32_t req_r)
{
    if(i == 0)
        return 0;
    if(cache.find(i+(req_r<<10)) != cache.end())
        return cache[i+(req_r<<10)];
    uint32_t result = solve(B, i - 1, req_r);
    if(req_r <= B[i-1].r)
        result = max(result, solve(B, i - 1, req_r + B[i-1].q) + 1);
    return cache[i+(req_r<<10)] = result;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<bauble> B(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i].r >> B[i].q;
    sort(B.begin(), B.end(), [&](bauble a, bauble b) {
        return make_tuple(b.r+b.q, a.q, a.r) < make_tuple(a.r+a.q, b.q, b.r);
    });
    cout << solve(B, n, 0);
}
