#include <bits/stdc++.h>

using namespace std;

template<typename T, T Base, typename Container>
struct number_t
{
    static_assert(Base > 1, "Invalid Base");
    Container A;

    number_t() {}
    template<typename Tp>
    static number_t from_integer(Tp x) { number_t n; n.A = {T(x)}; n.carry(); return n; }

    bool empty()                      const { return A.empty(); }
    number_t& operator= (const number_t& B) { A = B.A; return *this; }
    T& operator[] (size_t i)                { return A[i]; }
    const T& operator[] (size_t i)    const { return i < A.size() ? A[i] : 0; }
    size_t size() const                     { return A.size(); }
    void clear()                            { A.clear(); }

    void swap(number_t& o)
    {
        A.swap(o.A);
    }

    void carry()
    {
        if(A.empty()) return;
        for(size_t i = 0; i + 1 < A.size(); i++)
            if(A[i] >= Base)
                A[i+1] += A[i] / Base, A[i] %= Base;
        while(A.back() >= Base)
        {
            T x = A.back() / Base;
            A.back() %= Base;
            A.push_back(x);
        }
    }
    void fix_tail()
    {
        while(not A.empty() and not A.back())
            A.pop_back();
    }

    number_t& operator+= (const number_t& o)
    {
        if(o.A.size() > A.size())
            A.resize(o.A.size());
        for(size_t i = 0; i < o.size(); i++)
            A[i] += o.A[i];
        carry();
        return *this;
    }
    number_t operator+ (const number_t& o) const { number_t x = *this; x += o; return x; }

    number_t& operator-= (const number_t& o)
    {
        A.push_back(0);
        for(size_t i = o.size(); i --> 0; )
            A[i+1]--, A[i] += Base - o.A[i];
        carry(); fix_tail();
        return *this;
    }
    number_t operator- (const number_t& o) const { number_t x = *this; x -= o; return x; }

};

static constexpr array<uint64_t, 11> pow10 = {
    1, 10, 100, 1000, 10000, 100000, 1000000,
    10000000, 100000000, 1000000000, 10000000000
};

template<typename T, T Base, typename Container>
ostream& operator<< (ostream& out, const number_t<T, Base, Container>& n)
{
    if(n.empty())
        return out << '0';
    size_t k10 = find(pow10.begin(), pow10.end(), Base) - pow10.begin();
    if(k10 < pow10.size())
    {
        out << n.A.back();
        out << setfill('0');
        for(size_t i = n.A.size()-1; i --> 0; )
            out << setw(k10) << n.A[i];
    }
    else
        assert(false);
    return out;
}
template<typename T, T Base, typename Container>
istream& operator>> (istream& in, number_t<T, Base, Container>& n)
{
    static string buffer; buffer.clear();
    in >> buffer;
    if(buffer == "0")
    {
        n.A = {0};
        return in;
    }
    n.clear();
    size_t k10 = find(pow10.begin(), pow10.end(), Base) - pow10.begin();
    if(k10 < pow10.size())
    {
        reverse(buffer.begin(), buffer.end());
        buffer.insert(buffer.end(), (k10 - buffer.size()%k10) % k10, '0');
        n.A.resize(buffer.size() / k10);
        for(size_t i = buffer.size(); i --> 0; )
            n.A[i / k10] *= 10, n.A[i / k10] += buffer[i] - '0';
    }
    else
        assert(false);
    return in;
}

