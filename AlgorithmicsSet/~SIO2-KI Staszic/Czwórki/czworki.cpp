#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5000;
const uint32_t MAX_E = 500001;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.begin()+n);
    uint32_t maxim = A[n-1];
    static array<uint32_t, MAX_E> R2, R3;
    for(uint32_t i = 0; i < n; i++)
    {
        if(A[i]+A[0] > maxim) break;
        for(uint16_t j = 0; j < n; j++)
        {
            if(A[i]+A[j] > maxim) break;
            R2[A[i]+A[j]]++;
        }
    }
    for(uint32_t i = 0; i < n; i++)
    {
        if(A[i] < A[0]) break;
        for(uint32_t j = 0; j < n; j++)
        {
            if(A[i] < A[j]) break;
            R3[A[i]] += R2[A[i]-A[j]];
        }
    }
    uint64_t result = 0;
    for(uint32_t i = 0; i < n; i++)
        result += R3[A[i]];
    cout << result << endl;
}
