#include <bits/stdc++.h>

using namespace std;

const size_t MAX_V = 128;

long long conta(int S, int s[], int P, int p[])
{
    uint32_t people = P, plates = S;
    uint32_t *content = (uint32_t*)s, *preference = (uint32_t*)p;
    uint64_t result = 0;
    vector<uint32_t> positions[MAX_V];
    for(uint32_t i = 0; i < plates; i++)
        positions[content[i]].push_back(i);
    for(uint32_t right = plates+1; right --> 0; )
    {
        uint32_t lo = 0, hi = right;
        while(lo < hi)
        {
            uint32_t mid = (lo+hi)/2;
            uint32_t p = 0;
            for(uint32_t i = mid; i < right and p < people; i++)
            {
                if(content[i] == preference[p])
                    p++;
                else
                {
                    auto poslist = positions[preference[p]];
                    if(i > poslist.back())
                        break;
                    auto it = lower_bound(poslist.begin(), poslist.end(), i);
                    i = *it - 1;
                }
            }
            if(p == people)
                lo = mid + 1;
            else
                hi = mid;
        }
        cerr << lo << ", " << right << endl;
        result += lo;
    }
    return result;
}

#ifdef XHOVA
int main()
{
    int S, P;
    cin >> S >> P;
    static int s[1024], p[1024];
    for(int i = 0; i < S; i++)
        cin >> s[i];
    for(int i = 0; i < P; i++)
        cin >> p[i];
    cout << conta(S, s, P, p);
}
#endif
