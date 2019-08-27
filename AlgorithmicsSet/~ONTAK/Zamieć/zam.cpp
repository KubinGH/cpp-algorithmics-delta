#include <bits/stdc++.h>
#define SAVE_DIM(__A) const size_t w = __A[0].size(), h = __A.size()

using namespace std;

struct ext_kadane
{
    int best = INT_MIN, best_here = INT_MIN;
    void push(int x)
    {
        best_here = max(0, best_here) + x;
        best = max(best_here, best);
    }
};

int kadane(const vector<int>& A)
{
    ext_kadane K;
    for(auto x : A)
        K.push(x);
    return K.best;
}

struct ext_kadane_2d_row
{
    vector<vector<int>> A, K;
    void push_row(vector<int> a)
    {
        for(size_t y1 = 0; y1 < K.size(); y1++)
        {
            for(size_t x = 0; x < a.size(); x++)
                A[y1][x] += a[x];
            K[y1].push_back(kadane(A[y1]));
        }
        A.push_back(a);
        K.emplace_back(K.size() + 1, INT_MIN);
        K.back().push_back(kadane(a));
    }
};

struct ext_kadane_2d_col
{
    vector<vector<ext_kadane>> E;
    vector<vector<int>> K;
    void push_col(vector<int> a)
    {
        E.resize(a.size());
        K.resize(a.size());
        for(size_t y1 = 0; y1 < a.size(); y1++)
        {
            E[y1].resize(a.size() + 1);
            K[y1].resize(a.size() + 1, INT_MIN);
            int x = 0;
            for(size_t y2 = y1+1; y2 <= a.size(); y2++)
            {
                x += a[y2-1];
                E[y1][y2].push(x);
                K[y1][y2] = E[y1][y2].best;
            }
        }
    }
};

struct ext_kadane_2d
{
    ext_kadane_2d_row R;
    ext_kadane_2d_col C;
    void push_row(vector<int> a)
    {
        R.push_row(a);
        C.push_col(a);
    }
};

vector<vector<int>> rowkadane(const vector<vector<int>>& A)
{
    ext_kadane_2d_row E;
    for(const auto& a : A)
        E.push_row(a);
    return E.K;
}

vector<vector<int>> transposed(const vector<vector<int>>& A)
{
    SAVE_DIM(A);
    vector<vector<int>> B(w, vector<int>(h));
    for(size_t y = 0; y < h; y++)
        for(size_t x = 0; x < w; x++)
            B[x][y] = A[y][x];
    return B;
}

vector<vector<int>> row_reversed(const vector<vector<int>>& A)
{
    SAVE_DIM(A);
    vector<vector<int>> B(h, vector<int>(w));
    for(size_t y = 0; y < h; y++)
        for(size_t x = 0; x < w; x++)
            B[h-y-1][x] = A[y][x];
    return B;
}

int solve_first_k(const vector<vector<int>>& K)
{
    SAVE_DIM(K); (void)w;
    int result = INT_MIN;
    for(size_t y1 = 0; y1 < h; y1++)
        for(size_t y2 = y1+1; y2 <= h; y2++)
            result = max(result, K[y1][y2]);
    return result;
}

int solve_first(const vector<vector<int>>& A)
{
    return solve_first_k(rowkadane(A));
}

int solve_second_xk(const vector<vector<int>>& K)
{
    SAVE_DIM(K); (void)w;
    auto Q = K;
    for(size_t k = 2; k <= h; k++)
        for(size_t y1 = 0, y2 = k; y2 <= h; y1++, y2++)
            Q[y1][y2] = max({K[y1][y2], Q[y1+1][y2], Q[y1][y2-1]});
    int result = INT_MIN;
    for(size_t y = 1; y < h; y++)
        result = max(result, Q[0][y] + Q[y][h]);
    return result;
}

int solve_second_x(const vector<vector<int>>& A)
{
    return solve_second_xk(rowkadane(A));
}

int solve_second(const vector<vector<int>>& A)
{
    return max(solve_second_x(A), solve_second_x(transposed(A)));
}

int solve_third_x(const vector<vector<int>>& A)
{
    SAVE_DIM(A); (void)w;
    int result = INT_MIN;
    vector<vector<int>> P, Q = A;

    ext_kadane_2d_row top;

    vector<int> U(h), V(h);

    for(size_t y = 0; y < h; y++)
    {
        top.push_row(A[y]);
        U[y] = solve_first_k(top.K);
    }

    ext_kadane_2d bot;

    for(size_t y = h; y --> 0; )
    {
        bot.push_row(A[y]);
        V[y] = max(solve_second_xk(bot.R.K), solve_second_xk(bot.C.K));
    }

    for(size_t y = 0; y+1 < h; y++)
        result = max(result, U[y] + V[y+1]);

    return result;
}

int solve_third(const vector<vector<int>>& A)
{
    return max({
        solve_third_x(A),
        solve_third_x(transposed(A)),
        solve_third_x(row_reversed(A)),
        solve_third_x(row_reversed(transposed(A)))
    });
}

int main()
{
    size_t h, w, k;
    cin >> h >> w >> k;

    vector<vector<int>> A(h, vector<int>(w));
    for(size_t y = 0; y < h; y++)
        for(size_t x = 0; x < w; x++)
            cin >> A[y][x];

    if(k == 1)
        cout << solve_first(A);
    else if(k == 2)
        cout << solve_second(A);
    else if(k == 3)
        cout << solve_third(A);
}
