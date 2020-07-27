#pragma once
#include "core/all.hpp"
pair<array<ll, 2>, ll> tree_diameter(const vector<vector<ll>> &g) {
	/*! Returns diameter and center of a tree :param: g*/
	bfs b{g};
	b();
	const auto u = b.q.back();
	bfs b2{g};
	b2(u);
	const auto v = b2.q.back();
	auto c = v;
	fo(i, b2.distance[v] / 2) { c = b2.parent[c]; }
	return {{u, v}, c};
}
void test_tree_diameter() {
	{
		vector<vector<ll>> graph(5);
		add_edge(graph, 1, 3);
		add_edge(graph, 3, 2);
		add_edge(graph, 2, 0);
		add_edge(graph, 0, 4);
		auto ret = tree_diameter(graph);
		sort(al(ret.first));
		assert((ret.first == array<ll, 2>{1, 4}));
		assert(ret.second == 2);
	}
	{
		vector<vector<ll>> graph(5);
		add_edge(graph, 1, 3);
		add_edge(graph, 3, 2);
		add_edge(graph, 2, 0);
		add_edge(graph, 3, 4);
		auto ret = tree_diameter(graph).first;
		sort(al(ret));
		assert(ret[0] == 0);
	}
}
