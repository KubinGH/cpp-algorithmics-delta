#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::identity_element;

template<typename T, typename Fun>
struct segment_tree
{
    size_t w;
    vector<T> values;
    Fun F;

    segment_tree(size_t n) : w(1 << __lg(2*n - 1)), values(2*w, identity_element(F)) {}

    void set(size_t p, T v)
    {
        values[p += w] = v;
        while(p /= 2)
            values[p] = F(values[2*p], values[2*p+1]);
    }

    T get()
    {
        return values[1];
    }
};

struct msp_state
{
    int64_t sum, pref, suff, best;
    msp_state(int64_t v)
    {
        sum = v;
        suff = pref = best = max(v, (int64_t)0);
    }
    msp_state(int64_t _sum, int64_t _pref, int64_t _suff, int64_t _best)
        : sum(_sum), pref(_pref), suff(_suff), best(_best) {}

    friend msp_state operator+ (const msp_state& L, const msp_state& R)
    {
        return {
            L.sum + R.sum,
            max(L.pref, L.sum + R.pref),
            max(R.suff, R.sum + L.suff),
            max({L.best, R.best, L.suff + R.pref})
        };
    }
};

using msp_tree = segment_tree<msp_state, plus<msp_state>>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t t;
    cin >> t;

    while(t --> 0)
    {
        size_t n;
        cin >> n;

        vector<tuple<int, int, int>> P(n);
        map<int, size_t> xmap, ymap;
        for(auto& [x, y, w] : P)
        {
            cin >> x >> y >> w;
            xmap[x] = ymap[y] = 0;
        }
        size_t nx = 0, ny = 0;
        for(auto& [k, v] : xmap)
            v = nx++;
        for(auto& [k, v] : ymap)
            v = ny++;

        vector<tuple<size_t, size_t, int>> Q(n);

        vector<size_t> X;
        for(size_t i = 0; i < n; i++)
        {
            auto [x, y, w] = P[i];
            Q[i] = make_tuple(xmap[x], ymap[y], w);
            X.push_back(get<0>(Q[i]));
        }
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());

        sort(Q.begin(), Q.end());

        int64_t result = 0;

        for(size_t i1 = 0, i = 0; i1 < X.size(); i1++)
        {
            size_t x1 = X[i1];
            while(i < n and get<0>(Q[i]) < x1)
                i++;

            msp_tree T(ny);

            size_t j = i;

            for(size_t i2 = i1; i2 < X.size(); i2++)
            {
                size_t x2 = X[i2];

                while(j < n and get<0>(Q[j]) <= x2)
                {
                    auto [x, y, w] = Q[j];
                    auto v = T.values[T.w + y].sum;
                    T.set(y, v + w);
                    j++;
                }

                result = max(result, T.get().best);
            }
        }

        cout << result << '\n';
    }
}
