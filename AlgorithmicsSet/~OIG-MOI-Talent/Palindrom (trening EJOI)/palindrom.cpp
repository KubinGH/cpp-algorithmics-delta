#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    deque<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    uint32_t r = 0;
    while(A.size() >= 2)
    {
        if(A.front() == A.back())
        {
            A.pop_front();
            A.pop_back();
        }
        if(A.empty()) break;
        while(A.size() >= 2 and A.front() > A.back())
        {
            uint32_t a = A.back();
            A.pop_back(); r++;
            A.back() += a;
        }
        if(A.size() >= 2 and A.front() < A.back())
        {
            uint32_t a = A.front();
            A.pop_front(); r++;
            A.front() += a;
        }
    }
    cout << r;
}
