#include <iostream>
#include <ktl/graph/max_flow.cpp>
#include <ktl/util/fastio.cpp>

using namespace std;

int main()
{
    size_t n, m;
    ucin >> n >> m;

    flow_network<uint64_t, 22> G(n, 0, n - 1);

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; uint64_t c;
        ucin >> u >> v >> c; u--; v--;
        G.add_edge(u, v, c);
        G.add_edge(v, u, c);
    }

    ucout << G.max_flow();
}
