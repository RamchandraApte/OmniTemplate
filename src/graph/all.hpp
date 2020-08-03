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
		auto floyd = vl(short_dist[s], short_dist[s] + n);
		floyd[s] = 0;
		assert((dijkstra == floyd));
	}
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
void test_mst() {
	vector<edge> edges{{5, 0, 3}, {2, 1, 2}, {3, 1, 3}, {1, 3, 2}};
	auto ret = mst(edges, 6);
	sort(al(ret));
	assert((ret == vector<edge>{edges[3], edges[1], edges[0]}));
}
/*! Generalized graph searcher/visitor*/
template <typename Searcher> struct GeneralSearch {
	vector<vl> const &graph;
	vc<char> visited; //!< Whether vertex idx is visited
	deque<ll> q;	  //!< Queue
	vl parent;	  //!< Parent of vertex idx
	vl distance;	  //!< Distance from source to vertex idx
	GeneralSearch(const vector<vector<ll>> &g_) : graph(g_), visited(graph.size()), parent(graph.size(), -1), distance(graph.size(), inf) {}
	// virtual void operator()(ll) = 0;
	void operator()() {
		/* Run the searcher on all vertices. Useful for visiting the
		 * entire graph, and not just one connected component. */
		fo(i, graph.size()) {
			if (!visited[i]) {
				(*static_cast<Searcher *>(&this))(i);
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
	for (auto idx : rev(search.q)) {
		if (search.parent[idx] != -1) {
			sz[search.parent[idx]] += sz[idx];
		}
	}
	return sz;
}
/*! Depth-first search */
struct DFS : public GeneralSearch<DFS> {
	using GeneralSearch::operator(), GeneralSearch::GeneralSearch;
	void operator()(const ll source) {
		visited[source] = true;
		for (const auto &j : graph[source]) {
			if (visited[j]) {
				continue;
			}
			add(j, source);
			this(j);
		}
		q.push_front(source);
	}
};
/*! Breadth-first search*/
struct BFS : public GeneralSearch<BFS> {
	using GeneralSearch::operator(), GeneralSearch::GeneralSearch;
	void operator()(ll source) {
		ll old_size = q.size();
		q.push_back(source);
		visited[source] = true;
		distance[source] = 0;
		for (ll idx = old_size; idx < q.size(); ++idx) {
			auto i = q[idx];
			for (const auto &j : graph[i]) {
				if (visited[j]) {
					continue;
				}
				q.push_back(j);
				visited[j] = true;
				add(j, i);
			}
		}
	}
};
void test_BFS() {
	vector<vl> g(4);
	add_edge(g, 0, 1);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);
	add_edge(g, 2, 3);
	BFS b{g};
	b(0);
	assert((b.parent == vl{-1, 0, 1, 1}));
	assert((b.distance == vl{0, 1, 2, 2}));
}
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
void test_trans() {
	assert((trans(vector<vl>{{2, 3}, {2, 1}, {2}, {2, 3, 1}}) ==
		vector<vl>{{}, {1, 3}, {0, 1, 2, 3}, {0, 3}}));
	assert((trans(vector<vl>{}) == vector<vl>{}));
}
#include "biconnected.hpp"
#include "bipartite.hpp"
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
	for (ll i : s.q) {
		assign(i, i);
	}
	return cm;
}
void test_scc() {
	vector<vl> g(5);
	g[0].push_back(3);
	g[3].push_back(1);
	g[1].push_back(2);
	g[2].push_back(0);
	g[0].push_back(4);
	g[2].push_back(4);
	const auto cm = scc(g);
	vl v{cm[0], cm[1], cm[2], cm[3]};
	// TODO refactor this into a function
	assert((all_of(al(v), [&](auto x) { return x == v[0]; })));
	assert(cm[4] != cm[0]);
}
void test_add_edge() {
	vector<vl> g(10);
	add_edge(g, 3, 4);
	add_edge(g, 6, 4);
	add_edge(g, 9, 2);
	// Order doesn't matter
	for (auto &x : g) {
		sort(al(x));
	}
	assert(
	    (g == vector<vl>{{}, {}, {9}, {4}, {3, 6}, {}, {4}, {}, {}, {2}}));
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
void test_graph_theory() {
	test_add_edge();
	test_trans();
	test_shortest_dist();
	test_mst();
	test_BFS();
	test_bipartite();
	test_scc();
	test_max_match();
	test_tree_diameter();
	test_biconnected();
}
} // namespace graph_theory
using namespace graph_theory;
