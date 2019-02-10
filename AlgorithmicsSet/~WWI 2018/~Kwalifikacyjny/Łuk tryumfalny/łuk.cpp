#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    char c;
    while(cin >> c)
    {
        if(c == ' ')
            continue;
        c = toupper(c);
        if(c == 'U')
            c = 'V';
        cout << c;
    }
}
