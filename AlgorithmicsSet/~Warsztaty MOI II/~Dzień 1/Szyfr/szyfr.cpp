#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n;
    char om;
    cin >> n >> om;
    string S;
    cin >> S;
    static array<uint32_t, 26> C;
    for(uint32_t i = 0; i < n; i++)
        C[S[i] - 'A']++;
    char m = 'A';
    for(uint32_t i = 0; i < 26; i++)
    {
        if(C[i] > C[m - 'A'])
            m = i + 'A';
    }
    int cycle = m - om;
    for(char x : S)
        cout << (char)((((int)x - 'A' - cycle + 26) % 26) + 'A');
}
