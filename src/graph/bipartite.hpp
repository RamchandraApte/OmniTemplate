#pragma once
#include "core/all.hpp"
auto bipartite(const vector<vl> &graph) {
	/*! Returns a bipartite coloring if possible */
	BFS b{graph};
	b();
	auto n = size(graph);
	vl s(n);
	for (auto i : b.q) {
		if (const auto par = b.parent[i]; par != -1) {
			s[i] = !s[par];
		}
	}
	bool bi = true;
	fo(i, n) {
		for (const auto j : graph[i]) {
			bi &= s[i] != s[j];
		}
	}
	return bi ? optional{s} : nullopt;
}
void test_bipartite() {
	vector<vl> g(6);
	// (2,1,4) is one side, and (5,3,0) is another side
	// connected component 1
	add_edge(g, 2, 5);
	add_edge(g, 4, 5);
	add_edge(g, 4, 3);
	// connected component 2
	add_edge(g, 1, 0);
	add_edge(g, 4, 0);
	const auto col = bipartite(g).value();
	fo(i, 0, g.size()) {
		for (auto j : g[i]) {
			assert(col[i] ^ col[j]);
		}
	}
}
/*! Returns a maximum matching of bipartite graph using the
 * Hopcroft-Karp algorithm.*/
auto max_match(const vector<vl> &graph) {
	auto side = bipartite(graph).value();
	ll n = graph.size();
	vl match(n, -1);
	while (true) {
		/* Construct a directed graph to find aug_pathmenting paths*/
		// TODO refactor this to use lazy graphs
		vector<vl> aug_path(n + 2);
		const auto dummy_a = n;
		const auto dummy_b = n + 1;
		fo(i, n) {
			for (ll j : graph[i]) {
				if ((j == match[i]) == side[i]) {
					aug_path[i].push_back(j);
				}
			}
		}
		fo(i, n) {
			if (match[i] != -1) {
				continue;
			}
			if (side[i]) {
				aug_path[i].push_back(dummy_b);
			} else {
				aug_path[dummy_a].push_back(i);
			}
		}
		BFS b{aug_path};
		b(dummy_a);
		if (b.distance[dummy_b] == inf) {
			break;
		}
		vl vis(aug_path.size());
		auto path = fix{[&](const auto &path, ll i) -> bool {
			if (vis[i]) {
				return false;
			}
			vis[i] = true;
			if (i == dummy_b) {
				return true;
			}
			for (ll j : aug_path[i]) {
				if (b.distance[j] == b.distance[i] + 1) {
					if (path(j)) {
						if (i < n && j < n) {
							match[i] = j;
							match[j] = i;
						}
						return true;
					}
				}
			}
			return false;
		}};
		path(dummy_a);
	}
	return match;
}
/*! @brief Returns the size of the matching.
 * @param matching must be a a vector where idx is matched with matching[idx], or not matched if matching[idx] = -1
 */
ll matching_size(const vl &matching) {
	return count_if(al(matching), [&](const auto x) { return x != -1; });
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
