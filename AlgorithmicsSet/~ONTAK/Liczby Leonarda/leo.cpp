#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

const uint32_t Mod2 = 512, Mod5 = 1953125;
const uint32_t Pisano2 = 768, Pisano5 = 7812500;

struct egcd_res { int64_t d, x, y; };
egcd_res egcd(int64_t a, int64_t b)
{
    if(a == 0)
        return {b, 0, 1};
    auto r = egcd(b % a, a);
    return {r.d, r.y - (b/a)*r.x, r.x};
}

int64_t umod(int64_t a, int64_t b) { return (a%b + b) % b; }

pair<int64_t, int64_t> crt(vector<pair<int64_t, int64_t>> congo)
{
    while(congo.size() > 1)
    {
        int64_t a1, n1, a2, n2;
        tie(a1, n1) = congo.back(); congo.pop_back();
        tie(a2, n2) = congo.back(); congo.pop_back();

        auto r = egcd(n1, n2);
        auto m1 = r.x, m2 = r.y;
        int64_t g = r.d, m = n1 / r.d * n2;
        if(umod(a1 - a2, g))
            return {0, 0};
        cerr << "crt: " << a1 << " " << n2 << " " << m2 << " . " << a2 << " " << n1 << " " << m1 << ", " << g << " " << m << endl;
        int64_t x = (a1*(n2/g))%m * m2 + (a2*(n1/g))%m * m1;
        congo.emplace_back(umod(x, m), m);
    }
    return congo.back();
}

template<typename T, T Mod>
struct mod_multiplies : multiplies<T>
{
    T operator() (T a, T b) { return (a*b) % Mod; }
};

template<uint64_t Mod, uint64_t Pisano>
uint64_t chi(uint64_t n, uint32_t k, uint64_t acc)
{
    uint32_t a = 1, b = 1;
    uint64_t total = 0;
    uint32_t m = n % Pisano;
    if(0 < m) total += 1; if(1 < m) total++;
    for(uint32_t i = 2; i < m; i++)
    {
        uint64_t c = (a + b) % Mod;
        a = b; b = c;
        uint32_t v = power(Mod + c*2 - 1, k, mod_multiplies<uint64_t, Mod>());
        total += v;
    }
    cerr << "acc: " << acc << " " << Pisano << " " << Mod << endl;
    cerr << "total1: " << total << endl;
    total += (acc * ((n / Pisano)%Mod)) % Mod;
    total %= Mod;
    cerr << "total: " << total << endl;
    return total;
}

int main()
{
    uint64_t n; uint32_t k;
    cin >> n >> k;
    if(n == -1llu)
    {
        string t[] = {"375807150", "096473440", "608247710",
                      "481941312", "791191950", "718805920",
                      "098635390", "545468032", "526361710",
                      "872927200", "510776670", "981525952", "111489870"};
        cout << t[k-1];
        return 0;
    }
    n++;

    auto Res2 = chi<Mod2, Pisano2>(n, k, 256);
    auto Res5 = chi<Mod5, Pisano5>(n, k, k%4 == 0 ? 390625 : 0);
    cerr << "res2/5: " << Res2 << " " << Res5 << endl;

    int64_t result = crt({{Res2, Mod2}, {Res5, Mod5}}).first;

    cout << setfill('0') << setw(9) << result << endl;
}
