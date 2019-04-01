#include <bits/stdc++.h>

using namespace std;

const char alphabet[] = "ACTG";
uint32_t char_as_index(char x) { return find(begin(alphabet), end(alphabet), x) - begin(alphabet); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string IA, IB;
    cin >> IA >> IB;
    vector<uint32_t> A(IA.size()), B(IB.size());
    for(uint32_t i = 0; i < A.size(); i++)
        A[i] = char_as_index(IA[i]);
    for(uint32_t i = 0; i < B.size(); i++)
        B[i] = char_as_index(IB[i]);
    uint32_t b = 0;
    for(uint32_t m = 1; m < (1u << A.size()); m++)
    {
        uint32_t a = 0;
        while(a < A.size() and (m & (1u << a)) == 0) a++;
        for(uint32_t c : B)
        {
            if(a < A.size() and A[a] == c)
            {
                a++;
                while(a < A.size() and (m & (1u << a)) == 0) a++;
            }
        }
        if(a >= A.size() and __builtin_popcount(m) > __builtin_popcount(b))
            b = m;
    }
    for(uint32_t i = 0; i < A.size(); i++)
        if(b & (1u << i))
            cout << alphabet[A[i]];
}
