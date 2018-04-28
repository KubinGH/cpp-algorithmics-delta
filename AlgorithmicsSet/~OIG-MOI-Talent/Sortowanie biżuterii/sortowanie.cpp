#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

bool sizecomp(const string& a, const string& b)
{
    return a.size() < b.size();
}

int main()
{
    uint32_t n;
    cin >> n;
    vector<string> V;
    for(uint32_t i = 0; i < n; i++)
    {
        string current;
        cin >> current;
        V.push_back(current);
    }
    sort(V.begin(), V.end(), sizecomp);
    for(uint32_t i = 0; i < n; i++)
        cout << V[i] << '\n';
}
