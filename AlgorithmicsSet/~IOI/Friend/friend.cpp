#include <bits/stdc++.h>

using namespace std;

enum Protocol
{
    IAmYourFriend = 0,
    MyFriendsAreYourFriends = 1,
    WeAreYourFriends = 2
};

int findSample(int _n, int val[], int host[], int protocol[])
{
    size_t n = _n;

    vector<array<int, 2>> T(n);
    for(size_t u = 0; u < n; u++)
        T[u][1] = val[u];

    for(size_t u = n; u --> 1; )
    {
        auto v = host[u];
        if(protocol[u] == IAmYourFriend)
            T[v] = {T[v][0] + max(T[u][0], T[u][1]), T[v][1] + T[u][0]};
        else if(protocol[u] == MyFriendsAreYourFriends)
            T[v] = {T[u][0] + T[v][0], max({T[u][1] + T[v][1], T[u][1] + T[v][0], T[u][0] + T[v][1]})};
        else if(protocol[u] == WeAreYourFriends)
            T[v] = {T[u][0] + T[v][0], max({T[u][1] + T[v][0], T[u][0] + T[v][1]})};
    }
    return max(T[0][0], T[0][1]);
}
