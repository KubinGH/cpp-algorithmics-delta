#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200, MAX_C = 26*2;

uint32_t cell(char c)
{
    if('A' <= c and c <= 'Z')
        return c - 'A' + 26;
    else if('a' <= c and c <= 'z')
        return c - 'a';
    else
        return MAX_C;
}
char cellchar(uint32_t c)
{
    if(c < 26)
        return c + 'a';
    else if(c < 52)
        return c - 26 + 'A';
    else
        return ' ';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX_C+1> C;
    cin.ignore();
    for(uint32_t i = 0; i < n; i++)
    {
        string S;
        getline(cin, S);
        for(char c : S)
            C[cell(c)]++;
    }
    for(uint32_t i = 0; i < MAX_C; i++)
        if(C[i])
            cout << cellchar(i) << ' ' << C[i] << '\n';
}
