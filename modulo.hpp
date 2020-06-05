#pragma once
#include "core.hpp"
namespace modulo_namespace {
template <typename T> T power(T a, size_t b) {
	/*! Return \f$a^b\f$ */
	T ret{1};
	for (; b; b >>= 1, a *= a) {
		if (b & 1) {
			ret *= a;
		}
	}
	return ret;
}
struct no_mod {};
struct modulo {
	inline static ll modulus =
	    1e9 +
	    7; //!< Modulus used for operations like modular multiplication
	/*! Modular arithmetic class */
	ll x; //!< The representative element, which is in [0, M)
	modulo() : x{0LL} {}
	template <typename T,
		  typename = enable_if_t<is_integral<T>::value, void>>
	modulo(T x_) : x(ll(x_) % modulo::modulus) {}
	modulo(ll x_, no_mod) : x(x_) {}
	explicit operator auto() const { return x; }
};
// FIXME add more stuff in modulo namespace
modulo operator+(modulo const &a, modulo const &b) {
	ll const sum = a.x + b.x;
	return {sum >= modulo::modulus ? sum - modulo::modulus : sum, no_mod{}};
}
modulo operator++(modulo &a) { return a += 1; }
modulo operator-(modulo const &a) { return {modulo::modulus - a.x, no_mod{}}; }
// To avoid ADL issues
using ::operator-;
bin(==, modulo);
modulo operator*(modulo const &a, modulo const &b) {
	/*! Computes a times b modulo modulo::modulus using long double */
	const ull quot = ld(a.x) * ld(b.x) / ld(modulo::modulus);
	// Computes the approximate remainder
	const ll rem = ull(a.x) * ull(b.x) - ull(modulo::modulus) * quot;
	if (rem < 0) {
		return {rem + modulo::modulus, no_mod{}};
	}
	if (rem >= modulo::modulus) {
		return {rem - modulo::modulus, no_mod{}};
	}
	return {rem, no_mod{}};
}
modulo operator/(id, modulo const &b) {
	/*! Computes the modular inverse \f$b^{-1}\f$ */
	assert(b != 0);
	return power(b, modulo::modulus - 2);
}
using ::operator/;
template <typename Stream> auto &operator<<(Stream &os, modulo const &m) {
	return os << m.x;
}
void test_power() {
	assert(power(2, 3) == 8);
	assert(power(3, 10) == 59049);
	with _m{static_cast<ll>(1e9 + 7), modulo::modulus};
	assert(power(modulo{3}, 1000) == modulo{56888193});
}
void test_md() {
	with _m{7, modulo::modulus};
	assert(modulo{34} / modulo{-2} == modulo{4});
	assert(modulo{2} - modulo{6} == modulo{3});
}
} // namespace modulo_namespace
using namespace modulo_namespace;
namespace std {
template <> struct hash<modulo> {
	size_t operator()(modulo const &x) const { return x.x; }
};
} // namespace std
void test_modulo() {
	test_power();
	test_md();
}
