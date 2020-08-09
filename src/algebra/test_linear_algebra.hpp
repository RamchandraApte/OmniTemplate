#pragma once
#include "linear_algebra.hpp"
namespace linear_algebra::test {
template <typename... Ts> void test_invert_impl(const matrix<Ts...> &a) {
	assert(invert(a) * a == identity(multiplies<>{}, a));
	assert(a * invert(a) == identity(multiplies<>{}, a));
}
void test_invert() {
	with _m{ll(1e9 + 7), modulo::modulus};
	matrix<modulo> a{{2, 3, 5}, {3, 6, 10}, {5, 9, 16}};
	matrix<modulo> b{{1, 2, 3}, {4, 5, 6}, {9, 7, 8}};
	test_invert_impl(a);
	test_invert_impl(b);
}
void test_matrix() {
	with _m{ll(1e9 + 7), modulo::modulus};
	matrix<modulo> a{{2, 3, 5}, {3, 6, 10}, {5, 9, 16}};
	matrix<modulo> b{{1, 2, 3}, {4, 5, 6}, {9, 7, 8}};
	assert(a * (b / a) == b);
}
void test_lin_recur() {
	assert(lin_recur(vector<ll>{1, 2}, 5) == 21);
	assert(lin_recur(vector<ll>{2, 3, 1}, 4) == 65);
}

template <typename T> Polynomial<T> lin_recur_coef(vector<T> const &c) {}
void test_linear_algebra() {
	test_matrix();
	test_lin_recur();
	test_invert();
	// test_lin_recur_coef();
}
} // namespace linear_algebra::test
using namespace linear_algebra::test;
