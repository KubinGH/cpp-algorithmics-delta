#include <bits/stdc++.h>

using namespace std;

const size_t bad = 7777777;

template<typename Fun>
vector<uint> compressed(size_t n, Fun val)
{
    static vector<size_t> idx;
    idx.resize(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](size_t i, size_t j) {
        return val(i) < val(j);
    });
    vector<uint> result(n);
    uint c = 0;
    for(size_t i = 0; i < n; i++)
    {
        if(i and val(idx[i-1]) != val(idx[i]))
            c++;
        result[idx[i]] = c;
    }
    return result;
}

struct karp_miller_rosenberg
{
    vector<vector<uint>> A;

    template<typename It>
    karp_miller_rosenberg(It first, It last)
    {
        A.push_back(move(compressed(last - first, [&](size_t i) { return first[i]; })));
        const size_t n = A[0].size();
        for(size_t k = 1, p = 2; p <= n; k++, p *= 2)
        {
            auto& a = A.back();
            A.push_back(move(compressed(n-p+1, [&](size_t i) {
                return tie(a[i], a[i+p/2]);
            })));
        }
    }

    static karp_miller_rosenberg reversed(const karp_miller_rosenberg& kmr)
    {
        auto rmk = kmr;
        for(auto& a : rmk.A)
            reverse(a.begin(), a.end());
        return rmk;
    }

    pair<uint, uint> operator() (size_t l, size_t r) const
    {
        const size_t k = __lg(r - l);
        return {A[k][l], A[k][r - (1 << k)]};
    }
};


using at_table_t = vector<vector<vector<size_t>>>;
auto kmr_at_table(const karp_miller_rosenberg& kmr)
{
    auto& A = kmr.A;
    const size_t n = A[0].size(), m = A.size();
    at_table_t at(m, vector<vector<size_t>>(n));
    vector<size_t> ct(n);
    for(size_t k = 0; k < m; k++)
    {
        fill(ct.begin(), ct.end(), 0);
        for(size_t i = 0; i + (1u << k) <= n; i++)
            ct[A[k][i]]++;
        for(size_t x = 0; x < n; x++)
            if(ct[x])
                at[k][x].reserve(ct[x] + 2);
        for(size_t i = 0; i + (1u << k) <= n; i++)
            at[k][A[k][i]].push_back(i);
        for(size_t x = 0; x < n; x++)
            if(not at[k][x].empty())
                for(size_t t = 0; t < 2; t++)
                    at[k][x].push_back(bad);
    }
    return at;
}

vector<size_t> get_shortest_squares_at(const karp_miller_rosenberg& kmr, const at_table_t& at)
{
    auto& A = kmr.A;
    const size_t n = A[0].size();

    vector<size_t> R(n, bad);
    for(size_t i = 0; i < n; i++)
    {
        for(size_t k = 0; R[i] == bad and i + (1u << k) <= n; k++)
        {
            auto x = A[k][i];
            auto it = upper_bound(at[k][x].begin(), at[k][x].end(), i);
            size_t j1 = *it, j2 = *next(it);
            for(auto j : {j1, j2})
            {
                auto d = j - i;
                if(i + 2*d <= n and kmr(i, i + d) == kmr(j, j + d))
                {
                    R[i] = d;
                    break;
                }
            }
        }
    }

    return R;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    string S;
    cin >> S;

    karp_miller_rosenberg kmr(S.begin(), S.end()), kmrR = karp_miller_rosenberg::reversed(kmr);
    auto at = kmr_at_table(kmr), atR = kmr_at_table(kmrR);

    auto squareR = get_shortest_squares_at(kmr, at),
         squareL = get_shortest_squares_at(kmrR, atR);
    reverse(squareL.begin(), squareL.end());

    while(q --> 0)
    {
        size_t l, r;
        cin >> l >> r; l--;

        bool ok = false;

        if(l + 2*squareR[l] <= r)
            ok = true;
        else if(l + 2*squareL[r-1] <= r)
            ok = true;
        else
        {
            for(size_t k = 0, p = 1; not ok and 2*p <= r-l; k++, p *= 2)
            {
                auto x = kmr.A[k][l], y = kmr.A[k][r - p];
                if(x != y)
                {
                    auto it = upper_bound(at[k][y].begin(), at[k][y].end(), l);
                    auto j1 = *it, j2 = *next(it);
                    for(auto j : {j1, j2})
                    {
                        auto d = p + (j - l);
                        if(2*d <= r-l and kmr(l, l + d) == kmr(r - d, r))
                        {
                            ok = true;
                            break;
                        }
                    }
                }
                else
                    ok = true;
            }
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }
}
