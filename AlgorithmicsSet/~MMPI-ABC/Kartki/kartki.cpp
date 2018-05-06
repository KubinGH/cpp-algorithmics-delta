#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5, MAX_C = 1e6, TSIZE = 1 << 21;

struct segment_tree
{
    uint32_t values[TSIZE];
    void increment(uint32_t i)
    {
        i += TSIZE/2;
        values[i]++;
        while(i > 1)
            i /= 2, values[i]++;
    }
    uint32_t get(uint32_t i, uint32_t tbegin, uint32_t tend,
                             uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return get(2*i,   tbegin, (tbegin+tend)/2, sbegin, send)
                 + get(2*i+1, (tbegin+tend)/2+1, tend, sbegin, send);
    }
    uint32_t get(uint32_t sbegin, uint32_t send)
        { return get(1, 0, TSIZE/2-1, sbegin, send); }
};

int main()
{
    uint32_t n;
    cin >> n;
    static pair<uint32_t, uint32_t> A[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i].first >> A[i].second;
        if(A[i].second < A[i].first)
            swap(A[i].first, A[i].second);
    }
    sort(A, A + n);
    static segment_tree tree;
    uint64_t result = 0;
    uint32_t la = -1u;
    for(uint32_t i = 0; i < n; i++)
    {
        while(la+1 < i and A[la+1].first != A[i].first)
            la++, tree.increment(A[la].second);
        uint64_t t = tree.get(0, A[i].second - 1);
        result += (uint64_t)t;
    }
    cout << result;
}
