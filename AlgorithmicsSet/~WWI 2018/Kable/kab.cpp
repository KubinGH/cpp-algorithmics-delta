#include "kab.h"
#include <bits/stdc++.h>

using namespace std;

const size_t NAX = 1 << 20;

vector<bool> query(const vector<bool>& a)
{
    static bool buf[2*NAX];
    copy(a.begin(), a.end(), buf + 1);
    plug(buf);
    vector<bool> r(a.size());
    copy(buf + 1, buf + a.size() + 1, r.begin());
    return r;
}

void done(const vector<size_t>& conn)
{
    static int buf[2*NAX];
    copy(conn.begin(), conn.end(), buf + 1);
    for(size_t i = 0; i < conn.size(); i++)
        buf[i+1]++;
    return answer(buf);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n = init();

    vector<size_t> conn(2*n);
    for(size_t k = 0; k <= __lg(2*n - 1); k++)
    {
        vector<bool> t(2*n);
        for(size_t i = 0; i < 2*n; i++)
            t[i] = (i >> k) & 1;
        auto p = query(t);
        for(size_t i = 0; i < 2*n; i++)
            t[i] = !t[i];
        auto q = query(t);

        for(size_t i = 0; i < 2*n; i++)
        {
            if(p[i] and q[i])
                conn[i] |= (i ^ (1 << k)) & (1 << k);
            else if(p[i] ^ q[i])
                conn[i] |= i & (1 << k);
            else
                abort();
        }
    }
    done(conn);
}
