#include <bits/stdc++.h>

using namespace std;

string compose(const list<pair<string, bool>>& blocks)
{
    size_t n = 0;
    for(auto& [s, b] : blocks)
        n += s.size();
    string r(n, 0);
    size_t m = 0;
    for(auto& [s, b] : blocks)
    {
        if(b) copy(s.rbegin(), s.rend(), r.begin() + m);
        else  copy(s. begin(), s. end(), r.begin() + m);
        m += s.size();
    }
    return r;
}

list<pair<string, bool>> decompose(string str, size_t k)
{
    list<pair<string, bool>> blocks;
    for(size_t i = 0; i < str.size(); i += k)
        blocks.emplace_back(str.substr(i, k), false);
    return blocks;
}

list<pair<string, bool>>::iterator split_after(list<pair<string, bool>>& blocks, list<pair<string, bool>>::iterator it, size_t i)
{
    while(i and i >= it->first.size())
        i -= (it++)->first.size();
    if(i)
    {
        if(it->second)
            reverse(it->first.begin(), it->first.end()), it->second = false;
        blocks.insert(next(it), {it->first.substr(i), false});
        (it++)->first.resize(i);
    }
    return it;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    string init;
    cin >> init;

    constexpr double ALPHA = 3.9, BETA = 0.08;
    const size_t k = max(sqrt(n) * ALPHA, 1.0), k0 = max(k * BETA, 1.0);
    list<pair<string, bool>> blocks = decompose(init, k);

    while(m --> 0)
    {
        size_t a, b;
        cin >> a >> b; a--;

        auto first = split_after(blocks, blocks.begin(), a);
        auto last = split_after(blocks, first, b - a);
        reverse(first, last);
        for(auto it = first; it != last; ++it)
            it->second ^= 1;

        if(m % k0 == 0)
            blocks = decompose(compose(blocks), k);
    }

    cout << compose(blocks) << endl;
}
