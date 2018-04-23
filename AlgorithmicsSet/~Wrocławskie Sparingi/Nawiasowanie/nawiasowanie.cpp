#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string S;
    cin >> S;
    uint32_t o = 0, r = 0;
    for(char c : S)
    {
        if(c == '(')
            o++;
        else if(c == ')')
        {
            if(o)
                o--;
            else
                r++;
        }
    }
    cout << o + r;
}
