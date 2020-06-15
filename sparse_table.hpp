#pragma once
#include "core.hpp"
/*! Sparse table. T is the type of the data, Semilattice is a bounded semilattice.*/
template <typename T, typename Semilattice> class SparseTable {
      public:
	explicit SparseTable(const vector<T> &arr) : meet(ceil_log(arr.size(), 2), vector<ll>(arr.size())) {
		meet[0] = arr;
		fo(pw, 1, meet.size()) {
			fo(i, arr.size()) {
				const auto half = 1LL << (pw - 1);
				// TODO signed size
				meet[pw][i] = Semilattice{}(meet[pw - 1][i], meet[pw - 1][min(i + half, static_cast<ll>(arr.size()) - 1)]);
			}
		}
	}
	T query(ll l, ll r) const {
		const auto len = r - l;
		// TODO put this in a function
		const auto floor_log2 = (sizeof(ll) * CHAR_BIT) - 1 - __builtin_clzll(len);
		return Semilattice{}(meet[floor_log2][l], meet[floor_log2][r - (1LL << floor_log2)]);
	}

      private:
	vc<vl> meet; //!< meet[pw][i] stores the meet of elements in range [i, i+2^pw)
};
template <typename T, typename Monoid> class DisjointSparseTable {
      public:
	explicit DisjointSparseTable(vector<T> arr) : sum(ceil_log(arr.size(), 2), vector<T>(base_ceil(arr.size(), 2))) {
		arr.resize(sum[0].size(), identity(Monoid{}, T{}));
		fo(lvl, sum.size()) {
			fo(blk, 1LL << lvl) {
				// The first half of the block contains suffix sums, the second half contains prefix sums
				const auto st = blk << (sum.size() - lvl);
				const auto ed = (blk + 1) << (sum.size() - lvl);
				const auto mid = (ed + st) / 2;
				auto val = arr[mid];
				sum[lvl][mid] = val;
				fo(x, mid + 1, ed) {
					val = Monoid{}(val, arr[x]);
					sum[lvl][x] = val;
				}
				val = arr[mid - 1];
				sum[lvl][mid - 1] = val;
				fr(x, st, mid - 1) {
					val = Monoid{}(val, arr[x]);
					sum[lvl][x] = val;
				}
			}
		}
	}
	T query(ll l, ll r) const {
		/*! Returns sum of Monoid over range [l, r)*/
		assert(l < r);
		--r;
		const auto num_diff = (sizeof(ll) * CHAR_BIT) - 1 - __builtin_clzll(l ^ r);
		const auto lvl = sum.size() - 1 - num_diff;
		auto ret = sum[lvl][l];
		if (l != r) {
			ret = Monoid{}(ret, sum[lvl][r]);
		}
		return ret;
	}

      private:
	vector<vector<T>> sum;
};
template <template <typename...> typename Table, typename T, typename Monoid> void test_sparse_table_impl() {
	vector<T> data{6, 2, 4, 1, 7, 3, 4, 2, 7, 2, 4, 1, 6};
	Table<T, Monoid> sp{data};
	fo(start, data.size()) {
		fo(end, start + 1, data.size()) { assert(sp.query(start, end) == accumulate(begin(data) + start, begin(data) + end, identity(Monoid{}, T{}), Monoid{})); }
	}
}
void test_sparse_table() {
	with _m{ll(1e9 + 7), modulo::modulus};
	test_sparse_table_impl<SparseTable, ll, Min>();
	test_sparse_table_impl<DisjointSparseTable, ll, Min>();
	test_sparse_table_impl<DisjointSparseTable, ll, plus<>>();
	test_sparse_table_impl<DisjointSparseTable, modulo, multiplies<>>();
}
