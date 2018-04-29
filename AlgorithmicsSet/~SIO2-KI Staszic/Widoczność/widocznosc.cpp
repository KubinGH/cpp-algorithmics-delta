#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5e5;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    deque<uint32_t> Q;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        while(not Q.empty() and A[Q.front()] <= A[i])
            Q.pop_front();
        if(not Q.empty())
            cout << Q.front()+1 << "\n";
        else
            cout << -1 << "\n";
        Q.push_front(i);
    }
}
