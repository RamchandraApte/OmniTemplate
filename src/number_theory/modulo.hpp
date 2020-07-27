#pragma once
#include "core/all.hpp"
namespace modulo_namespace {
template <typename... Args> using invert_t = decltype(invert(std::declval<Args>()...));
/*! @brief Returns \f$a^b\f$
 * @param a the base
 * @param b the exponent
 * 
 * Time complexity: \f$O(\log_2 |b|)\f$ multiplications
*/
template <typename T> T power(T a, ll b) {
	if (b < 0) {
		if constexpr (experimental::is_detected_v<invert_t, multiplies<>, decltype(a)>) {
			a = invert(multiplies{}, a);
			b = -b;
		} else {
			assert(("b < 0 but unable to inverse a", false));
		}
	}
	T ret = identity(multiplies<>{}, a);
	for (; b; b >>= 1, a *= a) {
		if (b & 1) {
			ret *= a;
		}
	}
	return ret;
}
/*! @brief Returns the remainder of a divided by b as a nonnegative integer in [0, b).*/
ll mod(ll a, const ll b) {
	a %= b;
	if (a < 0) {
		a += b;
	}
	return a;
}
/*! Set a to the remainder when divided by b. */
ll mod_eq(ll &a, const ll b) { return a = mod(a, b); }
/*! no_mod tag class allows a modulo object to be quickly constructed from an integer in the range [0, b) without performing a modulo operation.*/
struct no_mod {};
struct modulo {
	inline static ll modulus =
	    1e9 +
	    7; //!< Modulus used for operations like modular multiplication
	/*! Modular arithmetic class */
	ll x; //!< The representative element, which is in [0, M)
	modulo() : x{0LL} {}
	template <typename T, typename = enable_if_t<is_integral<T>::value, void>>
	modulo(T x_) : x(mod(x_, modulo::modulus)) {}
	modulo(ll x_, no_mod) : x(x_) {}
	explicit operator auto() const { return x; }
};
modulo identity(plus<>, modulo) { return 0; }
modulo identity(multiplies<>, modulo) { return 1; }
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
modulo invert(multiplies<>, modulo const &b) {
	/*! Computes the modular inverse \f$b^{-1} \pmod{M}\f$ */
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
	assert(power(modulo{3}, -1000) * power(modulo{3}, 1000) == 1);
	assert(power(modulo{1}, 0) == 1);
}
void test_md() {
	with _m{7, modulo::modulus};
	assert(modulo{34} / modulo{-2} == modulo{4});
	assert(modulo{2} - modulo{6} == modulo{3});
}
void test_modulo() {
	test_power();
	test_md();
}
} // namespace modulo_namespace
using namespace modulo_namespace;
namespace std {
template <> struct hash<modulo> {
	ll operator()(modulo const &x) const { return x.x; }
};
} // namespace std
