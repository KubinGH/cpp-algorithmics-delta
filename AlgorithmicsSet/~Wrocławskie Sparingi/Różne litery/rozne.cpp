#include <bits/stdc++.h>

using namespace std;

int main()
{
    string A;
    cin >> A;
    static array<uint32_t, 26> C;
    for(char c : A)
        C[c - 'a']++;
    sort(C.begin(), C.end());
    static array<uint32_t, 27> S;
    for(uint32_t i = 0; i < 26; i++)
        S[i+1] = S[i] + C[i];
    for(uint32_t i = 26; i --> 0;)
    {
        cout << S[i] << " ";
        if(S[i] == 0)
            break;
    }
}
