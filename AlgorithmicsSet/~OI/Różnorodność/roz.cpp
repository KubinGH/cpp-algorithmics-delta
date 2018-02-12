#include <bits/stdc++.h>
#define MAX 8192
#define MAX_E 131072

using namespace std;

void load_uint32_t(uint32_t* p)
{
    char ch = getchar();
    *p = ch - '0';
    while('0' <= (ch = getchar()) and ch <= '9')
    {
        *p *= 10; *p += ch - '0';
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    static uint32_t A[MAX*MAX], AR[MAX*MAX];
    uint32_t m, n, k; // height, width, fragment size
    uint32_t i, j, x, y; // iteration: row/column
    load_uint32_t(&m); load_uint32_t(&n); load_uint32_t(&k);
    for(i = 0; i < m; ++i)
    {
        uint32_t o = i*m;
        for(j = 0; j < n; ++j)
        {
            load_uint32_t(A+o+j);
            //cin >> A[o+j];
            AR[j*n+i] = A[o+j];
        }
    }
    static uint32_t counts[MAX_E];
    uint64_t diff_max = 0, diff = 0, diff_sum = 0;
    for(x = 0; x < k; ++x)
    {
        uint32_t o = x*m, c=o+k;
        for(y = o; y < c; ++y)
        {
            if(++counts[A[y]] == 1)
                ++diff;
        }
    }
    diff_max = diff_sum = diff;
    uint32_t c0 = m - k, c01 = m - k + 1;
    for(i = 0; i < c01; ++i)
    {
        static uint32_t counts_at_row[MAX_E];
        uint64_t diff_at_row = diff;
        copy(counts, counts + MAX_E, counts_at_row);
        uint32_t c1 = n - k;
        for(j = 0; j < c1; ++j)
        {
            uint32_t o1 = j*n, ce = o1 + i + k, o2=(j+k)*n, cf = o2 + i + k;
            for(uint32_t e = o1 + i; e < ce; e++)
            {
                if(--counts[AR[e]] == 0)
                    --diff;
            }
            for(uint32_t f = o2 + i; f < cf; f++)
            {
                if(++counts[AR[f]] == 1)
                    ++diff;
            }
            diff_max = diff > diff_max ? diff : diff_max;
            diff_sum += diff;
        }
        if(i != c0)
        {
            copy(counts_at_row, counts_at_row + MAX_E, counts);
            diff = diff_at_row;
            uint32_t o1 = i*m, o2=(i+k)*m;
            for(y = 0; y < k; ++y)
            {
                if(--counts[A[o1+y]] == 0)
                    --diff;
                if(++counts[A[o2+y]] == 1)
                    ++diff;
            }
            diff_max = diff > diff_max ? diff : diff_max;
            diff_sum += diff;
        }
    }
    cout << diff_max << " " << diff_sum << endl;
}
