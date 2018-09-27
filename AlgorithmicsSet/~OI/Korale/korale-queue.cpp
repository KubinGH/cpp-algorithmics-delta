#include <bits/stdc++.h>
#ifdef XHOVA
#define cdbg cerr
#define init_io
#else
#define cdbg if(0) cerr
#define init_io { ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); }
#endif // XHOVA

using namespace std;

typedef tuple<uint64_t, uint32_t, set<uint32_t>, bool> coral;

struct coralcomp
{
    bool operator() (const coral& lhs, const coral& rhs)
    {
        if(get<0>(lhs) == get<0>(rhs))
        {
            if(get<2>(lhs) == get<2>(rhs))
            {
                if(get<1>(lhs) == get<1>(rhs))
                    return get<3>(lhs) > get<3>(rhs);
                return get<1>(lhs) > get<1>(rhs);
            }
            return lexicographical_compare(get<2>(rhs).begin(), get<2>(rhs).end(),
                                           get<2>(lhs).begin(), get<2>(lhs).end());
        }
        return get<0>(lhs) > get<0>(rhs);
    }
};

int main()
{
    init_io;
    uint32_t n, k;
    cin >> n >> k; k--;
    vector<pair<uint32_t, uint32_t>> O(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> O[i].first, O[i].second = i;
    sort(O.begin(), O.end());
    vector<uint32_t> A(n), T(n);
    for(uint32_t i = 0; i < n; i++)
        A[i] = O[i].first, T[i] = O[i].second;
    priority_queue<coral, vector<coral>, coralcomp> Q;
    Q.emplace(0ull, 0u, set<uint32_t>(), 1);
    while(k)
    {
        auto c = Q.top(); Q.pop();
        if(get<3>(c)) k--;
        cdbg << get<0>(c) << endl;
        for(uint32_t a : get<2>(c))
            cdbg << T[a]+1 << " ";
        cdbg << endl;
        cdbg << "--" << endl;
        if(get<1>(c) == n) continue;
        Q.emplace(get<0>(c), get<1>(c)+1, get<2>(c), 0);
        set<uint32_t> d = get<2>(c);
        d.insert(get<1>(c));
        Q.emplace(get<0>(c) + A[get<1>(c)], get<1>(c)+1, d, 1);
    }
    auto c = Q.top();
    cout << get<0>(c) << "\n";
    vector<uint32_t> R;
    for(uint32_t a : get<2>(c))
        R.push_back(T[a]);
    sort(R.begin(), R.end());
    for(uint32_t a : R)
        cout << a+1 << " ";
}
