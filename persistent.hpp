struct first_cmp {
	bool operator()(auto a, auto b) const { return a.first < b.first; }
};
auto tim = 0LL;
tm() struct pers {
	using event = pair<ll, T>;
	set<event, first_cmp> s;
	auto operator=(const auto &v) {
		event e{tim, v};
		s.erase(e);
		s.insert(e);
	}
	operator auto() const { return (*--s.upper_bound({tim, T{}})).second; }
};
tm() auto &operator<<(ostream &os, pers<T> const &p) {
	return os << static_cast<T>(p);
}
