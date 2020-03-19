#include <bits/stdc++.h>

using namespace std;

bool isprime(int n)
{
    if(n <= 1) return false;
    for(int d = 2; d*d <= n; d++)
        if(n % d == 0)
            return false;
    return true;
}


#ifdef XHOVA
struct lib
{
    int n;
    lib() { cout << "n = "; cin >> n; }
} liblib;
int libcnt = 0;
bool divisor(int n)
{
    assert(++libcnt <= 20);
    cout << "? " << n << " -> " << (liblib.n % n == 0) << endl;
    return liblib.n % n == 0;
}
#else
bool divisor(int n)
{
    cout << n << endl;
    string ret; cin >> ret;
    return ret == "yes";
}
#endif
bool answer(bool prime)
{
    cout << (prime ? "prime" : "composite") << endl;
#ifdef XHOVA
    assert(prime == isprime(liblib.n));
#endif
    exit(0);
}

int siev[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

int main()
{
    int q = 0;
    for(auto p : siev)
    {
        if(divisor(p))
        {
            if(q) answer(false);
            q = p;
        }
    }
    if(not q)
        answer(true);

    for(int r = 2; r <= 100; r++)
    {
        bool use = true;
        if(isprime(r))
            use = false;
        if(use) for(auto p : siev)
            if((p == q and r % p != 0) or (p != q and r % p == 0))
                use = false;
        if(not use) continue;

        if(divisor(r))
            answer(false);
    }

    answer(true);
}
