#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> A(n), B(n);
    for(size_t i = 0; i < n; i++)
    {
        double a, b;
        cin >> a >> b;
        A[i] = round(a * 1e4);
        B[i] = round(b * 1e4);
    }

    sort(A.rbegin(), A.rend());
    sort(B.rbegin(), B.rend());

    int64_t s = 0, z = 0, result = 0;
    for(size_t i = 0, j = 0; i < n or j < n; )
    {
        if(s > z)
        {
            if(j == n)
                break;
            z += B[j++];
        }
        else
        {
            if(i == n)
                break;
            s += A[i++];
        }
        result = max(result, min(s, z) - int(i + j)*10'000);
    }

    cout << fixed << setprecision(4) << result/1e4 << endl;
}
