#include <bits/stdc++.h>
#define LEN 32
#define LOG4(x) (log2(x) / 2)
#define PRINT_ARR(x) for(uint16_t _i = 0; _i < LEN; _i++) cout << x[_i];

using namespace std;

typedef unsigned long long int uint64_t;
typedef unsigned short uint16_t;
typedef short int16_t;

void inc(int16_t* arr, uint16_t i = 0)
{
    if(arr[i] >= 2)
    {
        arr[i] = 0;
        if(i + 1 < LEN)
            inc(arr, i + 1);
    }
    else
        arr[i]++;
}

void dec(int16_t* arr, uint16_t i = 0)
{
    if(arr[i] <= 0)
    {
        arr[i] = 2;
        if(i + 1 < LEN)
            dec(arr, i + 1);
    }
    else
        arr[i]--;
}

uint64_t val(int16_t* arr)
{
    uint64_t result = 0;
    for(uint64_t i = LEN - 1; i-- > 0;)
    {
        if(arr[i] == 2)
            result += pow(4, i);
        else if(arr[i] == 0)
            result -= pow(4, i);
    }
    return result;
}

int main()
{
    uint64_t A, B;
    cin >> A >> B;

    uint16_t A_log = 0, B_log = 32;
    while(pow(4, A_log + 1) <= A) A_log++;
    if(B == 0) B_log = 0;
    else while(pow(4, B_log - 1) >= B) B_log--;

    static int16_t AQ[LEN], BQ[LEN];
    fill(AQ, AQ + LEN, 1); fill(BQ, BQ + LEN, 1);
    AQ[A_log] = 2; BQ[B_log] = 2;
    uint64_t AQV = val(AQ), BQV = val(BQ);
    while(AQV < A)
    {
        inc(AQ);
        AQV = val(AQ);
    }
    while(BQV > B)
    {
        dec(BQ);
        BQV = val(BQ);
    }
    if(BQV < AQV)
    {
        cout << 0;
        return EXIT_SUCCESS;
    }
    else if(AQV == BQV)
    {
        cout << 1;
        return EXIT_SUCCESS;
    }
    uint64_t AR = 0, BR = 0;
    for(uint64_t i = 0; i < LEN; i++)
        AR += pow(3, i) * AQ[i];
    for(uint64_t i = 0; i < LEN; i++)
        BR += pow(3, i) * BQ[i];
    cout << BR - AR + 1;
}
