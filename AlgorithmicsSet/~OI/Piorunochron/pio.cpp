#include <bits/stdc++.h>
#include <ktl/structures/li_chao_tree.cpp>
#include <ktl/util/fastio.cpp>

using namespace std;

const size_t NAX = 1 << 20;

double sqrt_cache[NAX];

struct __sqrt_cache_init
{
    __sqrt_cache_init()
    {
        for(size_t i = 0; i < NAX; i++)
            sqrt_cache[i] = sqrt(i);
    }
} __sqrt_cache_init_inst;


struct li_chao_sqrt_fun
{
    int h, i; bool s;
    li_chao_sqrt_fun() : h(0), i(INT_MAX), s(false) {}
    li_chao_sqrt_fun(int _h, int _i) : h(_h), i(_i), s(false) {}
    double operator() (int j) const
    {
        if(j < i)
            return 0;
        return -(h + sqrt_cache[j - i]);
    }
    li_chao_sqrt_fun operator- () const { return *this; }
};

int main()
{
    size_t n;
    ucin >> n;

    vector<int> H(n);
    for(size_t i = 0; i < n; i++)
        ucin >> H[i];

    auto oneway = [&]() {
        li_chao_tree<int, double, li_chao_sqrt_fun> T(0, n);
        vector<int> M(n);
        for(size_t i = 0; i < n; i++)
        {
            T.insert({H[i], (int)i});
            M[i] = ceil(-T.get_value(i));
        }
        return M;
    };

    auto M = oneway();
    reverse(H.begin(), H.end());
    auto M1 = oneway();
    reverse(H.begin(), H.end());
    reverse(M1.begin(), M1.end());

    for(size_t i = 0; i < n; i++)
        ucout << max(M[i], M1[i]) - H[i] << '\n';

}
