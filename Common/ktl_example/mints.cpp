#include <ktl/math/modular.cpp>
#include <ktl/util/debug_macros.cpp>

using namespace std;

int main()
{
    using Z1 = mint<uint32_t, (uint32_t)1e9+7>;
    using Z2 = mint<uint32_t, 0>;
    mint_global_mod<uint32_t>(1e9+7);

    auto start = time(0);
    cout << start << endl;
    Z1 n1;
    Z2 n2;
    uint32_t n3 = 0;
    for(size_t i = 0; i < 1e8; i++)
        n1 += i;
    cout << n1 << " @ " << (time(0) - start) << endl;
    for(size_t i = 0; i < 1e8; i++)
        n2 += i;
    cout << n2 << " @ " << (time(0) - start) << endl;
    for(size_t i = 0; i < 1e8; i++)
        n3 += i, n3 %= uint32_t(1e9+7);
    cout << n3 << " @ " << (time(0) - start) << endl;

    n1 *= 2;

    using Z = mint<uint32_t, 11>;
    Z a = 5, b = 3;
    Z c = a + 2*b;
    Z d = (a + 2) + (2 + a);
    debugx(note(a));
    debugx(note(b));
    debugx(note(c));
    debugx(note(d));
    debugx(note(power(a, 9)));
    auto e = 1/a;
    debugx(note(e));
    auto f = a - b - c - d;
    debugx(note(f));

    Z x, y;
    cin >> x >> y;
    cout << 2*(x + y) << endl;
}
