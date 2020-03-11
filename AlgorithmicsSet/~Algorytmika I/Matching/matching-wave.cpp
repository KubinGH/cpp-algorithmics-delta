#include <bits/stdc++.h>

using namespace std;

uint VECTOR_SIZE_SUM = 0, NODE_COUNT = 0;

size_t ARENA_BEGIN = 0;
uint* arena_next(size_t n)
{
    static uint buffer[1 << 23];
    auto ret = buffer + ARENA_BEGIN;
    fill(ret, ret + n, 0);
    ARENA_BEGIN += n;
    return ret;
}

template<typename T>
struct wavelet_tree
{
    vector<T> v;
    struct node
    {
        T a, b;
        uint *S, *B;
        node *left = nullptr, *right = nullptr;

        template<typename It>
        node(It first, It last, T _a, T _b) : a(_a), b(_b)
        {
            auto n = last - first;
            NODE_COUNT++;
            if(a < b)
            {
                //static mt19937 gen(19937);
                //uniform_int_distribution<size_t> dis(0, last - first - 1);
                //c = first[dis(gen)];
                auto c = (a+b) / 2;

                auto f = [&](const T& x) {
                    return x <= c;
                };
                size_t i = 0;

                S = arena_next(n/32+2); B = arena_next(n/32+1);
                VECTOR_SIZE_SUM += 2 * ((n+31)/32+2);
                for(auto it = first; it != last; it++, i++)
                {
                    B[i/32] |= (uint)f(*it) << (i % 32);
                    if(i % 32 == 0)
                        S[i/32+1] = S[i/32];
                    S[i/32+1] += f(*it);
                }

                auto mid = stable_partition(first, last, f);
                if(first < mid) left = new node(first, mid, a, c);
                if(mid < last) right = new node(mid, last, c+1, b);
            }
        }

        uint rank0(size_t i) const
        {
            return S[i/32] + __builtin_popcount(B[i/32] & ((1 << (i%32)) - 1));
        }
        uint rank1(size_t i) const { return i - rank0(i); }

        uint count_le(size_t i, size_t j, T x) const
        {
            if(i == j or x <= a)
                return 0;
            else if(b < x)
                return j - i;
            else
                return (left ? left->count_le(rank0(i), rank0(j), x) : 0)
                     + (right ? right->count_le(rank1(i), rank1(j), x) : 0);
        }

        ~node() { if(left) delete left; if(right) delete right; }
    } *root;

    template<typename It>
    wavelet_tree(It first, It last) : v(first, last)
    {
        auto [mi, ma] = minmax_element(v.begin(), v.end());
        root = new node(v.begin(), v.end(), *mi, *ma);
        v = vector<T>(first, last);
    }

    uint count_le(size_t i, size_t j, T x) const
    {
        if(j - i < 32)
        {
            uint r = 0;
            for(size_t k = i; k < j; k++)
                if(v[k] < x)
                    r++;
            return r;
        }
        else
            return root->count_le(i, j, x);
    }

    ~wavelet_tree() { delete root; }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<int> Q(n), P(n);
    for(size_t i = 0; i < n; i++)
        cin >> Q[i], Q[i]--;
    for(size_t i = 0; i < n; i++)
        P[Q[i]] = i;

    vector<size_t> F(n);
    vector<uint> I(n);
    {
        wavelet_tree<int> V(P.begin(), P.end());
        cerr << "V done" << endl;

        for(size_t i = 1; i < n; i++)
        {
            F[i] = F[i-1];
            while(F[i] and V.count_le(0, F[i], P[F[i]]) != V.count_le(i-F[i], i, P[i]))
                F[i] = F[F[i]-1];
            if(V.count_le(0, F[i], P[F[i]]) == V.count_le(i-F[i], i, P[i]))
                F[i]++;
        }
        cerr << "failure done" << endl;
        for(size_t i = 0; i < n; i++)
            I[i] = V.count_le(0, i, P[i]);
        cerr << "I done" << endl;
        ARENA_BEGIN = 0;
    }

    vector<int> T(m);
    vector<pair<int, size_t>> keys;
    for(size_t i = 0; i < m; i++)
        cin >> T[i], keys.emplace_back(T[i], i);
    sort(keys.begin(), keys.end());
    for(size_t i = 0; i < m; i++)
        T[keys[i].second] = i;
    cerr << "scale done" << endl;

    wavelet_tree<int> W(T.begin(), T.end());
    cerr << "W done" << endl;
    vector<size_t> occ;

    for(size_t i = 0, k = 0; i < m; i++)
    {
        uint w = 0;
        while(k and (k+1 > n or I[k] != (w = W.count_le(i-k, i, T[i]))))
            k = F[k - 1];
        if(k == 0 or I[k] == w)
            k++;

        if(k == n)
            occ.push_back(i-k+1);
    }
    cerr << "occ done" << endl;

    cout << occ.size() << '\n';
    for(auto i : occ)
        cout << i+1 << ' ';
    cout << endl;
}
