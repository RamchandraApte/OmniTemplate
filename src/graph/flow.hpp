#pragma once
#include "algebra/linear_algebra.hpp"
#include "core/all.hpp"
namespace flow {
struct FlowEdge {
	ll capacity{}, flow{};
	ll residual() const { return capacity - flow; };
};
matrix<ll> edmond_karp(const matrix<ll> &capacity) {
	/*! Edmond-Karp maximum flow algorithm.
	 * \param capacity is a matrix with the capacity for each edge.
	 * The source node is 0, and the sink node is n-1.
	 * \returns The flow for each edge in a maximum flow.
	 */
	const ll n = capacity.rows_n;
	matrix<FlowEdge> network(n, n);
	fo(i, n){fo(j, n){network[i][j].capacity = capacity[i][j];
}
}; // namespace flow
while (true) {
	// Construct residual graph
	vector<vector<ll>> graph(n);
	fo(i, n) {
		fo(j, n) {
			if (network[i][j].residual() > 0) {
				graph[i].push_back(j);
			}
		}
	}
	// Find augmenting path
	BFS bfs{graph};
	bfs(0);

	ll mincap = inf;
	auto root_edges = [&](const auto &func) {
		for (ll x = n - 1; bfs.parent[x] != -1; x = bfs.parent[x]) {
			func(bfs.parent[x], x);
		}
	};
	root_edges([&](const ll u, const ll v) { min_eq(mincap, network[u][v].residual()); });
	if (!(0 < mincap && mincap < inf)) {
		break;
	}
	root_edges([&](const ll u, const ll v) {
		network[u][v].flow += mincap;
		network[v][u].flow -= mincap;
	});
}

matrix<ll> flow(n, n);
fo(i, n) {
	fo(j, n) { flow[i][j] = network[i][j].flow; }
}
return flow;
}
ll total_flow(const matrix<ll> &flow) { return accumulate(flow[0], flow[0] + flow.cols_n, 0LL); }
} // namespace flow
using namespace flow;
