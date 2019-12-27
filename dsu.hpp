struct dsu {
	mutable vl p;
	vl s;
	explicit dsu(_ n): p(n), s(n,1) {iota(al(p),0);}
	ll operator[](ll x) co {return x==p[x]?x:p[x]=this[p[x]];}
	_ operator()(_ x, _ y){
		x = this[x]; y = this[y];
		if(x == y){return false;}
		if(s[x] > s[y]){swap(x,y);}
		s[y]+=s[x];
		p[x] = y;
		return true;
	}
};
_& operator<<(ostream& os, dsu co& d){
	os<<"dsu{";
	fo(i,d.p.size()){
		if(i){os<<delim;}
		os<<d[i];
	}
	return os<<"}";
}