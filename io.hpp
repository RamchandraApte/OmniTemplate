struct rin {
	istream& in;
	rin(istream& in_): in(in_) {}
	auto& operator<<(const char*){
		return this;
	}
	auto& operator<<(string const& s){
		if(s.empty()){
			in>>const_cast<string&>(s);
		}
		return this;
	}
	rin& operator>>(auto& x){
		this << x;
		return this;
	}
};
template<typename R, typename T>
auto operator<<(R& r, const T& x) -> decltype(r.in>>const_cast<T&>(x), declval<enable_if_t<is_same<R, rin>::value, rin&>>()) {
	r.in>>const_cast<T&>(x);
	return r;
}
tm() enable_if_t<is_same<T, istream>::value, rin> operator>>(T& is, auto& x){
	rin r{is};
	return r>>x;
}
tm(...) auto& operator<<(ostream& os, tuple<T...> t){
	apply([&](auto& f, auto& ... x){
		os<<f;
		((os<<delim<<x), ...);
		}, t);
	return os;
}
auto print($ arg1, $... args){
	cout<<arg1;
	(void)((cout<<" "<<args),...);
	cout<<endl;
}
END_NS
namespace std {
	tm(...) auto& operator<<(ostream& os, pair<T...> const& p){
		return os<<simple_tp(p)<<"{"<<p.first<<delim<<p.second<<"}";
	}
	auto operator<<(ostream& os, $ v) -> decltype(begin(v), declval<tp(os)>()){
		auto ed = begin(v);
		auto big = v.size()>20;
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
	auto operator<<(rin& os, $ v) -> decltype(begin(v), declval<tp(os)>()){
		for($ elem:v){
			os<<elem;
		}
		return os;
	}
	#if __cplusplus >= 201703L
	tm() auto& operator<<(ostream& os, optional<T> const& opt){
		return opt?(os<<*opt):(os<<"nullopt");
	}
	#endif
}