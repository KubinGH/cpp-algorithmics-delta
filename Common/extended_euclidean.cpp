#include <bits/stdc++.h>

template<typename T>
inline T gcd(T a, T b) { return __gcd(a, b); }

template<typename T>
struct gcdext_result { T d, x, y; };

template<typename T>
gcdext_result<T> gcdext(T a, T b)
{
    if(a == 0)
        return {b, 0, 1};
    gcdext_result<T> next = gcdext(b % a, a);
    return {next.d, next.y - (b/a)*next.x, next.x};
}