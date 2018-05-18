#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1u << 17;
uint32_t cube(uint32_t x) { return x * x * x; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t a, b;
    cin >> a >> b;
    bitset<MAX> A;
    A[0] = 1;
    for(uint32_t n = 1; cube(n) < MAX; n++)
    {
        uint32_t c = cube(n);
        for(uint32_t i = MAX - c; i --> 0;)
        {
            if(A[i])
                A[i+c] = true;
        }
    }
    for(uint32_t i = a; i <= b; i++)
        if(A[i])
            cout << i << " ";
}
