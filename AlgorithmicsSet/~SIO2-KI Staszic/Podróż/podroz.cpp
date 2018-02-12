#include <bits/stdc++.h>

using namespace std;

struct coor_t
{
    int64_t x, y;
};
int64_t dist(coor_t& a, coor_t& b)
{
    return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}

const size_t MAX = 1001;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t a, b;
    cin >> a >> b;
    static array<coor_t, MAX> A, B;
    cin >> A[0].x >> A[0].y >> B[0].x >> B[0].y;
    for(uint64_t i = 0; i < a; i++)
    {
        char d;
        cin >> d;
        if(d == 'N')
            A[i+1].x = A[i].x, A[i+1].y = A[i].y + 1;
        else if(d == 'E')
            A[i+1].x = A[i].x + 1, A[i+1].y = A[i].y;
        else if(d == 'S')
            A[i+1].x = A[i].x, A[i+1].y = A[i].y - 1;
        else if(d == 'W')
            A[i+1].x = A[i].x - 1, A[i+1].y = A[i].y;
    }
    for(uint64_t i = 0; i < b; i++)
    {
        char d;
        cin >> d;
        if(d == 'N')
            B[i+1].x = B[i].x, B[i+1].y = B[i].y + 1;
        else if(d == 'E')
            B[i+1].x = B[i].x + 1, B[i+1].y = B[i].y;
        else if(d == 'S')
            B[i+1].x = B[i].x, B[i+1].y = B[i].y - 1;
        else if(d == 'W')
            B[i+1].x = B[i].x - 1, B[i+1].y = B[i].y;
    }
    static array<array<int64_t, MAX>, MAX> R;
    for(uint64_t i = 0; i < MAX; i++)
        R[i].fill(1ll << 42);
    R[0][0] = dist(A[0], B[0]);
    for(uint64_t i = 0; i <= a; i++)
    {
        for(uint64_t j = 0; j <= b; j++)
        {
            int64_t d = dist(A[i], B[j]);
            if(i > 0)
                R[i][j] = min(R[i][j], R[i-1][j] + d);
            if(j > 0)
                R[i][j] = min(R[i][j], R[i][j-1] + d);
            if(i > 0 and j > 0)
                R[i][j] = min(R[i][j], R[i-1][j-1] + d);
        }
    }
    cout << R[a][b] - dist(A[0], B[0]);
}
