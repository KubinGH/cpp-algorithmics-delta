#include <bits/stdc++.h>

using namespace std;

int n, k;

const size_t M = 384, MAX = 1 << 19;

struct block
{
    int L, R, offset, dex;
    vector<pair<int, size_t>> values;

    size_t count_ge()
    {
        return values.size() - dex;
    }
    template<typename Fun>
    size_t count_sat(Fun F)
    {
        size_t r = 0;
        for(auto [x, i] : values)
            r += F(x + offset, i);
        return r;
    }

    void pop_grown()
    {
        while(dex and values[dex-1].first + offset >= k)
            dex--;
    }
    void increment()
    {
        offset++;
        pop_grown();
    }
    template<typename Fun>
    void increment_sat(Fun F)
    {
        static pair<int, size_t> buf[2][M];
        size_t a = 0, b = 0;
        for(auto [x, i] : values)
            if(F(x, i))
                buf[1][b++] = {x + 1, i};
            else
                buf[0][a++] = {x, i};
        merge(buf[0], buf[0] + a, buf[1], buf[1] + b, values.begin());
        pop_grown();
    }
} blocks[MAX/M];

void inicjuj(int _n, int _k, int *D)
{
    n = _n; k = _k;
    for(int i = 0; i < n; i++)
        blocks[i / M].values.emplace_back(D[i], i);
    for(int i = 0; i < int(MAX/M); i++)
        blocks[i].L = i*M, blocks[i].R = (i+1)*M - 1;
    for(auto& b : blocks)
    {
        sort(b.values.begin(), b.values.end());
        b.dex = b.values.size();
        b.pop_grown();
    }
}

void podlej(int a, int b)
{
    for(auto& block : blocks)
        if(a <= block.L and block.R <= b)
            block.increment();
        else if(not (block.R < a or b < block.L))
            block.increment_sat([&](int x, int i) { (void)x; return a <= i and i <= b; });
}

int dojrzale(int a, int b)
{
    int result = 0;
    for(auto& block : blocks)
        if(a <= block.L and block.R <= b)
            result += block.count_ge();
        else if(not (block.R < a or b < block.L))
            result += block.count_sat([&](int x, int i) { return a <= i and i <= b and x >= k; });
    return result;
}
