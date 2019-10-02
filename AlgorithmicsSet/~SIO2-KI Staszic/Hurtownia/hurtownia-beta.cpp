#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<uint64_t> A(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];

    priority_queue<uint64_t> Q;

    uint64_t sum = 0, cap = 0;
    for(size_t i = 0; i < n; i++)
    {
        cap += A[i];
        uint64_t b;
        cin >> b;

        if(sum + b <= cap)
            Q.push(b), sum += b;
        else if(not Q.empty() and b < Q.top())
            sum += b - Q.top(), Q.pop(), Q.push(b);
    }

    cout << Q.size();
}
