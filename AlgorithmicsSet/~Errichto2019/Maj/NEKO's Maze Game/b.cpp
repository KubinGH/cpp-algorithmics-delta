#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<bool> A[2];
    A[0].resize(n+2); A[1].resize(n+2);
    int cnt = 0;

    while(q --> 0)
    {
        size_t y, x;
        cin >> y >> x; y--;

        int s = A[y][x] ? -1 : 1;
        for(int dx : {-1, 0, 1})
            if(A[y^1][x+dx])
                cnt += s;
        A[y][x] = not A[y][x];

        cout << (cnt == 0 ? "Yes\n" : "No\n");
    }
}
