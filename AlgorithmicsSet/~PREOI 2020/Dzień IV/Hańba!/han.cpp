#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t t;
    cin >> t;

    while(t --> 0)
    {
        size_t n;
        cin >> n;

        string A(n, 'a');
        vector<size_t> Q(n);

        A[0] = 'a';
        cin >> Q[0];
        for(size_t i = 1; i < n; i++)
        {
            cin >> Q[i];
            if(Q[i-1]+1 == Q[i])
                A[i] = A[Q[i]-1];
            else
                A[i] = (A[Q[i-1]] == 'b' ? 'a' : 'b');
        }

        vector<size_t> P(n);
        P[0] = 0;
        for(size_t i = 1; i < n; i++)
        {
            P[i] = P[i-1];
            while(P[i] and A[P[i]] != A[i])
                P[i] = P[P[i] - 1];
            if(A[P[i]] == A[i])
                P[i]++;
        }

        if(P == Q)
            cout << "TAK" << endl << A << endl;
        else
            cout << "NIE" << endl;
    }
}
