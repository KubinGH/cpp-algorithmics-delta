#include <bits/stdc++.h>

using namespace std;

uint64_t factorial_padic(uint64_t n, uint64_t k)
{
    uint64_t result = 0;
    auto l = k;
    while(n / l)
    {
        result += n / l;
        l *= k;
    }
    return result;
}

int main()
{
    size_t n;
    cin >> n;

    cout << min(factorial_padic(n, 2), factorial_padic(n, 5)) << endl;
}
