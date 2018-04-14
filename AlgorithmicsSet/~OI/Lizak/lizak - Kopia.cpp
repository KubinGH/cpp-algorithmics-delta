#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<uint32_t, MAX+1> A, S, SI;
    set<uint32_t> after1, after2;
    vector<uint32_t> to_insert1, to_insert2;
    static pair<uint32_t, uint32_t> available[2*MAX+1];
    static array<bool, 2*MAX+1> is_available;
    after1.insert(1); after2.insert(2);
    S[0] = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        if(c == 'W')
        {
            A[i] = 1;
            S[i+1] = S[i] + A[i];
            SI[S[i+1]] = i + 1;
            while(not after1.empty())
            {
                uint32_t x = *after1.begin(); after1.erase(after1.begin());
                is_available[x] = true;
                available[x].second = i;
                available[x].first = SI[S[i+1] - x];
                after2.erase(x);
                cout << x << ": 1" << endl;
                cout << 0 << endl;
                if(not is_available[x+1])
                {
                    cout << 0.1 << endl;
                    to_insert1.push_back(x+1);
                }
                cout << 1 << endl;
                if(not is_available[x+2])
                {
                    cout << 1.1 << endl;
                    after2.insert(x+2);
                }
            }
            for(uint32_t x : to_insert1)
                after1.insert(x);
            to_insert1.clear();
        }
        else if(c == 'T')
        {
            A[i] = 2;
            S[i+1] = S[i] + A[i];
            SI[S[i+1]] = i + 1;
            while(not after2.empty())
            {
                uint32_t x = *after2.begin(); after2.erase(after2.begin());
                is_available[x] = true;
                available[x].second = i;
                available[x].first = SI[S[i+1] - x];
                after1.erase(x);
                cout << x << ": 2" << endl;
                cout << 0 << endl;
                if(not is_available[x+1])
                {
                    cout << 0.1 << endl;
                    after1.insert(x+1);
                }
                cout << 1 << endl;
                if(not is_available[x+2])
                {
                    cout << 1.1 << endl;
                    to_insert2.push_back(x+2);
                }
            }
            for(uint32_t x : to_insert2)
                after2.insert(x);
            to_insert2.clear();
        }
    }
    for(uint32_t i = 0; i < 2*MAX+1; i++)
        if(is_available[i])
            cout << i << ": [" << available[i].first << ", " << available[i].second << "]" << endl;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t k;
        cin >> k;
        auto p = available[k];
        if(is_available[k])
            cout << p.first + 1 << " " << p.second + 1 << "\n";
        else
            cout << "NIE\n";
    }
}
