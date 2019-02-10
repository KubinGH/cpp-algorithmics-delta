#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        uint32_t n;
        cin >> n;
        static uint32_t A[MAX], B[MAX];
        for(uint32_t i = 0; i < n; i++)
            cin >> A[i] >> B[i];
        sort(A, A + n); sort(B, B + n);
        uint32_t c = 0, i = 0, j = 0;
        while(i < n or j < n)
        {
            if(j >= n or (i < n and A[i] < B[j]))
                c++, i++;
            else
                c--, j++;
            if(c > 1)
                break;
        }
        if(c > 1)
            cout << "NIE\n";
        else
            cout << "TAK\n";
    }
}
