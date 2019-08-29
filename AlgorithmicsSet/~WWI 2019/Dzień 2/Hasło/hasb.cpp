#include <bits/stdc++.h>

using namespace std;

size_t n, m;
string S, Z;
size_t best = INT_MAX;
set<string> ok;

void gather(size_t i, size_t j, string c)
{
    if(i == n and j == m)
    {
        if(c.size() < best)
            ok.clear(), best = c.size();
        if(c.size() == best)
            ok.insert(c);
    }
    else if(i < n and j < m and S[i] == Z[j])
        gather(i + 1, j + 1, c + S[i]);
    else
    {
        if(i < n)
            gather(i + 1, j, c + S[i]);
        if(j < m)
            gather(i, j + 1, c + Z[j]);
    }
}

int main()
{
    cin >> n >> m;
    cin >> S >> Z;

    gather(0, 0, "");

    cout << ok.size();
}
