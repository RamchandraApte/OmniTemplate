#pragma once
#include "core.hpp"
#include "dsu.hpp"
#include "linear_algebra.hpp"
#include "utility.hpp"
struct edge {
	ll w, a, b;
	auto to_tuple() const { return tuple{w, a, b}; }
};
bool operator<(edge const &a, edge const &b) {
	return a.to_tuple() < b.to_tuple();
}
template <typename Stream> auto &operator<<(Stream &os, edge const &e) {
	return os << "edge{" << e.a << "-" << e.w << "->" << e.b << "}";
}
auto dist(vector<vector<pr>> g, ll s) {
	vl d(g.size(), inf), pv(g.size(), -1);
	pq<pr> q;
	d[s] = 0;
	fo(i, d.size()) { q.push({d[i], i}); }
	while (q.size()) {
		const auto &[di, a] = q.top();
		q.pop();
		if (di != d[a]) {
			continue;
		}
		for (const auto &pb : g[a]) {
			const auto &[b, w] = pb;
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
auto dist(mat<ll> const &g) {
	assert(g.r == g.c);
	auto n = g.r;
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
auto mst(vector<edge> es) {
	//*! Returns the minimum spanning tree of the set of edges es, as a set
	// of edges*/
	sort(al(es));
	auto mi = -inf;
	for (const auto &e : es) {
		mi = max(mi, max(e.a, e.b));
	}
	dsu d{mi + 1};
	tp(es) ret;
	for (const auto &e : es) {
		if (d(e.a, e.b)) {
			continue;
		}
		ret.pb(e);
	}
	return ret;
}
struct gsearch {
	/*! Generalized graph searcher/visitor*/
	vc<vl> const &g;
	ll n;
	vl v;
	deque<ll> q;
	vl p, d;
	gsearch(const vector<vector<ll>> &g_)
	    : g(g_), n(size(g)), v(n), p(n, -1), d(n) {}
	virtual void operator()(ll) = 0;
	void operator()() {
		fo(i, n) {
			if (!v[i]) {
				this(i);
			}
		}
	}
	auto add(ll j, ll i) {
		d[j] = d[i] + 1;
		p[j] = i;
	}
};
#define searcher                                                               \
      public                                                                   \
	gsearch {                                                              \
		using gsearch::operator(), gsearch::gsearch;                   \
		void operator()(ll s)
struct dfs : searcher {
	/*! Depth-first search */
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
}
;
struct bfs : searcher {
	/*! Breadth-first search*/
	q.pb(s);
	for (ll idx = 0; idx < q.size(); ++idx) {
		auto i = q[idx];
		if (v[i]) {
			continue;
		}
		v[i] = true;
		for (const auto &j : g[i]) {
			q.pb(j);
			add(j, i);
		}
	}
}
}
;
auto trans(const vc<vl> &g) {
	ll n = size(g);
	vc<vl> h(n);
	fo(i, n) {
		for (ll j : g[i]) {
			h[j].pb(i);
		}
	}
	return h;
}
auto scc(const vc<vl> &g) {
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
auto bipartite(const vc<vl> &g) {
	/*! Returns a bipartite coloring if possible */
	bfs b{g};
	b();
	auto n = size(g);
	vl s(n);
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
auto max_match(const vc<vl> &g) {
	/*! Returns a maximum matching of g*/
	auto s = bipartite(g).value();
	ll n = g.size();
	vl m(n, -1);
	for (ll md = -1; md != inf;) {
		vl v(n);
		vc<vl> h(n);
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
auto add_edge(vc<vl> &g, ll u, ll v) {
	/*! Adds edge \f$u \leftrightarrow v\f$ to graph g*/
	g[u].pb(v);
	g[v].pb(u);
}
auto graph_in(vc<vl> &g, ll m) {
	/*! Reads 1-indexed list of edges into graph g*/
	fo(i, 0, m) {
		I(u);
		I(v);
		add_edge(g, --u, --v);
	}
}
