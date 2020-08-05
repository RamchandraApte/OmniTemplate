#include "number_theory.hpp"
void test_prime() {
	assert(prime(2));
	assert(prime(3));
	assert(!prime(4));
	assert(prime(5));
	assert(!prime(static_cast<ll>(1e9 + 6)));
	assert(prime(static_cast<ll>(1e9 + 7)));
}
void test_divisors() {
	assert((divisors(1) == vl{1}));
	assert((divisors(2) == vl{1, 2}));
	assert((divisors(3) == vl{1, 3}));
	assert((divisors(4) == vl{1, 2, 4}));
	assert((divisors(36) == vl{1, 2, 3, 4, 6, 9, 12, 18, 36}));
	assert((divisors(49) == vl{1, 7, 49}));
}
void test_sieve() { assert((sieve(11) == vl{0, 0, 2, 3, 2, 5, 2, 7, 2, 3, 2})); }
void test_fac() {
	assert((fac(1) == um{}));
	assert((fac(1) == um{}));
	assert((fac(2) == um{{2, 1}}));
	assert((fac(3) == um{{3, 1}}));
	assert((fac(4) == um{{2, 2}}));
	assert((fac(36) == um{{2, 2}, {3, 2}}));
	assert((fac(49) == um{{7, 2}}));
}
void test_egcd(ll a, ll b) {
	ll x, y;
	egcd(a, b, x, y);
	assert(x * a + y * b == gcd(a, b));
}
void test_egcd() {
	test_egcd(6, 15);
	test_egcd(3, 4);
	test_egcd(6, 6);
	test_egcd(2, 1);
	test_egcd(63, 12);
}
void test_totient() { assert(totient(1) == 1 && totient(2) == 1 && totient(6) == 2 && totient(84) == 24 && totient(127) == 126); }
void test_dlog() {
	auto check = [](modulo a, ll x, ll m) {
		with _m{m, modulo::modulus};
		auto b = power(a, x);
		dlog(a, b);
	};
	fo(a, 20) {
		fo(x, 20) {
			fo(m, 1, 20) {
				if (gcd(a, m) == 1) {
					check(a, x, m);
				}
			}
		}
	}
}
void test_primitive_root() {
	auto check = [&](ll m, ll x) {
		with _m{m, modulo::modulus};
		assert(primitive_root() == x);
	};
	check(1, 0);
	check(3, 2);
	check(6, 5);
	check(7, 3);
}
void test_number_theory() {
	test_prime();
	test_divisors();
	test_fac();
	test_totient();
	test_dlog();
	test_primitive_root();
	test_sieve();
	test_egcd();
}
