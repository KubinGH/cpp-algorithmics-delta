#include <vector>
#include <iostream>
#include <queue>
#include <cstdint>

using namespace std;

struct edge { uint32_t v; uint64_t w; };

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	uint32_t n, r;
	cin >> n >> r;
	vector<uint32_t> R(n);
	vector<vector<uint32_t>> occ(r);
	for(uint32_t i = 0; i < n; i++)
	{
		cin >> R[i], R[i]--;
		occ[R[i]].push_back(i);
	}
	vector<vector<edge>> graph(n);
	for(uint32_t i = 0; i < n - 1; i++)
	{
		uint32_t u, v, w;
		cin >> u >> v >> w; u--; v--;
		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}

	vector<bool> vis(n);
	vector<vector<uint32_t>> jump(n, vector<uint32_t>(__lg(n) + 1, -1u));
	vector<uint32_t> depth(n);
	vector<uint64_t> root_cost(n);
	queue<uint32_t> Q;
	Q.push(0); vis[0] = true;
	while(not Q.empty())
	{
		uint32_t u = Q.front(); Q.pop();
		for(auto e : graph[u]) if(not vis[e.v])
		{
			Q.push(e.v);
			vis[e.v] = true;
			depth[e.v] = depth[u] + 1;
			root_cost[e.v] = root_cost[u] + e.w;
			jump[e.v][0] = u;
			for(uint32_t i = 1; jump[e.v][i-1] != -1u and i <= __lg(n); i++)
				jump[e.v][i] = jump[jump[e.v][i-1]][i-1];
		}
	}

	auto lca = [&](uint32_t u, uint32_t v) {
		if(depth[u] > depth[v])
			swap(u, v);
		for(uint32_t k = __lg(n)+1; k --> 0; )
			if(jump[v][k] != -1u and depth[v] >= depth[u] + (1u << k))
				v = jump[v][k];
		if(u == v)
			return u;
		for(uint32_t k = __lg(n)+1; k --> 0; )
			if(depth[u] >= (1u << k) and jump[u][k] != jump[v][k])
				u = jump[u][k], v = jump[v][k];
		return jump[u][0];
	};
	auto get_dist = [&](uint32_t u, uint32_t v) {
		return root_cost[u] + root_cost[v] - 2*root_cost[lca(u, v)];
	};

	uint32_t q;
	cin >> q;
	while(q --> 0)
	{
		uint32_t u, v, t;
		cin >> u >> v >> t; u--; v--; t--;
		uint64_t result = -1llu;
		if(r > 1)
		{
			for(uint32_t p : occ[t])
				result = min(result, get_dist(u, p) + get_dist(v, p));
		}
			else
				result = get_dist(u, v);
		cout << (int64_t)result << "\n";
	}
}
