#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5;

uint32_t answers[MAX];
tuple<bool, uint32_t, uint32_t> queries[MAX];

void solve(uint32_t ibegin, uint32_t iend)
{
    if(ibegin == iend)
        return;
    uint32_t mid = (ibegin+iend)/2;
    vector<pair<uint32_t, uint32_t>> M;
    for(uint32_t i = ibegin; i <= mid; i++)
    {
        if(get<0>(queries[i]) == 0)
            M.emplace_back(get<2>(queries[i]), get<1>(queries[i]));
    }
    sort(M.rbegin(), M.rend());
    vector<pair<pair<uint32_t, uint32_t>, uint32_t>> D;
    for(uint32_t i = mid+1; i <= iend; i++)
    {
        if(get<0>(queries[i]) == 1)
            D.emplace_back(make_pair(get<2>(queries[i]), get<1>(queries[i])), i);
    }
    sort(D.rbegin(), D.rend());
    deque<pair<uint32_t, uint32_t>> Q;
    for(uint32_t i = 0, j = 0; i < D.size(); i++)
    {
        while(j < M.size() and M[j].first >= D[i].first.first)
        {
            while(not Q.empty() and Q.back().first >= M[j].second)
                Q.pop_back();
            Q.emplace_back(M[j].second, M[j].first);
            j++;
        }
        if(not Q.empty())
        {
            auto it = upper_bound(Q.begin(), Q.end(), make_pair(D[i].first.second, -1u));
            if(it != Q.begin())
                answers[D[i].second] = min(answers[D[i].second], (--it)->second);
        }
    }
    solve(ibegin, mid);
    solve(mid+1, iend);
}

int main()
{
    uint32_t n, q;
    cin >> n >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        char c;
        cin >> c >> get<1>(queries[i]) >> get<2>(queries[i]);
        get<0>(queries[i]) = c == 'D';
    }
    fill(answers, answers + q, -1u);
    solve(0, q-1);
    for(uint32_t i = 0; i < q; i++)
        if(get<0>(queries[i]) == 1)
            cout << int(answers[i]) << "\n";
}
