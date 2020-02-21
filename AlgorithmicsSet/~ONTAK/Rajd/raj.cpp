#include <bits/stdc++.h>

using namespace std;

const size_t N = 1024;

bool pass[N][N];
vector<bool> answer;

bitset<N> reach[2][N][N];
size_t col[N];

struct query
{
    uint64_t d;
    query() : d(0) {}
    query(uint64_t i, uint64_t x1, uint64_t y1, uint64_t x2, uint64_t y2)
        : d(i << 40 | x1 << 30 | y1 << 20 | x2 << 10 | y2) {}
    size_t  i() const { return d >> 40; }
    size_t x1() const { return d >> 30 & 1023; }
    size_t y1() const { return d >> 20 & 1023; }
    size_t x2() const { return d >> 10 & 1023; }
    size_t y2() const { return d & 1023; }
};

ostream& operator<< (ostream& out, const query& q)
{
    return out << "[" << q.i() << ": " << q.x1() << "," << q.y1() << ">" << q.x2() << "," << q.y2() << "]";
}


void divide_et_impera(size_t n, size_t L, size_t R, const vector<query>& queries)
{
    if(R == L+1)
    {
        for(size_t y = 1; y <= n; y++)
        {
            if(pass[y][L])
            {
                if(not pass[y-1][L])
                    col[y] = y;
                else
                    col[y] = col[y-1];
            }
        }
        for(auto q : queries)
            answer[q.i()] = (col[q.y1()] == col[q.y2()]);
        return;
    }

    size_t M = (L + R) / 2;
    vector<query> left, right, center;
    for(auto q : queries)
    {
        if(q.x1() < M and q.x2() < M)
            left.push_back(q);
        else if(q.x1() >= M and q.x2() >= M)
            right.push_back(q);
        else
            center.push_back(q);
    }

    for(auto i : {0, 1})
      for(size_t y = 1; y <= n; y++)
    {
        for(size_t x = L-1; x < R+1; x++)
            reach[i][y][x].reset();
        if(pass[y][M])
            reach[i][y][M].set(y);
    }

    for(size_t y = n+1; y --> 1; )
        for(size_t x = M; x --> L; )
            if(pass[y][x])
                reach[0][y][x] |= reach[0][y+1][x], reach[0][y][x] |= reach[0][y][x+1];
    for(size_t y = 1; y <= n; y++)
        for(size_t x = M; x < R; x++)
            if(pass[y][x])
                reach[1][y][x] |= reach[1][y-1][x], reach[1][y][x] |= reach[1][y][x-1];

    for(auto q : center)
        answer[q.i()] = (reach[0][q.y1()][q.x1()] & reach[1][q.y2()][q.x2()]).any();


    divide_et_impera(n, L, M, left);
    divide_et_impera(n, M, R, right);
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    for(size_t y = 1; y <= n; y++)
    {
        string S;
        cin >> S;
        for(size_t x = 1; x <= m; x++)
            pass[y][x] = (S[x-1] == '.');
    }

    vector<query> queries;
    queries.reserve(q);
    answer.resize(q);

    for(size_t i = 0; i < q; i++)
    {
        size_t x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 <= x2 and y1 <= y2)
            queries.emplace_back(i, y1, x1, y2, x2);
    }

    divide_et_impera(n, 1, m+1, queries);

    for(size_t i = 0; i < q; i++)
        cout << (answer[i] ? "YES" : "NO") << '\n';
}
