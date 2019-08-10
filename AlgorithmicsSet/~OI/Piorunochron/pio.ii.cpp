#include <bits/stdc++.h>

// -*- ktl/structures/li_chao_tree.cpp -*-

#include <type_traits>
#include <algorithm>
#include <memory>
#include <limits>

using std::unique_ptr;
using std::swap; using std::__lg;
using std::numeric_limits;
using std::is_integral;

template<typename Arg, typename Value, typename Fun>
struct li_chao_tree
{
    const Arg rangeL, rangeR, eps;
    const bool mirror_ox;

    struct li_chao_node
    {
        Fun opt;
        unique_ptr<li_chao_node> left_child, right_child;
        li_chao_node* get_left_child()
        {
            if(not left_child)
                left_child = unique_ptr<li_chao_node>(new li_chao_node);
            return left_child.get();
        }
        li_chao_node* get_right_child()
        {
            if(not right_child)
                right_child = unique_ptr<li_chao_node>(new li_chao_node);
            return right_child.get();
        }
        void insert(Fun fun, Arg left, Arg right, Arg eps)
        {
            Arg mid = left + (right - left) / 2;
            bool opt_left = fun(left) < opt(left),
                 opt_mid = fun(mid) < opt(mid);
            if(opt_mid)
                swap(fun, opt);
            if(left + eps >= right)
                return;
            else if(opt_left != opt_mid)
                return get_left_child()->insert(fun, left, mid, eps);
            else
                return get_right_child()->insert(fun, mid, right, eps);
        }
        Fun get(Arg x, Arg left, Arg right, Arg eps)
        {
            Arg mid = left + (right - left) / 2;
            if(left + eps >= right)
                return opt;
            Fun lo;
            if(x < mid)
                lo = (left_child ? left_child->get(x, left, mid, eps) : Fun());
            else
                lo = (right_child ? right_child->get(x, mid, right, eps) : Fun());
            return lo(x) < opt(x) ? lo : opt;
        }
    } root;

    template<typename T = Arg, typename std::enable_if<not is_integral<T>::value, bool>::type = true>
    li_chao_tree(Arg _rangeL, Arg _rangeR, Arg _eps, bool _mirror_ox = false)
        : rangeL(_rangeL), rangeR(_rangeR), eps(_eps), mirror_ox(_mirror_ox) {}

    template<typename T = Arg, typename std::enable_if<is_integral<T>::value, bool>::type = true>
    li_chao_tree(Arg _rangeL, Arg _rangeR, bool _mirror_ox = false)
        : rangeL(_rangeL), rangeR(_rangeL + (1 << __lg(2*(_rangeR-_rangeL)-1))),
          eps(1), mirror_ox(_mirror_ox) {}

    void insert(Fun fun)
    {
        return root.insert(mirror_ox ? -fun : fun, rangeL, rangeR, eps);
    }
    Fun get(Arg x)
    {
        auto r = root.get(x, rangeL, rangeR, eps);
        return mirror_ox ? -r : r;
    }
    Value get_value(Arg x)
    {
        return get(x)(x);
    }
};

template<typename T>
struct li_chao_line
{
    T slope, constant;
    li_chao_line() : slope(0), constant(numeric_limits<T>::max()) {}
    li_chao_line(T a, T b) : slope(a), constant(b) {}
    T operator() (T x) const { return slope*x + constant; }
    li_chao_line operator- () const { return {-slope, -constant}; }
};

template<typename A, typename T = A>
using line_li_chao_tree = li_chao_tree<A, T, li_chao_line<T>>;

// -$- ktl/structures/li_chao_tree.cpp -$-


// -*- ktl/util/fastio.cpp -*-

#include <cstdint>
#include <cstdio>
#include <type_traits>
#include <iostream>

#ifdef _WIN32
#define getchar_unlocked getchar
#define putchar_unlocked putchar
#define fputs_unlocked fputs
#endif

using std::is_integral; using std::is_unsigned; using std::is_signed;
using std::make_unsigned;
using std::enable_if;

struct unlocked_cin
{
    unlocked_cin& operator>> (char& x)
    {
        x = getchar_unlocked();
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        char lchar; x = 0;
        while(isspace(lchar = getchar_unlocked())) {}
        do {
            x *= 10, x += lchar - '0';
        } while(isdigit(lchar = getchar_unlocked()));
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        bool s = false; x = 0;
        char lchar;
        while(isspace(lchar = getchar_unlocked())) {}
        if(lchar == '-')
            s = true;
        else
            x += lchar - '0';
        while(isdigit(lchar = getchar_unlocked()))
            x *= 10, x += lchar - '0';
        if(s) x = -x;
        return *this;
    }
} ucin;

struct unlocked_cout
{
    unlocked_cout& operator<< (const char* c)
    {
        fputs_unlocked(c, stdout);
        return *this;
    }
    unlocked_cout& operator<< (char x)
    {
        putchar_unlocked(x);
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cout&>::type
    operator<< (T x)
    {
        static char buffer[64];
        size_t i = 0;
        if(not x)
            buffer[i++] = '0';
        while(x)
            buffer[i++] = (x % 10) + '0', x /= 10;
        for(; i --> 0; )
            putchar_unlocked(buffer[i]);
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cout&>::type
    operator<< (T x)
    {
        if(x < 0)
            putchar_unlocked('-'), x = -x;
        return *this << static_cast<typename make_unsigned<T>::type>(x);
    }
} ucout;

// -$- ktl/util/fastio.cpp -$-


using namespace std;

const size_t NAX = 1 << 20;

double sqrt_cache[NAX];

struct __sqrt_cache_init
{
    __sqrt_cache_init()
    {
        for(size_t i = 0; i < NAX; i++)
            sqrt_cache[i] = sqrt(i);
    }
} __sqrt_cache_init_inst;


struct li_chao_sqrt_fun
{
    int h, i; bool s;
    li_chao_sqrt_fun() : h(0), i(INT_MAX), s(false) {}
    li_chao_sqrt_fun(int _h, int _i) : h(_h), i(_i), s(false) {}
    double operator() (int j) const
    {
        if(j < i)
            return 0;
        return -(h + sqrt_cache[j - i]);
    }
    li_chao_sqrt_fun operator- () const { return *this; }
};

int main()
{
    size_t n;
    ucin >> n;

    vector<int> H(n);
    for(size_t i = 0; i < n; i++)
        ucin >> H[i];

    auto oneway = [&]() {
        li_chao_tree<int, double, li_chao_sqrt_fun> T(0, n);
        vector<int> M(n);
        for(size_t i = 0; i < n; i++)
        {
            T.insert({H[i], (int)i});
            M[i] = ceil(-T.get_value(i));
        }
        return M;
    };

    auto M = oneway();
    reverse(H.begin(), H.end());
    auto M1 = oneway();
    reverse(H.begin(), H.end());
    reverse(M1.begin(), M1.end());

    for(size_t i = 0; i < n; i++)
        ucout << max(M[i], M1[i]) - H[i] << '\n';

}
