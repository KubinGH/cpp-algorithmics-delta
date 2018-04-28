#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int uint64_t;
typedef unsigned int uint32_t;
typedef signed char int8_t;
typedef int8_t digit_t;

const size_t DIGITS_LONG = 210;
const digit_t BASE = 10;

template<size_t DIGITS>
struct integer
{
    static size_t digits;
    digit_t A[DIGITS];
    size_t size() const
    {
        return digits;
    }
    void clear()
    {
        fill(A, A + DIGITS, 0);
    }
    digit_t operator[] (size_t i) const
    {
        return A[i];
    }
    digit_t& operator[] (size_t i)
    {
        return A[i];
    }
    void set_to(const integer<DIGITS>& B)
    {
        copy(B.A, B.A + DIGITS, A);
    }
    void set_to(uint64_t n)
    {
        clear();
        if(n != 0) for(uint32_t i = 0; i < size() and n > 0; i++)
            A[i] = n % BASE, n /= BASE;
    }
    void operator= (const integer<DIGITS>& B)
    {
        return set_to(B);
    }
    void operator= (uint64_t n)
    {
        return set_to(n);
    }
    integer() { clear(); }
    integer(uint64_t n)
    {
        set_to(n);
    }
    void carry_one(size_t i)
    {
        if(A[i] >= BASE)
            A[i+1] += A[i] / BASE, A[i] %= BASE;
    }
    void add(const integer<DIGITS>& B)
    {
        for(size_t i = 0; i < size(); i++)
        {
            A[i] += B[i];
            carry_one(i);
        }
    }
    void operator+= (const integer<DIGITS>& B)
    {
        add(B);
    }
    void multiply(const integer<DIGITS>& B)
    {
        static integer<DIGITS> RESULT;
        RESULT.clear();
        for(size_t i = 0; i < size(); i++)
        {
            if(A[i] == 0) continue;
            for(size_t j = 0; j < B.size(); j++)
            {
                if(B[j] == 0) continue;
                RESULT[i+j] += A[i] * B[j];
                RESULT.carry_one(i+j);
            }
        }
        set_to(RESULT);
    }
    void operator*= (const integer<DIGITS>& B)
    {
        multiply(B);
    }
};
template<size_t DIGITS>
size_t integer<DIGITS>::digits = DIGITS;

template<size_t DIGITS>
istream& operator>> (istream& in, integer<DIGITS>& o)
{
    string buffer;
    in >> buffer;
    o.clear();
    for(size_t i = buffer.size(), j = 0; i --> 0; j++)
        o[j] = buffer[i] - '0';
    return in;
}
template<size_t DIGITS>
ostream& operator<< (ostream& out, integer<DIGITS>& o)
{
    bool f = false;
    for(size_t i = o.size(); i --> 0;)
    {
        if(o[i] != 0)
            f = true;
        if(f)
            out << (char)(o[i] + '0');
    }
    return out;
}

int main()
{
    string pattern;
    cin >> pattern;
    static integer<DIGITS_LONG> N, T, A;
    cin >> T;
    N = 562500;
    A = 4500; A *= T;
    N += A;
    A = T; A *= T; A *= 9;
    N += A;
    for(uint32_t i = 0; i < pattern.size(); i++)
    {
        if(pattern[i] == '?')
        {
            cout << (char)(N[pattern.size() - i - 1] + '0');
            break;
        }
    }
}
