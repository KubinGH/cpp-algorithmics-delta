#include <bits/stdc++.h>

using namespace std;

typedef tuple<uint64_t, set<uint32_t>, uint32_t> coral;

struct coralcomp
{
    bool operator() (const coral& lhs, const coral& rhs)
    {
        if(get<0>(lhs) == get<0>(rhs))
        {
            return lexicographical_compare(get<1>(rhs).begin(), get<1>(rhs).end(),
                                           get<1>(lhs).begin(), get<1>(lhs).end());
        }
        return get<0>(lhs) > get<0>(rhs);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k; k--;
    if(k == 0) { cout << "0"; return 0; }
    vector<pair<uint64_t, uint32_t>> O(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> O[i].first, O[i].second = i;
    sort(O.begin(), O.end());
    priority_queue<coral, vector<coral>, coralcomp> Q;
    Q.emplace(O[0].first, set<uint32_t>{O[0].second}, 0);
    while(not Q.empty() and --k)
    {
        auto c = Q.top(); Q.pop();
        uint32_t t = get<2>(c);
        if(t == n-1) continue;
        set<uint32_t> zf = get<1>(c);
        zf.erase(O[t].second); zf.insert(O[t+1].second);
        Q.emplace(get<0>(c) + O[t+1].first - O[t].first, zf, t+1);
        zf.insert(O[t].second);
        Q.emplace(get<0>(c) + O[t+1].first, zf, t+1);
    }
    if(Q.empty()) return 0;
    cout << get<0>(Q.top()) << "\n";
    for(uint32_t i : get<1>(Q.top()))
        cout << i+1 << " ";
}
