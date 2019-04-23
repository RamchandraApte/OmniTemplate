ll M = 1e9+7;
struct small_mod {};	
struct no_mod {};
struct md {
	ll x;
	md():x{0LL}{}
	template<typename T, typename = enable_if_t<is_integral<T>::value, void>>
	md(T x_):x(ll(x_)%M){}
	md(ll x_, small_mod):x(x_>=M?x_-M:x_){}
	md(ll x_, no_mod): x(x_) {}
	explicit operator _(){return x;}
};
md operator+(md co& a, md co& b){
	return {a.x+b.x, small_mod{}};
}
md operator++(md& a){
	return a+=1;
}
md operator-(md co& a){
	return {M-a.x, no_mod{}};
}
bin(==, md);
md operator*(md co& a, md co& b){
	ll ret = ull(a.x)*ull(b.x)-ull(M)*ull(ld(a.x)*ld(b.x)/ld(M));
	if(ret < 0){return {ret+M, no_mod{}};}
	if(ret >= M){return {ret-M, no_mod{}};}
	return {ret, no_mod{}};
}
struct id {};
md operator/(id, md co& b){
	assert(b != 0);
	return power(b, M-2);
}
_ operator/(md co& a, md co& b) {
	return a*(id{}/b);
}
_& operator<<(ostream& os, md co& m){return os<<m.x;}
END_NS
namespace std {
template<>
struct hash<md> {
	size_t operator()(md co& x) co {
		return x.x;
	}
};
}
BEGIN_NS