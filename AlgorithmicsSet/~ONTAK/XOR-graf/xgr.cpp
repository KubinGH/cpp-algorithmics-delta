#include <bits/stdc++.h>

using namespace std;

int msb(int x)
{
    return 1 << __lg(x);
}

int brute(const vector<int>& A)
{
    const size_t n = A.size();
    int result = 0;
    for(int m = 0; m < (1 << n); m++)
    {
        bool ok = true;
        for(size_t i = 1; i < n; i++)
            for(size_t j = 0; j < i; j++)
        {
            if((m >> i) & 1 and (m >> j) & 1)
            {
                if((A[i] ^ A[j]) <= max(A[i], A[j]))
                    ok = false;
            }
        }
        if(ok)
            result = max(result, __builtin_popcount(m));
    }
    return result;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;

    size_t b = 0;
    vector<int> A(n);
    for(size_t i = 0; i < n; i++)
    {
        cin >> A[i];
        b = max<size_t>(b, __lg(A[i]) + 1);
    }
    sort(A.begin(), A.end());
    vector<int> Q(1 << b);
    for(int a : A)
        for(int m = 0; m < msb(a); m++)
            if((a & m) == 0)
                Q[m | msb(a)] = max(Q[m | msb(a)], Q[m] + 1);

    //cerr << brute(A) << endl;
    cout << *max_element(Q.begin(), Q.end());
}
