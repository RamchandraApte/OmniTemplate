struct rin {
	istream& in;
	rin(istream& in_): in(in_) {}
	_& operator<<(const char*){
		return this;
	}
	_& operator<<(string co& s){
		if(s.empty()){
			in>>const_cast<string&>(s);
		}
		return this;
	}
	rin& operator>>(_& x){
		this << x;
		return this;
	}
};
template<typename R, typename T>
_ operator<<(R& r, const T& x) -> decltype(r.in>>const_cast<T&>(x), declval<enable_if_t<is_same<R, rin>::value, rin&>>()) {
	r.in>>const_cast<T&>(x);
	return r;
}
tm() enable_if_t<is_same<T, istream>::value, rin> operator>>(T& is, _& x){
	rin r{is};
	return r>>x;
}
tm(...) _& operator<<(ostream& os, tuple<T...> t){
	apply([&](_& f, _& ... x){
		os<<f;
		((os<<delim<<x), ...);
		}, t);
	return os;
}
_ print($ arg1, $... args){
	cout<<arg1;
	(void)((cout<<" "<<args),...);
	cout<<endl;
}
END_NS
namespace std {
	tm(...) _& operator<<(ostream& os, pair<T...> co& p){
		return os<<simple_tp(p)<<"{"<<p.first<<delim<<p.second<<"}";
	}
	_ operator<<(ostream& os, $ v) -> decltype(begin(v), declval<tp(os)>()){
		_ ed = begin(v);
		_ big = v.size()>20;
		if(big){
			advance(ed, 20);
		}
		else {
			ed = end(v);
		}
		os<<simple_tp(v)<<"{";
		copy(begin(v), ed, make_ostream_joiner(os, delim));
		if(big){
			os<<delim<<"...";
		}
		return os<<"}";
	}
	_ operator<<(rin& os, $ v) -> decltype(begin(v), declval<tp(os)>()){
		for($ elem:v){
			os<<elem;
		}
		return os;
	}
	#if __cplusplus >= 201703L
	tm() _& operator<<(ostream& os, optional<T> co& opt){
		return opt?(os<<*opt):(os<<"nullopt");
	}
	#endif
}