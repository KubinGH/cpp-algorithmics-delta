#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    string S, Z;
    cin >> S >> Z;

    vector<array<size_t, 26>> next(m + 1);
    for(size_t c = 0; c < 26; c++)
        next.back()[c] = m+1;
    for(size_t i = m; i --> 0; )
    {
        next[i] = next[i+1];
        next[i][Z[i]-'a'] = i+1;
    }

    vector<int> A(m+2, INT_MAX - 0xD), B = A;
    A[0] = 0;

    int result = INT_MAX;
    for(size_t i = 0; i < n; i++)
    {
        copy(A.begin(), A.end(), B.begin());
        for(size_t p = 0; p <= m; p++)
        {
            auto q = next[p][S[i]-'a'];
            B[q] = min(B[q], A[p] + 1);
        }
        result = min(result, B[m+1]);
        swap(A, B);
    }

    if(result > (int)n)
        cout << "NIE" << endl;
    else
        cout << result << endl;
}
