struct bigint {
	vc<ull> v;
	explicit bigint(const auto &v_) : v(v_) {}
	auto operator[](size_t i) const { return i < v.size() ? v[i] : 0; }
};
auto &operator<<(ostream &os, bigint const &a) { return os << a.v; }
#if 0
auto operator+(bigint const& a, bigint const& b){
#define addo __builtin_add_overflow
	initializer_list xs{a,b};
	ull sm = 0;
	for(const auto& x: xs){sm+=x.v.size();}
	bigint c(sm+1);
	fo(i,sm){
		for(const auto& x: xs){
			dbg(i);
			c.v[i+1] |= dbg(addo(c.v[i], x[i], c.v.data()+i));
		}
	}
	return c;
}
#endif