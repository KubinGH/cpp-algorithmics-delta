#include <bits/stdc++.h>

using namespace std;

const char alphabet[] = "ATCG";
uint32_t char_as_index(char x) { return find(begin(alphabet), end(alphabet), x) - begin(alphabet); }

uint32_t next_after(vector<uint32_t>& A, uint32_t i, uint32_t a)
{
    return find(A.begin()+i+1, A.end(), a) - A.begin();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string IA, IB;
    cin >> IA >> IB;
    uint32_t n = IA.size(), m = IB.size();
    vector<uint32_t> A(n), B(m);
    vector<array<uint32_t, 4>> S(n+1), Z(m+1);
    for(uint32_t i = 0; i < n; i++)
    {
        A[i] = char_as_index(IA[i]);
        S[i+1] = S[i]; S[i+1][A[i]]++;
    }
    for(uint32_t i = 0; i < m; i++)
    {
        B[i] = char_as_index(IB[i]);
        Z[i+1] = Z[i]; Z[i+1][B[i]]++;
    }
    vector<uint32_t> W;
    uint32_t se = -1u;
    for(uint32_t e = 0; e < 4 and W.empty(); e++)
    {
        if(min(S[n][e], Z[m][e]) > 0)
            W.resize(min(S[n][e], Z[m][e]), se = e);
    }
    //cerr << "Starting with " << alphabet[se] << " @ " << W.size() << endl;
    stack<int32_t> R_A, R_B;
    for(uint32_t e = 0; e < 4; e++)
    {
        if(e == se) continue;
        //cerr << "Extending with " << alphabet[e] << endl;
        int32_t L_A = -1, L_B = -1;
        R_A.push(n); R_B.push(m);
        for(uint32_t i = n, k = W.size(); i --> 0; )
            if(k > 0 and A[i] == W[k-1])
                R_A.push(i), k--;
        for(uint32_t i = m, k = W.size(); i --> 0; )
            if(k > 0 and B[i] == W[k-1])
                R_B.push(i), k--;
        vector<uint32_t> V; V.reserve(min(n, m));
        for(uint32_t i = 0; i <= W.size(); i++)
        {
            //cerr << "  in ranges: " << L_A+1 << ".." << R_A.top()-1 << "; " << L_B+1 << ".." << R_B.top()-1 << endl;
            uint32_t c = 0;
            if(L_A+1 < R_A.top() and L_B+1 < R_B.top())
                c = min(S[R_A.top()][e] - S[L_A+1][e], Z[R_B.top()][e] - Z[L_B+1][e]);
            //cerr << "  push " << c << " new" << endl;
            while(c --> 0)
            {
                V.push_back(e);
                L_A = next_after(A, L_A, e);
                L_B = next_after(B, L_B, e);
            }
            if(i < W.size())
            {
                V.push_back(W[i]);
                L_A = next_after(A, L_A, W[i]);
                L_B = next_after(B, L_B, W[i]);
            }
            R_A.pop(); R_B.pop();
        }
        swap(W, V);
    }

    for(uint32_t w : W)
        cout << alphabet[w];
}
