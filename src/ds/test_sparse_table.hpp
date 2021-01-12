#pragma once
#include "number_theory/modulo.hpp"
#include "sparse_table.hpp"
namespace sparse_table::test {
template <template <typename...> typename Table, typename T, typename Monoid>
void test_sparse_table_impl() {
	vector<T> data{6, 2, 4, 1, 7, 3, 4, 2, 7, 2, 4, 1, 6};
	Table<T, Monoid> sp{data};
	fo(start, data.size()) {
		fo(end, start, data.size()) {
			assert(sp.query(start, end) ==
			       accumulate(begin(data) + start, begin(data) + end,
					  identity(Monoid{}, T{}), Monoid{}));
		}
	}
}
void test_sparse_table() {
	with _m{ll(1e9 + 7), modulo::modulus};
	test_sparse_table_impl<SparseTable, ll, Min>();
	test_sparse_table_impl<DisjointSparseTable, ll, Min>();
	test_sparse_table_impl<DisjointSparseTable, ll, plus<>>();
	test_sparse_table_impl<DisjointSparseTable, modulo, multiplies<>>();
}
} // namespace sparse_table::test
using namespace sparse_table::test;
