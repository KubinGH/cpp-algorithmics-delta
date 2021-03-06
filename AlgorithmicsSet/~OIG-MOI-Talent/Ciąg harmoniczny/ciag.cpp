#include <deque>
#include <vector>
#include <cstdint>
#include <iostream>
#include <stack>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <bitset>
#define gcd __gcd


using namespace std;

const size_t MAX = 1 << 16;

template<size_t K = 30, typename T = uint64_t, typename Container = vector<T>>
struct number_t
{
    const T M = (1 << K);
    Container A;
    number_t() {}
    number_t(T x) { A.push_back(x); carry(); }
    number_t(const Container& a) { A = a; }
    void dprint() const { for(T d : A) cout << d << " "; cout << endl; }
    template<bool Normalize = true>
    void carry()
    {
        if(not A.empty()) for(size_t i = 0; i < A.size() - 1; i++)
            if(A[i] >= M)
                A[i+1] += A[i] / M, A[i] %= M;
        if(not A.empty() and A.back() >= M)
            A.push_back(A.back() / M), A[A.size() - 2] %= M;
        if(Normalize)
            while(not A.empty() and A.back() == 0)
                A.pop_back();
    }
    bool empty() const { return A.empty(); }
    operator bool() const { return not empty(); }
    number_t& operator= (T x) { A = {x}; carry(); return *this; }
    number_t& operator= (const number_t& B) { A = B.A; return *this; }
    T& operator[] (size_t i) { return A[i]; }
    const T& operator[] (size_t i) const { return A[i]; }
    size_t size() const { return A.size(); }
    void resize(size_t n) { A.resize(n); }
    bool operator<= (const number_t& B) const
    {
        if(A.size() != B.size()) return A.size() < B.size();
        for(size_t i = size(); i --> 0; )
            if(A[i] > B[i])
                return false;
            else if(A[i] < B[i])
                return true;
        return true;
    }
    bool operator!= (T x) const
    {
        if(size() != 1)
            return size() > 1;
        else
            return A[0] != x;
    }
    bool operator!= (int x) const { return *this != (T)x; }
    bool operator== (const number_t& B) const { return (*this <= B) and (B <= *this); }
    bool operator!= (const number_t& B) const { return not (*this == B); }
    bool operator< (const number_t& B) const { return *this <= B and *this != B; }
    bool operator>  (const number_t& B) const { return not (*this <= B); }
    bool operator>= (const number_t& B) const { return not (*this < B); }
    number_t& operator<<= (size_t n)
    {
        for(size_t i = 0; i < n; i++)
            A.push_front(0);
        return *this;
    }
    number_t operator<< (size_t b) const { number_t R = *this; return R <<= b; }
    void increment(size_t i = 0) { A[i]++; carry(); }
    number_t& operator+= (const number_t& B)
    {
        A.resize(max(A.size(), B.size())+2);
        for(size_t i = 0; i < B.size(); i++)
        {
            A[i] += B[i];
            if(A[i] >= M)
                A[i+1] += A[i] / M, A[i] %= M;
        }
        for(size_t i = B.size(); i < A.size() and A[i] >= M; i++)
            A[i+1] += A[i] / M, A[i] %= M;
        while(not A.empty() and A.back() == 0)
            A.pop_back();
        return *this;
    }
    number_t operator+ (const number_t& B) const { number_t R = *this; return R += B; }
    number_t& operator-= (const number_t& B)
    {
        //assert(*this >= B);
        if(not B) return *this;
        for(size_t i = size(); i --> 1; )
        {
            if(i<B.size())
                A[i] -= B[i];
            if(A[i]) A[i]--, A[i-1] += M;
        }
        A[0] -= B[0];
        carry();
        return *this;
    }
    number_t operator- (const number_t& B) const { number_t R = *this; return R -= B; }
    number_t brute_multiply(const number_t& B) const
    {
        if(not *this or not B) return number_t();
        number_t R; R.resize(A.size() + B.size() + 1);
        for(size_t i = 0; i < A.size(); i++)
        {
            for(size_t j = 0; j < B.size(); j++)
                R[i+j] += A[i] * B[j];
            R.carry<false>();
        }
        R.carry();
        return R;
    }
    pair<number_t, number_t> halven() const
    {
        number_t L, R;
        for(size_t i = 0; i < A.size()/2; i++)
            L.A.push_back(A[i]);
        for(size_t i = (A.size()+1)/2; i < A.size(); i++)
            R.A.push_back(A[i]);
        L.carry(); R.carry();
        return {L, R};
    }
    number_t karatsuba_multiply(number_t& B)
    {
        //cout << "karatsuba " << *this << " " << B << "\n";
        number_t a1, a2; tie(a1, a2) =   halven();
        number_t b1, b2; tie(b1, b2) = B.halven();
        number_t X = a2 * b2;
        number_t Y = a1 * b1;
        number_t P = a1 + a2, Q = b1 + b2;
        number_t Z = P * Q - X - Y;
        size_t m = size()/2;
        return Y + (Z << m) + (X << (2*m));
    }
    number_t operator* (number_t& B)
    {
        if(true or min(A.size(), B.size()) * min(A.size(), B.size())
                < max(A.size(), B.size()) or
          A.size() * B.size() < 64)
            return brute_multiply(B);
        else
        {
            while(A.size() < B.size()) A.push_back(0);
            while(B.size() < A.size()) B.A.push_back(0);
            if(size() % 2) A.push_back(0), B.A.push_back(0);
            number_t R = karatsuba_multiply(B);
            carry(); B.carry(); R.carry();
            return R;
        }
    }
    number_t operator* (T b) const
    {
        number_t R; R.resize(size() + 1);
        for(size_t i = 0; i < size(); i++)
            R[i] += A[i] * b;
        R.carry();
        return R;
    }
    number_t& operator*= (number_t& B) { number_t R = *this * B; return *this = R; }
    number_t& operator*= (T b) { number_t R = *this * b; return *this = R; }

    T __T_last_divisor, __T_last_modulo;

    Container __last_divisor, __last_dividend, __last_modulo;
    void __divmod (T b)
    {
        __T_last_divisor = b;
        number_t result;
        T buffer = 0;
        result.resize(A.size());
        for(size_t i = size(); i --> 0; )
        {
            if(buffer < b)
                buffer *= M, buffer += A[i];
            result[i] += buffer / b;
            buffer %= b;
        }
        result.carry();
        __last_dividend = result.A;
        __T_last_modulo = buffer;
    }
    number_t operator/ (T b) { __divmod(b); return number_t(__last_dividend); }
    number_t operator% (T b) { __divmod(b); return number_t(__T_last_modulo); }
    number_t& operator/= (T b) { number_t R = *this / b; return *this = R; }
    number_t& operator%= (T b) { number_t R = *this % b; return *this = R; }
    void __divmod (number_t& B)
    {
        if(K > 10)
        {
            __last_divisor = B.A;
            number_t lo, hi = *this + number_t(1); hi += 1;
            while(lo < hi)
            {
                number_t mid = (lo + hi) / T(2);
                number_t X = mid * B;
                if(X <= *this)
                    lo = mid, lo += 1;
                else
                    hi = mid;
            }
            lo -= 1;
            __last_dividend = lo.A;
            __last_modulo = (*this - lo * B).A;
        }
        else
        {
            __last_divisor = B.A;
            number_t result, buffer;
            result.resize(A.size());
            for(size_t i = size(); i --> 0; )
            {
                if(buffer < B)
                    buffer <<= 1, buffer += A[i];
                while(buffer >= B)
                    result[i]++, buffer -= B;
            }
            result.carry();
            __last_dividend = result.A;
            __last_modulo = buffer.A;
        }
    }
    number_t operator/ (number_t& B) { __divmod(B); return number_t(__last_dividend); }
    number_t operator% (number_t& B) { __divmod(B); return number_t(__last_modulo); }
    number_t& operator/= (number_t& B) { number_t R = *this / B; return *this = R; }
    number_t& operator%= (number_t& B) { number_t R = *this % B; return *this = R; }
};


template<size_t K, typename T>
istream& operator>> (istream& in, number_t<K, T>& n)
{
    string s; in >> s;
    number_t<K> p = 1;
    n.A.clear();
    for(size_t i = s.size(); i --> 0; )
    {
        number_t<K> d = T(s[i] - '0');
        number_t<K> m = p * d;
        n += m;
        p *= T(10);
    }
    return in;
}
template<size_t K, typename T>
ostream& operator<< (ostream& out, number_t<K, T> n)
{
    stack<char> o;
    while(n)
    {
        auto m = n % T(10);
        if(not m)
            o.push(0);
        else
            o.push(m[0]);
        n /= T(10);
    }
    if(o.empty()) out << '0';
    else while(not o.empty())
        out << char('0' + o.top()), o.pop();
    return out;
}

typedef number_t<30, uint64_t, vector<uint64_t>> unumber_t;

int main()
{
    uint32_t n;
    cin >> n;
    bitset<MAX> is_composite;
    vector<uint32_t> primes;
    for(uint32_t i = 2; i <= n; i++)
    {
        if(not is_composite[i])
        {
            primes.push_back(i);
            for(uint32_t x = i*i; x <= n; x += i)
                is_composite[x] = true;
        }
    }
    //cout << "sieve done" << endl;
    number_t<30, uint64_t> F = 1; F.A.reserve(1 << 20);
    for(uint32_t i = 2; i <= n; i++)
        F *= i;
    //cout << "factorial done" << endl;
    number_t<30, uint64_t> A; A.A.reserve(1 << 20);
    for(uint32_t i = 1; i <= n; i++)
        A += (F / (uint64_t)i);
    //cout << "sum done" << endl;
    for(uint64_t p : primes)
    {
        uint32_t k = 0; uint64_t p2 = p*p, p4 = p2*p2;
        while(true)
        {
            if(not (A % p4) and not (F % p4))
                k += 4;
            else if(not (A % p) and not (F % p))
                k += 2;
            else if(not (A % p) and not (F % p))
                k += 1;
            else
                break;
            A.A = A.__last_dividend, F.A = F.__last_dividend;
        }
        //cout << p << ": " << k << ", ";
    } //cout << endl;
    //cout << "gcd done" << endl;
    cout << A << "\n" << F;
}
