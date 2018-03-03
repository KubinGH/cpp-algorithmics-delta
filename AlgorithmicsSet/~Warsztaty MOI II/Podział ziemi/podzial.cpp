#include <bits/stdc++.h>
#define SI(i, j) (S[j+1] - S[i])
#define AVGI(i, j) ((double)(S[j+1] - S[i]) / (double)(j - i + 1))

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k, b, d;
    cin >> n >> k >> b >> d;
    cout << fixed; cout.precision(d);
    static array<uint32_t, MAX> A;
    static array<uint32_t, MAX+1> S;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        S[i+1] = S[i] + A[i];
    }
    uint32_t i = 0, ck = 0, rl = 0, ri = 0, rj = 0;
    double ra = -1;
    for(uint32_t j = 0; j < n; j++)
    {
        if(A[j] % k) ck++;
        while(i < j and ck > b)
        {
            if(A[i] % k) ck--;
            i++;
        }
        if(ck <= b and j - i + 1 >= rl)
        {
            if(j - i + 1 > rl)
            {
                ri = i, rj = j;
                ra = -1;
            }
            if(AVGI(i, j) >= ra)
            {
                ra = AVGI(i, j);
                ri = i, rj = j;
            }
            rl = j - i + 1;
        }
    }
    if(ra == -1)
        cout << "NIE";
    else
    {
        cout << rl << '\n';
        cout << ra << '\n';
        for(uint32_t i = ri; i <= rj; i++)
            cout << A[i] << ' ';
    }
}
