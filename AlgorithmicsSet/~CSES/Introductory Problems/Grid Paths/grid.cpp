#include <bits/stdc++.h>

using namespace std;

inline size_t I(size_t y, size_t x)
{
    return 7*y + x;
}
inline bool oob(size_t y, size_t x)
{
    return y >= 7 or x >= 7;
}
inline size_t push(size_t mask, size_t y, size_t x)
{
    return mask | (1ul << I(y, x));
}
inline size_t pop(size_t mask, size_t y, size_t x)
{
    return mask & ~(1ul << I(y, x));
}
inline bool lock(size_t mask, size_t y, size_t x)
{
    return oob(y, x) or (mask >> I(y, x) & 1);
}

void fun_next(size_t y, size_t x, size_t k);

char T[48];
size_t mask, result;

void fun(size_t y, size_t x, size_t k = 0)
{
    if(k == 48)
        { result += (y == 6 and x == 0); return; }
    if(T[k] == 'U' or T[k] == '?') fun_next(y - 1, x, k);
    if(T[k] == 'D' or T[k] == '?') fun_next(y + 1, x, k);
    if(T[k] == 'R' or T[k] == '?') fun_next(y, x + 1, k);
    if(T[k] == 'L' or T[k] == '?') fun_next(y, x - 1, k);
}

void fun_next(size_t y, size_t x, size_t k)
{
    if(lock(mask, y, x))
        return;
    if(k < 47 and y == 6 and x == 0)
        return;

    if(y == 6 and not lock(mask, y, x + 1))
        return;
    if(x == 6 and not lock(mask, y - 1, x))
        return;
    if(y == 0 and lock(mask, y + 1, x) and not lock(mask, y, x - 1))
        return;
    if(x == 0 and lock(mask, y, x + 1) and not lock(mask, y - 1, x))
        return;
    if(x != 0 and x != 6 and y != 0 and y != 6)
    {
        if(lock(mask, y+1, x) and lock(mask, y-1, x) and not lock(mask, y, x+1) and not lock(mask, y, x-1))
            return;
        if(not lock(mask, y+1, x) and not lock(mask, y-1, x) and lock(mask, y, x+1) and lock(mask, y, x-1))
            return;
    }

    /*
    size_t vis = push(mask, 6, 0);
    vector<pair<size_t, size_t>> Q;
    Q.clear(); Q.emplace_back(6, 0);
    auto maybe = [&](size_t y1, size_t x1) {
        if(not lock(vis, y1, x1))
            vis = push(vis, y1, x1), Q.emplace_back(y1, x1);
    };
    while(not Q.empty())
    {
        auto [y1, x1] = Q.back(); Q.pop_back();
        maybe(y1 + 1, x1); maybe(y1 - 1, x1);
        maybe(y1, x1 + 1); maybe(y1, x1 - 1);
    }
    if(vis != (1ul << 49) - 1)
        return 0;
    */

    mask = push(mask, y, x);
    fun(y, x, k + 1);
    mask = pop(mask, y, x);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> T;
    mask = push(0, 0, 0); fun(0, 0);
    cout << result << endl;
}
