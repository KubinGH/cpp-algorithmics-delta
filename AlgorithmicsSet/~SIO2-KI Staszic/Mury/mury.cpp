  #include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000;
const size_t MAX_E = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, h;
    cin >> n >> h;
    vector<uint32_t> N, S;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t c;
        cin >> c;
        if(i % 2 == 0)
            S.push_back(c);
        else
            N.push_back(c);
    }
    sort(N.begin(), N.end()); sort(S.rbegin(), S.rend());
    uint32_t minim = n + 1, minim_count = 0;
    uint32_t np = 0, sp = 0;
    for(uint32_t nk = 1, ns = h; nk < h + 1; nk++, ns--)
    {
        while(np < N.size() and N[np] < nk) np++;
        while(sp < S.size() and S[sp] >= ns) sp++;
        uint32_t v = (N.size() - np) + sp;
        if(v < minim)
        {
            minim = v;
            minim_count = 1;
        }
        else if(v == minim)
            minim_count++;
    }
    cout << minim << " " << minim_count;
}
