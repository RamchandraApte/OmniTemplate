struct hash_str {
	static _ constexpr lcg_mod = (1ULL<<62)-57;
	const char* st;
	vc<md> h, p;
	explicit hash_str($ s): st(s.data()), h(s.size()+1), p(s.size()) {
		with _w{lcg_mod,M};
		md g = 1;
		fo(i,0,s.size()){
			g*=md{0x51a3e995948c0deULL};
			//dbg(A);
			//dbg(B);
			//dbg(lli((int128(A.x)*int128(B.x))%int128(M)));
			h[i+1] = md{s[i]}*g;
		}
		//dbg(h);
		partial_sum(al(h), begin(h));		
		_ co inv = md{1}/md{0x51a3e995948c0deULL};
		md x = 1;
		fo(i,0,p.size()){
			p[i] = x;
			x*=md{inv};
		}
	}
	size_t operator()(string_view co& v){
		with _w{lcg_mod,M};
		ll l = v.data()-st;
		//dbg(l);
		//dbg(v.size());
		//dbg(md{10}-md{100});
		//dbg(h[l+v.size()]-h[l]);
		//dbg(p[l]);
		return ll((h[l+v.size()]-h[l]) * p[l]);
	}
};
struct bytehash {
	_ operator()($ x) co{
		return hash<string_view>{}(string_view{reinterpret_cast<const char*>(&x), sizeof(x)});
	}
};
vl prefix(string co& s){
	ll n = s.size();
	vl p(n);	
	fo(i,1,n){
		for(ll j = p[i-1]; ; j = p[j-1]){
			if(s[j] == s[i]){p[i] = j+1;break;}
			if(!j){break;}
		}
	}
	dbg(p);
	return p;
}
_ search_all(string co& t, string co& s){
	_ p = prefix(s+'\0'+t);
	vl v;
	fo(i,t.size()){
		if(p[s.size()+1+i] == s.size()){
			v.pb(i);
		}
	}
	return v;
}
string empstr = "";
struct search_it: it_base<ll> {
	using iterator_category = input_iterator_tag;
	string co& t, s;
	const ll n, ed;
	vl p;
	ll i=0, o=0;
	search_it(string co& t_, string co& s_): t(t_), s(s_), n(s.size()), ed(n+1+t.size()), p(n) {++this;}
	explicit search_it():search_it(empstr, empstr){}
	_ operator*(){
		assert(n);
		return i-(n+1);
	}
	void operator++(){
		for(++i;i < ed;++i){
			_ cur = i <= n?s.c_str()[i]:t[*this];
		 	for(ll j = o; ; j = p[j-1]){
				if(s[j] == cur){o = j+1; break;}
				if(!j){o = 0;break;}
			}
			if(i<n){
				p[i] = o;
			}
			dbg(i);dbg(o);
			if(o == n){
				break;
			}
		}
	}
};
_ operator==(search_it co& a, search_it co& b){
	bool sa = a.n, sb = b.n;
	if(sa ^ sb){return a.i == b.i;}
	if(sa){return a.i == a.ed;}
	if(sb){return b.ed == b.i;}
}
_ operator<(search_it co& a, search_it co& b){
	bool sa = a.n, sb = b.n;
	if(sa ^ sb){return a.i < b.i;}
	if(sa){return a.i < a.ed;}
	if(sb){return b.ed < b.i;}
}
_ search_ra($... args){
	return range{search_it(args...), search_it()};
}