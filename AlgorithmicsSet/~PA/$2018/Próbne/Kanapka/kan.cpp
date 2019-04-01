#include <bits/stdc++.h>
#include "kanapka.h"
#include "message.h"

using namespace std;

struct socket
{
    uint32_t conn;
    socket(uint32_t _conn) : conn(_conn) {}
    socket& operator+ () { Receive(conn); return *this; }
    socket& operator- () { Send(conn); return *this; }
    #define BYTES(_b) template<typename T> typename enable_if<(_b) == sizeof(T), socket&>::type
    BYTES(1) operator<< (T val) { PutChar(conn, val); return *this; }
    BYTES(1) operator>> (T& var) { var = GetChar(conn); return *this; }
    BYTES(4) operator<< (T val) { PutInt(conn, val); return *this; }
    BYTES(4) operator>> (T& var) { var = GetInt(conn); return *this; }
    BYTES(8) operator<< (T val) { PutLL(conn, val); return *this; }
    BYTES(8) operator>> (T& var) { var = GetLL(conn); return *this; }
    #undef BYTES
};

int main()
{
    uint32_t NODES = NumberOfNodes(), ID = MyNodeId();
    uint32_t N = GetN();
    NODES = min((uint32_t)ceil(sqrt(N)), NODES);
    if(ID >= NODES)
        return 0;
    uint32_t PART = (N + NODES - 1) / NODES;
    uint32_t A = min(PART*ID, N), B = min(PART*(ID+1), N);
    int64_t run = 0, best_left = 0, best_right = 0, best_mid = 0;
    for(uint32_t i = A; i < B; i++)
        best_left = max(best_left, run += GetTaste(i));
    run = 0;
    vector<pair<uint32_t, int64_t>> Q;
    Q.emplace_back(B, 0);
    for(uint32_t i = B; i --> A; )
    {
        best_right = max(best_right, run += GetTaste(i));
        if(best_right > Q.back().second)
            Q.emplace_back(i, best_right);
    }
    run = 0;
    for(uint32_t i = A; i < B; i++)
    {
        if(Q.back().first == i)
            Q.pop_back();
        best_mid = max(best_mid, (run += GetTaste(i)) + Q.back().second);
    }
    if(ID == 0)
    {
        uint32_t n = NODES;
        vector<int64_t> S(n), L(n), R(n), M(n);
        S[0] = run; L[0] = best_left; R[0] = best_right; M[0] = best_mid;
        for(uint32_t v = 1; v < n; v++)
            (+socket(v)) >> S[v] >> L[v] >> R[v] >> M[v];
        vector<int64_t> T(n+1);
        for(uint32_t v = 0; v < n; v++)
            T[v+1] = T[v] + S[v];
        auto sum = [&](uint32_t i, uint32_t j) {
            return T[j+1] - T[i];
        };
        int64_t result = 0;
        for(uint32_t v = 0; v < n; v++)
            result = max(result, (v>0 ? sum(0, v-1) : 0)
                               + (v<n-1 ? sum(v+1, n-1) : 0)
                               + M[v]);
        Q.clear();
        Q.emplace_back(n, 0);
        for(uint32_t v = n; v --> 0; )
        {
            int64_t c = (v<n-1 ? sum(v+1, n-1) : 0) + R[v];
            if(c > Q.back().second)
                Q.emplace_back(v, c);
        }
        for(uint32_t v = 0; v < n; v++)
        {
            if(Q.back().first == v)
                Q.pop_back();
            result = max(result, (v>0 ? sum(0, v-1) : 0) + L[v] + Q.back().second);
        }
        cout << result << endl;
    }
    else
        -(socket(0) << run << best_left << best_right << best_mid);
}
