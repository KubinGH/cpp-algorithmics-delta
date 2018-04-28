#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;
struct dt { uint32_t i, c; }; // index, count

const size_t MAX = 1000000, JUMP_POINTERS = 21;

uint64_t pairs(uint64_t n)
{
    return (n * (n - 1)) / 2;
}

ostream& operator<< (ostream& out, const dt& o)
{
    out << (int)o.i+(o.i>0) << ":" << o.c;
    return out;
}

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static vector<uint32_t> graph[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        scanf("%u %u", &u, &v); u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    static bool visited[MAX];
    static uint32_t parent[MAX], topological[MAX]; uint32_t ti = 0;
    static vector<uint32_t> children[MAX];
    queue<uint32_t> to_visit;
    to_visit.push(0);
    visited[0] = true;
    while(not to_visit.empty())
    {
        uint32_t u;
        u = to_visit.front(); to_visit.pop();
        topological[ti++] = u;
        for(uint32_t i = 0; i < graph[u].size(); i++)
        {
            uint32_t v = graph[u][i];
            if(not visited[v])
            {
                parent[v] = u;
                children[u].push_back(v);
                to_visit.push(v);
                visited[v] = true;
            }
        }
    }
    reverse(topological, topological + n);
    static uint32_t subtree_count[MAX];
    fill(subtree_count, subtree_count + n, 1);
    static dt subtrees[MAX][2];
    uint32_t x = (n + 1) / 3;
    cout << "target " << x << endl;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t u = topological[i];
        subtrees[u][0].i = subtrees[u][1].i = -1u;
        subtrees[u][0].c = subtrees[u][1].c = 0;
        for(uint32_t j = 0; j < children[u].size(); j++)
        {
            uint32_t v = children[u][j];
            subtree_count[u] += subtree_count[v];
        }
        if(subtree_count[u] <= x)
        {
            subtrees[u][0].i = u;
            subtrees[u][0].c = subtree_count[u];
        }
        else
        {

        }
        cout << u+1 << ": " << subtree_count[u] << " " << subtrees[u][0] << " " << subtrees[u][1] << endl;
    }
    cout << pairs(subtrees[0][0].c) + pairs(subtrees[0][1].c) +
            pairs(n - subtrees[0][0].c - subtrees[0][1].c);
}

/*
16
13 7
7 2
2 1
14 8
15 8
8 3
9 3
16 10
10 3
3 1
4 1
11 5
12 5
5 1
6 1
*/
