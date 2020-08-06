#pragma once
#include "biconnected.hpp"
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
GraphAdj graph_disunion(const GraphAdj &a, const GraphAdj &b) {
	auto ret = a;
	ret.resize(a.size() + b.size());
	fo(u, b.size()) {
		for (const auto v : b[u]) {
			ret[a.size() + u].push_back(a.size() + v);
		}
	}
	return ret;
}
void test_biconnected() {
	// FIXME
	if (true) {
		return;
	}
	// TODO disconnected case
	// TODO test ear decomp
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
	auto test_random_perms = [](const GraphAdj &graph, const auto &test, ll num = 1e4) {
		const ll n = graph.size();
		vl perm(n);
		iota(al(perm), 0LL);
		fo(i, num) {
			shuffle(al(perm), reng);
			test(graph, perm);
		}
	};
	using Exp = pair<vector<ll>, vector<array<ll, 2>>>;
	auto make_test = [&](const auto &exp_func) {
		return [&](const auto &graph, const auto &perm) {
			const auto check_func = [&, permuted = permute(perm, graph)](const auto &func) { assert(check(func(permuted), exp_func(perm))); };
			check_func(biconnected);
			check_func(biconnected_ear);
		};
	};

	GraphAdj graph_t1(6);
	// Create two triangles
	make_triangle(graph_t1, 0);
	add_edge(graph_t1, 2, 3);
	make_triangle(graph_t1, 3);
	test_all_perms(graph_t1, make_test([](const auto perm) { return Exp{{perm[2], perm[3]}, {{perm[2], perm[3]}}}; }));

	GraphAdj graph_t2(8);
	make_triangle(graph_t2, 0);
	// Complete graph minus 3 to 4
	add_edge(graph_t2, 2, 3);
	add_edge(graph_t2, 2, 4);
	add_edge(graph_t2, 4, 5);
	add_edge(graph_t2, 3, 5);
	add_edge(graph_t2, 2, 5);
	make_triangle(graph_t2, 5);
	test_all_perms(graph_t2, make_test([&](const auto perm) { return Exp{{perm[2], perm[5]}, {}}; }));

	GraphAdj graph2(2);
	add_edge(graph2, 0, 1);
	test_all_perms(graph2, make_test([](const auto perm) { return Exp{{}, {{perm[0], perm[1]}}}; }));

	GraphAdj graph1(1);
	test_all_perms(graph1, make_test([](const auto perm) { return Exp{{}, {}}; }));

	// Disconnect graph, union of 1 and 2
	const auto graph_dis = graph_disunion(graph_t1, graph_t2);
	test_random_perms(graph_dis, make_test([&](const auto perm) { return Exp{{perm[2], perm[3], perm[graph_t1.size() + 2], perm[graph_t1.size() + 5]}, {{perm[2], perm[3]}}}; }));
}
