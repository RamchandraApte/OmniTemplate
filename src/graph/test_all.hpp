#pragma once
#include "all.hpp"
#include "test_biconnected.hpp"
#include "test_bipartite.hpp"
#include "test_flow.hpp"
#include "tree/test_centroid.hpp"
namespace graph_theory::test {
void test_BFS() {
	GraphAdj g(4);
	add_edge(g, 0, 1);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);
	add_edge(g, 2, 3);
	BFS b{g};
	b(0);
	assert((b.parent == vector<ll>{-1, 0, 1, 1}));
	assert((b.distance == vector<ll>{0, 1, 2, 2}));
}
void test_trans() {
	assert((trans(GraphAdj{{2, 3}, {2, 1}, {2}, {2, 3, 1}}) == GraphAdj{{}, {1, 3}, {0, 1, 2, 3}, {0, 3}}));
	assert((trans(GraphAdj{}) == GraphAdj{}));
}
void test_shortest_dist() {
	matrix<ll> g{{7, 2, 5}, {2, 4, 1}, {3, 2, 5}};
	matrix<ll> short_dist{{4, 2, 3}, {2, 3, 1}, {3, 2, 3}};
	assert(shortest_dist(g) == short_dist);
	const auto n = g.rows_n;
	vector<vector<pr>> adj(n);
	fo(i, 0, n) {
		fo(j, 0, n) { adj[i].push_back({j, g[i][j]}); }
	}
	fo(s, 0, n) {
		// TODO test pv
		const auto dijkstra = shortest_dist(adj, s)[0];
		auto floyd = vector<ll>(short_dist[s], short_dist[s] + n);
		floyd[s] = 0;
		assert((dijkstra == floyd));
	}
}
void test_mst() {
	vector<edge> edges{{5, 0, 3}, {2, 1, 2}, {3, 1, 3}, {1, 3, 2}};
	auto ret = mst(edges, 6);
	sort(al(ret));
	assert((ret == vector<edge>{edges[3], edges[1], edges[0]}));
}
void test_scc() {
	GraphAdj g(5);
	g[0].push_back(3);
	g[3].push_back(1);
	g[1].push_back(2);
	g[2].push_back(0);
	g[0].push_back(4);
	g[2].push_back(4);
	const auto cm = scc(g);
	vector<ll> v{cm[0], cm[1], cm[2], cm[3]};
	// TODO refactor this into a function
	assert((all_of(al(v), [&](auto x) { return x == v[0]; })));
	assert(cm[4] != cm[0]);
}
void test_add_edge() {
	GraphAdj g(10);
	add_edge(g, 3, 4);
	add_edge(g, 6, 4);
	add_edge(g, 9, 2);
	// Order doesn't matter
	for (auto &x : g) {
		sort(al(x));
	}
	assert((g == GraphAdj{{}, {}, {9}, {4}, {3, 6}, {}, {4}, {}, {}, {2}}));
}
void test_graph_theory() {
	test_add_edge();
	test_trans();
	test_shortest_dist();
	test_mst();
	test_BFS();
	test_scc();
	test_tree_diameter();
	test_biconnected();
	test_flow();
	test_bipartite();
	test_sat2();
	test_graph_view();
	test_centroid_decomp();
}
} // namespace graph_theory::test
using namespace graph_theory::test;
