#include <bits/stdc++.h>
#include <ktl/util/extio.cpp>

using namespace std;

string compose(const vector<string>& blocks)
{
    size_t n = 0;
    for(auto& s : blocks)
        n += s.size();
    string r(n, 0);
    size_t m = 0;
    for(auto& s : blocks)
        copy(s.begin(), s.end(), r.begin() + m), m += s.size();
    return r;
}

vector<string> decompose(string str, size_t k)
{
    vector<string> blocks;
    for(size_t i = 0; i < str.size(); i += k)
        blocks.push_back(str.substr(i, k));
    return blocks;
}

vector<string>::iterator split_after(vector<string>& blocks, vector<string>::iterator it, size_t i)
{
    while(i and i >= it->size())
        i -= (it++)->size();
    if(i)
    {
        auto j = it - blocks.begin();
        blocks.insert(next(it), it->substr(i));
        it = blocks.begin() + j;
        (it++)->resize(i);
    }
    return it;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    string init;
    // cin >> init;
    for(size_t i = 0; i < n; i++) init.push_back('A' + (i%26));

    constexpr double ALPHA = 4.0, BETA = 0.5;
    const size_t k = max(floor(sqrt(n)) * ALPHA, 1.0), k0 = max(k * BETA, 1.0);
    auto blocks = decompose(init, k);

    while(m --> 0)
    {
        size_t a, b;
        // cin >> a >> b; a--;
        a = rand() % n; b = rand() % n; if(a > b) swap(a, b); b++;

        auto first1 = split_after(blocks, blocks.begin(), a);
        auto i = first1 - blocks.begin();
        auto last1 = split_after(blocks, blocks.begin() + i, b - a);
        auto j = last1 - blocks.begin();
        blocks.reserve(blocks.size() + (j - i));
        auto first = blocks.begin() + i, last = blocks.begin() + j;
        // blocks.splice(blocks.end(), blocks, first, last);
        move(first, last, back_inserter(blocks));
        blocks.erase(first, last);

        if(m % k0 == 0)
            blocks = decompose(compose(blocks), k);
    }

    cout << compose(blocks) << endl;
}
