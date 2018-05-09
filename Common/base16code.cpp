#include <bits/stdc++.h>

using namespace std;

const char* alphabet = "0123456789ABCDEF";

size_t a_find(char c)
{
    uint32_t i;
    for(i = 0; alphabet[i] != '\0'; i++)
        if(c == alphabet[i])
            return i;
    return i;
}

string b16encode(string in)
{
    string out;
    for(char c : in)
    {
        out += alphabet[(c & 0xF0) >> 4];
        out += alphabet[c & 0x0F];
    }
    return out;
}

string b16decode(string in)
{
    string out;
    uint32_t p = 0;
    uint8_t b = 0;
    for(char c : in)
    {
        if(a_find(c) == 16)
            continue;
        b <<= 4;
        b |= a_find(c);
        p++;
        if(p == 2)
        {
            if(b == 0)
                break;
            out += b;
            p = 0;
            b = 0;
        }
    }
    return out;
}

int main()
{
    /*
    ifstream in("ktl.cpp");
    stringstream buffer;
    buffer << in.rdbuf();
    //string s = "int main() { cout << \"Hello World\"; }";
    string s = buffer.str();
    cout << b16encode(s) << endl;
    */
    ifstream in("file.txt");
    stringstream buffer;
    buffer << in.rdbuf();
    string s = buffer.str();
    cout << b16decode(s);
}
