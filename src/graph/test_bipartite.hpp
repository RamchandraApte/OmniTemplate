#pragma once
#include "bipartite.hpp"
namespace graph_theory::bipartite::test {
void test_color2() {
	vector<vl> g(6);
	// (2,1,4) is one side, and (5,3,0) is another side
	// connected component 1
	add_edge(g, 2, 5);
	add_edge(g, 4, 5);
	add_edge(g, 4, 3);
	// connected component 2
	add_edge(g, 1, 0);
	add_edge(g, 4, 0);
	const auto col = color2(g).value();
	fo(i, 0, g.size()) {
		for (auto j : g[i]) {
			assert(col[i] ^ col[j]);
		}
	}
}
void test_max_match() {
	{
		vector<vl> g(3);
		// 0, 2 on one side, 1 on the other side
		add_edge(g, 0, 1);
		add_edge(g, 2, 1);
		assert((matching_size(max_match(g)) == 2 * 1));
	}
	{
		vector<vl> g(4);
		// 0, 2 on one side, 1, 3 on the other side
		add_edge(g, 0, 1);
		add_edge(g, 2, 1);
		add_edge(g, 2, 3);
		assert((matching_size(max_match(g)) == 2 * 2));
	}
	{
		vector<vl> g(6);
		// 0, 2, 4 on one side, 1, 3, 5 on the other side
		add_edge(g, 0, 1);
		add_edge(g, 0, 3);
		add_edge(g, 2, 3);
		add_edge(g, 2, 5);
		add_edge(g, 4, 1);
		add_edge(g, 4, 5);
		const auto matching = max_match(g);
		assert((matching_size(max_match(g)) == 2 * 3));
	}
	{
		vector<vl> g(6);
		// 0, 2, 4 on one side, 1, 3, 5 on the other side
		add_edge(g, 0, 1);
		add_edge(g, 0, 3);
		add_edge(g, 2, 1);
		add_edge(g, 2, 5);
		add_edge(g, 4, 1);
		add_edge(g, 4, 5);
		assert((matching_size(max_match(g)) == 2 * 3));
	}
	{
		vector<vl> g(6);
		// 0, 2, 4 on one side, 1, 3, 5 on the other side
		add_edge(g, 0, 1);
		add_edge(g, 2, 1);
		add_edge(g, 2, 5);
		add_edge(g, 4, 1);
		add_edge(g, 4, 5);
		assert((matching_size(max_match(g)) == 2 * 2));
	}
	{
		vector<vl> g(10);
		// 0, 2, 4 on one side, 1, 3, 5 on the other side
		fo(i, 0, g.size() / 2) {
			if (2 * i - 1 >= 0) {
				add_edge(g, 2 * i, 2 * i - 1);
			}
			if (2 * i + 1 < g.size()) {
				add_edge(g, 2 * i, 2 * i + 1);
			}
		}
		assert((matching_size(max_match(g)) == 2 * g.size() / 2));
	}
}
void test_bipartite() {
	test_color2();
	test_max_match();
}
} // namespace graph_theory::bipartite::test
using namespace graph_theory::bipartite::test;
