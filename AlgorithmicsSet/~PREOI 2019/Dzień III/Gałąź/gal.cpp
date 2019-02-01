#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

using vec2d = complex<int64_t>;
#define X real
#define Y imag
int64_t   dot(vec2d a, vec2d b) { return (conj(a) * b).X(); }
int64_t cross(vec2d a, vec2d b) { return (conj(a) * b).Y(); }

int sgn(int64_t x) { return x < 0 ? -1 : x > 0; }
bool dot_positive(vec2d u, vec2d v)
{
    long double a = u.X(), b = u.Y(), c = v.X(), d = v.Y();
    return a/d < -b/c;
}
bool cross_positive(vec2d u, vec2d v)
{
    long double a = u.X(), b = u.Y(), c = v.X(), d = v.Y();
    return a/c > b/d;
}

void add_line(vector<vec2d>& hull, vector<vec2d>& normals, vector<uint32_t>& indices,
              int64_t a, int64_t b, uint32_t i)
{
    vec2d curr = {a, b};
    while(not normals.empty() and dot_positive(normals.back(), curr - hull.back()))
        hull.pop_back(), normals.pop_back(), indices.pop_back();
    if(not hull.empty())
        normals.push_back(vec2d{0, 1} * (curr - hull.back()));
    hull.push_back(curr);
    indices.push_back(i);
}

struct hull_trick { vector<vec2d> hull, normals; vector<uint32_t> indices; };

void calc_layer(vector<int64_t>& curr, vector<int64_t>& prev,
                vector<uint32_t>& track, hull_trick& H, const vector<int64_t>& S,
                int64_t malus, uint32_t initial, uint32_t n, bool zeroline)
{
    H.hull.clear(); H.normals.clear(); H.indices.clear();
    uint32_t j = 0;
    for(uint32_t i = initial; i <= n; i++)
    {
        if(zeroline) add_line(H.hull, H.normals, H.indices, -S[i-1], S[i-1]*S[i-1], i-1);
        add_line(H.hull, H.normals, H.indices, -S[i-1], S[i-1]*S[i-1] - prev[i-1] + malus, i-1);
        if(H.hull.empty())
            track[i] = i-1;
        else
        {
            vec2d query = {S[i], 1};
            while(j+1 < H.hull.size() and -dot(query, H.hull[j]) <= -dot(query, H.hull[j+1]))
                j++;
            curr[i] = -dot(query, H.hull[j]);
            track[i] = H.indices[j];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    vector<int64_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    vector<int64_t> S(n+1);
    partial_sum(A.begin(), A.end(), S.begin()+1);
    hull_trick H;
    if((uint64_t)n * k < (uint64_t)1e7)
    {
        vector<vector<int64_t>> T(k+1, vector<int64_t>(n+1));
        vector<vector<uint32_t>> L(k+1, vector<uint32_t>(n+1));
        for(uint32_t t = 1; t <= k; t++)
            calc_layer(T[t], T[t-1], L[t], H, S, 0, t+1, n, false);
        cout << T[k][n] << "\n";

        vector<uint32_t> U;
        for(uint32_t i = n, t = k+1; t --> 1; )
            U.push_back(i = L[t][i]);
        reverse(U.begin(), U.end());
        for(auto i : U)
            cout << i << " ";
    }
    else
    {
        int64_t a_lo = 0, a_hi = S[n]*S[n]+1;
        vector<int64_t> T(n+1); vector<uint32_t> L(n+1);
        vector<uint32_t> U; U.reserve(n);
        auto rebuild = [&](int64_t a) {
            fill(T.begin(), T.end(), 0);
            fill(L.begin(), L.end(), 0);
            calc_layer(T, T, L, H, S, a, 1, n, true);
            U.clear();
            for(uint32_t i = L[n]; i > 0; i = L[i])
                U.push_back(i);
        };
        while(a_lo < a_hi)
        {
            int64_t a = (a_lo + a_hi) / 2;
            rebuild(a);
            if(U.size() <= k)
                a_hi = a;
            else
                a_lo = a + 1;
        }
        rebuild(a_lo);
        int64_t c1 = U.size(), a1 = T[n] + a_lo * c1;
        rebuild(a_lo+1);
        int64_t c2 = U.size(), a2 = T[n] + (a_lo+1) * c2;

        int64_t result = c1 == c2 ? a1 : a1 + (a1 - a2) / (c1 - c2) * (k - c1);
        cout << result << "\n";

        for(uint32_t i = 0; i < k; i++)
            cout << i+1 << " ";
    }
}
