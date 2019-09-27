#include <bits/stdc++.h>
#define COUNT(__A, __v) count(__A.begin(), __A.end(), __v)

using namespace std;

int main() {
    size_t n;
    string S;
    cin >> n >> S;
    vector<pair<size_t, char>> cnt = {
        {COUNT(S, 'A'), 'A'}, {COUNT(S, 'C'), 'C'}, {COUNT(S, 'T'), 'T'}, {COUNT(S, 'G'), 'G'}
    };
    sort(cnt.begin(), cnt.end());

    cout << cnt[0].first << endl << string(n, cnt[0].second);
}
