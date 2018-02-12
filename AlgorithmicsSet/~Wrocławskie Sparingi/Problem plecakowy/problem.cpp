#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 7000;

template<typename T1, typename T2>
ostream& operator<< (ostream& out, pair<T1, T2> p)
{
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; uint64_t m;
    cin >> n >> m;
    static array<pair<uint64_t, uint64_t>, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i].first >> A[i].second;
    sort(A.begin(), A.begin() + n);
    map<uint64_t, uint32_t> M;
    M[A[0].first] = 0;
    uint32_t lb = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(A[i].second >= A[lb].second)
            M[A[i].first] = i, lb = i;
        else
            M[A[i].first] = lb;
    }
    uint64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(A[i].first > m)
            break;
        for(uint32_t j = i+1; j < n; j++)
        {
            if(A[i].first + A[j].first > m)
                break;
            if(n > 500)
            {
                r = max(r, A[i].second + A[j].second);
                auto it = M.lower_bound(m - A[i].first - A[j].first);
                if(it == M.end()) it--;
                uint32_t k = it->second;
                if(k <= j)
                    break;
                r = max(r, A[i].second + A[j].second + A[k].second);
            }
            else
            {
                for(uint32_t k = j+1; k < n; k++)
                {
                    if(A[i].first + A[j].first + A[k].first > m)
                        break;
                    r = max(r, A[i].second + A[j].second + A[k].second);
                }
                r = max(r, A[i].second + A[j].second);
            }
        }
        r = max(r, A[i].second);
    }
    cout << r;
}
