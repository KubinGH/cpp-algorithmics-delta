#include <bits/stdc++.h>

using namespace std;

int factorial_p_adic(int p, int n)
{
    int r = 0, q = p;
    while(n >= q)
        r += n / q, q *= p;
    return r;
}
int binomial_p_adic(int p, int n, int k)
{
    return factorial_p_adic(p, n) - (factorial_p_adic(p, k) + factorial_p_adic(p, n - k));
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    int x = 0;
    n--;
    for(size_t i = 0; i <= n; i++)
    {
        int a;
        cin >> a;
        if(not binomial_p_adic(2, n, i))
            x ^= a;
    }

    cout << x << endl;
}
