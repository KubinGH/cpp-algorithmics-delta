#include <bits/stdc++.h>
#if not(defined(_WIN32))
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

using namespace std;

typedef unsigned char uint8_t;
typedef unsigned long long int uint64_t;

const size_t LETTERS = 26;
const size_t DIGITS = 160, BUF_DIGITS = 3;
const size_t MAX = 100;
const uint8_t BASE = 10;


void print(int8_t* A, uint8_t a)
{
    bool f = false;
    for(uint8_t i = a; i --> 0;)
        if(not f and A[i] != 0)
            f = true, putchar(A[i]+'0');
        else if(f)
            putchar(A[i]+'0');
    if(not f)
        putchar('0');
}

uint64_t to_uint64(int8_t* A, uint8_t a)
{
    uint64_t r = 0;
    for(uint8_t i = DIGITS; i --> 0;)
    {
        if(A[i] and i > 19)
            return -1;
        r *= BASE, r += A[i];
    }
    return r;
}

void to_arr(uint64_t n, int8_t* A, uint8_t a)
{
    for(uint8_t i = 0; i < a and n; i++)
        A[i] = n % BASE, n /= BASE;
}

void carry(int8_t* A, uint8_t a)
{
    for(uint8_t i = 0; i < a; i++)
        if(A[i] >= BASE)
            A[i+1] += A[i]/BASE, A[i] %= BASE;
}

void carry_back(int8_t* A, uint8_t a)
{
    bool f = true;
    while(f)
    {
        f = false;
        for(uint8_t i = 0; i < a; i++)
            if(A[i] < 0)
                f = true, A[i] += BASE, A[i+1]--;
    }
}

void rshift(int8_t* A, uint8_t a)
{
    for(uint8_t i = a; i --> 0;)
        A[i] = A[i-1];
}

bool iless(int8_t* A, uint8_t a, int8_t* B, uint8_t b)
{
    for(uint8_t i = max(a, b); i --> 0;)
        if(A[i] < B[i])
            return true;
        else if(A[i] > B[i])
            break;
    return false;
}

bool igreater(int8_t* A, uint8_t a, int8_t* B, uint8_t b)
{
    for(uint8_t i = max(a, b); i --> 0;)
        if(A[i] > B[i])
            return true;
        else if(A[i] < B[i])
            break;
    return false;
}

bool iequal(int8_t* A, uint8_t a, int8_t* B, uint8_t b)
{
    for(uint8_t i = max(a, b); i --> 0;)
        if((i < a ? A[i] : 0) != (i < b ? B[i] : 0))
            return false;
    return true;
}

void add(int8_t* A, uint8_t a, int8_t* B, uint8_t b, uint8_t md = 0)
{
    for(uint8_t i = 0; i < b; i++)
        A[i+md] += B[i];
    carry(A, a);
}

void increment(int8_t* A, uint8_t a, uint8_t i = 0)
{
    A[i]++;
    carry(A, a);
}

void subtract(int8_t* A, uint8_t a, int8_t* B, uint8_t b)
{
    for(uint8_t i = 0; i < b; i++)
        A[i] -= B[i];
    carry_back(A, a);
}

void multiply(int8_t* A, uint8_t a, int8_t* B, uint8_t b)
{
    static int8_t C[DIGITS], D[BUF_DIGITS];
    fill(C, C+DIGITS, 0); fill(D, D+BUF_DIGITS, 0);
    for(uint8_t i = 0; i < b; i++)
    {
        for(uint8_t j = 0; j < a; j++)
        {
            int8_t d = B[i] * A[j];
            D[0] = d % BASE; D[1] = (d / BASE) % BASE; D[2] = (d / (BASE*BASE)) % BASE;
            add(C, DIGITS, D, BUF_DIGITS, i+j);
        }
    }
    copy(C, C+a, A);
}

void divide(int8_t* A, uint8_t a, int8_t* B, uint8_t b)
{
    if(to_uint64(B, b) <= 1)
        return;
    if(iequal(A, a, B, b))
    {
        fill(A, A+a, 0);
        A[0] = 1;
        return;
    }
    static int8_t C[DIGITS], D[DIGITS], E[DIGITS];
    fill(C, C+DIGITS, 0); fill(D, D+DIGITS, 0); fill(E, E+DIGITS, 0);
    for(uint8_t i = a; i --> 0;)
    {
        if(iless(D, DIGITS, B, b))
        {
            rshift(D, DIGITS);
            D[0] = A[i];
        }
        while(igreater(D, DIGITS, B, b) or iequal(D, DIGITS, B, b))
        {
            if(D[DIGITS-1]) D[1u<<31]++;
            subtract(D, DIGITS, B, b);
            increment(C, DIGITS, i);
        }
    }
    copy(C, C+a, A);
}

void factorial(int8_t* A, uint8_t a, uint8_t n)
{
    static int8_t D[BUF_DIGITS];
    fill(A, A+a, 0); fill(D, D+BUF_DIGITS, 0);
    A[0] = 1;
    for(uint8_t i = 2; i < n+1; i++)
    {
        to_arr(i, D, BUF_DIGITS);
        multiply(A, DIGITS, D, BUF_DIGITS);
    }
}

int main()
{
    static uint8_t C[LETTERS];
    char c; uint8_t n = 0;
    while((c = getchar()) >= 'a')
        C[c - 'a']++, n++;
    static int8_t N[DIGITS];
    factorial(N, DIGITS, n);
    static int8_t D[DIGITS], E[DIGITS];
    D[0] = 1;
    for(uint8_t i = 0; i < LETTERS; i++)
    {
        fill(E, E+DIGITS, 0);
        factorial(E, DIGITS, C[i]);
        multiply(D, DIGITS, E, DIGITS);
    }
    divide(N, DIGITS, D, DIGITS);
    print(N, DIGITS);
}
