#include <bits/stdc++.h>

using namespace std;

struct segment_tree
{
    size_t w;

    vector<int> values;
    vector<bool> set_tag[2];

    segment_tree(size_t n) : w(1 << __lg(2*n - 1)), values(2*w)
    {
        set_tag[0].resize(2*w);
        set_tag[1].resize(2*w);
    }

    template<typename It>
    void build(It first, It last)
    {
        fill(values.begin(), values.end(), 0);
        for(size_t b : {0, 1})
            fill(set_tag[b].begin(), set_tag[b].end(), false);
        for(size_t i = 0; first != last; i++, ++first)
            values[w + i] = *first;
        for(size_t i = w; i --> 1; )
            values[i] = values[2*i] + values[2*i + 1];
    }

    void pull(size_t i, size_t nodeL, size_t nodeR)
    {
        for(size_t b = 0; b < 2; b++)
        {
            if(set_tag[b][i])
            {
                values[i] = b ? nodeR - nodeL + 1 : 0;
                if(nodeL < nodeR)
                {
                    set_tag[ b ][2*i  ] = true;
                    set_tag[ b ][2*i+1] = true;
                    set_tag[b^1][2*i  ] = false;
                    set_tag[b^1][2*i+1] = false;
                }
                set_tag[b][i] = false;
            }
        }
    }

    template<bool tag>
    void set(size_t i, size_t nodeL, size_t nodeR, size_t queryL, size_t queryR)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < queryL or queryR < nodeL)
            return;
        else if(queryL <= nodeL and nodeR <= queryR)
        {
            set_tag[tag][i] = true; set_tag[tag^1][i] = false;
            pull(i, nodeL, nodeR);
        }
        else
        {
            set<tag>(2*i, nodeL, (nodeL+nodeR)/2, queryL, queryR);
            set<tag>(2*i+1, (nodeL+nodeR)/2+1, nodeR, queryL, queryR);
            values[i] = values[2*i] + values[2*i+1];
        }
    }

    template<bool tag>
    void set(size_t queryL, size_t queryR)
    {
        if(queryL <= queryR and queryR < w)
            return set<tag>(1, 0, w - 1, queryL, queryR);
        else
            return;
    }

    int get(size_t i, size_t nodeL, size_t nodeR, size_t queryL, size_t queryR)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < queryL or queryR < nodeL)
            return 0;
        else if(queryL <= nodeL and nodeR <= queryR)
            return values[i];
        else
            return get(2*i, nodeL, (nodeL+nodeR)/2, queryL, queryR) +
                   get(2*i+1, (nodeL+nodeR)/2+1, nodeR, queryL, queryR);
    }

    int get(size_t queryL, size_t queryR)
    {
        if(queryL <= queryR and queryR < w)
            return get(1, 0, w - 1, queryL, queryR);
        else
            return 0;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<int> A(n);
    for(auto& a : A) cin >> a;

    vector<pair<size_t, size_t>> Q(m);
    for(auto& [l, r] : Q)
        cin >> l >> r, l--, r--;


    auto S = A;
    sort(S.begin(), S.end());
    S.erase(unique(S.begin(), S.end()), S.end());

    int lo = 0, hi = S.size() - 1;

    vector<bool> B(n);
    segment_tree tree(n);
    while(lo < hi)
    {
        int mid = (lo + hi) / 2;

        for(size_t i = 0; i < n; i++)
            B[i] = (A[i] <= S[mid]);
        tree.build(B.begin(), B.end());

        for(auto [l, r] : Q)
        {
            bool a = l <= r;
            if(not a)
                swap(l, r);
            int o = tree.get(l, r);
            if(a)
                tree.set<1>(l, l+o-1), tree.set<0>(l+o, r);
            else
                tree.set<1>(r-o+1, r), tree.set<0>(l, r-o);
        }


        if(tree.get((n-1)/2, (n-1)/2))
            hi = mid;
        else
            lo = mid+1;
    }

    cout << S[lo];
}
