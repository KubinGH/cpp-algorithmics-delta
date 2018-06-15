#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5;

double anglecomp(const pair<int64_t, int64_t>& a, const pair<int64_t, int64_t>& b)
{
    double c = atan2(a.second, a.first), d = atan2(b.second, b.first);
    return c < d or (c == d and a < b);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static pair<int64_t, int64_t> A[2*MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i].first >> A[i].second;
    sort(A, A + n, anglecomp);
    int64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        int64_t x = A[i].first, y = A[i].second; r = max(r, x*x+y*y);
        uint32_t a = i+1, b = n+i-1;
        double t = atan2(A[i].second, A[i].first);
        while(a <= b)
        {
            if(abs(t - atan2(A[a].second, A[a].first)) <
               abs(t - atan2(A[b].second, A[b].first)))
                x += A[a].first, y += A[a].second, a++;
            else
                x += A[b].first, y += A[b].second, b--;
            r = max(r, x*x+y*y);
        }
        A[n+i] = A[i];
    }
    cout << r;
}
