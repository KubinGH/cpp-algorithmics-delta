#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

template<typename T, size_t SIZE>
struct fstack
{
    array<T, SIZE> A;
    size_t i = 0;
    T& top()
    {
        return A[i-1];
    }
    void push(T o)
    {
        A[i] = o; i++;
    }
    void pop()
    {
        i--;
    }
    void clear()
    {
        i = 0;
    }
    size_t size()
    {
        return i;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, k;
    cin >> n >> m >> k;
    static array<uint32_t, MAX> S;
    for(uint32_t i = 0; i < n; i++)
        cin >> S[i], S[i]--;
    static array<uint32_t, MAX> P, C, T, R;
    iota(P.begin(), P.begin() + k, 0);
    iota(C.begin(), C.begin() + k, 0);
    iota(R.begin(), R.begin() + k, 0);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        if(R[a] == k or a == b) continue;
        if(C[b] != b)
        {
            if(R[b] == k)
            {
                C[R[a]] = b;
                R[b] = R[a];
                R[a] = k;
            }
            else
            {
                P[R[a]] = R[b];
                C[R[a]] = k;
                R[a] = k;
            }
        }
        else
        {
            P[R[a]] = b;
            C[R[a]] = k;
            R[a] = k;
        }
    }
    static array<bool, MAX> V;
    for(uint32_t i = 0; i < k; i++)
    {
        if(V[i]) continue;
        static fstack<uint32_t, MAX> S;
        S.clear();
        S.push(i); V[i] = true;
        while(P[S.top()] != S.top() and not V[P[S.top()]])
            S.push(P[S.top()]), V[S.top()] = true;
        if(P[S.top()] == S.top())
            T[S.top()] = C[S.top()];
        else if(V[P[S.top()]])
            S.push(P[S.top()]);
        uint32_t c = T[S.top()];
        for(uint32_t j = 0; j < S.size(); j++)
            T[S.A[j]] = c;
    }
    for(uint32_t i = 0; i < n; i++)
        cout << T[S[i]]+1 << " ";
}
