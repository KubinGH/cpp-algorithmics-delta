#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> S = {0};
    int result = 0;

    auto push = [&](int x) {
        while(S.back() > x)
            S.pop_back(), result++;
        if(S.back() < x)
            S.push_back(x);
    };

    for(size_t i = 0; i < n; i++)
    {
        int h;
        cin >> h;
        h = INT_MAX - h;
        push(h);
    }
    push(0);

    cout << result << endl;
}
