#include <bits/stdc++.h>

using namespace std;

vector<string> gray(size_t n)
{
    if(n == 0)
        return {""};
    auto sub0 = gray(n - 1), sub1 = sub0;
    for(auto& s : sub0)
        s.push_back('0');
    for(auto& s : sub1)
        s.push_back('1');
    copy(sub1.rbegin(), sub1.rend(), back_inserter(sub0));
    return sub0;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    for(auto s : gray(n))
        cout << s << '\n';
}
