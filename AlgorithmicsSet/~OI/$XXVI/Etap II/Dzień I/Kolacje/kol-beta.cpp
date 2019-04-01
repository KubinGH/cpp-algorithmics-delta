#define _GLIBCXX_DEBUG
#include <vector>
#include <iostream>
#include <queue>
#include <cstdint>
#include <cmath>
#include <algorithm>

using namespace std;

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

struct edge { uint32_t v; uint64_t w; };
bool operator< (const edge& lhs, const edge& rhs)
{
	return make_pair(lhs.w, lhs.v) < make_pair(rhs.w, rhs.v);
}
bool operator> (const edge& lhs, const edge& rhs)
{
	return make_pair(lhs.w, lhs.v) > make_pair(rhs.w, rhs.v);
}
struct query { uint32_t u, v, t; };

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	uint32_t n, r;
	cin >> n >> r;
	vector<uint32_t> R(n);
	vector<vector<uint32_t>> occ(r);
	uint32_t max_occ = 0;
	for(uint32_t u = 0; u < n; u++)
	{
		cin >> R[u], R[u]--;
		occ[R[u]].push_back(u);
		max_occ = max(max_occ, occ[R[u]].size());
	}

	vector<vector<edge>> graph(n);
	for(uint32_t i = 0; i < n - 1; i++)
	{
		uint32_t u, v, w;
		cin >> u >> v >> w; u--; v--;
		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}

	uint32_t q;
	cin >> q;
	vector<query> queries(q);
	for(uint32_t i = 0; i < q; i++)
	{
		uint32_t u, v, t;
		cin >> u >> v >> t; u--; v--; t--;
		queries[i] = {u, v, t};
	}

	vector<bool> vis(n);
	vector<vector<uint32_t>> jump(n, vector<uint32_t>(__lg(n) + 1, -1u));
	vector<uint32_t> depth(n), order; order.reserve(n);
	vector<uint64_t> root_cost(n);
	queue<uint32_t> Q;
	Q.push(0); vis[0] = true;
	while(not Q.empty())
	{
		uint32_t u = Q.front(); Q.pop();
		order.push_back(u);
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

	const uint32_t limus = ceil(sqrt(n));
	vector<uint32_t> grande, grandex(r, -1u);
	if((uint64_t) q * max_occ > (uint64_t)3e6 and r > 1)
      for(uint32_t t = 0; t < r; t++) if(occ[t].size() > limus)
        grandex[t] = grande.size(), grande.push_back(t);
	vector<uint64_t> dist(n);
	vector<vector<vector<uint64_t>>> jump_closest(grande.size(), vector<vector<uint64_t>>(n, vector<uint64_t>(__lg(n) + 1)));
	for(uint32_t ti = 0; ti < grande.size(); ti++)
	{
		uint32_t t = grande[ti];
		min_priority_queue<edge> P;
		fill(dist.begin(), dist.end(), -1llu);
		for(auto u : occ[t])
			P.push({u, dist[u] = 0});
		while(not P.empty())
		{
			auto c = P.top(); P.pop();
			if(c.w > dist[c.v])
				continue;
			for(auto e : graph[c.v])
				if(c.w + e.w < dist[e.v])
					P.push({e.v, dist[e.v] = c.w + e.w});
		}
		auto& jdist = jump_closest[ti];
		for(uint32_t u : order)
		{
			if(jump[u][0] != -1u)
				jdist[u][0] = min(dist[u], dist[jump[u][0]]);
			for(uint32_t i = 1; i <= __lg(n) and jump[u][i] != -1u; i++)
				jdist[u][i] = min(jdist[u][i-1], jdist[jump[u][i-1]][i-1]);
		}
	}

	for(uint32_t i = 0; i < q; i++)
	{
		uint32_t u = queries[i].u, v = queries[i].v, t = queries[i].t;
		if(grandex[t] != -1u)
		{
			uint32_t a = lca(u, v);
			uint64_t overpath = -1llu;
			const auto& jdist = jump_closest[grandex[t]];
			uint32_t u1 = u, v1 = v;
			for(uint32_t k = __lg(n+1); k --> 0; )
				if(depth[u1] >= depth[a] + (1u << k))
			{
				overpath = min(overpath, jdist[u1][k]);
				u1 = jump[u1][k];
			}
			for(uint32_t k = __lg(n+1); k --> 0; )
				if(depth[v1] >= depth[a] + (1u << k))
			{
				overpath = min(overpath, jdist[v1][k]);
				v1 = jump[v1][k];
			}
			cout << 2 * overpath + get_dist(u, v) << "\n";
		}
		else
		{
			uint64_t result = -1llu;
			if(r > 1)
                for(uint32_t p : occ[t])
					result = min(result, get_dist(u, p) + get_dist(v, p));
			else
				result = get_dist(u, v);
			cout << (int64_t)result << endl;
		}
	}
}
