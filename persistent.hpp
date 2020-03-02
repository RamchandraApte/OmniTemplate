struct first_cmp {
bool	operator()(_ a, _ b) const{
		return a.first < b.first;
	}
};
_ tim = 0LL;
tm()
struct pers {
	using event = pair<ll, T>;
	set<event, first_cmp> s;
	_ operator =($ v){
		event e{tim,v};
		s.erase(e);
		s.insert(e);
	}
	operator _() const{
		return (*--s.upper_bound({tim, T{}})).second;
	}
};
tm() _& operator<<(ostream& os, pers<T> const& p){
	return os<<static_cast<T>(p);
}
