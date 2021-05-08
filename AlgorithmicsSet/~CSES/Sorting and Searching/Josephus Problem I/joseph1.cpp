#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    deque<size_t> que;
    for(size_t i = 1; i <= n; i++)
        que.push_back(i);

    while(not que.empty())
    {
        que.push_back(que.front());
        que.pop_front();
        cout << que.front() << ' ';
        que.pop_front();
    }
    cout << endl;
}
