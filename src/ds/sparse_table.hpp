#pragma once
#include "core/all.hpp"
namespace sparse_table {
// TODO return identity when l = r
/*! Sparse table.
 * @param T is the type of the data,
 * @param Semilattice is a bounded semilattice.*/
template <typename T, typename Semilattice> class SparseTable {
      public:
	explicit SparseTable(const vector<T> &arr) : meet(log_ceil(arr.size(), 2), vector<ll>(arr.size())) {
		meet[0] = arr;
		fo(pw, 1, meet.size()) {
			fo(i, arr.size()) {
				const auto half = 1LL << (pw - 1);
				meet[pw][i] = Semilattice{}(meet[pw - 1][i], meet[pw - 1][min(i + half, ssize(arr) - 1)]);
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
	vector<vector<ll>> meet; //!< meet[pw][i] stores the meet of elements in range [i, i+2^pw)
};
/*! @brief Disjoint sparse table.
 * 
 * Space complexity: \f$O(n \log n)\f$.
 * 
 * Time complexity: \f$O(n \log n)\f$ to construct, \f$O(1)\f$ per query.
 */
template <typename T, typename Monoid> class DisjointSparseTable {
      public:
	explicit DisjointSparseTable(vector<T> arr) : sum(log_ceil(arr.size(), 2), vector<T>(power_ceil(arr.size(), 2))) {
		arr.resize(sum[0].size(), identity(Monoid{}, T{}));
		fo(level, sum.size()) {
			fo(block, 1LL << level) {
				// The first half of the block contains suffix sums, the second half contains prefix sums
				const auto start = block << (sum.size() - level);
				const auto end = (block + 1) << (sum.size() - level);
				const auto middle = (end + start) / 2;
				auto val = arr[middle];
				sum[level][middle] = val;
				fo(x, middle + 1, end) {
					val = Monoid{}(val, arr[x]);
					sum[level][x] = val;
				}
				val = arr[middle - 1];
				sum[level][middle - 1] = val;
				fr(x, start, middle - 1) {
					val = Monoid{}(val, arr[x]);
					sum[level][x] = val;
				}
			}
		}
	}
    /*! Returns Monoid sum over range [l, r)*/
	T query(ll l, ll r) const {
		assert(l < r);
		// Convert half open interval to closed interval
		--r;
		if(l == r){
			return sum.back()[l];
		}
		// Position of the leftmost different bit from the right
		const auto pos_diff = (sizeof(ll) * CHAR_BIT) - 1 - __builtin_clzll(l ^ r);
		const auto level = sum.size() - 1 - pos_diff;
		return Monoid{}(sum[level][l], sum[level][r]);
	}

      private:
	vector<vector<T>> sum;
};
} // namespace sparse_table
using namespace sparse_table;
