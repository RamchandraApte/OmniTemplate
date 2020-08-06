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
	fo(i, n) {
		fo(j, n) { network[i][j].capacity = capacity[i][j]; }
	}
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
matrix<ll> dinic(const matrix<ll> &capacity) {
	const ll n = capacity.rows_n;
	vector<vector<ll>> graph(n); // stores edge ids
	vector<pair<ll, FlowEdge>> edges;
	fo(i, n) {
		fo(j, n) {
			if (capacity[i][j]) {
				graph[i].push_back(edges.size());
				edges.push_back({j, FlowEdge{capacity[i][j]}});
				graph[j].push_back(edges.size());
				edges.push_back({i, {}});
			}
		}
	}
	while (true) {
		// Construct residual graph
		vector<vector<ll>> res_graph(n);
		fo(i, n) {
			for (auto edge_id : graph[i]) {
				const auto [j, edge] = edges[edge_id];
				if (edge.residual() > 0) {
					res_graph[i].push_back(j);
				}
			}
		}
		BFS bfs{res_graph};
		bfs(0);


		if (bfs.distance[n - 1] == inf) {
			break;
		}

		vector<vector<ll>> level_graph(n);

		fo(i, n) {
			for (const auto edge_id : graph[i]) {
				const auto [j, edge] = edges[edge_id];
				if (edge.residual() > 0 && bfs.distance[i] + 1 == bfs.distance[j]) {
					level_graph[i].push_back(edge_id);
				}
			}
		}


		vector<ll> next_idx(n);

		const auto dfs = [&](const auto &dfs, const ll u) -> bool {
			if (u == n - 1) {
				return true;
			}
			while (true) {
				if (next_idx[u] == level_graph[u].size()) {
					return false;
				}
				const auto [v, edge] = edges[level_graph[u][next_idx[u]]];
				if (edge.residual() > 0 && dfs(dfs, v)) {
					return true;
				}
				++next_idx[u];
			}
		};

		while (dfs(dfs, 0)) {
			ll mn = inf;
			vl v;
			for (ll x = 0; x != n - 1; x = edges[level_graph[x][next_idx[x]]].first) {
				v.push_back(x);
			}
			for (auto x : v) {
				const auto &flow_edge = edges[level_graph[x][next_idx[x]]].second;
				mn = min(mn, flow_edge.residual());
			}
			for (auto x : v) {
				const auto edge_id = level_graph[x][next_idx[x]];
				auto &flow_edge = edges[edge_id].second;
				auto &flow_edge_rev = edges[edge_id ^ 1].second;
				flow_edge.flow += mn;
				flow_edge_rev.flow -= mn;
			}
		}
	}

	matrix<ll> flow(n, n);
	fo(i, n) {
		for (const auto edge_id : graph[i]) {
			const auto [j, edge] = edges[edge_id];
			if (edge.capacity > 0) {
				flow[i][j] = edge.flow;
			}
		}
	}
	return flow;
}
ll total_flow(const matrix<ll> &flow) { return accumulate(flow[0], flow[0] + flow.cols_n, 0LL); }
} // namespace flow
using namespace flow;
