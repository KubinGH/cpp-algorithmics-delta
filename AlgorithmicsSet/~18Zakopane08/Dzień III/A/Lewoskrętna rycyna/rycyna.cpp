#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 18, TSIZE = 1 << 19;

template<typename T>
size_t own_upper_bound(const vector<T>& A, T a)
{
    size_t lo = 0, hi = A.size();
    while(lo < hi)
    {
        size_t mid = (lo + hi) / 2;
        if(A[mid] > a)
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

struct segment_set_tree
{
    vector<uint32_t> values[TSIZE];
    void insert(uint32_t i, uint32_t x)
    {
        i += TSIZE/2;
        values[i].push_back(x);
        while(i > 1)
            i /= 2, values[i].push_back(x);
    }
    uint32_t get(size_t sbegin, size_t send, uint32_t lo, uint32_t hi)
    {
        send++;
        uint32_t result = 0; bool any = false;
        for(sbegin += TSIZE/2, send += TSIZE/2; sbegin < send;
            sbegin /= 2, send /= 2)
        {
            if(sbegin % 2 == 1)
            {
                if(not values[sbegin].empty())
                {
                    auto it = own_upper_bound(values[sbegin], hi);
                    if(it != 0 and values[sbegin][--it] >= lo)
                        result = max(result, values[sbegin][it]), any = true;
                }
                sbegin++;
            }
            if(send % 2 == 1)
            {
                send--;
                if(not values[send].empty())
                {
                    auto it = own_upper_bound(values[send], hi);
                    if(it != 0 and values[send][--it] >= lo)
                        result = max(result, values[send][it]), any = true;
                }
            }
        }
        return any ? result : -1u;
    }
};

char FCHAR;
template<typename T>
void load_dec_unsafe(T& x)
{
    while(isdigit(FCHAR = getchar()))
        x *= 10, x += FCHAR - '0';
}

int main()
{
    uint32_t n = 0;
    load_dec_unsafe(n);
    static uint32_t A[MAX];
    static segment_set_tree tree;
    uint32_t m = 0;
    for(uint32_t i = 0; i < n; i++)
        load_dec_unsafe(A[i]), tree.insert(A[i], i), m = max(m, A[i]);
    uint32_t q = 0;
    load_dec_unsafe(q);
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t x = 0, y = 0;
        load_dec_unsafe(x); load_dec_unsafe(y); x--; y--;
        uint32_t ra = -1u, rb = -1u;
        uint32_t mm = -1u;
        for(uint32_t a = x; a < y - (rb - ra); a++)
        {
            if(A[a] == m or A[a] >= mm) continue;
            uint32_t b = tree.get(A[a]+1, m, a+1, y);
            if(b != -1u and b - a > rb - ra)
                ra = a, rb = b;
            mm = min(mm, A[a]);
        }
        if(ra != -1u) ra++; if(rb != -1u) rb++;
        printf("%u %u\n", ra, rb);
    }
}
