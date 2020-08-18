#pragma once
#include "core/all.hpp"
namespace graph_theory::bipartite {
/*! Returns a bipartite coloring if possible */
auto color2(const GraphAdj &graph) {
	BFS b{graph};
	b();
	auto n = size(graph);
	vector<ll> s(n);
	for (auto i : b.queue) {
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
/*! Returns a maximum matching of bipartite graph using the
 * Hopcroft-Karp algorithm.*/
auto max_match(const GraphAdj &graph) {
	auto side = color2(graph).value();
	ll n = graph.size();
	vector<ll> match(n, -1);
	while (true) {
		/* Construct a directed graph to find aug_pathmenting paths*/
		// TODO refactor this to use lazy graphs
		GraphAdj aug_path(n + 2);
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
		vector<ll> vis(aug_path.size());
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
 * @param matching must be a a vector where idx is matched with matching[idx], or not matched if
 * matching[idx] = -1
 */
ll matching_size(const vector<ll> &matching) {
	return count_if(al(matching), [&](const auto x) { return x != -1; });
}
} // namespace graph_theory::bipartite
using namespace graph_theory::bipartite;
