ll M = 1e9+7; // modulus
struct no_mod{};
struct md {
	ll x;
	md():x{0LL}{}
	template<typename T, typename = enable_if_t<is_integral<T>::value, void>>
	md(T x_):x(ll(x_)%M){}
	md(ll x_, no_mod): x(x_) {}
	explicit operator _(){return x;}
};
md operator+(md const& a, md const& b){
	ll const sum = a.x+b.x;
	return {sum>=M?sum-M:sum, no_mod{}};
}
md operator++(md& a){
	return a+=1;
}
md operator-(md const& a){
	return {M-a.x, no_mod{}};
}
bin(==, md);
md operator*(md const& a, md const& b){
	const ull quot = ld(a.x)*ld(b.x)/ld(M);
	// Computes the approximate remainder
	const ll rem = ull(a.x)*ull(b.x)-ull(M)*quot;
	if(rem < 0){return {rem+M, no_mod{}};}
	if(rem >= M){return {rem-M, no_mod{}};}
	return {rem, no_mod{}};
}
struct id {};
md operator/(id, md const& b){
	assert(b != 0);
	return power(b, M-2);
}
_ operator/(md const& a, md const& b) {
	return a*(id{}/b);
}
_& operator<<(ostream& os, md const& m){return os<<m.x;}
END_NS
namespace std {
template<>
struct hash<md> {
	size_t operator()(md const& x) const {
		return x.x;
	}
};
}
BEGIN_NS