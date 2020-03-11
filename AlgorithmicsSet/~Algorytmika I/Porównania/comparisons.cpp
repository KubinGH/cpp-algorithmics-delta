#include <bits/stdc++.h>
#include <ktl/text/kmr.cpp>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;

    karp_miller_rosenberg kmr(S.begin(), S.end());

    size_t q;
    cin >> q;
    while(q --> 0)
    {
        size_t a, b, l;
        cin >> a >> b >> l; a--; b--;

        auto x = kmr(a, a + l), y = kmr(b, b + l);
        if(x < y)
            cout << "<\n";
        else if(x > y)
            cout << ">\n";
        else
            cout << "=\n";
    }
}
