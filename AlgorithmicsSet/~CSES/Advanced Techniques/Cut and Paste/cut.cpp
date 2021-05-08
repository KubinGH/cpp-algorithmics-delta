#include <bits/stdc++.h>

using namespace std;

string compose(const list<string>& blocks)
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

list<string> decompose(string str, size_t k)
{
    list<string> blocks;
    for(size_t i = 0; i < str.size(); i += k)
        blocks.push_back(str.substr(i, k));
    return blocks;
}

list<string>::iterator split_after(list<string>& blocks, list<string>::iterator it, size_t i)
{
    while(i and i >= it->size())
        i -= (it++)->size();
    if(i)
        blocks.insert(next(it), it->substr(i)), (it++)->resize(i);
    return it;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    string init;
    cin >> init;
    // for(size_t i = 0; i < n; i++) init.push_back('A' + (i%26));

    constexpr double ALPHA = 4.0, BETA = 0.075;
    const size_t k = floor(sqrt(n)) * ALPHA, k0 = max(k * BETA, 1.0);
    list<string> blocks = decompose(init, k);

    while(m --> 0)
    {
        size_t a, b;
        cin >> a >> b; a--;
        // a = rand() % n; b = rand() % n; if(a > b) swap(a, b); b++;

        auto first = split_after(blocks, blocks.begin(), a);
        auto last = split_after(blocks, first, b - a);
        blocks.splice(blocks.end(), blocks, first, last);

        if(m % k0 == 0) // blocks.size() > k0)
            blocks = decompose(compose(blocks), k);
    }

    cout << compose(blocks) << endl;
}
