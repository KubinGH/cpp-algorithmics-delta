#include <bits/stdc++.h>
#include <ktl/text/suffix_array.cpp>

using namespace std;

int main()
{
    string S;
    cin >> S;
    for(auto x : suffix_array(S.begin(), S.end()))
        cout << x << "\n";
}
