#include <cstdint>
#include <type_traits>
#include <string>
#include "message.h"

using std::enable_if; using std::uint32_t;
using std::string;

struct socket
{
    uint32_t conn;
    socket(uint32_t _conn) : conn(_conn) {}
    void rebind(uint32_t _conn) { conn = _conn; }
    socket& operator+ ()
    {
        uint32_t that = Receive(conn);
        if(conn == -1u) conn = that;
        return *this;
    }
    socket& operator- () { Send(conn); return *this; }
    #define BYTES(_b) template<typename T> typename enable_if<(_b) == sizeof(T), socket&>::type
    BYTES(1) operator<< (T val) { PutChar(conn, val); return *this; }
    BYTES(1) operator>> (T& var) { var = GetChar(conn); return *this; }
    BYTES(4) operator<< (T val) { PutInt(conn, val); return *this; }
    BYTES(4) operator>> (T& var) { var = GetInt(conn); return *this; }
    BYTES(8) operator<< (T val) { PutLL(conn, val); return *this; }
    BYTES(8) operator>> (T& var) { var = GetLL(conn); return *this; }
    #undef BYTES
    socket& operator<< (const string& str)
    {
        for(char c : str) (*this) << c;
        (*this) << '\0';
        return (*this);
    }
    socket& operator>> (string& out)
    {
        out.clear();
        char c; (*this) >> c;
        while(c != '\0') out += c, (*this) >> c;
        return (*this);
    }
};