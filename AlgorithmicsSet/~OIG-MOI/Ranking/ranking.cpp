#include <bits/stdc++.h>

using namespace std;

typedef int int32_t;

const size_t MAX = 400000;
const int32_t INF = numeric_limits<int32_t>::max();

int main()
{
    int32_t n;
    cin >> n;
    static bitset<MAX> A;
    static int32_t L[MAX][2];
    int32_t a = 0, b = 0;
    for(int32_t i = 0; i < 2*n; i++)
    {
        int32_t c;
        cin >> c;
        A[i] = c == 2;
        if(i > 0)
            L[i][0] = L[i-1][0], L[i][1] = L[i-1][1];
        L[i][A[i]]++;
        if(A[i] == 1)
            b += 2*n - i - 1;
        else
            a += 2*n - i - 1;
    }
    int32_t ar = INF, br = INF;
    for(int32_t i = 0; i < 2*n; i++)
    {
        if(L[i][0] > L[i][1])
            ar = min(max(0, (b - a + L[i][0] - L[i][1]) / (L[i][0] - L[i][1])) + 2*n - 1, ar);
    }
    for(int32_t i = 0; i < 2*n; i++)
    {
        if(L[i][1] > L[i][0])
            br = min(max(0, (a - b + L[i][1] - L[i][0]) / (L[i][1] - L[i][0])) + 2*n - 1, br);
    }
    if(ar == INF)
        cout << "NIE" << endl;
    else
        cout << ar << endl;
    if(br == INF)
        cout << "NIE" << endl;
    else
        cout << br << endl;
}
