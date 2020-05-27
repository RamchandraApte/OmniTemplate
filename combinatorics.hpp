#pragma once
#include "core.hpp"
template <typename T> auto perm(T a, T b) {
	return accumulate(int_it<T>{a + 1 - b}, int_it<T>{a + 1}, 1LL,
			  multiplies<>{});
}
template <typename T> auto fact(T n) {
	/*! Return the factorial of n. */
	return perm(n, n);
}
template <typename T> auto choose(T a, T b) {
	/*! Returns a choose b*/
	return perm(a, b) / fact(b);
}
