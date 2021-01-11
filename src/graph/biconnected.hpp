#pragma once
#include "core/all.hpp"
/*! Returns articulation points and bridges of \param graph.
 * @returns pair of a vector with 1s for all the articulation points and a vector of bridge edges
 */
pair<vector<char>, vector<array<ll, 2>>> biconnected(const GraphAdj &graph) {
	DFS d{graph};
	// TODO this should be fixed in DFS
	vector<char> articulations(graph.size());
	vector<array<ll, 2>> bridges;
	vector<ll> low(graph.size(), inf);
	fo(root, graph.size()) {
		if (d.visited[root]) {
			continue;
		}
		ll croot = 0;
		d.distance[root] = 0;
		d(root);
		for (const auto v : rev(d.queue)) {
			min_eq(low[v], d.distance[v]);
		}
		for (const auto v : rev(d.queue)) {
			croot += (d.parent[v] == root);
			for (const auto u : graph[v]) {
				if (u == d.parent[v]) {
					min_eq(low[v], d.distance[d.parent[v]]);
					continue;
				}
				min_eq(low[v], low[u]);
				if (low[u] >= d.distance[v] && v != root) {
					articulations[v] = true;
				}
			}
			if (d.parent[v] != -1) {
				bool is_bridge = all_of(al(graph[v]),
							[&](ll u) {
								return u == d.parent[v] ||
								       low[u] == d.distance[v];
							}) &&
						 low[v] == d.distance[d.parent[v]];
				if (is_bridge) {
					bridges.push_back({d.parent[v], v});
				}
			}
		}
		if (croot >= 2) {
			articulations[root] = true;
		}
		d.queue.clear();
	}
	return {articulations, bridges};
}
/*! \brief Returns ear decomposition of graph.
 * \param graph the graph as an adjacency list*/
vector<vector<vector<ll>>> ear_decomp(const GraphAdj &graph) {
	DFS d{graph};
	vector<ll> visited(graph.size());
	vector<vector<vector<ll>>> ears_list;
	fo(root, graph.size()) {
		if (d.visited[root]) {
			continue;
		}
		d(root);
		vector<vector<ll>> ears;
		for (const auto u : d.queue) {
			for (const auto v : graph[u]) {
				if (d.parent[u] == v || d.parent[v] == u) {
					continue;
				}
				// Backedge
				vector<ll> ear{u};
				visited[u] = true;
				for (ll x = v;; x = d.parent[x]) {
					ear.push_back(x);
					if (visited[x]) {
						break;
					}
					visited[x] = true;
				}
				ears.push_back(ear);
			}
		}
		ears_list.push_back(ears);
		d.queue.clear();
	}
	return ears_list;
}
/*! @brief Finds biconnected components of graph using ear decompositions.*/
pair<vector<char>, vector<array<ll, 2>>> biconnected_ear(GraphAdj graph) {
	// art_points[i] = whether vertex i is an articulation point
	vector<char> art_points(graph.size());
	// Bridge edges
	vector<array<ll, 2>> bridges;
	// Find ears apart from the first one which are cycles.
	const auto ear_list = ear_decomp(graph);
	for (const auto &ears : ear_list) {
		fo(i, ears.size()) {
			if (i != 0 && ears[i].front() == ears[i].back()) {
				art_points[ears[i].front()] = 1;
			}
		}
	}
	// Graph containing all ear edges
	GraphAdj ear_graph(graph.size());
	for (const auto &ears : ear_list) {
		for (const auto &ear : ears) {
			fo(i, ear.size() - 1) { ear_graph.add_edge(ear[i], ear[i + 1]); }
		}
	}
	// TODO add print overload for vector<char>
	// Find edges which are not in ear decomposition
	vector<ll> ear_adj(graph.size());
	fo(u, graph.size()) {
		vector<ll> non_ear_adj;
		const auto set = [&](const bool val) {
			for (const auto v : ear_graph[u]) {
				ear_adj[v] = val;
			}
		};
		set(true);
		for (const auto v : graph[u]) {
			if (!ear_adj[v]) {
				non_ear_adj.push_back(v);
			}
		}
		// Clear ear_adj efficiently
		set(false);
		for (const auto x : non_ear_adj) {
			if (u < x) {
				array<ll, 2> edge{u, x};
				bridges.push_back(edge);
				for (const auto v : edge) {
					if (graph[v].size() > 1) {
						art_points[v] = true;
					}
				}
			}
		}
	}
	return {art_points, bridges};
};
#include "test_biconnected.hpp"
