#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;

size_t brute(size_t n, int k)
{
    vector<int> A(n);

    size_t last = 0;
    auto inc = [&]() {
        A[0]++;
        last = 0;
        for(size_t i = 0; i+1 < n; i++)
            if(A[i] == k)
                A[i] = 0, A[i+1]++, last = i;
        if(A[n-1] == k)
            last = n, A[n-1] = 0;
    };

    set<vector<int>> S;
    for(; last <= n/2; inc())
    {
        for(size_t i = 0; i < n/2; i++)
            A[n-i-1] = A[i];
        for(size_t i = 0; i < n; i++)
        {
            S.insert(A);
            rotate(A.begin(), A.begin() + 1, A.end());
        }
    }

    return S.size();
}

int main()
{
    size_t n, k;
    cin >> n >> k;
    cout << brute(n, k);
}
