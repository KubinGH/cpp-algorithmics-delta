#include <bits/stdc++.h>

using namespace std;

struct bits_generator
{
    mt19937 gen;
    uint32_t acc = 0, left = 0;
    bool operator() ()
    {
        if(not left)
            left = 32, acc = gen();
        bool o = acc & 1;
        acc >>= 1; left--;
        return o;
    }
};


#ifdef XHOVA
string __M;
uint32_t query(const vector<bool>& S)
{
    uint32_t r = 0;
    //cerr << "? ";
    for(uint32_t i = 0; i < S.size(); i++)
    {
        //cerr << S[i];
        if(__M[i] - '0' == S[i])
            r++;
    }
    //cerr << endl;
    //cout << "= " << r << endl;
    return r == S.size() ? 2 : (r == S.size()/2);
}
#else
uint32_t query(const vector<bool>& S)
{
    for(bool o : S)
        cout << o;
    cout << endl;
    uint32_t r;
    cin >> r;
    return r == S.size() ? 2 : (r == S.size()/2);
}
#endif

int main()
{
    uint32_t n;
#ifdef XHOVA
    //cin >> __M;
    cin >> n;
    __M.resize(n, '1');
#else
    cin >> n;
#endif
    bits_generator bit;
    bit.gen.seed(time(0));
    vector<bool> S(n);

    uint32_t c0 = 0, c1 = 0;
    for(uint32_t i = 0; i < n/2+250; i++)
    {
        for(uint32_t i = 1; i < n; i++)
            S[i] = bit();
        uint32_t r = query(S);
        if(r == 1)
            c0++;
    }
    S[0] = 1;
    for(uint32_t i = 0; i < n/2+250; i++)
    {
        for(uint32_t i = 1; i < n; i++)
            S[i] = bit();
        uint32_t r = query(S);
        if(r == 1)
            c1++;
    }
    cout << c0 << " " << c1 << endl;
}
