#pragma once
#include "core/all.hpp"
/*! Combinatorics header. */
inline namespace combinatorics {
template <typename T> T perm(const T a, const T b) {
	/*!Return \f$P(a,b)\f$, the falling factorial.*/
	return accumulate(int_it<T>{a + 1 - b}, int_it<T>{a + 1}, T{1}, multiplies<>{});
}
template <typename T> T fact(const T n) {
	/*! Return the factorial of n, i.e. \f$n!\f$. */
	return perm(n, n);
}
template <typename T> T choose(const T a, const T b) {
	/*! Returns a choose b, i.e. \f$\binom{a}{b}\f$*/
	return perm(a, b) / fact(b);
}
} // namespace combinatorics
