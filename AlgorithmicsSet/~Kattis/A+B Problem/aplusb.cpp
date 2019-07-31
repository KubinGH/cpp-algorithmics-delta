#include <ktl/math/fft.cpp>
#include <ktl/math/poly.cpp>
#include <ktl/util/extio.cpp>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;

    vector<int> A(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];

    int minim = *min_element(A.begin(), A.end()), maxim = *max_element(A.begin(), A.end());

    polynomial<int64_t, rfft<int64_t, double, 32>> P(maxim - minim);
    map<int, size_t> cnt;
    for(auto x : A)
    {
        P[x - minim]++;
        cnt[x]++;
    }

    auto P2 = P * P;

    map<int, int64_t> wae;
    for(int i = 0; i <= 2 * (maxim - minim); i++)
        wae[i + 2*minim] = P2[i];

    int64_t result = 0;
    for(size_t k = 0; k < n; k++)
    {
        result += wae[A[k]];
        if(A[k])
        {
            if(A[k] % 2 == 0)
                result -= cnt[A[k]/2];
            result -= 2 * cnt[0];
        }
        else
            result -= 1 + 2*(cnt[0] - 1) + (cnt[0] - 1);
    }

    cout << result << endl;
}
