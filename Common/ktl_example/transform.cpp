#include <bits/stdc++.h>
#include <ktl/math/fft.cpp>
#include <ktl/math/ntt.cpp>

using namespace std;

int main()
{
    vector<int> A;
    for(int i = 0; i < 1e6; i++)
        A.push_back(i);

    auto a = fft<long double>{}[fft<long double>{}(A)];
    auto b = ntt_alpha{}[ntt_alpha{}(A)];

    cout << a[1] << " " << a[256] << " " << a[6125] << " " << a[99999] << endl;
    cout << b[1] << " " << b[256] << " " << b[6125] << " " << b[99999] << endl;
}
