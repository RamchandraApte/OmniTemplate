#pragma once
#include "core/all.hpp"
#include "number_theory/modulo.hpp"
/**
 * @brief  Polynomial class. poly[i] is coefficient for x^i
 * Example: `Polynomial<ll>{1, 2, 3}` is \f$3x^2+2x+1\f$
 */
namespace polynomial_ns {
template <typename T> class Polynomial : public vector<T> {
	using vector<T>::vector;

      public:
	void shrink() {
		while (!this->empty() && this->back() == 0) {
			this->pop_back();
		}
	}
	ll degree() const {
		/*! Returns the degree of polynomial. Returns \f$-\infty\f$ for the \f$0\f$
		 * polynomial.*/
		fr(j, 0, this->size()) {
			if ((*this)[j] != 0) {
				return j;
			}
		}
		return -inf;
	}
};
template <typename T> Polynomial<T> operator+(const Polynomial<T> &a, const Polynomial<T> &b) {
	if (!(a.size() <= b.size())) {
		return b + a;
	}
	auto sum = b;
	fo(i, a.size()) { sum[i] += a[i]; }
	return sum;
}
template <typename T> Polynomial<T> operator*(const Polynomial<T> &a, const Polynomial<T> &b) {
	Polynomial<T> prod(a.size() - 1 + b.size() - 1 + 1);
	fo(i, a.size()) {
		fo(j, b.size()) { prod[i + j] += a[i] * b[j]; }
	}
	return prod;
}
template <typename T> Polynomial<T> operator%(Polynomial<T> a, const Polynomial<T> &b) {
	const auto bdeg = b.degree();
	fr(i, 0, a.size()) {
		// TODO should we use identity instead of 0?
		if (!(i >= bdeg && a[i] != 0)) {
			continue;
		}
		const auto mul = a[i] / b[bdeg];
		fo(j, 0, bdeg + 1) { a[j + i - bdeg] -= mul * b[j]; }
	}
	return a;
}
template <typename T> bool operator==(const Polynomial<T> &a, const Polynomial<T> &b) {
	/*! Checks if two polynomials are equal. Note that polynomials can have different sizes but
	 * be equal*/
	if (!(a.size() <= b.size())) {
		return b == a;
	}
	return equal(al(a), b.begin(), b.begin() + a.size()) &&
	       all_of(b.begin() + a.size(), b.end(), [](T x) { return x == 0; });
}
} // namespace polynomial_ns
using namespace polynomial_ns;
