#include <bits/stdc++.h>

using namespace std;

int main()
{
    srand(time(NULL));
    uint32_t n, m, maxim;
    cin >> n >> m >> maxim;
    cout << n << " " << m << endl;
    for(uint32_t i = 0; i < n; i++)
        cout << rand() % maxim << " ";
    cout << endl;
    for(uint32_t i = 0; i < m; i++)
    {
        if(rand() % 2 == 0)
            cout << "0 " << (rand() % n) + 1 << " " << rand() % maxim << endl;
        else
        {
            uint32_t a = rand() % n, b;
            if(a < n - 1) b = (rand() % (n - a)) + a;
            else b = a;
            cout << "1 " << a+1 << " " << b+1 << endl;
        }
    }
}
