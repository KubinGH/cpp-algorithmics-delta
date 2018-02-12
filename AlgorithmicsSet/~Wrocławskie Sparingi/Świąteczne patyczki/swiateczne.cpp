#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 7000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint64_t, MAX> A;
    unordered_map<uint64_t, uint64_t> M;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], M[A[i]*A[i]]++;
    uint64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = i + 1; j < n; j++)
        {
            uint64_t s = A[i]*A[i] + A[j]*A[j];
            if(M.find(s) != M.end())
                r += M[s];
        }
    }
    cout << r << endl;
}
