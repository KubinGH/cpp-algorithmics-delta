#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    set<uint64_t> S;
    for(uint32_t qi = 0; qi < n; qi++)
    {
        char c; cin >> c;
        if(c == '+')
        {
            uint64_t x; cin >> x;
            S.insert(x);
        }
        else if(c == '-')
        {
            uint64_t x; cin >> x;
            S.erase(x);
        }
        else if(c == 'Q')
        {
            if(S.size() < 3)
                cout << S.size() << "\n";
            else
            {
                auto ai = S.begin(), bi = ai, ci = bi;
                bi++; ci++; ci++;
                uint32_t r = 2;
                while(ci != S.end())
                {
                    if(*ai + *bi <= *ci)
                    {
                        ai = bi;
                        bi = ci;
                        r++;
                    }
                    ci = S.lower_bound(*ai + *bi);
                }
                cout << r << "\n";
            }
        }
    }
}
