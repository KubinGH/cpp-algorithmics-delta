#include <bits/stdc++.h>

using namespace std;

int main()
{
    string S;
    uint64_t k;
    cin >> S >> k;
    static array<uint32_t, 256> C;
    for(uint32_t i = 0; i < S.size(); i++)
        C[S[i]]++;

}
