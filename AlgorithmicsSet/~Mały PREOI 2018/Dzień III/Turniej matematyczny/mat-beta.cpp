#include <bits/stdc++.h>

using namespace std;

const uint Mod = 1e9 + 7;

vector<vector<uint>> get_rect_count(const vector<vector<bool>>& A)
{
    const size_t m = A[0].size() - 2, n = A.size() - 2;
    vector<vector<uint>> R(n+2, vector<uint>(m+2)), D = R;

    for(size_t y = 1; y <= n; y++)
        for(size_t x = 1; x <= m; x++)
            D[y][x] = A[y][x] ? D[y-1][x] + 1 : 0;

    for(size_t y = 1; y <= n; y++)
    {
        struct rect { uint w, h; };
        vector<rect> S = {{0, 0}};

        for(size_t x = 1; x <= m+1; x++)
        {
            auto d = D[y][x];
            uint e = 0;
            while(S.size() > 1 and S.back().h >= d)
            {
                auto [w, h] = S.back(); S.pop_back();
                auto l = max(S.back().h, d);
                e += w;
                R[l + 1][e]++;
                R[h + 1][e]--;
            }
            S.push_back({++e, d});
        }
    }

    for(size_t y = 0; y <= n; y++)
        for(size_t x = 0; x <= m; x++)
            R[y+1][x] += R[y][x];
    for(size_t t = 0; t < 2; t++)
        for(size_t y = 0; y <= n+1; y++)
            for(size_t x = m+2; x --> 1; )
                R[y][x-1] += R[y][x];

    return R;
}

uint get_rect_area_sum(const vector<vector<bool>>& A)
{
    const size_t n = A[0].size() - 2, m = A.size() - 2;
    auto R = get_rect_count(A);
    uint r = 0;
    for(uint y = 1; y <= n; y++)
        for(uint x = 1; x <= m; x++)
            r = (r + (uint64_t)R[y][x] * y * x) % Mod;
    return r;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<vector<bool>> A(n+2, vector<bool>(n+2)), B = A;
    for(size_t y = 1; y <= n; y++)
        for(size_t x = 1; x <= n; x++)
            A[y][x] = []() { bool b; cin >> b; return b; }(), B[y][x] = not A[y][x];

    cout << (get_rect_area_sum(A) + get_rect_area_sum(B)) % Mod;
}
