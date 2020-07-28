#include <bits/stdc++.h>

using namespace std;

struct fraction
{
    int64_t n, d;
    fraction(int64_t a, int64_t b)
    {
        if(b < 0) a = -a, b = -b;
        auto g = gcd(abs(a), abs(b));
        n = a / g; d = b / g;
    }
    constexpr fraction(int64_t a) : n(a), d(1) {}

    long double real() const { return (long double)n / d; }
};

bool operator< (const fraction& lhs, const fraction& rhs)
{
    return lhs.n*rhs.d - rhs.n*lhs.d < 0;
}
bool operator== (const fraction& lhs, const fraction& rhs)
{
    return lhs.n == rhs.n and lhs.d == rhs.d;
}
bool operator!= (const fraction& lhs, const fraction& rhs) { return not (lhs == rhs); }
bool operator<= (const fraction& lhs, const fraction& rhs) { return lhs == rhs or lhs < rhs; }
bool operator>= (const fraction& lhs, const fraction& rhs) { return not (lhs < rhs); }
bool operator>  (const fraction& lhs, const fraction& rhs) { return not (lhs <= rhs); }

ostream& operator<< (ostream& out, const fraction& it)
{
    return out << it.n << '/' << it.d;
}

template<typename T, typename Cmp>
struct ex_tree
{
    size_t w;
    const T neutral;
    vector<T> values;
    Cmp cmp;

    ex_tree(size_t n, T _neutral)
        : w(1 << __lg(2*n - 1)), neutral(_neutral), values(2*w, neutral) {}

    void set(size_t i, const T& v)
    {
        values[i += w] = v;
        while(i > 1)
        {
            i /= 2;
            values[i] = min(values[2*i], values[2*i+1], cmp);
        }
    }
    void clear(size_t i) { return set(i, neutral); }
    const T& extremum() const { return values[1]; }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<pair<int64_t, int64_t>> L(n+2);
    for(size_t i = 1; i <= n; i++)
        cin >> L[i].second >> L[i].first;

    vector<size_t> P(n+2);
    for(size_t i = 1; i <= n; i++)
        cin >> P[i];
    P.back() = n+1;


    ex_tree<fraction, less<fraction>> minim(n, 1e9);
    ex_tree<fraction, greater<fraction>> maxim(n, 0);


    size_t locks = 0;
    auto push = [&](size_t i) {
        if(i == 0 or i >= n) return;
        auto [a, b] = L[P[i]];
        auto [c, d] = L[P[i+1]];
        if(a - c > 0)
            minim.set(i, fraction(d-b, a-c));
        else if(a - c < 0)
            maxim.set(i, fraction(d-b, a-c));
        else if(d - b < 0)
            locks++;
    };

    auto pop = [&](size_t i) {
        if(i == 0 or i >= n) return;
        auto [a, b] = L[P[i]];
        auto [c, d] = L[P[i+1]];
        if(a - c > 0)
            minim.clear(i);
        else if(a - c < 0)
            maxim.clear(i);
        else if(d - b < 0)
            locks--;
    };

    for(size_t i = 1; i < n; i++)
        push(i);

    auto answer = [&]() -> fraction {
        return not locks and maxim.extremum() <= minim.extremum() ? minim.extremum() : 0;
    };

    auto print_answer = [&]() {
        auto f = answer();
        if(f == 0)
            cout << "NIE\n";
        else
            cout << f << '\n';
    };

    print_answer();

    size_t q;
    cin >> q;

    while(q --> 0)
    {
        size_t i, j;
        cin >> i >> j;
        pop(i-1); pop(i);
        pop(j-1); pop(j);
        swap(P[i], P[j]);
        push(j-1); push(j);
        push(i-1); push(i);

        print_answer();
    }
}
