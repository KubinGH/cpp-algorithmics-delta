#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

template<typename Fun>
void venture(vector<array<int, 3>>& T, size_t i, size_t k, array<int, 3> curr, vector<size_t>& build, Fun f) {
    if(k)
    {
        for(size_t x = 0; x < 3; x++)
        {
            auto next = curr;
            for(size_t t = 0; t < 3; t++)
                if(x != t)
                    next[t] += T[i][t];
            build.push_back(x);
            venture(T, i+1, k-1, next, build, f);
            build.pop_back();
        }
    }
    else
        f(curr, build);
}
template<typename Fun>
void venture(vector<array<int, 3>>& T, size_t a, size_t b, Fun f)
{
    vector<size_t> build;
    venture(T, a, b - a, {0, 0, 0}, build, f);
}


int main()
{
    size_t n;
    cin >> n;

    vector<array<int, 3>> T(n);
    for(auto& t : T) cin >> t[0] >> t[1] >> t[2];

    map<array<int, 3>, pair<int, vector<size_t>>> cache;

    venture(T, 0, n/2, [&](array<int, 3> val, vector<size_t> build) {
        auto minim = min({val[0], val[1], val[2]});
        for(size_t i = 0; i < 3; i++)
            val[i] -= minim;
        if(auto it = cache.find(val); it != cache.end())
            cache[val] = max(cache[val], {minim, build});
        else
            cache[val] = {minim, build};
    });

    pair<int, vector<size_t>> result = {-(1 << 30), {}};

    venture(T, n/2, n, [&](array<int, 3> val, vector<size_t> build) {
        auto maxim = max({val[0], val[1], val[2]});
        for(size_t i = 0; i < 3; i++)
            val[i] = maxim - val[i];
        if(auto it = cache.find(val); it != cache.end())
        {
            auto candy = make_pair(maxim + it->second.first, it->second.second);
            copy(build.begin(), build.end(), back_inserter(candy.second));
            result = max(result, candy);
        }
    });

    const char* S[] = {"MW", "LW", "LM"};
    if(result.second.empty())
        cout << "Impossible";
    else
        for(auto i : result.second)
            cout << S[i] << '\n';
}
