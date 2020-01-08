#include <bits/stdc++.h>

using namespace std;

const size_t P = 2048;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    vector<bool> prime(P, true);
    prime[0] = prime[1] = false;
    for(size_t p = 2; p < P; p++)
        if(prime[p])
            for(size_t x = p*p; x < P; x += p)
                prime[x] = false;

    string S;
    cin >> S;

    bool all_ok = true;
    for(uint p = 2; p < P; p++) if(prime[p])
    {
        uint s = 0;
        for(char c : S)
            s *= 10, s += c - '0', s %= p;

        bool ok = false;
        for(uint k = 0; k < p; k++)
            if(k*k % p == s)
                ok = true;

        if(not ok)
        {
            all_ok = false;
            break;
        }
    }

    cout << (all_ok ? "YES" : "NO");
}
