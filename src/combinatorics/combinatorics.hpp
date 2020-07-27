#pragma once
#include "core/all.hpp"
/*! Combinatorics header. */
namespace combinatorics {
template <typename T> T perm(const T a, const T b) {
	/*!Return \f$P(a,b)\f$, the falling factorial.*/
	return accumulate(int_it<T>{a + 1 - b}, int_it<T>{a + 1}, T{1},
			  multiplies<>{});
}
void test_perm() {
	assert(perm(4, 2) == 4 * 3);
	assert(perm(4, 4) == 4 * 3 * 2 * 1);
	assert(perm(4, 0) == 1);
	assert(perm(0, 0) == 1);
	assert(perm(1, 0) == 1);
	assert(perm(1, 1) == 1);
}
template <typename T> T fact(const T n) {
	/*! Return the factorial of n, i.e. \f$n!\f$. */
	return perm(n, n);
}
void test_fact() {
	assert(fact(4) == 4 * 3 * 2 * 1);
	assert(fact(0) == 1);
	assert(fact(1) == 1);
	assert(fact(8) == 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1);
}
template <typename T> T choose(const T a, const T b) {
	/*! Returns a choose b, i.e. \f$\binom{a}{b}\f$*/
	return perm(a, b) / fact(b);
}
void test_choose() {
	assert(choose(5, 2) == 10);
	assert(choose(5, 3) == 10);
	assert(choose(5, 0) == 1);
	assert(choose(5, 5) == 1);
	assert(choose(0, 0) == 1);
	assert(choose(1, 0) == 1);
	assert(choose(1, 1) == 1);
	assert(choose(6, 3) == 20);
}
void test_combinatorics() {
	test_perm();
	test_fact();
	test_choose();
}
} // namespace combinatorics
using namespace combinatorics;
