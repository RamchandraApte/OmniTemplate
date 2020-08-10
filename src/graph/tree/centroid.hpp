#pragma once
#include "core/all.hpp"
#include "graph/graph_view.hpp"
/** @brief Centroid decomposition of a tree.
 *  @returns cent_lvl where cent_lvl[i][j] is the jth centroid on the path from the root to i*/
template <typename Graph> vector<vector<ll>> centroid_decomp(const Graph &tree) {
	vector<vector<ll>> cent_lvl(tree.size());
	//! Whether we have visited this node as a centroid
	vector<ll> vis_cent(tree.size());
	auto rec_decomp = fix{[&](const auto &rec_decomp, const ll u, const ll lvl) -> void {
		// Decompose the subtree beginning on u
		const auto pred = [&](const ll u, const ll v) { return !vis_cent[u] && !vis_cent[v]; };
		Subgraph sub{tree, pred};
		DFS dfs{sub};
		dfs(u);
		const auto sz = get_size(dfs);
		vector<ll> max_child_sz(tree.size(), -inf);
		/*! Set up max_child*/
		for (const auto x : rev(dfs.queue)) {
			if (dfs.parent[x] != -1) {
				max_eq(max_child_sz[dfs.parent[x]], sz[x]);
				max_eq(max_child_sz[x], sz[u] - sz[x]);
			}
		}
		const auto find_centroid = [&]() {
			for (const auto x : rev(dfs.queue)) {
				if (2 * max_child_sz[x] <= sz[u]) {
					return x;
				}
			}
			assert(("There should be a centroid", false));
		};
		const auto centroid = find_centroid();
		vis_cent[centroid] = true;
		for (const auto x : dfs.queue) {
			cent_lvl[x].push_back(centroid);
		}
		for (const auto v : tree[centroid]) {
			if (!vis_cent[v]) {
				rec_decomp(v, lvl + 1);
			}
		}
	}};
	rec_decomp(0, 0);
	assert(all_of(al(vis_cent), [](const auto x) { return x; }));
	return cent_lvl;
}
