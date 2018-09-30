#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <fstream>

using namespace std;

template<typename T, T BASE, T MOD>
struct rolling_hash
{
    size_t n;
    vector<T> H, B;
    template<typename Iterator>
    rolling_hash(Iterator first, Iterator last, T fix = 0)
    {
        n = distance(first, last);
        H.resize(n+1); B.resize(n+1);
        H[0] = (T(*first) + fix) % MOD; first++;
        B[0] = 1;
        for(size_t i = 1; first != last; ++first, i++)
        {
            H[i] = (H[i-1] * BASE + T(*first) + fix) % MOD;
            B[i] = (B[i-1] * BASE) % MOD;
        }
    }
    T operator() (size_t i, size_t j)
    {
        if(i == 0) return H[j];
        else return (2*MOD + H[j] - (H[i-1] * B[j-i+1])%MOD) % MOD;
    }
};

int main()
{
    string S;
    cin >> S;
    uint32_t n = S.size();
    rolling_hash<uint64_t, 29, (1LLU << 31) - 1>
        H(S.begin(), S.end(), -('a' - 1)),
        Ht(S.rbegin(), S.rend(), -('a' - 1));
    auto is_palindrome = [&n, &H, &Ht](size_t i, size_t j) {
        return H(i, j) == Ht(n-j-1, n-i-1);
    };
    for(uint32_t s = 0; s < 2; s++)
    {
        vector<uint32_t> DP(n+1, -1u), M(n+1, -1u);
        DP[0] = 0;
        for(uint32_t i = 1; i <= n; i++)
        {
            for(uint32_t j = i-2; j <= n; j -= 2)
            {
                if(is_palindrome(j, i-1) and DP[j] != -1u and (DP[i] == -1u or (s ? (DP[j] + 1 > DP[i]) : (DP[j] + 1 < DP[i]))))
                    DP[i] = DP[j] + 1, M[i] = j;
            }
        }
        if(DP[n] != -1u)
        {
            stack<string> A;
            uint32_t i = n;
            while(0 < i and i <= n)
            {
                A.push(S.substr(M[i], i - M[i]));
                i = M[i];
            }
            while(not A.empty())
            {
                cout << A.top();
                A.pop();
                if(not A.empty()) cout << " ";
            }
            if(s == 0) cout << "\n";
        }
        else
        {
            cout << "NIE";
            break;
        }
    }
}
