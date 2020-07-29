#pragma core
#include "core/all.hpp"
pair<vector<char>, vector<array<ll, 2>>> biconnected(const GraphAdj &graph) {
	/*! Returns articulation points and bridges of \param graph. graph must be connected*/
	// TODO non-connected graph
	dfs d{graph};
	// TODO this should be fixed in dfs
	const ll root = 0;
	d.distance[root] = 0;
	d(root);
	auto low = d.distance;
	vector<char> articulations(graph.size());
	vector<array<ll, 2>> bridges;
	ll croot = 0;
	for (const auto v : rev(d.q)) {
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
	return {articulations, bridges};
}
GraphAdj permute(const vector<ll> &perm, const GraphAdj &graph) {
	/*! Return \param graph permuted by \param perm.*/
	GraphAdj pgraph(graph.size());
	fo(u, graph.size()) {
		for (auto v : graph[u]) {
			pgraph[perm[u]].push_back(perm[v]);
		}
	}
	return pgraph;
}
void test_biconnected() {
	// TODO test root case and 1/2 vertices
	constexpr auto make_triangle = [](auto &graph, const ll offset) -> void {
		add_edge(graph, offset + 0, offset + 1);
		add_edge(graph, offset + 0, offset + 2);
		add_edge(graph, offset + 1, offset + 2);
	};
	constexpr auto check = [](auto bicon, auto exp) -> bool {
		const auto [exp_art_vec, exp_bridge] = exp;
		const ll n = bicon.first.size();
		vector<char> exp_art(n);
		for (const auto i : exp.first) {
			exp_art[i] = true;
		}
		auto edge_graph = [&](auto edges) {
			GraphAdj graph(n);
			for (auto [u, v] : edges) {
				add_edge(graph, u, v);
			}
			return graph;
		};
		return bicon.first == exp_art && edge_graph(bicon.second) == edge_graph(exp_bridge);
	};
	auto test_all_perms = [](const GraphAdj &graph, const auto &test) {
		const ll n = graph.size();
		vl perm(n);
		iota(al(perm), 0LL);
		do {
			test(graph, perm);
		} while (next_permutation(al(perm)));
	};
	using Exp = pair<vector<ll>, vector<array<ll, 2>>>;
	auto make_test = [&](const auto &exp_func) {
		return [&](const auto &graph, const auto &perm) {
			const auto ret = biconnected(permute(perm, graph));
			assert(check(ret, exp_func(perm)));
		};
	};
	{
		GraphAdj graph(6);
		// Create two triangles
		make_triangle(graph, 0);
		add_edge(graph, 2, 3);
		make_triangle(graph, 3);
		test_all_perms(graph, make_test([](const auto perm) { return Exp{{perm[2], perm[3]}, {{perm[2], perm[3]}}}; }));
	}
	{
		GraphAdj graph(8);
		make_triangle(graph, 0);
		// Complete graph minus 3 to 4
		add_edge(graph, 2, 3);
		add_edge(graph, 2, 4);
		add_edge(graph, 4, 5);
		add_edge(graph, 3, 5);
		add_edge(graph, 2, 5);
		make_triangle(graph, 5);
		test_all_perms(graph, make_test([&](const auto perm) { return Exp{{perm[2], perm[5]}, {}}; }));
	}
	{
		GraphAdj graph(2);
		add_edge(graph, 0, 1);
		test_all_perms(graph, make_test([](const auto perm) { return Exp{{}, {{perm[0], perm[1]}}}; }));
	}
}
