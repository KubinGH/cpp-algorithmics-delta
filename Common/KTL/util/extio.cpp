#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <map>

using std::ostream; using std::istream;
using std::cout; using std::cin;

template<typename T>
T sread(istream& in)
{
    T x;
    in >> x;
    return x;
}

template<typename T>
T read() { return sread<T>(cin); }

template<typename _1, typename _2>
ostream& operator<< (ostream& out, const std::pair<_1, _2>& p)
{
    return out << "[" << p.first << ", " << p.second << "]" << endl;
}

template<typename Container>
ostream& _print_container_imp (ostream& out, const Container& c)
{
    auto it = c.begin();
    out << "{" << *it;
    while(++it != c.end())
        out << ", " << *it;
    return out << "}";
}

#define CNTR_PRINT(...) \
    ostream& operator<< (ostream& out, const __VA_ARGS__ & v) { return _print_container_imp(out, v); }
#define CNTR_PRINT1(...) template<typename T> CNTR_PRINT(__VA_ARGS__)
#define CNTR_PRINT2(...) template<typename T1, typename T2> CNTR_PRINT(__VA_ARGS__)
CNTR_PRINT1(std::vector<T>)
CNTR_PRINT1(std::set<T>)
CNTR_PRINT2(std::map<T1, T2>)
#undef CNTR_PRINT
