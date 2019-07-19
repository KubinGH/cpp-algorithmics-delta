#include <bits/stdc++.h>
#include <ktl/text/suffix_array.cpp>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string S;
    cin >> S;
    for(auto x : suffix_array(S.begin(), S.end()))
        cout << x << "\n";
}
