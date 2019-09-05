#include <bits/stdc++.h>

using namespace std;

inline int unique3(int a, int b, int c)
{
    return __builtin_popcount((1 << a) | (1 << b) | (1 << c));
}

int ft(char c)
{
    if(c == 'M') return 0;
    else if(c == 'F') return 1;
    else if(c == 'B') return 2;
    return -1;
}

using state = array<array<array<array<int, 3>, 3>, 3>, 3>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    //cin >> n;
    string S;
    //cin >> S;

    n = 1e6;
    S = string(n, 'F');

    array<state, 2> r;

#define FOR_EACH_SUBSTATE \
      for(int a = 0; a < 3; a++) \
        for(int b = 0; b < 3; b++) \
          for(int x = 0; x < 3; x++) \
            for(int y = 0; y < 3; y++)

    auto clear_state = [&](state& s, int v) {
        FOR_EACH_SUBSTATE
            s[a][b][x][y] = v;
    };
    clear_state(r[0], 0);

    for(size_t i = 0; i < n; i++)
    {
        clear_state(r[1], INT_MIN/2);
        auto v = ft(S[i]);
        FOR_EACH_SUBSTATE
        {
            r[1][b][v][x][y] = max(r[1][b][v][x][y], r[0][a][b][x][y] + unique3(a, b, v));
            r[1][a][b][y][v] = max(r[1][a][b][y][v], r[0][a][b][x][y] + unique3(x, y, v));
        }
        swap(r[0], r[1]);
    }

    int result = 0;
    FOR_EACH_SUBSTATE
        result = max(result, r[0][a][b][x][y]);

    cout << result - 6;
}
