#pragma once
#include "core.hpp"
/*! \deprecated{Custom int class where a%b always return a nonnegative
 * remainder}*/
struct ll {
	ll x;
	constexpr ll(long long int x_ = 0) : x(x_) {}
	constexpr operator auto &() { return x; }
	constexpr operator ll() const { return x; }
// template<typename T, typename = enable_if_t<is_integral<T>::value, void>>
// template<typename T, typename = enable_if_t<is_integral<T>::value, void>>
#define opi(type)                                                                                  \
	operator type() { return x; }
	// opi(double);opi(int);opi(size_t);opi(long double);opi(unsigned
	// int);opi(bool); constexpr operator T() const{return x;}
	/*operator bool() const{return x;}
	operator size_t() const {return x;}
	operator int128() const {return x;}*/
	constexpr ll operator-() const { return -x; }
	ll operator--() {
		--x;
		return this;
	}
	ll operator++() {
		++x;
		return this;
	}
	ll operator+=(ll b) { return x += b.x; }
};
#ifdef __SIZEOF_INT128__
using int128 = __int128;
using uint128 = __uint128_t;
#endif
#ifdef __SIZEOF_INT128__
#define MIX128(op, T1) mix(op, T1, int128)
#else
#define MIX128(...)
#endif
#define mix1(op, T1, T2)                                                                           \
	constexpr auto operator op(T1 a, T2 b) { return static_cast<ll>(a) op static_cast<ll>(b); }
#define mix(op, T1, T2) mix1(op, T1, T2) mix1(op, T2, T1)
#define mixll(op)                                                                                  \
	mix(op, ll, int) mix(op, ll, ll) MIX128(op, ll) mix(op, ll, size_t) mix(op, ll, double)
#define bill(op)                                                                                   \
	constexpr ll operator op(ll const &a, ll const &b) { return ll(a) op ll(b); }
bill(+) bill(*) bill(|) bill(&) bill(^) bill(<<) bill(>>) constexpr ll operator/(ll const &a,
										 ll const &b) {
	ll x = ll(a) / ll(b), r = ll(a) % ll(b);
	return x - ((x < 0) && r);
}
constexpr auto operator<(ll a, ll b) { return ll(a) < ll(b); }
constexpr auto operator==(ll a, ll b) { return ll(a) == ll(b); }
constexpr ll operator%(ll a, ll b) {
	ll x = ll(a) % ll(b);
	if (ll(x) < 0) {
		x += ll(b);
	}
	return x;
}
mixll(+) mixll(/) mixll(*) mixll(<) mixll(==) mixll(%) mixll(&) mixll(>>) mixll(<<)

    template <typename Stream>
    auto &operator<<(Stream &os, ll const &a) {
	return os << a.x;
}
ll operator"" _ll(unsigned long long int x) { return x; }
auto ceil_div(ll x, ll y) { return (x + y - 1) / y; }
namespace std {
#define inh(cls) template <> struct cls<ll> : cls<ll>
inh(hash) { using hash<ll>::hash; };
inh(is_integral){};
inh(is_unsigned){};
inh(is_signed){};
inh(numeric_limits){};
template <typename T, typename ll_t, typename = enable_if_t<is_same_v<ll_t, ll>, void>>
auto operator+(T a, ll_t b) {
	return a + ll(b);
}
} // namespace std
