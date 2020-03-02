struct edge {
	ll w, a, b;
	_ to_tuple() const{
		return tuple{w,a,b};
	}
};
bool operator<(edge const& a, edge const& b){
	return a.to_tuple() < b.to_tuple();
}
_& operator<<(ostream& os, edge const& e){
	return os<<"edge{"<<e.a<<"-"<<e.w<<"->"<<e.b<<"}";
}
_ dist(_ g, _ s){
	vl d(g.size(),inf), pv(g.size(),-1);
	pq<pr> q;
	d[s] = 0;
	fo(i,d.size()){
		q.push({d[i], i});
	}
	while(q.size()){
		$ [di, a] = q.top();
		q.pop();
		if(di != d[a]){continue;}
		for($ pb: g[a]){
			$ [b,w] = pb;
			_& x = d[b];
			_ nw = di+w;
			if(nw < x){
				pv[b] = a;
				x = nw;
				q.push({x,b});
			}
		}
	}
	return array<vl,2>{d,pv};
}
_ dist(mat<ll> const& g){
	assert(g.r == g.c);
	_ n = g.r;
	_ d = g;
	fo(k,n){
		fo(i,n){
			fo(j,n){
				_& x = d[i][j];
				x = min(x, d[i][k]+d[k][j]);
			}
		}
	}
	return d;
}
_ mst(_ es){
	sort(al(es));
	_ mi = -inf;
	for($ e: es){
		mi = max(mi,max(e.a,e.b));
	}
	dsu d{mi+1};
	tp(es) ret;
	for($ e: es){
		if(d(e.a,e.b)){continue;}
		ret.pb(e);
	}
	return ret;
}
struct gsearch {
	vc<vl> const& g;
	ll n;
	vl v;
	deque<ll> q;
	vl p, d;
	gsearch($ g_): g(g_), n(size(g)), v(n), p(n,-1), d(n) {}
	virtual void operator()(ll) = 0;
	void operator()(){
		fo(i,n){if(!v[i]){this(i);}}
	}
	_ add(ll j, ll i){
		d[j] = d[i]+1;
		p[j] = i;
	}
};
#define searcher public gsearch {using gsearch::operator(), gsearch::gsearch; void operator()(ll s)
struct dfs: searcher {
	v[s] = true;
	for($ j: g[s]){
		if(v[j]){continue;}
		add(j, s);
		this(j);
	}
	q.push_front(s);
}
};
struct bfs: searcher {
	q.pb(s);
	for(ll idx = 0; idx < q.size(); ++idx){
		_ i = q[idx];
		if(v[i]){continue;}
		v[i]=true;
		for($ j: g[i]){
			q.pb(j);
			add(j, i);
		}
	}
}
};
_ trans($ g){
	ll n = size(g);
	vc<vl> h(n);
	fo(i,n){
		for(ll j:g[i]){
			h[j].pb(i);
		}
	}
	return h;
}
_ scc($ g){
	// Returns the strongly connected component for each vertex of the graph g.
	_ h = trans(g);
	dbg(h);
	vl cm(size(g), -1);
	_ assign = fix([&]($ assign, ll u, ll c) -> void {
			dbg(u);
			if(cm[u]!=-1){return;}
			cm[u] = c;
			for(ll v: h[u]){
				assign(v,c);
			}
		});
	dfs s{g};
	s();
	dbg(s.q);
	for(ll i:s.q){
		assign(i, i);
	}
	return cm;
}
_ bipartite($ g){
	bfs b{g};
	b();
	_ n = size(g);
	vl s(n);
	for(_ i:b.q){
		if(_ x = b.p[i]; x!=-1){s[i] = !s[x];}
	}
	bool bi = true;
	fo(i,n){
		for(_ j:g[i]){
			bi &= s[i] != s[j];
		}
	}
	return bi?optional{s}:nullopt;
}
_ max_match($ g){
	_ s = bipartite(g).value();
	ll n = g.size();
	vl m(n,-1);
	for(ll md = -1; md != inf;){
		vl v(n);
		vc<vl> h(n);
		fo(i,n){
			for(ll j:g[i]){
				if((j == m[i]) == s[i]){
					h[i].pb(j);
				}
			}
		}
		bfs b{h};
		b();
		md = inf;
		fo(i,n){
			if(s[i]==1 && m[i] == -1){
				md = min(md, b.d[i]);
			}
		}
		dbg(md);
		dbg(b.d);
		dbg(m);
		dbg(s);
		auto path = fix([&]($ path, ll i) -> bool{
			dbg(i);
			if(v[i]){return false;}
			v[i] = true;
			if(s[i] == 1 && m[i] == -1 && b.d[i] == md){return true;}
			for(ll j: g[i]){
				if(b.d[j] = b.d[i]+1){
					if(dbg(path(j))){
						dbg(j);
						if(s[i] == 0){
							m[i] = j;
							m[j] = i;
						}
						return true;
					}
				}
			}
			return false;
		});
		fo(i,n){
			if(s[i]==0 && m[i] == -1){
				path(i);
			}
		}
	}
	return m;
}
_ add_edge(vc<vl>& g, ll u, ll v){
	g[u].pb(v);
	g[v].pb(u);
}
_ graph_in(vc<vl>& g, ll m){
	fo(i,0,m){
		I(u);I(v);
		add_edge(g, --u, --v);
	}
}
