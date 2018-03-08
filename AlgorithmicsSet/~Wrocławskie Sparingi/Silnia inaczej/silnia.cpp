#include <bits/stdc++.h>

using namespace std;

int main()
{
    string S;
    cin >> S;
    if(S == "1")
        cout << '1';
    else if(S == "2")
        cout << '2';
    else if(S == "6")
        cout << '3';
    else if(S == "24")
        cout << '4';
    else if(S == "120")
        cout << '5';
    else if(S == "720")
        cout << '6';
    else
    {
        double clog = log10(720);
        uint64_t i;
        for(i = 7; floor(clog) + 1 < S.size(); i++)
            clog += log10(i);
        cout << i - 1;
    }
}
