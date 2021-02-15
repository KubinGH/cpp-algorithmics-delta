#pragma once

#include <type_traits>
#include <iostream>
#include <utility>
#include <string>

using std::ostream; using std::istream;
using std::cout; using std::cin;
using std::string;
using std::is_same;
using std::enable_if;
using std::get;

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

#if __cplusplus >= 201402L 
template<typename... Args, size_t... I>
void tupprint(ostream& out, const std::tuple<Args...>& t, std::index_sequence<I...>)
{
    (..., (out << (I ? ", " : "") << get<I>(t)));
}

template<typename... Args>
ostream& operator<< (ostream& out, const std::tuple<Args...>& t)
{
    out << '[';
    tupprint(out, t, std::make_index_sequence<sizeof...(Args)>());
    return out << ']';
}
#endif

template<typename Container>
ostream& _print_container_imp (ostream& out, const Container& c)
{
    if(c.begin() == c.end())
        return out << "{}";
    auto it = c.begin();
    out << "{" << *it;
    while(++it != c.end())
        out << ", " << *it;
    return out << "}";
}

template<
    typename Container, typename = typename Container::iterator,
    typename = typename enable_if<!is_same<Container, string>::value>::type
>
ostream& operator<< (ostream& out, const Container& c) { return _print_container_imp(out, c); }
