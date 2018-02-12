#include <bits/stdc++.h>
#define MAX 200000
#define TESTING
#define TEST_FILENAME "tests/testc3"
#ifdef TESTING
#include "testhelper.h"
#endif

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    INIT_TESTER
    static bool attacked[MAX];
    string buffer;
    cin >> buffer;
    uint32_t nests = buffer.size();
    for(uint32_t i = 0; i < nests; i++)
        attacked[i] = (buffer[i] == 'a');
    static uint32_t psums[MAX]; fill(psums, psums + MAX, 0);
    for(uint32_t i = 0; i < nests; i++)
    {
        if(i != 0)
            psums[i] = psums[i - 1];
        if(attacked[i])
            psums[i]++;
    }
    uint32_t questions;
    cin >> questions;
    for(uint32_t q = 0; q < questions; q++)
    {
        uint32_t i, j;
        cin >> i >> j; i--; j--;
        uint32_t v;
        if(i == j) v = attacked[i];
        else       v = psums[j] - (i > 0 ? psums[i - 1] : 0);
        printf("%u\n", v);
    }
    FINISH_TEST
}
