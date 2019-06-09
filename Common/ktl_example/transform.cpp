#include <bits/stdc++.h>
#include <ktl/math/fft.cpp>

using namespace std;

int main()
{
    vector<int> A;
    for(int i = 0; i < 1e6; i++)
        A.push_back(i);

    auto a = fft<long double>{}[fft<long double>{}(A)];

    cout << a[1] << " " << a[256] << " " << a[6125] << " " << a[99999] << endl;
}
