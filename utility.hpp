struct with {
	ll old;
	ll& v;
	with(ll new_, ll& v_):old(v_), v(v_){v = new_;}
	~with(){v = old;}
};
auto fix($ func){
	// Helper for lambda recursive functions
	return [=](auto... args) {return func(fix(func), args...);};
}
#define lambda(f) [&](auto... args){return f(args...);}
auto maxeq(auto&& x, auto const& y){
	x = max(x, y);
}
auto mineq(auto&& x, auto const& y){
	x = min(x, y);
}
template<typename T>
auto cache($ f){
	T ch;
	return [=]($ arg) mutable {
		if(ch.find(arg) == end(ch)){
			ch[arg] = f(arg);
		}
		return ch[arg];
	};
}
template<typename Eq = equal_to<>, typename T = less<>>
auto uniq(auto& v, Eq const& up = Eq{}, T const& sp = T{}){
	sort(al(v), sp);
	v.resize(unique(al(v), up)-begin(v));
	return v;
}
template<typename T = less<>>
auto map_args($ f, T g = T{}){
	return [&]($... args){return g(f(args)...);};
}
auto prev_less($ v){
	ll n = v.size();
	vl l(n,-1);
	stack<ll> s;
	fo(i,n){
		while(s.size() && !(s.top() < v[i])){
			s.pop();
		}
		if(s.size()){
			l[i] = s.top();
		}
		s.push(v[i]);
	}
	return l;
}
auto nx2(auto x){
	return ll(1LL)<<ll(ceil(log2(lli(x))));
}
ll next_comb(ll x){
	ll tz = __builtin_ctz(x);
	ll y = x+(ll{1}<<tz);
	return y|(y^x)>>(2+tz);
}
