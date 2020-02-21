#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t T;
    cin >> T;

    while(T --> 0)
    {
        string A, B; int k;
        cin >> A >> B >> k;

        const size_t n = A.size();

        int a = 0, b = 0;
        for(auto x : A) a *= 10, a += x - '0';
        for(auto x : B) b *= 10, b += x - '0';
        bool ret = false;
        for(int c = b; c --> 0; )
        {
            string C(n, 0);
            int cc = c;
            for(size_t i = n; i --> 0; cc /= 10)
                C[i] = cc%10 + '0';

            int l = 0;
            for(size_t i = 0; i < n; i++)
                if(A[i] != C[i])
                    l++;

            if(l == k)
            {
                cout << C << '\n';
                ret = true;
                break;
            }
        }
        if(not ret)
            cout << "-1\n";
    }
}
