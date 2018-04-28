#include <bits/stdc++.h>
#if not(defined(_WIN32))
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

using namespace std;

typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef unsigned long long int uint64_t;
typedef int8_t digit_t;

const digit_t BASE = 10;
const size_t DIGITS_LONG = 250, DIGITS_BUFFER = 3;

template<typename T, size_t SIZE>
struct arrayk
{
    T _arr[SIZE];
    const T& operator[] (size_t i) const
    {
        return _arr[i];
    }
    T& operator[] (size_t i)
    {
        return _arr[i];
    }
};

template<size_t DIGITS>
struct number_t
{
    static const size_t digits = DIGITS;
    arrayk<digit_t, digits> A;
    number_t() {}
    number_t(uint64_t n)
    {
        load_uint64(n);
    }
    void clear()
    {
        fill(A._arr, A._arr + DIGITS, 0);
    }
    size_t size() const
    {
        return digits;
    }
    void print() const
    {
        bool f = false;
        for(size_t i = size(); i --> 0;)
            if(not f and A[i] != 0)
                f = true, putchar(A[i]+'0');
            else if(f)
                putchar(A[i]+'0');
        if(not f)
            putchar('0');
    }
    void set_to(const number_t<DIGITS> B)
    {
        for(size_t i = 0; i < B.size(); i++)
            A[i] = B[i];
    }
    const digit_t& operator[] (size_t i) const
    {
        return A[i];
    }
    digit_t& operator[] (size_t i)
    {
        return A[i];
    }
    uint64_t to_uint64() const
    {
        uint64_t r = 0;
        for(size_t i = size(); i --> 0;)
        {
            if(A[i] and i > 19)
                return -1;
            r *= BASE, r += A[i];
        }
        return r;
    }
    void load_uint64(uint64_t n)
    {
        clear();
        for(size_t i = 0; i < size() and n; i++)
            A[i] = n % BASE, n /= BASE;
    }
    void carry()
    {
        for(size_t i = 0; i < size(); i++)
            if(A[i] >= BASE)
                A[i+1] += A[i]/BASE, A[i] %= BASE;
    }
    void carry_back()
    {
        bool f = true;
        while(f)
        {
            f = false;
            for(size_t i = 0; i < size(); i++)
                if(A[i] < 0)
                    f = true, A[i] += BASE, A[i+1]--;
        }
    }
    void rshift(size_t n = 1)
    {
        for(size_t i = size(); i --> n;)
            A[i] = A[i-n];
    }
    bool operator< (const number_t<DIGITS> B) const
    {
        for(size_t i = size(); i --> 0;)
            if(A[i] != B[i])
                return A[i] < B[i];
        return false;
    }
    bool operator> (const number_t<DIGITS> B) const
    {
        for(size_t i = size(); i --> 0;)
            if(A[i] != B[i])
                return A[i] > B[i];
        return false;
    }
    bool operator== (const number_t<DIGITS> B) const
    {
        for(size_t i = size(); i --> 0;)
            if(A[i] != B[i])
                return false;
        return true;
    }
    bool operator>= (const number_t<DIGITS> B) const
    {
        return operator>(B) or operator==(B);
    }
    bool operator<= (const number_t<DIGITS> B) const
    {
        return operator<(B) or operator==(B);
    }
    void increment(size_t exp = 0)
    {
        A[exp]++;
        carry();
    }
    void decrement(size_t exp = 0)
    {
        A[exp]--;
        carry_back();
    }
    template<size_t DIGITS_B>
    void add(const number_t<DIGITS_B> B, size_t exp = 0)
    {
        for(size_t i = 0; i < B.size(); i++)
            A[i+exp] += B[i];
        carry();
    }
    template<size_t DIGITS_B>
    void subtract(const number_t<DIGITS_B> B, size_t exp = 0)
    {
        for(size_t i = 0; i < B.size(); i++)
            A[i+exp] -= B[i];
        carry_back();
    }
    template<size_t DIGITS_B>
    void multiply(const number_t<DIGITS_B> B)
    {
        static number_t<DIGITS_LONG> RESULT;
        static number_t<DIGITS_BUFFER> BUFFER;
        RESULT.clear(); BUFFER.clear();
        for(size_t i = 0; i < B.size(); i++)
        {
            for(size_t j = 0; j < size(); j++)
            {
                digit_t r = B[i] * A[j];
                BUFFER[0] = r % BASE;
                BUFFER[1] = (r / BASE) % BASE;
                BUFFER[2] = (r / (BASE*BASE)) % BASE;
                RESULT.add(BUFFER, i + j);
            }
        }
        set_to(RESULT);
    }
    void divide(const number_t<DIGITS> B)
    {
        static number_t<DIGITS_LONG> RESULT, BUFFER;
        if(B.to_uint64() <= 1)
            return;
        if(operator==(B))
        {
            load_uint64(1);
            return;
        }
        RESULT.clear(); BUFFER.clear();
        for(size_t i = size(); i --> 0;)
        {
            if(BUFFER < B)
            {
                BUFFER.rshift();
                BUFFER[0] = A[i];
            }
            while(BUFFER >= B)
            {
                BUFFER.subtract(B);
                RESULT.increment(i);
            }
        }
        while(BUFFER >= B)
        {
            BUFFER.subtract(B);
            RESULT.increment(0);
        }
        set_to(RESULT);
    }
};

const number_t<DIGITS_LONG> ELEVEN(11);

int main()
{
    string buffer;
    cin >> buffer;
    static number_t<DIGITS_LONG> A;
    for(digit_t x = 0; x < 10; x++)
    {
        A.clear();
        int32_t a = 0, b = 0;
        for(size_t i = buffer.size(); i --> 0;)
        {
            if(buffer[buffer.size() - i - 1] == 'X')
                A[i] = x;
            else
                A[i] = buffer[buffer.size() - i - 1] - '0';
            if(i % 2)
                a += A[i];
            else
                b += A[i];
        }
        if(abs(a - b) % 11 == 0)
        {
            A.divide(ELEVEN);
            break;
        }
    }
    A.print();
}
