
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_linear_algebra.hpp.rst.txt:

Program Listing for File program_listing_file_linear_algebra.hpp.rst.txt
========================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_linear_algebra.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_linear_algebra.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_linear_algebra.hpp:
   
   Program Listing for File linear_algebra.hpp
   ===========================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_linear_algebra.hpp>` (``linear_algebra.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      #include "modulo.hpp"
      #include "polynomial.hpp"
      // TODO Tensors? Also, matrix_row class.
      // TODO fix default constructor causing segfault
      namespace linear_algebra {
      tm() struct matrix {
          ll rows_n, cols_n; 
          vector<T> a; 
          explicit matrix(ll r_, ll c_, df(v, 0LL))
              : rows_n(r_), cols_n(c_), a(rows_n * cols_n, v) {
              assert(rows_n >= 1 && cols_n >= 1);
          }
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
      };
      template <typename T> auto identity(const plus<>, const matrix<T> &mat) {
          return matrix(mat.rows_n, mat.cols_n);
      }
      template <typename T> auto identity(const multiplies<>, const matrix<T> &mat) {
          assert(mat.rows_n == mat.cols_n);
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
      tm(...) bool operator==(matrix<T...> const &a, matrix<T...> const &b) {
          return a.rows_n == b.rows_n && a.cols_n == b.cols_n && a.a == b.a;
      }
      tm(...) auto operator*(matrix<T...> const &a, matrix<T...> const &b) {
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
          assert(a.rows_n == a.cols_n);
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
      tm(...) auto operator/(const matrix<T...> &b, const matrix<T...> &a) {
          return gauss(b, a).first;
      }
      template <typename T> T det(const matrix<T> &a) {
          return gauss(matrix<T>(a.rows_n, 1), a).second;
      }
      template <typename Stream, typename... T>
      auto &operator<<(Stream &os, matrix<T...> const &m) {
          os << simple_tp(m) << endl;
          fo(i, m.rows_n) {
              copy(m[i], m[i] + m.cols_n, make_ostream_joiner(os, delim));
              os << endl;
          }
          return os << "}";
      }
      void test_matrix() {
          with _m{ll(1e9 + 7), modulo::modulus};
          matrix<modulo> a{{2, 3, 5}, {3, 6, 10}, {5, 9, 16}};
          matrix<modulo> b{{1, 2, 3}, {4, 5, 6}, {9, 7, 8}};
          assert(a * (b / a) == b);
      }
      template <typename T> auto lin_recur(vector<T> const &c, const ll n) {
          // TODO support constant term
          matrix<T> m(size(c), size(c));
          copy(al(c), m[0]);
          fo(i, 1, size(c)) { m[i][i - 1] = 1; }
          return power(m, n)[0][0];
      }
      void test_lin_recur() {
          assert(lin_recur(vl{1, 2}, 5) == 21);
          assert(lin_recur(vl{2, 3, 1}, 4) == 65);
      }
      
      template <typename T> Polynomial<T> lin_recur_coef(vector<T> const &c) {}
      void test_linear_algebra() {
          test_matrix();
          test_lin_recur();
          test_invert();
          // test_lin_recur_coef();
      }
      } // namespace linear_algebra
      using namespace linear_algebra;
