#pragma once
#include "core.hpp"
// TODO Tensors? Also, matrix_row class.
namespace linear_algebra {
tm() struct matrix {
	/*! Matrix class*/
	ll rows_n, cols_n; //!< Row, column
	vector<T> a; //! Array storing the data, in row-major order
	matrix(ll r_, ll c_, df(v, 0LL))
	    : rows_n(r_), cols_n(c_), a(rows_n * cols_n, v) {
		assert(rows_n >= 1 && cols_n >= 1);
	}
	matrix(T d) : rows_n(1), cols_n(1), a{d} {}
	matrix(vector<vector<pr>> const &g) : matrix(g.size(), g.size(), inf) {
		fo(i, rows_n) {
			for (const auto &p : g[i]) {
				auto [x, w] = p;
				this[i][x] = w;
			}
		}
		fo(i, rows_n) { this[i][i] = 0; }
	}
	matrix(const initializer_list<initializer_list<ll>> &vals)
	    : matrix(size(vals), size(begin(vals)[0])) {
		fo(i, rows_n) {
			assert(size(begin(vals)[i]) == cols_n);
			fo(j, cols_n) { this[i][j] = begin(begin(vals)[i])[j]; }
		}
	}
	auto operator[](ll i) {
		return const_cast<T *>(const_cast<matrix const &>(this)[i]);
	}
	auto operator[](ll i) const { return &a[i * cols_n]; }
	auto id() const {
		return this.rows_n == 1 && this.cols_n == 1 && this[0][0] == 1;
	}
};
tm(...) bool operator==(matrix<T...> const &a, matrix<T...> const &b) {
	return a.rows_n == b.rows_n && a.cols_n == b.cols_n && a.a == b.a;
}
tm(...) auto operator*(matrix<T...> const &a, matrix<T...> const &b) {
	/*! Returns the matrix product of a and b*/
	if (a.id()) {
		return b;
	}
	if (b.id()) {
		return a;
	}
	assert(a.cols_n == b.rows_n);
	matrix<T...> c{a.rows_n, b.cols_n};
	fo(i, c.rows_n) {
		fo(j, a.cols_n) {
			fo(k, c.cols_n) { c[i][k] += a[i][j] * b[j][k]; }
		}
	}
	return c;
}
template <typename T> pair<matrix<T> &&, T> gauss(matrix<T> b, matrix<T> a) {
	/*!
	Returns matrix x such that \f$ax = b\f$ and the determinant of \f$a\f$
	via Gaussian elimination.
	*/
	assert(a.rows_n == a.cols_n);
	assert(a.rows_n == b.rows_n);
	T det = 1;
	fo(i, a.rows_n) {
		const auto div = a[i][i];
		det *= div;
		for (auto &ar : {ref(a), ref(b)}) {
			fo(k, ar.get().cols_n) { ar.get()[i][k] /= div; }
		}
		fo(j, a.rows_n) {
			if (j == i) {
				continue;
			}
			const auto mul = a[j][i];
			for (auto &ar : {ref(a), ref(b)}) {
				fo(k, ar.get().cols_n) {
					ar.get()[j][k] -= ar.get()[i][k] * mul;
				}
			}
		}
	}
	return {move(b), det};
}
tm(...) auto operator/(matrix<T...> b, matrix<T...> a) {
	/*! Returns \f$ba^{-1}\f$*/
	// TODO or is it the other way round 🤔?
	return gauss(b, a).first;
}
template <typename T> T det(const matrix<T> &a) {
	/*! Returns the determinant of matrix a*/
	return gauss(matrix<T>(a.rows_n, 1), a).second;
}
template <typename Stream, typename... T>
auto &operator<<(Stream &os, matrix<T...> const &m) {
	/*! Print the matrix rows, line by line*/
	os << "mat{" << endl;
	fo(i, m.rows_n) {
		copy(m[i], m[i] + m.cols_n, make_ostream_joiner(os, delim));
		os << endl;
	}
	return os << "}";
}
template <typename T> auto lin_recur(vector<T> const &c, ll n) {
	/*! Returns nth term of linear recurrence described by c*/
	// TODO which direction is the linear recurrence? 🤔
	matrix<T> m{size(c), size(c)};
	copy(al(c), m[0]);
	fo(i, 1, size(c)) { m[i][i - 1] = 1; }
	return power(m, n)[0][0];
}
void test_matrix() {
	matrix<ld> a{{2, 3, 5}, {3, 6, 10}, {5, 9, 16}};
	matrix<ld> b{{1, 2, 3}, {4, 5, 6}, {9, 7, 8}};
	auto x = b / a;
	// TODO 😩 there are no asserts here
	dbg(x);
	dbg(a * x);
	dbg(b);
	dbg(det(a));
}
} // namespace linear_algebra
using namespace linear_algebra;
