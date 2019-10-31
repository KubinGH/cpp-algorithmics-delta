#include <iostream>
#include <optional>
#include <vector>

using namespace std;

// i*k <= lim, i in {0, 1, 2, ...}
int64_t count_multiples(int64_t k, int64_t lim)
{
    return lim >= 0 ? lim/k+1 : 0;
}
// a <= i*k <= b, i in {0, 1, 2, ...}
int64_t count_multiples(int64_t k, int64_t a, int64_t b)
{
    return count_multiples(k, b) - count_multiples(k, a-1);
}

optional<pair<int64_t, string>> solve(int64_t N, int64_t k, int64_t A, int64_t B, int64_t C, int64_t D)
{
    for(auto name : {"Dima", "Mitya"})
    {
        for(auto x : {(int64_t)1, N+1, A, B+1, C, D+1})
        {
            x %= k;
            if(x == 0) x += k;
            auto n = N-x, a = A-x, b = B-x, c = C-x, d = D-x;

            auto p = count_multiples(2*k, n), q = count_multiples(2*k, n - k);
            auto u = count_multiples(2*k, a, b), v = count_multiples(2*k, c-k, d-k);
            p -= u; q += u;
            q -= v; p += v;

            if(p == q)
                return make_pair(x, name);
        }
        swap(A, C);
        swap(B, D);
    }
    return {};
}

int main()
{
    int64_t N, k, A, B, C, D;
    cin >> N >> k >> A >> B >> C >> D;

    if(auto sol = solve(N, k, A, B, C, D))
        cout << sol->first << endl << sol->second << endl;
    else
        cout << -1;
}
