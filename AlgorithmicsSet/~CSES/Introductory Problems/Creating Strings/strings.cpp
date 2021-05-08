#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;

    vector<string> strings;

    sort(S.begin(), S.end());
    do {
        strings.push_back(S);
    } while(next_permutation(S.begin(), S.end()));

    sort(strings.begin(), strings.end());
    strings.erase(unique(strings.begin(), strings.end()), strings.end());

    cout << strings.size() << endl;
    for(auto s : strings)
        cout << s << '\n';
}
