struct bigint {
	vc<ull> v;
	explicit bigint($ v_): v(v_) {}
	_ operator[](size_t i) co{
		return i<v.size()?v[i]:0;
	}
};
_& operator<<(ostream& os, bigint co& a){
	return os<<a.v;
}
#if 0
_ operator+(bigint co& a, bigint co& b){
	#define addo __builtin_add_overflow
	initializer_list xs{a,b};
	ull sm = 0;
	for($ x: xs){sm+=x.v.size();}
	bigint c(sm+1);
	fo(i,sm){
		for($ x: xs){
			dbg(i);
			c.v[i+1] |= dbg(addo(c.v[i], x[i], c.v.data()+i));
		}
	}
	return c;
}
#endif