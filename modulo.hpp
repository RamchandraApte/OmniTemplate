#pragma once
#include "core.hpp"
namespace modulo_name {
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
} // namespace modulo_name
using namespace modulo_name;
// FIXME add more stuff in modulo namespace
ll M = 1e9 + 7; //^ Modulus
struct no_mod {};
struct modulo {
	/*! Modular arithmetic class */
	ll x; //!< The representative element, which is in [0, M)
	modulo() : x{0LL} {}
	template <typename T,
		  typename = enable_if_t<is_integral<T>::value, void>>
	modulo(T x_) : x(ll(x_) % M) {}
	modulo(ll x_, no_mod) : x(x_) {}
	explicit operator auto() { return x; }
};
modulo operator+(modulo const &a, modulo const &b) {
	ll const sum = a.x + b.x;
	return {sum >= M ? sum - M : sum, no_mod{}};
}
modulo operator++(modulo &a) { return a += 1; }
modulo operator-(modulo const &a) { return {M - a.x, no_mod{}}; }
bin(==, modulo);
modulo operator*(modulo const &a, modulo const &b) {
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
modulo operator/(id, modulo const &b) {
	/*! Computes the modular inverse \f$b^{-1}\f$ */
	assert(b != 0);
	return power(b, M - 2);
}
auto operator/(modulo const &a, modulo const &b) { return a * (id{} / b); }
template <typename Stream> auto &operator<<(Stream &os, modulo const &m) {
	return os << m.x;
}

void test_power() {
	assert(power(2, 3) == 8);
	assert(power(3, 10) == 59049);
	with _m{static_cast<ll>(1e9 + 7), M};
	assert(power(modulo{3}, 1000) == modulo{56888193});
}
void test_md() {
	with _m{7, M};
	assert(modulo{34} / modulo{-2} == modulo{4});
	assert(modulo{2} - modulo{6} == modulo{3});
}
namespace std {
template <> struct hash<modulo> {
	size_t operator()(modulo const &x) const { return x.x; }
};
} // namespace std
void test_modulo() {
	test_power();
	test_md();
}
