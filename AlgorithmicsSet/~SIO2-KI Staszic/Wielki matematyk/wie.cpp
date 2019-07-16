#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    getline(cin, S);
    istringstream sin(S);

    vector<size_t> A(istream_iterator<size_t>(sin), {});
    const size_t n = A.size();

    vector<bool> ok(n + 1);
    ok[n] = true;
    for(size_t i = n; i --> 0; )
        if(i + A[i] + 1 <= n)
            ok[i] = ok[i + A[i] + 1];

    for(size_t i = 1; i <= n; i++)
        if(ok[i])
            cout << i << " ";
}
