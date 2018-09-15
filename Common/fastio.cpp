#include <cstdint>
#include <cstdio>
#include <type_traits>
#include <iostream>
#ifdef _WIN32
#define getchar_unlocked getchar
#define putchar_unlocked putchar
#endif

using namespace std;

struct unlocked_cin
{
    unlocked_cin& operator>> (char& x)
    {
        x = getchar_unlocked();
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        char lchar;
        while(isdigit(lchar = getchar_unlocked()))
            x *= 10, x += lchar - '0';
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        bool s = false;
        char lchar = getchar_unlocked();
        if(lchar == '-')
            s = true;
        else
            x += lchar - '0';
        while(isdigit(lchar = getchar_unlocked()))
            x *= 10, x += lchar - '0';
        if(s) x = -x;
        return *this;
    }
} ucin;

using namespace std;

int main()
{
    uint32_t a = 0; uint64_t b = 0; int64_t c = 0; char d;
    ucin >> a >> b >> c >> d;
    cout << a << " " << b << " " << c << " " << d;
}
