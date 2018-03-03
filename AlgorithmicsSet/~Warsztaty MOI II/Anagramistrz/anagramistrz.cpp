#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string A, B;
    cin >> A >> B;
    static array<uint32_t, 256> BC;
    for(char c : B)
        BC[c]++;
    string AR;
    for(uint32_t i = 0; i < A.size(); i++)
    {
        if(BC[A[i]])
        {
            AR.push_back(A[i]);
            BC[A[i]]--;
        }
    }
    static array<uint32_t, 256> AC;
    for(char c : A)
        AC[c]++;
    string BR;
    for(uint32_t i = 0; i < B.size(); i++)
    {
        if(AC[B[i]])
        {
            BR.push_back(B[i]);
            AC[B[i]]--;
        }
    }
    if(AR.empty() or BR.empty())
    {
        cout << "BRAK";
    }
    else
    {
        cout << AR.size() << '\n' << AR << '\n';
        cout << BR.size() << '\n' << BR;
    }
}
