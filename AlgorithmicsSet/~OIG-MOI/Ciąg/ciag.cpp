#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 8e6;

int main()
{
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    A[1] = 1; A[2] = 2; A[3] = 2;
    cout << "1: 1 <1>\n2: 2 <3>" << endl;
    uint32_t i = 4;
    for(uint32_t k = 3; i <= n; k++)
    {
        for(uint32_t t = 0; t < A[k]; i++, t++)
        {
            A[i] = k;
            //cout << A[i] << " ";
        }
        cout << k << ": " << A[k] << " <" << i-1 << ">";
        cout << endl;
    }
    cout << A[n];
}
