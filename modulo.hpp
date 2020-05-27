#pragma once
#include "core.hpp"
template <typename T> T power(T a, size_t b) {
	/*! Return \f$a^b\f$ */
	T ret = 1;
	for (; b; b >>= 1, a *= a) {
		if (b & 1) {
			ret *= a;
		}
	}
	return ret;
}
ll M = 1e9 + 7; //^ Modulus
struct no_mod {};
struct md {
	/*! Modular arithmetic class */
	ll x;
	md() : x{0LL} {}
	template <typename T,
		  typename = enable_if_t<is_integral<T>::value, void>>
	md(T x_) : x(ll(x_) % M) {}
	md(ll x_, no_mod) : x(x_) {}
	explicit operator auto() { return x; }
};
md operator+(md const &a, md const &b) {
	ll const sum = a.x + b.x;
	return {sum >= M ? sum - M : sum, no_mod{}};
}
md operator++(md &a) { return a += 1; }
md operator-(md const &a) { return {M - a.x, no_mod{}}; }
bin(==, md);
md operator*(md const &a, md const &b) {
	/*! Computes a times b modulo M using long double */
	const ull quot = ld(a.x) * ld(b.x) / ld(M);
	// Computes the approximate remainder
	const ll rem = ull(a.x) * ull(b.x) - ull(M) * quot;
	if (rem < 0) {
		return {rem + M, no_mod{}};
	}
	if (rem >= M) {
		return {rem - M, no_mod{}};
	}
	return {rem, no_mod{}};
}
struct id {};
md operator/(id, md const &b) {
	/*! Computes the modular inverse \f$b^{-1}\f$ */
	assert(b != 0);
	return power(b, M - 2);
}
auto operator/(md const &a, md const &b) { return a * (id{} / b); }
template <typename Stream> auto &operator<<(Stream &os, md const &m) {
	return os << m.x;
}
END_NS
void test_power() {
	assert(power(2, 3) == 8);
	assert(power(3, 10) == 59049);
	with _m{static_cast<ll>(1e9 + 7), M};
	assert(power(md{3}, 1000) == md{56888193});
}
void test_md() {
	with _m{7, M};
	assert(md{34} / md{-2} == md{4});
	assert(md{2} - md{6} == md{3});
}
namespace std {
template <> struct hash<md> {
	size_t operator()(md const &x) const { return x.x; }
};
} // namespace std
void test_modulo() {
	test_power();
	test_md();
}
BEGIN_NS
