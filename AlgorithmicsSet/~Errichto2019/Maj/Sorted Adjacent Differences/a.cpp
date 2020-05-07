#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t T;
    cin >> T;
    while(T --> 0)
    {
        size_t n;
        cin >> n;

        vector<int> A(n);
        for(auto& a : A)
            cin >> a;
        sort(A.begin(), A.end());

        vector<int> B; B.reserve(n);
        for(size_t i = 0; i < (n+1)/2; i++)
        {
            B.push_back(A[i]);
            if(i < n-i-1)
                B.push_back(A[n-i-1]);
        }
        reverse(B.begin(), B.end());

        for(auto& b : B)
            cout << b << ' ';
        cout << '\n';
    }
}
