#include "ope.cpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
    UmyjRece();
    while(true)
    {
        char c;
        cin >> c;
        if(c == '+')
        {
            uint32_t v;
            cin >> v;
            cout << Dodaj(v) << endl;
        }
        else if(c == '-')
        {
            uint32_t u, v;
            cin >> u >> v;
            cout << Usun(u, v) << endl;
        }
    }
    return 0;
}
