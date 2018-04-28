#include <bits/stdc++.h>

using namespace std;

typedef pair<uint64_t, pair<uint64_t, uint64_t>> dt;

const size_t MAX = 200001;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t a, b, n, k;
    cin >> a >> b >> n >> k;
    static array<uint64_t, MAX> A, B;
    uint64_t p, p2 = 0;
    for(uint64_t i = 0; i < n; i++)
    {
        cin >> p;
        A[i] = p - p2;
        p2 = p;
    }
    A[n] = a - p2;
    p2 = 0;
    for(uint64_t i = 0; i < n; i++)
    {
        cin >> p;
        B[i] = p - p2;
        p2 = p;
    }
    B[n] = b - p2;
    sort(A.begin(), A.begin() + n+1, greater<uint64_t>());
    sort(B.begin(), B.begin() + n+1, greater<uint64_t>());
    //cerr << "A: ";
    //for(uint64_t i = 0; i < n+1; i++)
    //    cerr << A[i] << " "; cerr << endl;
    //cerr << "B: ";
    //for(uint64_t i = 0; i < n+1; i++)
    //    cerr << B[i] << " "; cerr << endl;
    set<pair<uint64_t, uint64_t>> S;
    priority_queue<dt, vector<dt>, less<dt>> Q;
    Q.emplace(A[0]*B[0], make_pair(0, 0));
    uint64_t i = 0, result = 1;
    while(i < k)
    {
        dt c = Q.top(); Q.pop();
        if(S.find(c.second) != S.end())
            continue;
        i++;
        if(i == k)
            result = c.first;
        uint64_t x = c.second.first, y = c.second.second;
        //cerr << i << " " << c.first << " (" << x << ", " << y << ")" << endl;
        if(x < n) Q.emplace(A[x+1]*B[y], make_pair(x+1, y));
        if(y < n) Q.emplace(A[x]*B[y+1], make_pair(x, y+1));
        S.emplace(c.second);
    }
    cout << result;
}
