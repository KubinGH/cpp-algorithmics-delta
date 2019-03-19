#define TESTNAME "tro4"
#define INFILE TESTNAME".in"
#define OUTFILE TESTNAME".out"
#define MODIFYOUT

#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;

int main()
{
    ifstream cin(INFILE);
    uint32_t h, w; uint64_t s, t;
    cin >> h >> w >> s >> t;
    static vector<uint32_t> pre_cont[MAX], cont[MAX];
    static uint32_t vals[MAX];
    uint64_t mx = 0, mxcount = 0, total = 0;
    for(uint32_t y = 0; y < h; y++)
    {
        if(y % 128 == 0)
            cout << "row " << y << endl;
        static uint32_t sums[MAX];
        for(uint32_t x = 0; x < w; x++)
        {
            s = (1103515245 * s + 12345) % (1LLU << 31);
            vals[x] = (s / 65536) < t;
        }
        partial_sum(vals, vals + w, sums + 1);
        for(uint32_t x = 0; x < w; x++)
        {
            cont[x].clear();
            if(vals[x])
                cont[x].push_back(0);
            uint32_t lo = 0, hi = w;
            while(lo < hi)
            {
                uint32_t m = (lo + hi) / 2;
                if(x < m or x + m >= w or sums[x+m+1] - sums[x-m] < 2*m+1)
                    hi = m;
                else
                    lo = m + 1;
            }
            uint32_t r = lo;
            for(uint32_t t = 1; t < min(x+1, w-x); t++)
            {
                if(r == t and vals[x-t] and vals[x+t])
                    r++;
                else
                    break;
            }
            for(uint32_t t : pre_cont[x])
            {
                if(x < t+1 or x+t+1 >= w) break;
                if(x >= t+1 and vals[x-t-1] and x+t+1 < w and vals[x+t+1])
                    cont[x].push_back(t+1);
            }
            auto it = upper_bound(cont[x].begin(), cont[x].end(), r);
            total += it - cont[x].begin();
            if(r)
            {
                it--;
                if(*it > mx)
                    mx = *it, mxcount = 0;
                if(*it == mx)
                    mxcount++;
            }
            swap(pre_cont[x], cont[x]);
        }
    }
    cout << mx+1 << "\n" << mxcount << "\n" << total;
#ifdef MODIFYOUT
    ofstream fout(OUTFILE);
    fout << mx+1 << "\n" << mxcount << "\n" << total;
#endif
}
