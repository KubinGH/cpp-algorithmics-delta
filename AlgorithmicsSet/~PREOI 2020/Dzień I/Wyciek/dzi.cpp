#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int64_t n;
    cin >> n;

    if(n == 1)
    {
        cout << "OK\n";
        return 0;
    }

    auto fail = [&]() {
        cout << "WYCIEK\n";
        exit(0);
    };

    vector<int64_t> A(n);
    for(auto& a : A)
        cin >> a;

    int64_t sum = accumulate(A.begin(), A.end(), (int64_t)0), stsum = n*(n+1)/2;
    if(sum % stsum)
        fail();

    int64_t k = sum / stsum, curr = A.back(), drops = 0;

    int64_t t = 0, base = 0;
    for(auto a : A)
    {
        int64_t delta = k;

        if((curr + k - a) % n)
            fail();
        auto d = (curr + k - a) / n;
        if(d < 0)
            fail();

        delta -= d*n;
        drops += d;
        if(t) base += (n - t) * d;
        base += d;

        curr += delta;
        t++;
    }

    if(drops < k or base != A[0])
        fail();

    cout << "OK\n";
}
