#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;

struct fenwick_tree
{
    size_t n;
    vector<int> F;

    fenwick_tree(size_t _n) : n(_n), F(n+1, INT_MIN) {}

    static constexpr size_t lsb(size_t x) { return x & -x; }

    int get_prefix(size_t p) const
    {
        int r = INT_MIN;
        while(p)
            r = max(r, F[p]), p -= lsb(p);
        return r;
    }

    void maximize(size_t p, int v)
    {
        p++;
        while(p <= n)
            F[p] = max(F[p], v), p += lsb(p);
    }
};

int main()
{
    int t;
    cin >> t;

    while(t --> 0)
    {
        static int S[MAX];
        size_t n = 0;
        bool init = true;
        while(true)
        {
            auto c = getchar_unlocked();
            if(c != 'W' and c != 'P')
            {
                if(not init)
                    break;
            }
            else
                S[n+1] = S[n] + (c == 'W' ? +1 : -1), n++;
            init = false;
        }

        int r = 0, r1 = 0;
        auto a = *min_element(S, S + (n+1)), b = *max_element(S, S + (n+1));
        fenwick_tree fen(b - a + 1);
        fen.maximize(-a, 0);
        for(size_t i = 1; i <= n; i++, r1 = r)
        {
            r = max(r1, (int)i + fen.get_prefix(S[i] - a));
            fen.maximize(S[i] - a, r - (int)i);
        }

        cout << r << '\n';
    }
}
