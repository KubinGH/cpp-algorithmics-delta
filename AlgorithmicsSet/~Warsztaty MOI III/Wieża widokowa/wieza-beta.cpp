#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6+1;

int64_t gcd(int64_t a, int64_t b) { return __gcd(a, b); }
int64_t lcm(int64_t a, int64_t b) { return a / gcd(a, b) * b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static int64_t H[MAX+1];
    int64_t m = -2e9;
    for(uint32_t i = 1; i <= n; i++)
    {
        char c;
        cin >> c;
        H[i] = H[i-1];
        if(c == 'D')
            H[i]--;
        else if(c == 'G')
            H[i]++;
        if(i < n)
            m = max(m, H[i]);
    }
    if(n == 1)
        { cout << 1; return 0; }
    // a * i > H[i]
    // a > H[i] / i
    // x+H[n] / n > H[i] / i
    // x > nH[i] / i - H[n]
    // x > (nH[i] - iH[n]) / i
    // i=n: (x >= (nH[n] - nH[n]) / n <=> x >= 0)
    pair<int64_t, int64_t> result = make_pair(0, 1);
    for(int64_t i = 1; i < (int64_t)n; i++)
    {
        pair<int64_t, int64_t> prop = make_pair(n*H[i] - i*H[n], i);
        //cout << result.first << "/" << result.second << " "
        //     << prop.first << "/" << prop.second << endl;
        if(result.first * prop.second < prop.first * result.second)
            result = prop;
    }
    //cout << result.first << "/" << result.second << endl;
    int64_t r = max(result.first/result.second + 1, 0LL);
    if(r == 1)
    {
        bool sub = true;
        for(int64_t i = 1; i < n and sub; i++)
            if(H[n] * i <= H[i] * n)
                sub = false;
        if(sub)
            r--;
    }
    cout << r;
}
