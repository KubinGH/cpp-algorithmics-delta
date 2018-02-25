#include <bits/stdc++.h>
#define MAX 1000000
#define A_START '('
#define A_END   ')'
#define B_START '['
#define B_END   ']'
#define C_START '{'
#define C_END   '}'

using namespace std;

int main()
{
    uint32_t n;
    cin >> n;
    static char str[MAX+1];
    cin >> str;
    stack<char> cstack;
    for(uint32_t i = 0; i < n; i++)
    {
        switch(str[i])
        {
            case A_END:
                if(not cstack.empty() and cstack.top() == A_START) cstack.pop();
                else goto fail;
                break;
            case B_END:
                if(not cstack.empty() and cstack.top() == B_START) cstack.pop();
                else goto fail;
                break;
            case C_END:
                if(not cstack.empty() and cstack.top() == C_START) cstack.pop();
                else goto fail;
                break;
            case A_START: case B_START: case C_START:
                cstack.push(str[i]);
                break;
        }
    }
    if(not cstack.empty())
    {
    fail:
        cout << "NIE";
        return 0;
    }
    int32_t a = 0, b = 0, c = 0;
    int32_t maximum = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        switch(str[i])
        {
            case A_START: a++; break;
            case A_END: a--; break;
            case B_START: b++; break;
            case B_END: b--; break;
            case C_START: c++; break;
            case C_END: c--; break;
        }
        switch(str[i])
        {
            case A_START: case B_START: case C_START:
                if(a + b + c > maximum)
                    maximum = a + b + c;
        }
    }
    cout << maximum;
}
