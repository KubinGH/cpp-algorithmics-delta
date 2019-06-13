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
    return out << "[" << p.first << ", " << p.second << "]";
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

template<typename Container, typename _Iterator = typename Container::iterator>
ostream& operator<< (ostream& out, const Container& c) { return _print_container_imp(out, c); }
