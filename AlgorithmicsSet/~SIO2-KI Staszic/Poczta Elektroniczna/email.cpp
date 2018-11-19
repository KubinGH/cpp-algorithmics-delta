#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n;
    cin >> n;
    vector<int> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    vector<vector<uint32_t>> Q(n+1, vector<uint32_t>(n+1, 0));
    for(uint32_t d = 1; d <= n; d++)
      for(uint32_t i = 0, j = d; j <= n; i++, j++)
    {
        Q[i][j] = -1u;
        //cout << i << ".." << j << ": " << endl;
        vector<int> P(d);
        copy(A.begin()+i, A.begin()+j, P.begin());
        sort(P.begin(), P.end());
        P.erase(unique(P.begin(), P.end()), P.end());
        for(int x : P)
        {
            //cout << "  dominant " << x << endl;
            uint32_t p = i;
            vector<uint32_t> regions;
            //cout << "   ";
            while(p < j)
            {
                regions.emplace_back(p);
                //cout << p << " ";
                if(A[p] == x) while(p+1 < j and A[p+1] == x) p++;
                else          while(p+1 < j and A[p+1] != x) p++;
                p++;
            }
            //cout << endl;
            for(uint32_t a = 0; a < regions.size(); a++)
            {
                bool k = (A[regions[a]] == x);
                uint32_t r = Q[i][regions[a]], f = k;
                for(uint32_t b = a; b < regions.size(); b++, k = !k)
                {
                    uint32_t z = b+1 < regions.size() ? regions[b+1] : j;
                    if(not k)
                        r += Q[regions[b]][z];
                    else
                        f = 1;
                    Q[i][j] = min(Q[i][j], r + f + Q[z][j]);
                }
            }
            //cout << "> " << Q[i][j] << endl;
        }
        for(uint32_t m = i+1; m < j; m++)
            Q[i][j] = min(Q[i][j], Q[i][m] + Q[m][j]);
    }
    cout << Q[0][n];
}

/*
16
2 3 5 2 5 3 1 2 6 7 8 2 8 7 6 2
*/
