#pragma GCC optimize ("Ofast")
#pragma GCC target ("tune=native")
#include <bits/stdc++.h>

using namespace std;


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

template<typename T, typename BinaryOperation>
struct sparse_table
{
    BinaryOperation F;
    vector<vector<T>> A;

    template<typename Iterator>
    sparse_table(Iterator first, Iterator last, BinaryOperation _F = {}) : F(_F)
    {
        const size_t n = distance(first, last);
        A.emplace_back();
        A[0].reserve(n);
        copy(first, last, back_inserter(A[0]));
        for(size_t k = 1, p = 2; p <= n; k++, p *= 2)
        {
            A.emplace_back(n - p + 1);
            for(size_t i = 0; i + p <= n; i++)
                A[k][i] = F(A[k-1][i], A[k-1][i+p/2]);
        }
    }

    T operator() (size_t l, size_t r)
    {
        const size_t k = __lg(r - l);
        return F(A[k][l], A[k][r - (1 << k)]);
    }
};
struct max_i { unsigned operator() (unsigned a, unsigned b) { return max(a, b); } };

int main()
{
    size_t n, m;
    ucin >> n >> m;

    vector<uint64_t> A(n);
    for(size_t i = 0; i < n; i++)
        ucin >> A[i];

    vector<uint64_t> S(n + 1);
    partial_sum(A.begin(), A.end(), S.begin() + 1);

    sparse_table<unsigned, max_i> T(A.begin(), A.end());

    while(m --> 0)
    {
        size_t l, r;
        ucin >> l >> r; l--;
        ucout << (S[r] - S[l] > 2*T(l, r) ? "TAK" : "NIE") << "\n";
    }
}
