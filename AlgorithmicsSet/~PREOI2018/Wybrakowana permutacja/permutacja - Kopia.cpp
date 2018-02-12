#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;
const size_t TSIZE = 1 << 20;

struct interval_tree
{
    array<array<uint32_t, 3>, TSIZE> values, to_add;
    void set_value(uint32_t i, uint32_t value)
    {
        i += TSIZE/2;
        values[i] = value;
        while(i != 1)
            i /= 2, values[i] = max(values[2*i], values[2*i+1]);
    }
    void add_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {

    }
    void add_value(uint32_t sbegin, uint32_t send, uint32_t k)
    {
        return add_value(1, 0, TSIZE/2-1, sbegin, send, k);
    }
    uint32_t find_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return max(find_value(2*i, tbegin, (tbegin+tend)/2, sbegin, send),
                       find_value(2*i+1, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint32_t find_value(uint32_t sbegin, uint32_t send)
    {
        return find_value(1, 0, TSIZE/2-1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A, P;
    static array<uint32_t, MAX+1> C, U;
    static array<bool, MAX+1> B;
    fill(B.begin() + 1, B.begin() + n + 1, true);
    vector<uint32_t> V;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        C[i+1] = C[i] + (A[i] == 0);
        if(A[i] != 0)
            V.push_back(i), B[A[i]] = false;
    }
    for(uint32_t i = 1; i < n+1; i++)
        U[i] = U[i-1] + B[i];
    uint32_t m = C[n];
    static interval_tree tree;
    for(uint32_t vi = 0; vi < V.size(); vi++)
    {
        uint32_t i = V[vi];
        uint32_t p = 0;
        for(uint32_t vj = 0; vj < vi; vj++)
        {
            uint32_t j = V[vj];
            if(A[j] < A[i])
                p = max(p, P[j] + min(U[A[i]] - U[A[j]], C[i] - C[j]));
        }
        p = max(p, min(U[A[i]], C[i]));
        p++;
        P[i] = p;
        uint32_t v = P[i] + min(U[n] - U[A[i]], C[n] - C[i]);
        if(v > m)
            m = v;
    }
    cout << m;

}
