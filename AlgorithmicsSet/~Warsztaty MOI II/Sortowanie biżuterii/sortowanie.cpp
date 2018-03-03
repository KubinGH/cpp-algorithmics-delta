#include <bits/stdc++.h>

using namespace std;

const size_t MAXC = 201, MAX = 150;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<vector<string>, MAXC> A;
    for(uint32_t i = 0; i < n; i++)
    {
        string current;
        cin >> current;
        A[current.size()].push_back(current);
    }
    for(uint32_t i = 0; i < MAXC; i++)
    {
        sort(A[i].begin(), A[i].end());
        for(string c : A[i])
            cout << c << '\n';
    }
}
