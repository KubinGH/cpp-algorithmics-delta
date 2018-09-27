#include <bits/stdc++.h>
#pragma GCC optimize ("O3")

using namespace std;

const size_t MAX_V = 128;

uint32_t own_lower_bound(vector<uint32_t>& A, uint32_t a)
{
    uint32_t lo = 0, hi = A.size();
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;
        if(A[mid] >= a)
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

long long conta(int S, int s[], int P, int p[])
{
    uint32_t people = P, plates = S;
    uint32_t *content = (uint32_t*)s, *preference = (uint32_t*)p;
    uint64_t result = 0;
    vector<uint32_t> positions[MAX_V];
    for(uint32_t i = 0; i < plates; i++)
        positions[content[i]].push_back(i);
    auto cando = [&](uint32_t left, uint32_t right) {
        uint32_t p = 0;
        for(uint32_t i = left; i < right and p < people; i++)
        {
            if(content[i] == preference[p])
                p++;
            else
            {
                auto poslist = positions[preference[p]];
                if(i > poslist.back())
                    break;
                i = poslist[own_lower_bound(poslist, i)] - 1;
            }
        }
        return p == people;
    };
    uint32_t lo = 0, hi = plates;
    while(lo < hi)
    {
        uint32_t mid = (lo+hi)/2;
        if(cando(mid, plates))
            lo = mid + 1;
        else
            hi = mid;
    }
    result += lo;
    for(uint32_t left = lo+1, right = plates; right --> 0; )
    {
        while(left != 0 and not cando(left-1, right))
            left--;
        if(left == 0) break;
        result += left;
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
