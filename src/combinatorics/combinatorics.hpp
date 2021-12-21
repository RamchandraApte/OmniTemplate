#pragma once
#include "core/all.hpp"
/** @brief Combinatorics header. */
inline namespace combinatorics {
// TODO should b be integer type??
/*!Return \f$P(a,b)\f$, the falling factorial.*/
template <typename T> T perm(const T a, const T b) {
	return accumulate(int_it<T>{a + 1 - b}, int_it<T>{a + 1}, T{1}, multiplies<>{});
}
/** @brief Return the factorial of n, i.e. \f$n!\f$. */
template <typename T> T fact(const T n) {
	return perm(n, n);
}
/** @brief Binomal coefficients.
 *  @return a choose b, i.e. \f$\binom{a}{b}\f$*/
template <typename T> T binom(const T a, const T b) { return perm(a, b) / fact(b); }
} // namespace combinatorics
