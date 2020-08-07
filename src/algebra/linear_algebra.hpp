#pragma once
#include "core/all.hpp"
#include "number_theory/modulo.hpp"
#include "polynomial.hpp"
/*! @file */
// TODO Tensors? Also, matrix_row class.
// TODO fix default constructor causing segfault
inline namespace linear_algebra {
template <typename T> struct matrix {
	/*! Matrix class*/
	ll rows_n, cols_n; //!< Row, column
	vector<T> a; //! Array storing the data, in row-major order
	explicit matrix(ll r_, ll c_, T v = {}) : rows_n(r_), cols_n(c_), a(rows_n * cols_n, v) { assert(rows_n >= 1 && cols_n >= 1); }
	explicit matrix(T d) : rows_n(1), cols_n(1), a{d} {}
	explicit matrix(vector<vector<pr>> const &g)
	    : matrix(g.size(), g.size(), inf) {
		fo(i, rows_n) {
			for (const auto &p : g[i]) {
				auto [x, w] = p;
				this[i][x] = w;
			}
		}
		fo(i, rows_n) { this[i][i] = 0; }
	}
	explicit matrix(const initializer_list<initializer_list<ll>> &vals)
	    : matrix(size(vals), size(begin(vals)[0])) {
		fo(i, rows_n) {
			assert(size(begin(vals)[i]) == cols_n);
			fo(j, cols_n) { this[i][j] = begin(begin(vals)[i])[j]; }
		}
	}
	auto operator[](const ll i) {
		return const_cast<T *>(const_cast<matrix const &>(this)[i]);
	}
	auto operator[](const ll i) const { return &a[i * cols_n]; }
	bool is_square() const { return rows_n == cols_n; }
};
template <typename T> auto identity(const plus<>, const matrix<T> &mat) {
	return matrix(mat.rows_n, mat.cols_n);
}
template <typename T> auto identity(const multiplies<>, const matrix<T> &mat) {
	assert(mat.is_square());
	matrix<T> id(mat.rows_n, mat.cols_n);
	fo(i, mat.rows_n) { id[i][i] = 1; }
	return id;
}
template <typename... Ts>
auto operator+(const matrix<Ts...> &a, const matrix<Ts...> &b) {
	assert(a.rows_n == b.rows_n && a.rows_n == b.rows_n);
	matrix c(a.rows_n, a.cols_n);
	fo(i, a.rows_n) {
		fo(j, a.col_n) { c[i][j] = a[i][j] + b[i][j]; }
	}
	return c;
}
template <typename... Ts> auto operator-(const matrix<Ts...> &a) {
	matrix c(a.rows_n, a.cols_n);
	fo(i, a.rows_n) {
		fo(j, a.col_n) { c[i][j] = -a[i][j]; }
	}
	return c;
}
template <typename... Ts> bool operator==(matrix<Ts...> const &a, matrix<Ts...> const &b) { return a.rows_n == b.rows_n && a.cols_n == b.cols_n && a.a == b.a; }
template <typename... Ts> auto operator*(matrix<Ts...> const &a, matrix<Ts...> const &b) {
	/*! Returns the matrix product of a and b*/
	assert(a.cols_n == b.rows_n);
	matrix<Ts...> c{a.rows_n, b.cols_n};
	fo(i, c.rows_n) {
		fo(j, a.cols_n) {
			fo(k, c.cols_n) { c[i][k] += a[i][j] * b[j][k]; }
		}
	}
	return c;
}
/*! Test func*/
ll foo(ll a, ll b) { return a + b; }
/*! @brief Returns matrix x such that \f$ax = b\f$ and the determinant of \f$a\f$
via Gaussian elimination.
*/
template <typename T> pair<matrix<T>, T> gauss(matrix<T> b, matrix<T> a) {
	assert(a.is_square());
	assert(a.rows_n == b.rows_n);
	T det{1};
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
template <typename... Ts> matrix<Ts...> invert(const matrix<Ts...> &a) { return identity(multiplies<>{}, a) / a; }
template <typename... Ts> auto operator/(const matrix<Ts...> &b, const matrix<Ts...> &a) {
	/*! Returns \f$a^{-1}b\f$*/
	return gauss(b, a).first;
}
template <typename T> T det(const matrix<T> &a) {
	/*! Returns the determinant of matrix a*/
	return gauss(matrix<T>(a.rows_n, 1), a).second;
}
template <typename Stream, typename... Ts> auto &operator<<(Stream &os, matrix<Ts...> const &m) {
	/*! Print the matrix rows, line by line*/
	os << simple_tp(m) << endl;
	fo(i, m.rows_n) {
		copy(m[i], m[i] + m.cols_n, make_ostream_joiner(os, delim));
		os << endl;
	}
	return os << "}";
}
template <typename T> auto lin_recur(vector<T> const &c, const ll n) {
	/*! Returns nth term of linear recurrence described by c. \f$x(i) =
	 * x_{i-1}c_0 + x_{i-2}c_1 + \dots \f$ and \f$x(0) = 1\f$*/
	// TODO support constant term
	matrix<T> m(size(c), size(c));
	copy(al(c), m[0]);
	fo(i, 1, size(c)) { m[i][i - 1] = 1; }
	return power(m, n)[0][0];
}

} // namespace linear_algebra
