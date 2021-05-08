#include <bits/stdc++.h>


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
    char _whitespace_skip()
    {
        char lchar;
        while(isspace(lchar = getchar_unlocked())) {}
        return lchar;
    }
    unlocked_cin& operator>> (char& x)
    {
        x = _whitespace_skip();
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        x = 0;
        char lchar = _whitespace_skip();
        do {
            x *= 10, x += lchar - '0';
        } while(isdigit(lchar = getchar_unlocked()));
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        bool s = false;
        x = 0;
        char lchar = _whitespace_skip();
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

using namespace std;

template<typename T>
struct fenwick_tree
{
    vector<T> F;
    const size_t n;

    fenwick_tree(size_t _n) : F(_n+1), n(_n) {}

    template<typename It>
    fenwick_tree(It first, It last) : F(first, last), n(F.size())
    {
        F.insert(F.begin(), 0);
        for(size_t p = 1; p <= n; p++)
            if(p + (p&-p) <= n)
                F[p + (p&-p)] += F[p];
    }

    void delta(size_t p, T v)
    {
        for(p++; p <= n; p += p & -p)
            F[p] += v;
    }

    T get_prefix(size_t p) const
    {
        T r = 0;
        for(; p; p &= p - 1)
            r += F[p];
        return r;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    ucin >> n >> q;

    vector<int> A(n);
    for(auto& a : A)
        ucin >> a;

    for(size_t i = A.size(); i --> 1; )
        A[i] -= A[i-1];
    fenwick_tree<int64_t> tree(A.begin(), A.end());

    while(q --> 0)
    {
        char t;
        ucin >> t;
        if(t == '1')
        {
            size_t l, r; int v;
            ucin >> l >> r >> v; l--;
            tree.delta(l, +v);
            tree.delta(r, -v);
        }
        else if(t == '2')
        {
            size_t p;
            ucin >> p;
            ucout << tree.get_prefix(p) << '\n';
        }
    }
}
