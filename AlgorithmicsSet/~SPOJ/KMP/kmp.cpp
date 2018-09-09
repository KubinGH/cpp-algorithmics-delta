#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        uint32_t _; cin >> _;
        string input, pattern_str;
        cin >> pattern_str >> input;
        regex pattern("(?=(" + pattern_str + ")).");
        sregex_iterator it(input.begin(), input.end(), pattern);
        sregex_iterator alldone;
        for(; it != alldone; ++it)
            cout << it->position() << "\n";
    }
}
