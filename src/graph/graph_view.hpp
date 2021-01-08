#pragma once
#include "core/all.hpp"
/*! \brief Filters graph by a predicate.
 * \tparam Graph graph type
 * \tparam Pred Predicate functor type */
template <typename Graph, typename Pred> struct Subgraph {
	const Graph &graph;
	const Pred &pred;
	explicit Subgraph(const Graph &graph_arg, const Pred &pred_arg)
	    : graph{graph_arg}, pred{pred_arg} {}
	struct iterator : it_base<ll> {
		const Subgraph &subgraph;
		const ll i;
		const vector<ll> &adj_list;
		vector<ll>::const_iterator it;
		explicit iterator(const Subgraph &subgraph_arg, const ll i_arg)
		    : subgraph{subgraph_arg}, i{i_arg}, adj_list{subgraph.graph[i]},
		      it{adj_list.begin()} {
			advance();
		}
		void advance() {
			for (; it != adj_list.end() && !subgraph.pred(i, *it); ++it) {
			}
		}
		ll operator*() const { return *it; }
		void operator++() {
			++it;
			advance();
		}
		bool operator==(const iterator &oth) const { return it == oth.it; }
		// FIXME should be genericized for all classes
		bool operator!=(const iterator &oth) const { return !(*this == oth); }
	};
	range<iterator> operator[](const ll i) const {
		iterator st_it{*this, i};
		iterator ed_it{*this, i};
		ed_it.it = ed_it.adj_list.end();
		return range<iterator>{st_it, ed_it};
	}
	ll size() const { return graph.size(); }
};
void test_graph_view() {
	GraphAdj g(5);
	fo(i, g.size()) {
		fo(j, i + 1, g.size()) { add_edge(g, i, j); }
	}
	const auto pred = [](const ll i, const ll j) { return i % 2 == j % 2; };
	Subgraph subgraph{g, pred};
	fo(i, g.size()) {
		for (const auto j : subgraph[i]) {
			assert(pred(i, j));
		}
	}

	BFS bfs{subgraph};
	bfs(0);
	fo(i, g.size()) { assert(bfs.visited[i] == (i % 2 == 0)); }
}
