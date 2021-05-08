#pragma once

#include <cstdint>
#include <cstdio>
#include <type_traits>
#include <iostream>

#ifdef _WIN32
#define getchar_unlocked getchar
#define putchar_unlocked putchar
#define fputs_unlocked fputs
#endif

using std::is_integral; using std::is_unsigned; using std::is_signed;
using std::make_unsigned;
using std::enable_if;

struct unlocked_cin
{
    char _whitespace_skip()
    {
        char lchar;
        while(isspace(lchar = getchar_unlocked())) {}
        return lchar;
    }
    unlocked_cin& operator>> (char& x)
    {
        x = _whitespace_skip();
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        x = 0;
        char lchar = _whitespace_skip();
        do {
            x *= 10, x += lchar - '0';
        } while(isdigit(lchar = getchar_unlocked()));
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        bool s = false;
        x = 0;
        char lchar = _whitespace_skip();
        if(lchar == '-')
            s = true;
        else
            x += lchar - '0';
        while(isdigit(lchar = getchar_unlocked()))
            x *= 10, x += lchar - '0';
        if(s) x = -x;
        return *this;
    }
    template<typename... Args>
    void tie(Args...) {}
} ucin;

struct unlocked_cout
{
    unlocked_cout& operator<< (const char* c)
    {
        fputs_unlocked(c, stdout);
        return *this;
    }
    unlocked_cout& operator<< (char x)
    {
        putchar_unlocked(x);
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cout&>::type
    operator<< (T x)
    {
        static char buffer[64];
        size_t i = 0;
        if(not x)
            buffer[i++] = '0';
        while(x)
            buffer[i++] = (x % 10) + '0', x /= 10;
        for(; i --> 0; )
            putchar_unlocked(buffer[i]);
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cout&>::type
    operator<< (T x)
    {
        if(x < 0)
            putchar_unlocked('-'), x = -x;
        return *this << static_cast<typename make_unsigned<T>::type>(x);
    }
    template<typename... Args>
    void tie(Args...) {}
} ucout;
