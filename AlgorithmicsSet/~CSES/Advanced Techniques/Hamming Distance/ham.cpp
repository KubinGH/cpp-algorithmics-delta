#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n, k;
    cin >> n >> k;

    vector<uint> A;
    int r = INT_MAX;

    for(size_t i = 0; i < n; i++)
    {
        string S;
        cin >> S;
        A.emplace_back();
        for(size_t p = 0; p < k; p++)
            if(S.rbegin()[p] == '1')
                A.back() += 1u << p;
        for(size_t j = 0; j < i; j++)
            r = min(r, __builtin_popcount(A[i] ^ A[j]));
    }

    cout << r << endl;
}
