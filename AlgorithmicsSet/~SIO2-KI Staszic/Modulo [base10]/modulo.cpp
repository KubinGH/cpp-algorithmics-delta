#include <bits/stdc++.h>
#if not(defined(_WIN32))
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

using namespace std;

typedef int8_t digit_t;

const digit_t BASE = 10;
const size_t DIGITS_LONG = 210, DIGITS_BUFFER = 3;
const size_t BITS = 1024;

template<size_t DIGITS>
struct number_t
{
    static size_t digits;
    digit_t A[DIGITS];
    number_t() {}
    number_t(uint64_t n)
    {
        load_uint64(n);
    }
    void clear()
    {
        fill(A, A + size(), 0);
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
    void read()
    {
        clear();
        static char BUFFER[DIGITS_LONG];
        char c = getchar();
        uint32_t b = 0;
        while('0' <= c and c <= '9')
            BUFFER[b++] = c, c = getchar();
        for(uint32_t i = 0; i < b; i++)
            A[i] = BUFFER[b-i-1] - '0';
    }
    void set_to(const number_t<DIGITS>& B)
    {
        copy(B.A, B.A + B.size(), A);
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
        for(size_t i = 0; i < size() - 1; i++)
            if(A[i] >= BASE)
                A[i+1] += A[i]/BASE, A[i] %= BASE;
    }
    void carry_back()
    {
        bool f = true;
        while(f)
        {
            f = false;
            for(size_t i = 0; i < size() - 1; i++)
                if(A[i] < 0)
                    f = true, A[i] += BASE, A[i+1]--;
        }
    }
    void rshift(size_t n = 1)
    {
        for(size_t i = size(); i --> n;)
            A[i] = A[i-n];
    }
    template<size_t DIGITS_B>
    bool operator< (const number_t<DIGITS_B>& B) const
    {
        for(size_t i = size(); i --> 0;)
            if(A[i] != B[i])
                return A[i] < B[i];
        return false;
    }
    template<size_t DIGITS_B>
    bool operator> (const number_t<DIGITS_B>& B) const
    {
        for(size_t i = size(); i --> 0;)
            if(A[i] != B[i])
                return A[i] > B[i];
        return false;
    }
    bool operator== (const number_t<DIGITS>& B) const
    {
        for(size_t i = size(); i --> 0;)
            if(A[i] != B[i])
                return false;
        return true;
    }
    template<size_t DIGITS_B>
    bool operator>= (const number_t<DIGITS_B>& B) const
    {
        return not operator<(B);
    }
    template<size_t DIGITS_B>
    bool operator<= (const number_t<DIGITS_B>& B) const
    {
        return not operator>(B);
    }
    void increment(size_t exp = 0)
    {
        A[exp]++;
        for(size_t i = exp; i < size() - 1 and A[i] >= BASE; i++)
        {
            A[i+1] += A[i] / BASE, A[i] %= BASE;
        }
    }
    void decrement(size_t exp = 0)
    {
        A[exp]--;
        carry_back();
    }
    template<size_t DIGITS_B>
    void add(const number_t<DIGITS_B>& B, size_t exp = 0, digit_t mul = 1)
    {
        for(size_t i = 0; i < B.size(); i++)
        {
            A[i+exp] += B[i]*mul;
            if(A[i+exp] >= BASE and i+exp+1 < size())
                A[i+exp+1] += A[i+exp] / BASE, A[i+exp] %= BASE;
        }
        for(uint32_t i = B.size() + exp + 1; i < size() - 1 and A[i] >= BASE; i++)
        {
            A[i+1] += A[i] / BASE, A[i] %= BASE;
        }
    }
    template<size_t DIGITS_B>
    void subtract(const number_t<DIGITS_B>& B, size_t exp = 0)
    {
        for(size_t i = 0; i < B.size(); i++)
            A[i+exp] -= B[i];
        carry_back();
    }
    template<size_t DIGITS_B>
    void multiply(const number_t<DIGITS_B>& B)
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
    bool divide(const number_t<DIGITS>& B, bool print_modulo = false)
    {
        static number_t<DIGITS_LONG> RESULT, BUFFER;
        if(B.to_uint64() <= 1)
        {
            if(print_modulo)
                putchar('0');
            return true;
        }
        RESULT.clear(); BUFFER.clear();
        bool nonzero = false;
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
                nonzero = true;
            }
        }
        while(BUFFER >= B)
        {
            BUFFER.subtract(B);
            RESULT.increment(0);
            nonzero = true;
        }
        set_to(RESULT);
        if(print_modulo)
            BUFFER.print();
        return nonzero;
    }
    bool divide_uint64(uint64_t b)
    {
        static number_t<DIGITS_LONG> RESULT;
        if(b <= 1)
            return true;
        RESULT.clear();
        uint64_t buffer = 0;
        bool nonzero = false;
        for(size_t i = size(); i --> 0;)
        {
            if(buffer < b)
            {
                buffer *= 10;
                buffer += A[i];
            }
            while(buffer >= b)
            {
                buffer -= b;
                RESULT.increment(i);
                nonzero = true;
            }
        }
        while(buffer >= b)
        {
            buffer -= b;
            RESULT.increment(0);
            nonzero = true;
        }
        set_to(RESULT);
        return nonzero;
    }
};
template<size_t DIGITS>
size_t number_t<DIGITS>::digits = DIGITS;

int main()
{
    static number_t<DIGITS_LONG> first, second;
    first.read(); second.read();
    first.divide(second, true);
}
