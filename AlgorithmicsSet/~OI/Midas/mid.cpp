#include <bits/stdc++.h>
#define note(x) #x << " = " << x

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n), L(n), R(n), D(n), P(n), B(n);
    iota(P.begin(), P.end(), 0);
    for(uint32_t u = 0; u < n; u++)
    {
        uint32_t v, w;
        cin >> v >> w; v--; w--;
        L[u] = v; R[u] = w;
    }
    queue<uint32_t> Q;
    Q.push(0);
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        uint32_t v = L[u], w = R[u];
        if(v != -1u)
        {
            A[v] = u; D[v] = D[u] + 1; Q.push(v);
            B[v] = B[u] ? B[u] + 1 : 0;
        }
        if(w != -1u)
        {
            A[w] = u; D[w] = D[u] + 1; Q.push(w);
            B[w] = B[u] + 1;
        }
    }

    auto make_path = [&](uint32_t u) {
        string U = "0";
        U.reserve(B[u]+1);
        while(B[u])
        {
            if(u == R[A[u]])
                U += "1";
            else
                U += "0";
            u = A[u];
        }
        reverse(U.begin(), U.end());
        return U;
    };
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint32_t v, w;
        cin >> v >> w; v--; w--;

        if(B[v] < B[w])
            cout << "NIE";
        else if(B[v] > B[w])
            cout << "TAK";
        else
        {
            string V = make_path(v), W = make_path(w);
            cout << (V >= W ? "TAK" : "NIE");
        }
        cout << "\n";
    }
}
