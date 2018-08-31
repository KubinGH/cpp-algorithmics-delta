#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1<<17;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; int64_t m;
    cin >> n >> m;
    static int64_t A[MAX];
    static vector<uint32_t> T[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i]; A[i]--;
        T[i].push_back(i);
    }
    //for(uint32_t i = 0; i < n; i++)
    //    cerr << A[i] << " "; cerr << endl;
    static int64_t C[MAX];
    int64_t b = 0;
    for(uint32_t i = 1; i < n; i++)
        b += (m + A[i] - A[i-1])%m;
    fill(C, C + m, b);
    for(uint32_t i = 1; i < n; i++)
    {
        int64_t a = A[i-1], b = A[i];
        if(a > b)
        {
            uint32_t g = 0;
            for(uint32_t j = a+1; j < m; j++, g++)
                C[j] -= g;
            for(uint32_t j = 0; j <= b; j++, g++)
                C[j] -= g;
        }
        else
            for(uint32_t j = a+1, g = 0; j <= b; j++, g++)
                C[j] -= g;
    }
    int64_t r = INT64_MAX;
    for(uint32_t x = 0; x < m; x++)
    {
        int64_t c = 0;
        for(uint32_t i = 1; i < n; i++)
            c += min((m + A[i] - A[i-1]) % m, (m + A[i] - x)%m + 1);
        //cerr << x << " -> " << c << " " << C[x] << endl;
        r = min(r, c);
    }
    cout << r;
}
