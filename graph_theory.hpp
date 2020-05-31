#pragma once
#include "core.hpp"
#include "dsu.hpp"
#include "linear_algebra.hpp"
// TODO get stuff below into namespace
struct edge {
	ll w, a, b;
	auto to_tuple() const { return tuple{w, a, b}; }
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
	return os << "edge{" << e.a << "-(" << e.w << ")>" << e.b << "}";
}
namespace graph_theory {
auto add_edge(vector<vl> &g, ll u, ll v) {
	/*! Adds edge \f$u \leftrightarrow v\f$ to graph g*/
	g[u].pb(v);
	g[v].pb(u);
}
auto dist(vector<vector<pr>> g, ll s) {
	/*! Given an adjacency-list of a graph, returns the shortest distance to
	 * each vertex from the source. Algorithm: Dijkstra*/
	vl d(g.size(), inf), pv(g.size(), -1);
	pq<pr> q;
	d[s] = 0;
	fo(i, d.size()) { q.push({d[i], i}); }
	while (q.size()) {
		const auto [di, a] = q.top();
		q.pop();
		dbg(a);
		if (di != d[a]) {
			continue;
		}
		for (const auto &pb : g[a]) {
			// TODO Why doesn't the macro pb expand?
			const auto &[b, w] = pb;
			auto &x = d[b];
			auto nw = di + w;
			dbg(di);
			dbg(nw);
			dbg(b);
			if (nw < x) {
				pv[b] = a;
				x = nw;
				q.push({x, b});
			}
		}
	}
	return array<vl, 2>{d, pv};
}
auto dist(matrix<ll> const &g) {
	/*! Given a 2D matrix of distances for each edge in g, returns a 2D
	 * matrix of the shortest distances. We do not consider paths of length
	 * zero. Algorithm: Floyd-Warshall*/
	// TODO do we want to consider zero-length paths?
	assert(g.rows_n == g.cols_n);
	auto n = g.rows_n;
	auto d = g;
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
void test_dist() {
	matrix<ll> g{{7, 2, 5}, {2, 4, 1}, {3, 2, 5}};
	matrix<ll> short_dist{{4, 2, 3}, {2, 3, 1}, {3, 2, 3}};
	dbg(dist(g));
	dbg(short_dist);
	assert(dist(g) == short_dist);
	const auto n = g.rows_n;
	vector<vector<pr>> adj(n);
	fo(i, 0, n) {
		fo(j, 0, n) { adj[i].pb({j, g[i][j]}); }
	}
	fo(s, 0, n) {
		// TODO test pv
		const auto dijkstra = dist(adj, s)[0];
		auto floyd = vl(short_dist[s], short_dist[s] + n);
		floyd[s] = 0;
		dbg(dijkstra);
		dbg(floyd);
		assert((dijkstra == floyd));
	}
}
auto mst(vector<edge> es) {
	/*! Returns the minimum spanning tree of the set of edges es, as a set
	 * of edges*/
	// TODO what happens if no MST?
	sort(al(es));
	auto mi = -inf;
	for (const auto &e : es) {
		mi = max(mi, max(e.a, e.b));
	}
	dsu d{mi + 1};
	vector<edge> ret;
	for (const auto &e : es) {
		if (!d(e.a, e.b)) {
			continue;
		}
		ret.pb(e);
	}
	return ret;
}
void test_mst() {
	vector<edge> edges{{5, 0, 3}, {2, 1, 2}, {3, 1, 3}, {1, 3, 2}};
	auto ret = mst(edges);
	sort(al(ret));
	dbg(ret);
	assert((ret == vector<edge>{edges[3], edges[1], edges[0]}));
}
struct gsearch {
	/*! Generalized graph searcher/visitor*/
	vector<vl> const &g;
	ll n;
	vl v;
	deque<ll> q;
	vl p, d;
	gsearch(const vector<vector<ll>> &g_)
	    : g(g_), n(size(g)), v(n), p(n, -1), d(n) {}
	virtual void operator()(ll) = 0;
	void operator()() {
		/* Run the searcher on all vertices. Useful for visiting the
		 * entire graph, and not just one connected component. */
		fo(i, n) {
			if (!v[i]) {
				this(i);
			}
		}
	}
	auto add(ll j, ll i) {
		/*! Add vertex j as a child of already visited vertex i in the
		 * searcher tree*/
		d[j] = d[i] + 1;
		p[j] = i;
	}
};
/*! Depth-first search */
struct dfs : public gsearch {
	using gsearch::operator(), gsearch::gsearch;
	void operator()(ll s) {
		v[s] = true;
		for (const auto &j : g[s]) {
			if (v[j]) {
				continue;
			}
			add(j, s);
			this(j);
		}
		q.push_front(s);
	}
};
/*! Breadth-first search*/
struct bfs : public gsearch {
	using gsearch::operator(), gsearch::gsearch;
	void operator()(ll s) {
		ll old_size = q.size();
		q.pb(s);
		v[s] = true;
		for (ll idx = old_size; idx < q.size(); ++idx) {
			auto i = q[idx];
			for (const auto &j : g[i]) {
				if (v[j]) {
					continue;
				}
				q.pb(j);
				v[j] = true;
				add(j, i);
			}
		}
	}
};
void test_bfs() {
	vector<vl> g(4);
	add_edge(g, 0, 1);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);
	add_edge(g, 2, 3);
	bfs b{g};
	b(0);
	dbg(b.p);
	assert((b.p == vl{-1, 0, 1, 1}));
	assert((b.d == vl{0, 1, 2, 2}));
}
auto trans(const vector<vl> &g) {
	ll n = size(g);
	vector<vl> h(n);
	fo(i, n) {
		for (ll j : g[i]) {
			h[j].pb(i);
		}
	}
	return h;
}
void test_trans() {
	assert((trans(vector<vl>{{2, 3}, {2, 1}, {2}, {2, 3, 1}}) ==
		vector<vl>{{}, {1, 3}, {0, 1, 2, 3}, {0, 3}}));
	assert((trans(vector<vl>{}) == vector<vl>{}));
}
auto scc(const vector<vl> &g) {
	/*! Returns the strongly connected component for each vertex of the
	 * graph g.*/
	auto h = trans(g);
	dbg(h);
	vl cm(size(g), -1);
	auto assign = fix{[&](const auto &assign, ll u, ll c) -> void {
		dbg(u);
		if (cm[u] != -1) {
			return;
		}
		cm[u] = c;
		for (ll v : h[u]) {
			assign(v, c);
		}
	}};
	dfs s{g};
	s();
	dbg(s.q);
	for (ll i : s.q) {
		assign(i, i);
	}
	return cm;
}
void test_scc() {
	vector<vl> g(5);
	g[0].pb(3);
	g[3].pb(1);
	g[1].pb(2);
	g[2].pb(0);
	g[0].pb(4);
	g[2].pb(4);
	const auto cm = scc(g);
	vl v{cm[0], cm[1], cm[2], cm[3]};
	// TODO refactor this into a function
	assert((all_of(al(v), [&](auto x) { return x == v[0]; })));
	assert(cm[4] != cm[0]);
}
auto bipartite(const vector<vl> &g) {
	/*! Returns a bipartite coloring if possible */
	bfs b{g};
	b();
	auto n = size(g);
	vl s(n);
	dbg(b.p);
	for (auto i : b.q) {
		if (auto x = b.p[i]; x != -1) {
			s[i] = !s[x];
		}
	}
	bool bi = true;
	fo(i, n) {
		for (auto j : g[i]) {
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
auto max_match(const vector<vl> &g) {
	/*! Returns a maximum matching of g*/
	auto s = bipartite(g).value();
	ll n = g.size();
	vl m(n, -1);
	for (ll md = -1; md != inf;) {
		vl v(n);
		vector<vl> h(n);
		fo(i, n) {
			for (ll j : g[i]) {
				if ((j == m[i]) == s[i]) {
					h[i].pb(j);
				}
			}
		}
		bfs b{h};
		b();
		md = inf;
		fo(i, n) {
			if (s[i] == 1 && m[i] == -1) {
				md = min(md, b.d[i]);
			}
		}
		dbg(md);
		dbg(b.d);
		dbg(m);
		dbg(s);
		auto path = fix{[&](const auto &path, ll i) -> bool {
			dbg(i);
			if (v[i]) {
				return false;
			}
			v[i] = true;
			if (s[i] == 1 && m[i] == -1 && b.d[i] == md) {
				return true;
			}
			for (ll j : g[i]) {
				if (b.d[j] == b.d[i] + 1) {
					if (dbg(path(j))) {
						dbg(j);
						if (s[i] == 0) {
							m[i] = j;
							m[j] = i;
						}
						return true;
					}
				}
			}
			return false;
		}};
		fo(i, n) {
			if (s[i] == 0 && m[i] == -1) {
				path(i);
			}
		}
	}
	return m;
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
void test_graph_theory() {
	test_add_edge();
	test_trans();
	test_dist();
	test_mst();
	test_bfs();
	test_bipartite();
	test_scc();
}
} // namespace graph_theory
using namespace graph_theory;
