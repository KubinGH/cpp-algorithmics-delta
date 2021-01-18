#include <bits/stdc++.h>

using namespace std;

const int64_t oo = 1e13;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int64_t> A(n+1);

    for(size_t i = 1; i <= n; i++)
        cin >> A[i];

    bool ok = true;
    for(size_t i = 1; i <= n and ok; i++)
        for(size_t j = 1; j < i and ok; j++)
            if(A[i] - A[j] > A[i-j])
                ok = false;

    if(ok)
    {
        cout << "TAK" << endl << n << endl;
        for(size_t i = 1; i <= n; i++)
            cout << A[i]-A[i-1] << ' ';
        cout << endl;
    }
    else
        cout << "NIE" << endl;
}
