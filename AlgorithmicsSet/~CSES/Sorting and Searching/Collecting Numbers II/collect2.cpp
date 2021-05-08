#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<size_t> A(n+3), I(n+2);
    A[0] = SIZE_MAX; A[n+1] = 0; A[n+2] = n+1;
    I[0] = n+1; I[n+1] = n+2;
    for(size_t i = 1; i <= n; i++)
    {
        cin >> A[i];
        I[A[i]] = i;
    }

    auto is_start = [&](size_t a) {
        return I[a-1] > I[a];
    };

    size_t result = 0;
    for(size_t i = 1; i <= n; i++)
        result += is_start(i);

    while(m --> 0)
    {
        size_t a, b;
        cin >> a >> b;
        size_t x = A[a], y = A[b];
        if(x > y)
            swap(x, y);
        result -= is_start(x) + is_start(y) + is_start(y+1) + (x+1<y ? is_start(x+1) : 0);
        swap(A[a], A[b]);
        I[A[a]] = a; I[A[b]] = b;
        result += is_start(x) + is_start(y) + is_start(y+1) + (x+1<y ? is_start(x+1) : 0);

        cout << result << '\n';
    }
}
