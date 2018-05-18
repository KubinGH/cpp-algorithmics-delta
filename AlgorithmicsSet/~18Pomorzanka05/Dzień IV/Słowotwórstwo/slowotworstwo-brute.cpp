#include <bits/stdc++.h>

using namespace std;

uint32_t is_odd_palindrome(string& S, uint32_t a, uint32_t b)
{
    if((b-a+1)%2 == 0)
        return false;
    for(uint32_t i = a, j = b+1; i <= b and j --> a; i++)
    {
        if(S[i] != S[j])
            return false;
    }
    return true;
}

uint32_t CHECK(string S)
{
    string T;
    uint32_t r = 0;
    for(uint32_t d = 0; d < S.size()/2; d++)
        for(uint32_t ai = d; ai < S.size()-d; ai++)
            for(uint32_t aj = ai; aj <= S.size()-d; aj++)
    {
        T.clear();
        for(uint32_t i = 0; i < S.size(); i++)
            if((ai <= i and i < aj) or i < d or i >= S.size()-d)
                T += S[i];
        if(is_odd_palindrome(T, 0, T.size()-1))
        {
            if(T.size() > r)
            {
                //cout << T << " " << ai << ".." << aj << " " << d << endl;
                r = T.size();
            }
        }
    }
    cout << r;
    return r;
}

int main()
{
    uint32_t n;
    cin >> n;
    string S;
    cin >> S;
    CHECK(S);
}
