#pragma once
#include "algebra/linear_algebra.hpp"
#include "core/all.hpp"
#include "ds/dsu.hpp"
namespace graph_theory {
//!< Adjacency-list representation of graph
using GraphAdj = vector<vector<ll>>;
//!< Edge with weight weight from a to b
struct edge {
	ll weight, a, b;
	auto to_tuple() const { return tuple{weight, a, b}; }
};
bool operator<(edge const &a, edge const &b) {
	/*! Compare the edges by weight, with ties compared by a and b*/
	return a.to_tuple() < b.to_tuple();
}
bool operator==(edge const &a, edge const &b) {
	return a.to_tuple() == b.to_tuple();
}
template <typename Stream> auto &operator<<(Stream &os, edge const &e) {
	/*! Print the edge*/
	return os << "edge{" << e.a << "-(" << e.weight << ")>" << e.b << "}";
}
auto add_edge(vector<vl> &graph, ll u, ll v) {
	/*! Adds edge \f$u \leftrightarrow v\f$ to graph graph*/
	graph[u].push_back(v);
	graph[v].push_back(u);
}
auto shortest_dist(vector<vector<pr>> graph, ll source) {
	/*! Given an adjacency-list of a graph, returns the shortest distance to
	 * each vertex from the source. Algorithm: Dijkstra*/
	vl d(graph.size(), inf), pv(graph.size(), -1);
	prio_queue_t<pr, greater<>> q;
	d[source] = 0;
	fo(i, d.size()) { q.push({d[i], i}); }
	while (q.size()) {
		const auto [di, a] = q.top();
		q.pop();
		if (di != d[a]) {
			continue;
		}
		for (const auto &edge : graph[a]) {
			const auto &[b, w] = edge;
			auto &x = d[b];
			auto nw = di + w;
			if (nw < x) {
				pv[b] = a;
				x = nw;
				q.push({x, b});
			}
		}
	}
	return array<vl, 2>{d, pv};
}
/*! Given a 2D matrix of distances for each edge in g, returns a 2D
    * matrix of the shortest distances. We do not consider paths of length
    * zero. Algorithm: Floyd-Warshall*/
// TODO do we want to consider zero-length paths?
auto shortest_dist(matrix<ll> const &graph) {
	assert(graph.rows_n == graph.cols_n);
	auto n = graph.rows_n;
	auto d = graph;
	fo(k, n) {
		fo(i, n) {
			fo(j, n) {
				auto &x = d[i][j];
				x = min(x, d[i][k] + d[k][j]);
			}
		}
	}
	return d;
}
/*! Returns the minimum spanning forest of the set of edges es, as a set of edges*/
auto mst(vector<edge> edges, const ll n) {
	sort(al(edges));
	dsu d{n};
	vector<edge> ret;
	for (const auto &e : edges) {
		if (!d.join(e.a, e.b)) {
			continue;
		}
		ret.push_back(e);
	}
	return ret;
}
/*! Generalized graph searcher/visitor*/
template <typename Searcher, typename Graph> struct GeneralSearch {
	Graph const &graph;
	vc<char> visited; //!< Whether vertex idx is visited
	deque<ll> queue;  //!< Queue
	vl parent;	  //!< Parent of vertex idx
	vl distance;	  //!< Distance from source to vertex idx
	GeneralSearch(const Graph &g_) : graph(g_), visited(graph.size()), parent(graph.size(), -1), distance(graph.size(), inf) {}
	void operator()() {
		/* Run the searcher on all vertices. Useful for visiting the
		 * entire graph, and not just one connected component. */
		fo(i, graph.size()) {
			if (!visited[i]) {
				(static_cast<Searcher &>(this))(i);
			}
		}
	}
	void add(const ll child, const ll par) {
		/*! Add vertex j as a child of already visited vertex i in the
		 * searcher tree*/
		distance[child] = distance[par] + 1;
		parent[child] = par;
	}
};
/*! Given a searcher object, returns an array containing the size of each subtree */
template <typename Searcher> vector<ll> get_size(const Searcher &search) {
	vector<ll> sz(search.parent.size(), 1);
	for (auto idx : rev(search.queue)) {
		if (search.parent[idx] != -1) {
			sz[search.parent[idx]] += sz[idx];
		}
	}
	return sz;
}
/*! Depth-first search */
template <typename Graph = GraphAdj> struct DFS : public GeneralSearch<DFS<Graph>, Graph> {
	using GeneralSearch_t = GeneralSearch<DFS, Graph>;
	using GeneralSearch_t::operator(), GeneralSearch_t::GeneralSearch;
	void operator()(const ll source) {
		this.visited[source] = true;
		for (const auto &j : this.graph[source]) {
			if (this.visited[j]) {
				continue;
			}
			this.add(j, source);
			this(j);
		}
		this.queue.push_front(source);
	}
};
template <typename Graph> DFS(Graph) -> DFS<Graph>;
/*! Breadth-first search*/
template <typename Graph = GraphAdj> struct BFS : GeneralSearch<BFS<Graph>, Graph> {
	using GeneralSearch_t = GeneralSearch<BFS, Graph>;
	using GeneralSearch_t::operator(), GeneralSearch_t::GeneralSearch;
	void operator()(const ll source) {
		ll old_size = this.queue.size();
		this.queue.push_back(source);
		this.visited[source] = true;
		this.distance[source] = 0;
		for (ll idx = old_size; idx < this.queue.size(); ++idx) {
			auto i = this.queue[idx];
			for (const auto &j : this.graph[i]) {
				if (this.visited[j]) {
					continue;
				}
				this.queue.push_back(j);
				this.visited[j] = true;
				this.add(j, i);
			}
		}
	}
};
template <typename Graph> BFS(Graph) -> BFS<Graph>;
/** Returns the transpose graph of directed graph */
auto trans(const vector<vl> &graph) {
	ll n = size(graph);
	vector<vl> h(n);
	fo(i, n) {
		for (ll j : graph[i]) {
			h[j].push_back(i);
		}
	}
	return h;
}
#include "biconnected.hpp"
#include "flow.hpp"
#include "graph_view.hpp"
#include "test_flow.hpp"
#include "tree/tree.hpp"
auto scc(const vector<vl> &graph) {
	/*! Returns the strongly connected component for each vertex of the
	 * graph g.*/
	auto h = trans(graph);
	vl cm(size(graph), -1);
	auto assign = fix{[&](const auto &assign, ll u, ll c) -> void {
		if (cm[u] != -1) {
			return;
		}
		cm[u] = c;
		for (ll v : h[u]) {
			assign(v, c);
		}
	}};
	DFS s{graph};
	s();
	for (ll i : s.queue) {
		assign(i, i);
	}
	return cm;
}
auto graph_in(vector<vl> &g, ll m) {
	/*! Reads 1-indexed list of edges into graph g*/
	fo(i, 0, m) {
		I(u);
		I(v);
		add_edge(g, --u, --v);
	}
}
/*vector<vector<ll>> chain_decomposition(const vector<vector<ll>>& graph){
	DFS d{graph};
	d();
}*/
} // namespace graph_theory
using namespace graph_theory;
#include "bipartite.hpp"
