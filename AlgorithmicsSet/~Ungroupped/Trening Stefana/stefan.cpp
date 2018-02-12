#include <bits/stdc++.h>
#define MAX 100000

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    static char in[MAX + 1];
    uint32_t length, result = 0;
    cin >> length >> in;
    for(uint32_t i = 0; i < length - 1; i++)
    {
        if((in[i] == '-' and in[i+1] == '+') or
           (in[i] == '+' and in[i+1] == '-'))
        {
            result++;
            i++;
        }
    }
    cout << result;
}
