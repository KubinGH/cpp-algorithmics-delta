#include <bits/stdc++.h>

using namespace std;

struct disjoint_sets
{
    vector<size_t> repr, rank, mini, maxi;

    disjoint_sets(size_t n) : repr(n)
    {
        iota(repr.begin(), repr.end(), 0);
        mini = maxi = rank = repr;
        shuffle(rank.begin(), rank.end(), mt19937{});
    }

    size_t find(size_t u)
    {
        return u == repr[u] ? u : repr[u] = find(repr[u]);
    }

    bool unite(size_t u, size_t v)
    {
        if((u = find(u)) == (v = find(v)))
            return false;
        if(rank[u] > rank[v])
            swap(u, v);
        repr[u] = v;
        mini[v] = min(mini[v], mini[u]);
        maxi[v] = max(maxi[v], maxi[u]);
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> A(2*n+4);
    for(size_t t : {0, 1})
        for(size_t i = 1; i <= n; i++)
            cin >> A[2*i+t];
    A[0] = A[1] = A[2];

    disjoint_sets desu(2*n+4);
    for(size_t i = 0; i <= n+1; i++)
        if(A[2*i] == A[2*i+1])
            desu.unite(2*i, 2*i+1);
    for(size_t t : {0, 1})
        for(size_t i = 0; i <= n; i++)
            if(A[2*i+t] == A[2*i+t+2])
                desu.unite(2*i+t, 2*i+t+2);

    vector<pair<size_t, int>> gobble;
    map<int, vector<int>> gobbles;
    for(size_t i = 2; i < 2*n+2; i++)
        if(desu.find(0) != desu.find(i) and i == desu.mini[desu.find(i)])
            gobble.emplace_back(i, A[i]);
    sort(gobble.begin(), gobble.end());

    size_t x = desu.maxi[desu.find(0)] / 2, g = 0;
    int curr = A[2];

    function<void()> update_gobble = [&]() {
        while(g < gobble.size() and gobble[g].first/2 <= x)
        {
            cerr << " gobble " << gobble[g].second << "@" << desu.find(gobble[g].first) << endl;
            gobbles[gobble[g].second].push_back(desu.find(gobble[g].first));
            g++;
        }
        bool xc = false;
        if(gobbles.count(curr)) for(auto i : gobbles[curr])
        {
            desu.unite(0, i);
            if(desu.maxi[desu.find(0)]/2 > x)
                xc = true;
        }
        cerr << " erase gobble " << curr << endl;
        gobbles.erase(curr);
        if(xc) update_gobble(); // shouldn't happen
    };

    auto print = [&]() {
        for(size_t t : {0, 1})
        {
            for(size_t i = 1; i <= n; i++, cerr << ' ')
                cerr << (desu.find(0) == desu.find(2*i+t) ? curr : A[2*i+t]);
            cerr << endl;
        }
    };

    size_t result = 0;
    auto paint = [&](size_t t) {
        if(desu.find(0) == desu.find(t))
            return;
        cerr << "- painting to " << t << endl;
        x = max(x, desu.maxi[t] / 2);
        curr = A[t];
        desu.unite(0, t);
        result++;
        update_gobble();
    };

    cerr << endl;
    update_gobble();
    while(x < n)
    {
        cerr << "x = " << x << endl;
        print();
        bool h[2] = {
            desu.find(0) == desu.find(2*x), desu.find(0) == desu.find(2*x+1)
        };
        cerr << "lo/hi " << h[0] << "/" << h[1] << endl;
        size_t nxt[4] = {
            h[0] ? desu.maxi[desu.find(2*x+0 + 1)] : 0,
            h[0] ? desu.maxi[desu.find(2*x+0 + 2)] : 0,
            h[1] ? desu.maxi[desu.find(2*x+1 - 1)] : 0,
            h[1] ? desu.maxi[desu.find(2*x+1 + 2)] : 0
        };
        for(auto& i : nxt)
            i = desu.find(0) == desu.find(i) or i/2 <= x ? 0 : i;
        sort(nxt, nxt + 4);

        cerr << ": ";
        for(auto i : nxt)
            cerr << i << " ";
        cerr << endl;

        size_t t = SIZE_MAX;
        if(nxt[2] and nxt[3] and nxt[2] != nxt[3] and nxt[2]/2 == nxt[3]/2)
        {
            cerr << "go to " << nxt[2] << " or " << nxt[3] << endl;
            auto a = nxt[2], b = nxt[3];
            while(a/2 == b/2 and a/2 <= n)
            {
                a = desu.maxi[desu.find(a + 2)];
                b = desu.maxi[desu.find(b + 2)];
            }
            t = a/2 >= b/2 ? a : b;
            auto c = a/2 >= b/2 ? nxt[2] : nxt[3];
            while(c != t)
            {
                paint(c);
                c = desu.maxi[desu.find(c + 2)];
            }
        }
        else if(nxt[3])
        {
            cerr << "go to " << nxt[3] << endl;
            t = desu.find(nxt[3]);
        }
        else
            assert(false);

        paint(t);
        cerr << endl;
    }
    cerr << "overdraw is " << gobbles.size() << ": ";
    for(auto k : gobbles) cerr << k.first << "; ";
    cerr << endl; cerr << endl;
    result += gobbles.size();
    print(); cerr << endl;

    cout << result << '\n';
}
