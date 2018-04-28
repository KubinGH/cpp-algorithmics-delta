#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    static array<uint32_t, MAX+1> S;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        S[i+1] = S[i] + A[i];
    }
    auto sum_cycled = [=](uint32_t a, uint32_t b) {
        if(a <= b)
            return S[b+1] - S[a];
        else
            return S[n] - (S[a] - S[b+1]);
    };
    static array<uint32_t, MAX> M;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = i+1; j-i <= (n+1)/2; j++)
        {
            M[i] = max(M[i], sum_cycled(j%n, (j+n/2-1)%n));
            //cerr << sum_cycled(j%n, (j+n/2-1)%n) << " @ "
            //     << j%n << ".." << (j+n/2-1)%n << endl;
        }
        //cerr << i << ": " << M[i] << endl;
    }
    cout << S[n] - *min_element(M.begin(), M.begin() + n);
}
