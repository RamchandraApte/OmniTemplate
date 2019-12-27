#define aug(op) _ operator op##=(_& a, $ b){return a = a op b;}
struct ll {
	lli x;
	constexpr ll(long long int x_ = 0): x(x_) {}
	constexpr operator _&(){return x;}
	constexpr operator lli() co {return x;}
	//template<typename T, typename = enable_if_t<is_integral<T>::value, void>>
	//template<typename T, typename = enable_if_t<is_integral<T>::value, void>>
	#define opi(type) operator type(){return x;}
	//opi(double);opi(int);opi(size_t);opi(long double);opi(unsigned int);opi(bool);
	//constexpr operator T() co{return x;}
	/*operator bool() co{return x;}
	operator size_t() co {return x;}
	operator int128() co {return x;}*/
	constexpr ll operator-() co{return -x;}
	ll operator--(){--x; return this;}
	ll operator++(){++x; return this;}
	ll operator+=(ll b){return x += b.x;}
};
#ifdef __SIZEOF_INT128__
using int128 = __int128;
using uint128 = __uint128_t;
#endif
aug(+); aug(-); aug(*); aug(/);
#ifdef __SIZEOF_INT128__
#define MIX128(op, T1) mix(op, T1, int128)
#else
#define MIX128(...)
#endif
#define mix1(op, T1, T2) constexpr _ operator op(T1 a, T2 b){return static_cast<ll>(a) op static_cast<ll>(b);}
#define mix(op, T1, T2) mix1(op, T1, T2) mix1(op, T2, T1)
#define mixll(op) mix(op, ll, int) mix(op, ll, lli) MIX128(op, ll) mix(op, ll, size_t) mix(op, ll, double)
#define bill(op) constexpr ll operator op(ll co& a, ll co& b){return lli(a) op lli(b);}
bill(+) bill(*) bill(|) bill(&) bill(^) bill(<<) bill(>>)
constexpr ll operator/(ll co& a, ll co& b){
   lli x = lli(a)/lli(b), r = lli(a)%lli(b);
   return x-((x < 0) && r);
}
constexpr _ operator<(ll a, ll b){return lli(a) < lli(b);}
constexpr _ operator==(ll a, ll b){return lli(a) == lli(b);}
constexpr ll operator%(ll a, ll b){
	lli x = lli(a)%lli(b);
	if(lli(x) < 0){x+=lli(b);}
	return x;
}
mixll(+) mixll(/) mixll(*) mixll(<) mixll(==) mixll(%) mixll(&) mixll(>>) mixll(<<)
_& operator<<(ostream& os, ll co& a){
	return os<<a.x;
}
ll operator ""M (unsigned long long int x){
	return x;
}
_ ceil_div(ll x, ll y){
	return (x+y-1)/y;
}
END_NS
namespace std {
#define inh(cls) template<> struct cls<ll> : cls<lli>
inh(hash){using hash<lli>::hash;};
inh(is_integral){}; inh(is_unsigned){}; inh(is_signed){}; inh(numeric_limits){};
_ operator+(_ a, ll b){return a+lli(b);}
}
BEGIN_NS