#pragma once
#include "core/all.hpp"
/*! Returns articulation points and bridges of \param graph.
 * \pre graph must be connected
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
				bool is_bridge = all_of(al(graph[v]), [&](ll u) { return u == d.parent[v] || low[u] == d.distance[v]; }) && low[v] == d.distance[d.parent[v]];
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
				if (d.parent[u] == v || d.parent[v] == u || !(d.distance[u] < d.distance[v])) {
					continue;
				}
				// Backedge
				vector<ll> ear{u};
				visited[u] = true;
				ll x = v;
				while (true) {
					ear.push_back(x);
					if (visited[x]) {
						break;
					}
					visited[x] = true;
					x = d.parent[x];
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
	vector<char> art_points(graph.size());
	vector<array<ll, 2>> bridges;
	const auto ear_list = ear_decomp(graph);
	for (const auto &ears : ear_list) {
		fo(i, ears.size()) {
			if (i != 0 && ears[i].front() == ears[i].back()) {
				art_points[ears[i].front()] = 1;
			}
		}
	}
	for (auto &vec : graph) {
		sort(al(vec));
	}
	GraphAdj ear_graph(graph.size());
	for (const auto &ears : ear_list) {
		for (const auto &ear : ears) {
			fo(i, ear.size() - 1) { add_edge(ear_graph, ear[i], ear[i + 1]); }
		}
	}
	// TODO add print overload for vector<char>
	// TODO  get rid of set_intersection
	fo(u, graph.size()) {
		sort(al(ear_graph[u]));
		vector<ll> out;
		set_difference(al(graph[u]), al(ear_graph[u]), back_inserter(out));
		for (const auto x : out) {
			if (u < x) {
				bridges.push_back({u, x});
				if (graph[u].size() > 1) {
					art_points[u] = true;
				}
				if (graph[x].size() > 1) {
					art_points[x] = true;
				}
			}
		}
	}
	return {art_points, bridges};
};
#include "test_biconnected.hpp"
