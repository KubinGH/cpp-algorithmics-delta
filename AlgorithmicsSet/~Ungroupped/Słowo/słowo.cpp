#include <bits/stdc++.h>
#define MAX 100000

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t length, questions;
    cin >> length >> questions;
    string word;
    cin >> word;
    static bool used_char[256];
    static uint32_t run[MAX];
    for(uint32_t i = 0; i < length; i++)
    {
        if(i > 0) run[i] = run[i - 1];
        if(not used_char[(unsigned int) word[i]])
        {
            used_char[(unsigned int) word[i]] = true;
            run[i]++;
        }
    }
    for(uint32_t q = 0; q < questions; q++)
    {
        uint32_t begin, end;
        cin >> begin >> end; begin--; end--;
        cout << run[end] - run[begin] + 1 << endl;
    }
}
