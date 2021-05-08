#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    if(n % 4 == 0)
    {
        cout << "YES" << endl;
        for(size_t c : {1, 2})
        {
            cout << n/2 << endl;
            for(size_t k = c; k < n - k + 1; k += 2)
                cout << k << " " << n-k+1 << " ";
            cout << endl;
        }
    }
    else if(n % 4 == 3)
    {
        cout << "YES" << endl;
        for(size_t c : {1, 2})
        {
            cout << n/2-c+2 << endl;
            for(size_t k = c; k < n - k; k += 2)
                cout << k << " " << n-k << " ";
            if(c == 2)
                cout << n;
            cout << endl;
        }
    }
    else
        assert(n*(n+1)/2 % 2), cout << "NO" << endl;
}
