#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t q;
    cin >> q;

    while(q --> 0)
    {
        size_t n;
        cin >> n;

        int a1 = 0, a2 = 0;
        size_t i1 = 0, i2 = 0, result = 0;

        for(size_t i = 0; i < n; i++)
        {
            int a;
            cin >> a;

            if(not a1) a1 = a, i1 = i;
            else if(not a2 and a != a1) a2 = a, i2 = i;
            if(a1 and a1 != a) result = max(result, i - i1);
            if(a2 and a2 != a) result = max(result, i - i2);
        }

        if(result) cout << result;
        else cout << "BRAK";
        cout << endl;
    }
}
