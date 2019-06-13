#include "minerals.h"
#include <bits/stdc++.h>

using namespace std;


vector<size_t> range(size_t start, size_t stop)
{
    vector<size_t> out(stop - start);
    iota(out.begin(), out.end(), start);
    return out;
}

bool __translate = false;
int __count = 0;
vector<size_t> E;

bool toggle(size_t x)
{
    auto t = Query((__translate ? E[x] : x) + 1);
    bool b = t != __count;
    __count = t;
    return b;
}

void answer(size_t a, size_t b)
{
    return Answer((__translate ? E[a] : a) + 1, (__translate ? E[b] : b) + 1);
}

void divida_et_impera(size_t rangeL, size_t rangeR, const vector<size_t>& against, bool range_in_set)
{
    const size_t m = rangeR - rangeL;

    if(m == 1)
        return answer(rangeL, against[0]);
    else if(m == 2)
    {
        size_t x = rangeL, y = rangeL + 1, u = against[0], v = against[1];
        toggle(x);
        if(not range_in_set)
            swap(x, y);
        if(toggle(u))
            answer(x, u), answer(y, v);
        else
            answer(x, v), answer(y, u);
        return;
    }

    const size_t k = max(1l, lround((range_in_set ? 0.66667 : 0.33333) * m));
    const size_t k1 = m - k, rangeM = rangeL + k;

    vector<size_t> againstL, againstR;
    againstL.reserve(k); againstR.reserve(k1);

    if(range_in_set)
        for(size_t x = rangeM; x < rangeR; x++)
            toggle(x);
    else
        for(size_t x = rangeL; x < rangeM; x++)
            toggle(x);

    for(size_t x : against)
        (toggle(x) ? againstR : againstL).push_back(x);

    divida_et_impera(rangeL, rangeM, againstL, true);
    divida_et_impera(rangeM, rangeR, againstR, false);
}

void Solve(int N)
{
    const size_t n = N;

    vector<size_t> X, Y;
    X.reserve(n); Y.reserve(n);

    for(size_t i = 0; i < 2 * n; i++)
        if(toggle(i))
            X.push_back(i);
        else
            Y.push_back(i);

    mt19937 gen(1337);
    shuffle(X.begin(), X.end(), gen);
    shuffle(Y.begin(), Y.end(), gen);

    E.resize(2 * n);
    copy(X.begin(), X.end(), E.begin());
    copy(Y.begin(), Y.end(), E.begin() + n);

    __translate = true;

    for(size_t i = 0; i < n; i++)
        toggle(i);

    divida_et_impera(0, n, range(n, 2*n), false);
}
