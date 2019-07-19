#include <bits/stdc++.h>

using namespace std;

const uint32_t MOD = 1e9 + 7;

struct cell { uint32_t x, y; };
bool operator== (const cell& lhs, const cell& rhs)
    { return lhs.x == rhs.x and lhs.y == rhs.y; }
bool operator!= (const cell& lhs, const cell& rhs)
    { return not (lhs == rhs); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> Y(n), X(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> Y[i];
    for(uint32_t i = 0; i < n; i++)
        cin >> X[i];
    cell a = {0, 0}, b = {0, 0};
    Y[0]--; X[0]--;
    uint32_t result = 1;
    bool ok = true;
    for(uint32_t i = 0; i < 2*(n - 1); i++)
    {
        cell c = a, d = b;
        int q1 = (c.x+1<n and !!X[c.x+1] and !!Y[c.y]),
            q2 = (c.y+1<n and !!Y[c.y+1] and !!X[c.x]),
            q3 = (d.x+1<n and !!X[d.x+1] and !!Y[d.y]),
            q4 = (d.y+1<n and !!Y[d.y+1] and !!X[d.x]);
        uint32_t z = (q1<<3) | (q2<<2) | (q3<<1) | q4;
        if(z == 0b0101 or z == 0b1101 or z == 0b0111) c.y++, d.y++;
        if(z == 0b1011 or z == 0b1110 or z == 0b1010) c.x++, d.x++;
        if(z == 0b1001) c.x++, d.y++;
        if(z == 0b0110 or z == 0b1111) c.y++, d.x++;

        if(a == b and c != d)
            result *= 2, result %= MOD;
        if(a == c or b == d)
        {
            ok = false;
            break;
        }
        if(c == d)
            X[c.x]--, Y[c.y]--;
        else
            X[c.x]--, Y[c.y]--, X[d.x]--, Y[d.y]--;
        a = c; b = d;
    }
    if(ok) for(uint32_t i = 0; i < n; i++)
        if(X[i] or Y[i])
            ok = false;
    //cout << (ok ? "YES" : "NO") << endl;
    cout << (ok ? result : 0);
}
