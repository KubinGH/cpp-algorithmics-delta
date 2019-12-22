#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

const size_t N = 1 << 20, M = 1 << 30;
const int V = 1 << 24;

int main()
{
    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    auto randint = [&](int a, int b) { return uniform_int_distribution<int>{a, b}(gen); };

    unordered_map<int, int> m;
    cc_hash_table<int, int> cc;
    gp_hash_table<int, int> gp;

    cout << "populate" << endl;
    for(size_t i = 0; i < N; i++)
    {
        int v = randint(-V, V), w = randint(INT_MIN, INT_MAX);
        m[v] = w;
        cc[v] = w;
        gp[v] = w;
    }

    cout << "queries" << endl;
    for(size_t i = 0; i < M; i++)
    {
        int v = randint(-V, V);
        bool e = (m.find(v) != m.end());
        assert(e == (cc.find(v) != cc.end()));
        assert(e == (gp.find(v) != gp.end()));

        if(e)
        {
            assert(m[v] == cc[v]);
            assert(m[v] == gp[v]);
            if(not randint(0, 32))
            {
                cout << "." << flush;
                m.erase(v);
                cc.erase(v);
                gp.erase(v);
            }
        }
        else
        {
            if(not randint(0, 64))
            {
                cout << "," << flush;
                m.erase(v);
                cc.erase(v);
                gp.erase(v);
            }
        }

    }
}
