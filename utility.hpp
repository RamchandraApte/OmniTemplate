struct with {
	ll old;
	ll& v;
	with(ll new_, ll& v_):old(v_), v(v_){v = new_;}
	~with(){v = old;}
};
_ fix($ func){
	// Helper for lambda recursive functions
	return [=](_... args) {return func(fix(func), args...);};
}
#define lambda(f) [&](_... args){return f(args...);}
_ maxeq(_&& x, _ const& y){
	x = max(x, y);
}
_ mineq(_&& x, _ const& y){
	x = min(x, y);
}
template<typename T>
_ cache($ f){
	T ch;
	return [=]($ arg) mutable {
		if(ch.find(arg) == end(ch)){
			ch[arg] = f(arg);
		}
		return ch[arg];
	};
}
template<typename Eq = equal_to<>, typename T = less<>>
_ uniq(_& v, Eq const& up = Eq{}, T const& sp = T{}){
	sort(al(v), sp);
	v.resize(unique(al(v), up)-begin(v));
	return v;
}
template<typename T = less<>>
_ map_args($ f, T g = T{}){
	return [&]($... args){return g(f(args)...);};
}
_ prev_less($ v){
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
_ nx2(_ x){
	return ll(1LL)<<ll(ceil(log2(lli(x))));
}
ll next_comb(ll x){
	ll tz = __builtin_ctz(x);
	ll y = x+(ll{1}<<tz);
	return y|(y^x)>>(2+tz);
}