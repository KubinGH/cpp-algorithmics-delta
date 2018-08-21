#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n;
    cin >> n;
    uint32_t* T = new uint32_t[3*n];
    iota(T, T + 3*n, 1);
    do
    {
        bool ok = true;
        for(uint32_t i = 0; i < 3*n and ok; i++)
        {
            if((i % n != 0) and T[i] < T[i-1])
                ok = false;
            if(i >= n and T[i] < T[i-n])
                ok = false;
        }
        if(ok)
        {
            for(uint32_t i = 0; i < 3*n; i++)
            {
                if(i == n or i == 2*n) cout << endl;
                cout << T[i] << " ";
            }
            cout << endl << endl;
        }
    } while(next_permutation(T, T + 3*n));

    delete[] T;
}
