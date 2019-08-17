#include <bits/stdc++.h>
#define SAVE_DIM(__A) const size_t w = __A[0].size(), h = __A.size()

using namespace std;

int kadane(const vector<int>& A)
{
    int best = INT_MIN, best_here = INT_MIN;
    for(auto x : A)
    {
        best_here = max(0, best_here) + x;
        best = max(best_here, best);
    }
    return best;
}

vector<vector<int>> rowkadane(const vector<vector<int>>& A)
{
    SAVE_DIM(A);
    vector<vector<int>> resulto(h, vector<int>(h + 1));
    for(size_t y1 = 0; y1 < h; y1++)
    {
        vector<int> a(w);
        for(size_t y2 = y1+1; y2 <= h; y2++)
        {
            for(size_t x = 0; x < w; x++)
                a[x] += A[y2-1][x];
            resulto[y1][y2] = kadane(a);
        }
    }
    return resulto;
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

vector<vector<int>> col_reversed(const vector<vector<int>>& A)
{
    SAVE_DIM(A);
    vector<vector<int>> B(h, vector<int>(w));
    for(size_t y = 0; y < h; y++)
        for(size_t x = 0; x < w; x++)
            B[y][w-x-1] = A[y][x];
    return B;
}

int solve_first(const vector<vector<int>>& A)
{
    SAVE_DIM(A); (void)w;
    auto K = rowkadane(A);
    int result = INT_MIN;
    for(size_t y1 = 0; y1 < h; y1++)
        for(size_t y2 = y1+1; y2 <= h; y2++)
            result = max(result, K[y1][y2]);
    return result;
}

int solve_second_x(const vector<vector<int>>& A)
{
    SAVE_DIM(A); (void)w;
    auto K = rowkadane(A);
    auto Q = K;
    for(size_t k = 2; k <= h; k++)
        for(size_t y1 = 0, y2 = k; y2 <= h; y1++, y2++)
            Q[y1][y2] = max({K[y1][y2], Q[y1+1][y2], Q[y1][y2-1]});
    int result = INT_MIN;
    for(size_t y = 1; y < h; y++)
        result = max(result, Q[0][y] + Q[y][h]);
    return result;
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
    for(size_t y = 1; y < h; y++)
    {
        P.push_back(Q.front());
        Q.erase(Q.begin());
        result = max({result, solve_first(P) + solve_second_x(Q)});
    }
    return result;
}

int solve_third_2(const vector<vector<int>>& A)
{
    return max(solve_third_x(A), solve_third_x(col_reversed(A)));
}

int solve_third_1(const vector<vector<int>>& A)
{
    return max(solve_third_2(A), solve_third_2(row_reversed(A)));
}

int solve_third(const vector<vector<int>>& A)
{
    return max(solve_third_1(A), solve_third_1(transposed(A)));
}

int main()
{
    size_t h, w, k;
    cin >> h >> w >> k;

    vector<vector<int>> A(h, vector<int>(w));
    for(size_t y = 0; y < h; y++)
        for(size_t x = 0; x < w; x++)
            cin >> A[y][x];

    cout << ";";

    if(k == 1)
        cout << solve_first(A);
    else if(k == 2)
        cout << solve_second(A);
    else if(k == 3)
        cout << solve_third(A);
}
