#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 100;
const char DOT = '.';

int main()
{
    static char str[MAX + 1];
    cin >> str;
    uint32_t len = strlen(str);
    for(uint32_t i = 0; i < len; i++)
    {
        if(i % 4 == 0)
            cout << str[i];
        else
            cout << DOT;
    }
    cout << endl;
    for(uint32_t i = 0; i < len; i++)
    {
        if(i % 2 != 0)
            cout << str[i];
        else
            cout << DOT;
    }
    cout << endl;
    for(uint32_t i = 0; i < len; i++)
    {
        if((i - 2) % 4 == 0)
            cout << str[i];
        else
            cout << DOT;
    }
}
