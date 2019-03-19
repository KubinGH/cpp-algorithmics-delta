#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

const size_t MAX = 1u << 18;

template<typename T, T MOD, T BASE, size_t N>
struct rolling_hash
{
    vector<T> H;
    vector<T> base_pow;
    size_t n;
    template<typename Iterator>
    rolling_hash(Iterator begin, Iterator end, T fix = 0)
    {
        n = distance(begin, end);
        H.reserve(n); base_pow.reserve(n);
        Iterator it = begin;
        for(uint32_t i = 0; i < n; i++)
        {
            if(i > 0)
                H[i] = H[i-1] * BASE, H[i] %= MOD;
            H[i] += T(*it) + fix;
            H[i] %= MOD;

            if(i > 0)
                base_pow[i] = (base_pow[i-1] * BASE) % MOD;
            else
                base_pow[i] = 1;
            it++;
        }
    }
    const T& operator[] (size_t i) const { return H[i]; }
    T operator() (size_t i, size_t j) const
    {
        if(i == 0)
            return H[j];
        else
            return (2*MOD + H[j] - ((H[i-1]*base_pow[j - i + 1]) % MOD)) % MOD;
    }
};

typedef rolling_hash<uint64_t, uint64_t(1e9+33), 29LLU, MAX> rhash;

int main()
{
    string S;
    uint32_t n;
    cin >> S; n = S.size();
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        A[i] = S[i] - 'a';
    static rhash H(A.begin(), A.end(), 1);
    uint32_t k;
    cin >> k;
    vector<pair<char, uint32_t>> Q(k);
    vector<vector<bool>> T(k+1);
    vector<vector<pair<char, uint32_t>>> P(k+1);
    for(uint32_t q = 0; q <= k; q++)
        T[q].reserve(n+1), P[q].reserve(n+1);
    T[0][0] = 1; P[0][0] = {'\0', -1};
    for(uint32_t q = 1; q <= k; q++)
    {
        char t;
        cin >> t;
        if(t == 'A')
        {
            char _c; cin >> _c;
            uint32_t c = _c - 'a';
            for(uint32_t i = 1; i <= n; i++)
            {
                if(T[q-1][i-1] and A[i-1] == c)
                    T[q][i] = 1, P[q][i] = {'A', c};
            }
        }
        else if(t == 'B')
        {
            uint32_t j;
            cin >> j;
            cout << j << endl;
            for(uint32_t i = 2*j+1; i <= n; i++)
            {
                if(T[q-1][i-j+1] and H(0, j-1) == H(i-j+1, i))
                    T[q][i] = 1, P[q][i] = {'B', j};
            }
        }
        else
        {
            ;
        }
    }
    if(T[k][n])
    {
        cout << k << "\n";
        stack<pair<char, uint32_t>> V;
        uint32_t q = k, i = n;
        while(P[q][i].first != '\0')
        {
            V.push(P[q][i]);
            cout << P[q][i].first << " " << P[q][i].second << endl;
            if(P[q][i].first == 'A')
                i--;
            else
                i -= P[q][i].second;
            q--;
            cout << q << ":" << i << " ";
        }
        while(not V.empty())
            cout << V.top().first << " " << V.top().second << "\n", V.pop();
    }
    else
        cout << -1;
}
