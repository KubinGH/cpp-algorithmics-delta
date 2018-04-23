#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000, TSIZE = 1 << 19;

struct segment_tree
{
    array<uint32_t, TSIZE> values;
    void set(uint32_t i, uint32_t value)
    {
        i += TSIZE/2;
        values[i] = value;
        while(i != 1)
            i /= 2, values[i] = max(values[2*i], values[2*i+1]);
    }
    uint32_t get(uint32_t i, uint32_t tbegin, uint32_t tend,
                             uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return max(get(2*i,   tbegin, (tbegin+tend)/2, sbegin, send),
                       get(2*i+1, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint32_t get(uint32_t sbegin, uint32_t send)
    {
        return get(1, 0, TSIZE/2-1, sbegin, send);
    }
};

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    static pair<uint32_t, uint32_t> B[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i].first, B[i].second = i;
    sort(B, B + n);
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0, f = 0; i < n; i++)
        A[B[i].second] = i - f;
    static segment_tree tree;
    uint32_t result = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        tree.set(A[i], (A[i] ? tree.get(0, A[i]-1) : 0) + 1);
        result = max(result, tree.values[1]);
        if(i >= k)
            tree.set(A[i-k], 0);
    }
    cout << result;
}
