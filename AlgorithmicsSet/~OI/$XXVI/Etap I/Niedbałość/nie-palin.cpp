#include <bits/stdc++.h>

using namespace std;

char I_G[4] = {'A', 'T', 'C', 'G'};
map<char, uint32_t> G_I = {{'A', 0}, {'T', 1}, {'C', 2}, {'G', 3}};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string SA, SB;
    cin >> SA >> SB;
    uint32_t n = SA.size(), m = SB.size();
    vector<uint32_t> A(2*n), B(2*m);
    deque<uint32_t> P[4], Q[4];
    for(uint32_t i = 0; i < 2*n; i++)
    {
        if(i<n) A[i] = G_I[SA[i]];
        else    A[i] = G_I[SA[2*n-i-1]];
        P[A[i]].push_back(i);
    }
    for(uint32_t i = 0; i < 2*m; i++)
    {
        if(i<m) B[i] = G_I[SB[i]];
        else    B[i] = G_I[SB[2*m-i-1]];
        Q[B[i]].push_back(i);
    }
    int32_t ax = 0, ay = 2*n-1, bx = 0, by = 2*m-1;
    vector<uint32_t> R; R.reserve(2*min(n, m));
    uint32_t middle = -1u;
    bool allow_middles = false;
    while(true)
    {
        bool extended = false;
        uint32_t c = -1u, ct = 1<<28;
        for(uint32_t p = 0; p < 4 and not extended; p++)
        {
            while(not P[p].empty() and (int32_t)P[p].front() < ax) P[p].pop_front();
            while(not P[p].empty() and (int32_t)P[p].back() > ay) P[p].pop_back();
            while(not Q[p].empty() and (int32_t)Q[p].front() < bx) Q[p].pop_front();
            while(not Q[p].empty() and (int32_t)Q[p].back() > by) Q[p].pop_back();
            if(not (P[p].empty() or Q[p].empty()))
            {
                if(allow_middles)
                {
                    if(P[p].size() == 1 or Q[p].size() == 1)
                        middle = p, extended = true;
                }
                else if(P[p].size() >= 2 and Q[p].size() >= 2)
                {
                    if(P[p].front()+1 - ax < ct)
                        ct = P[p].front()+1 - ax, c = p;
                    //cout << "consider " << p << " @ " << P[p].front()+1 - ax << endl;
                }
            }
        }
        if(c != -1u)
        {
            ax = P[c].front()+1; ay = P[c].back()-1;
            bx = Q[c].front()+1; by = Q[c].back()-1;
            //cout << "extend with " << c << endl;
            R.push_back(c);
            extended = true;
        }
        if(not extended and not allow_middles)
            allow_middles = true;
        else if(not extended or allow_middles)
            break;
    }
    (void)middle;
    for(uint32_t i = 0; i < R.size(); i++)
        cout << I_G[R[i]];
}
