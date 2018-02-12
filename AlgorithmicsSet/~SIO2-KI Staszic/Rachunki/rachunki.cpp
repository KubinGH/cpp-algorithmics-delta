#include <bits/stdc++.h>
#if not(defined(_WIN32))
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

using namespace std;

typedef int32_t digit_t;

const digit_t POW10[] = {1, 10, 100, 1000, 10000, 100000, 1000000};

const digit_t BASE = 1000, BASE_LOG10 = 3;
const size_t DIGITS_LONG = 1024, DIGITS_BUFFER = 3;

template<size_t DIGITS>
struct number_t
{
    static const size_t digits = DIGITS;
    array<digit_t, digits> A;
    number_t() {}
    number_t(uint64_t n)
    {
        load_uint64(n);
    }
    void clear()
    {
        A.fill(0);
    }
    size_t size() const
    {
        return digits;
    }
    void print() const
    {
        if(BASE <= 10)
        {
            bool f = false;
            for(size_t i = msd() + 1; i --> 0;)
                if(not f and A[i] != 0)
                    f = true, putchar(A[i]+'0');
                else if(f)
                    putchar(A[i]+'0');
            if(not f)
                putchar('0');
        }
        else
        {
            for(size_t i = msd() + 1; i --> 0;)
                cout << static_cast<uint32_t>(A[i]);
        }
    }
    void set_to(const number_t<DIGITS>& B)
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
    size_t msd() const
    {
        for(size_t i = size(); i --> 0;)
            if(A[i] > 0)
                return i;
        return 0;
    }
    void rshift(size_t n = 1)
    {
        for(size_t i = size(); i --> n;)
            A[i] = A[i-n];
    }
    bool operator< (const number_t<DIGITS>& B) const
    {
        for(size_t i = size(); i --> 0;)
            if(A[i] != B[i])
                return A[i] < B[i];
        return false;
    }
    bool operator> (const number_t<DIGITS>& B) const
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
    bool operator>= (const number_t<DIGITS>& B) const
    {
        return operator>(B) or operator==(B);
    }
    bool operator<= (const number_t<DIGITS>& B) const
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
    void add(const number_t<DIGITS_B>& B, size_t exp = 0)
    {
        for(size_t i = 0; i < B.size(); i++)
            A[i+exp] += B[i];
        carry();
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
        static number_t<DIGITS> RESULT;
        static number_t<DIGITS_BUFFER> BUFFER;
        RESULT.clear(); BUFFER.clear();
        size_t bs = B.msd() + 1, s = msd() + 1;
        for(size_t i = 0; i < bs; i++)
        {
            if(B[i] == 0) continue;
            for(size_t j = 0; j < s; j++)
            {
                if(i + j >= DIGITS) break;
                digit_t r = B[i] * A[j];
                if(r == 0) continue;
                BUFFER[0] = r % BASE;
                BUFFER[1] = (r / BASE) % BASE;
                BUFFER[2] = (r / (BASE*BASE)) % BASE;
                RESULT.add(BUFFER, i + j);
            }
        }
        set_to(RESULT);
    }
    void divide(const number_t<DIGITS>& B)
    {
        static number_t<DIGITS> RESULT, BUFFER;
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
    void load_from_stdin()
    {
        clear();
        string buffer;
        cin >> buffer;
        if(BASE <= 10)
        {
            for(size_t i = buffer.size(); i --> 0;)
            {
                A[buffer.size() - i - 1] = buffer[i] - '0';
            }
        }
        else
        {
            size_t d = 0, a = 0;
            for(size_t i = buffer.size(); i --> 0;)
            {
                A[a] += POW10[d] * (buffer[i] - '0');
                d++;
                if(d == BASE_LOG10)
                    d = 0, a++;
            }
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    char op;
    static number_t<DIGITS_LONG> A, B, C, D;
    while(true)
    {
        A.load_from_stdin();
        cin >> op;
        B.load_from_stdin();
        if(A.to_uint64() == 0 and B.to_uint64() == 0 and op == '+')
            break;
        if(op == '+')
        {
            A.add(B);
            A.print();
        }
        else if(op == '-')
        {
            if(A < B)
            {
                B.subtract(A);
                if(BASE <= 10)
                    putchar('-');
                else
                    cout << '-';
                B.print();
            }
            else
            {
                A.subtract(B);
                A.print();
            }
        }
        else if(op == '*')
        {
            A.multiply(B);
            A.print();
        }
        else if(op == '/')
        {
            A.divide(B);
            A.print();
        }
        else if(op == '%')
        {
            D.set_to(A);
            A.divide(B);
            C.set_to(A);
            C.multiply(B);
            D.subtract(C);
            D.print();
        }
        if(BASE <= 10)
            putchar('\n');
        else
            cout << '\n';
    }
}
