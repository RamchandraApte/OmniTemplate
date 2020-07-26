#pragma once
#include "core.hpp"
/**
 * @brief  Polynomial class. poly[i] is coefficient for x^i
 * 
 */
template <typename T> class Polynomial : public vector<T> {
	using vector<T>::vector;
      public:
	void shrink() {
		while (!this.empty() && this.back() == 0) {
			this.pop_back();
		}
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
template <typename T> bool operator==(const Polynomial<T> &a, const Polynomial<T> &b) {
	/*! Checks if two polynomials are equal. Note that polynomials can have different sizes but be equal*/
	if (!(a.size() <= b.size())) {
		return b == a;
	}
	return equal(al(a), b.begin(), b.begin() + a.size()) && all_of(b.begin() + a.size(), b.end(), [](T x) { return x == 0; });
}
void test_polynomial() {
	Polynomial<ll> p1{1, 2, 3};
	Polynomial<ll> p2{2, -3};
	assert((p2 * p1 == p1 * p2 && p1 * p2 == Polynomial<ll>{2, 1, 0, -9, 0, 0}));
	assert((p2 + p1 == p1 + p2 && p1 + p2 == Polynomial<ll>{3, -1, 3, 0}));
	assert((p1 + p2 != Polynomial<ll>{3, -1, 3, 1}));
}
