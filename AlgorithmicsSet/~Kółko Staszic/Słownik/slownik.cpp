#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    unordered_set<string> S;
    string current;
    while(cin >> current)
    {
        S.insert(current);
        if(current == "prrr") break;
    }
    cout << S.size();
}
