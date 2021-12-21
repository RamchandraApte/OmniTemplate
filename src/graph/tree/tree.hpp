#pragma once
#include "core/all.hpp"
/*! @brief Find tree diameter.
 * @returns Returns diameter and center of a tree :param: g*/
pair<array<ll, 2>, ll> tree_diameter(const GraphAdj &g) {
	BFS b{g};
	b();
	const auto u = b.queue.back();
	BFS b2{g};
	b2(u);
	const auto v = b2.queue.back();
	auto c = v;
	fo(i, b2.distance[v] / 2) { c = b2.parent[c]; }
	return {{u, v}, c};
}
// TODO this test function should be in a separate file
void test_tree_diameter() {
	{
		GraphAdj graph(5);
		graph.add_edge(1, 3);
		graph.add_edge(3, 2);
		graph.add_edge(2, 0);
		graph.add_edge(0, 4);
		auto ret = tree_diameter(graph);
		sort(al(ret.first));
		assert((ret.first == array<ll, 2>{1, 4}));
		assert(ret.second == 2);
	}
	{
		GraphAdj graph(5);
		graph.add_edge(1, 3);
		graph.add_edge(3, 2);
		graph.add_edge(2, 0);
		graph.add_edge(3, 4);
		auto ret = tree_diameter(graph).first;
		sort(al(ret));
		assert(ret[0] == 0);
	}
}
