#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static uint32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    for(uint32_t qi = 0; qi < q; qi++)
    {
        char c; uint32_t a, b, v;
        cin >> c >> a >> b;
        if(c == '^' or c == '&' or c == '|')
            cin >> v;
        if(c == '^')
        {
            for(uint32_t i = a; i <= b; i++)
                A[i] ^= v;
        }
        else if(c == '&')
        {
            for(uint32_t i = a; i <= b; i++)
                A[i] &= v;
        }
        else if(c == '|')
        {
            for(uint32_t i = a; i <= b; i++)
                A[i] |= v;
        }
        else if(c == '?')
        {
            uint32_t v = 0;
            for(uint32_t i = a; i <= b; i++)
                v += A[i];
            cout << v << "\n";
        }
    }
}
