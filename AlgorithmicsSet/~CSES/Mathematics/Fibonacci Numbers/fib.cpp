#include <bits/stdc++.h>

using namespace std;

constexpr uint64_t mod = 1e9 + 7;
constexpr auto modmul = [](uint64_t x, uint64_t y) { return x * y % mod; };

template<typename T, typename Tk, typename AssociativeBinaryOp = multiplies<T>>
T power(T n, Tk k, AssociativeBinaryOp f = {}, T r = T(1))
{
    while(k)
    {
        if(k % 2)
            r = f(r, n);
        k /= 2;
        n = f(n, n);
    }
    return r;
}

uint64_t inverse(uint64_t n)
{
    return power(n, mod - 2, modmul);
}

struct ring
{
    uint64_t a, b;

    ring(uint64_t x) : a(x), b(0) {}
    ring(uint64_t x, uint64_t y) : a(x), b(y) {}
};
ring operator- (const ring& p) { return {p.a ? mod - p.a : 0, p.b ? mod - p.b : 0}; }
ring operator+ (const ring& p, const ring& q) { return {(p.a + q.a) % mod, (p.b + q.b) % mod}; }
ring operator- (const ring& p, const ring& q) { return p + (-q); }
ring inverse (const ring& p)
{
    auto x = inverse((5*mod + modmul(p.a, p.a) - 5*modmul(p.b, p.b)) % mod);
    return {modmul(p.a, x), modmul(mod - p.b, x)};
}
ring operator* (const ring& p, const ring& q) { return {(modmul(p.a, q.a) + 5 * modmul(p.b, q.b)) % mod, (modmul(p.a, q.b) + modmul(p.b, q.a)) % mod}; }
ring operator/ (const ring& p, const ring& q) { return p * inverse(q); }
ostream& operator<< (ostream& out, const ring& p) { return out << "(" << p.a << "+" << p.b << "*rt(5))"; }

const ring phi = ring{1, 1} / ring{2, 0}, iphi = ring{1, 0} - phi;

ring binet(uint64_t n)
{
    return (power(phi, n) - power(iphi, n)) / (phi - iphi);
}

int main()
{
    uint64_t n;
    cin >> n;

    cout << binet(n).a << endl;
}
