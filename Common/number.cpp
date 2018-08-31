#include <deque>
#include <cstdint>
#include <iostream>
#include <stack>
#include <tuple>

using namespace std;

template<size_t K = 30>
struct number_t
{
    const uint64_t M = (1 << K);
    deque<uint64_t> A;
    number_t() {}
    number_t(uint64_t x) { A.push_back(x); carry(); }
    number_t(const deque<uint64_t>& a) { A = a; }
    void dprint() const { for(uint64_t d : A) cout << d << " "; cout << endl; }
    void carry()
    {
        if(not A.empty()) for(size_t i = 0; i < A.size() - 1; i++)
            if(A[i] >= M)
                A[i+1] += A[i] / M, A[i] %= M;
        if(not A.empty() and A.back() >= M)
            A.push_back(A.back() / M), A[A.size() - 2] %= M;
        while(not A.empty() and A.back() == 0)
            A.pop_back();
    }
    operator bool() const { return not A.empty(); }
    number_t& operator= (uint64_t x) { A = {x}; carry(); return *this; }
    number_t& operator= (const number_t& B) { A = B.A; return *this; }
    uint64_t& operator[] (size_t i) { return A[i]; }
    const uint64_t& operator[] (size_t i) const { return A[i]; }
    size_t size() const { return A.size(); }
    void resize(size_t n) { A.resize(n); }
    bool operator<= (const number_t& B) const
    {
        if(A.size() != B.size()) return A.size() < B.size();
        for(size_t i = size(); i --> 0; )
            if(A[i] > B[i])
                return false;
        return true;
    }
    bool operator< (const number_t& B) const
    {
        if(A.size() != B.size()) return A.size() < B.size();
        for(size_t i = size(); i --> 0; )
            if(A[i] >= B[i])
                return false;
        return true;
    }
    bool operator== (const number_t& B) const { return not (*this < B) and not (B < *this); }
    bool operator!= (const number_t& B) const { return not (*this == B); }
    bool operator>  (const number_t& B) const { return not (*this <= B); }
    bool operator>= (const number_t& B) const { return not (*this < B); }
    number_t& operator<<= (size_t n)
    {
        for(size_t i = 0; i < n; i++)
            A.push_front(0);
        return *this;
    }
    number_t operator<< (size_t b) const { number_t R = *this; return R <<= b; }
    number_t& operator>>= (size_t n)
    {
        for(size_t i = 0; i < n; i++)
            A.pop_front();
        return *this;
    }
    number_t operator>> (size_t b) const { number_t R = *this; return R >>= b; }
    void increment(size_t i = 0) { A[i]++; carry(); }
    number_t& operator+= (const number_t& B)
    {
        if(A.size() < B.size()) A.resize(B.size());
        for(size_t i = 0; i < B.size(); i++)
            A[i] += B[i];
        carry();
        return *this;
    }
    number_t operator+ (const number_t& B) const { number_t R = *this; return R += B; }
    number_t& operator-= (const number_t& B)
    {
        //assert(*this >= B);
        for(size_t i = A.size(); i --> 1; )
            A[i] -= B[i], A[i-1] += M;
        A[0] -= B[0];
        carry();
        return *this;
    }
    void shifted_add(uint64_t x, size_t i)
    {
        A[i] += x;
        carry();
    }
    number_t operator- (const number_t& B) const { number_t R = *this; return R -= B; }
    number_t brute_multiply(const number_t& B) const
    {
        if(not *this or not B) return number_t();
        cout << "A: "; dprint();
        cout << "B: "; B.dprint();
        number_t R; R.resize(A.size() + B.size());
        for(size_t i = 0; i < A.size(); i++)
        {
            for(size_t j = 0; j < B.size(); j++)
                R[i+j] += A[i] * B[j];
            R.carry();
        }
        return R;
    }
    pair<number_t, number_t> halven() const
    {
        number_t L, R;
        for(size_t i = 0; i < A.size()/2; i++)
            L.A.push_back(A[i]);
        for(size_t i = (A.size()+1)/2; i < A.size(); i++)
            R.A.push_back(A[i]);
        return {L, R};
    }
    number_t karatsuba_multiply(const number_t& B) const
    {
        cout << "karatsuba call" << endl;
        number_t a1, a2; tie(a1, a2) =   halven();
        number_t b1, b2; tie(b1, b2) = B.halven();
        number_t X = a1 * b1;
        number_t Y = a2 * b2;
        number_t Z = (a1 + a2) * (b1 + b2) - X - Y;
        size_t m = size()/2;
        return (X << (2*m)) + Y + (Z << m);
    }
    uint32_t __multiply_stack_count = 0;
    number_t operator* (number_t& B)
    {
        if(min(A.size(), B.size()) * min(A.size(), B.size()) < max(A.size(), B.size()) or A.size() * B.size() < 64)
            return brute_multiply(B);
        else
        {
            while(A.size() < B.size()) A.push_back(0);
            while(B.size() < A.size()) B.A.push_back(0);
            if(size() % 2) A.push_back(0), B.A.push_back(0);
            __multiply_stack_count++;
            number_t R = karatsuba_multiply(B);
            __multiply_stack_count--;
            if(__multiply_stack_count == 0)
                carry(), B.carry();
            return R;
        }
    }
    number_t& operator*= (number_t& B) { number_t R = *this * B; return *this = R; }
    deque<uint64_t> __last_divisor, __last_dividend, __last_modulo;
    void __divmod (uint64_t b)
    {
        __last_divisor = {b};
        number_t result;
        uint64_t buffer = 0;
        result.resize(A.size());
        for(size_t i = size(); i --> 0; )
        {
            if(buffer < b)
                buffer *= M, buffer += A[i];
            result.shifted_add(buffer / b, i);
            buffer %= b;
            cout << i << " " << buffer << " \ ";
            result.dprint();
        }
        result.shifted_add(buffer / b, 0);
        buffer %= b;
        result.carry();
        __last_dividend = result.A;
        __last_modulo = {buffer};
    }

};

template<size_t K>
istream& operator>> (istream& in, number_t<K>& n)
{
    cout << "begin in" << endl;
    string s; in >> s;
    number_t<K> p = 1, ten = 10;
    for(size_t i = s.size(); i --> 0; )
    {
        cout << i << ": " << endl;
        number_t<K> d = uint64_t(s[i] - '0');
        d.dprint();
        number_t<K> m = p * d;
        n += m;
        p *= ten;
        cout << "n = "; n.dprint();
    }
    cout << "end in" << endl;
    return in;
}
template<size_t K>
ostream& operator<< (ostream& out, number_t<K> n)
{
    cout << "begin out" << endl;
    stack<char> o;
    while(n)
    {
        n.dprint();
        n.__divmod(10); n.A = n.__last_dividend;
        o.push(n.__last_modulo[0]);
    }
    while(not o.empty())
        out << char('0' + o.top()), o.pop();
    cout << endl << "end out" << endl;
    return out;
}

int main()
{
    number_t<30> A;
    cin >> A;
    cout << A;
}
