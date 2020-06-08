#pragma once
#include "core.hpp"
/*! Segment tree class
 * T is the value type of the segment tree
 * Query is the monoid for queries
 * Update is the monoid for queries
 * Query must be an additive monoid of a semiring, and Update must be a
 * multiplicative monoid of a semiring
 */
template <typename T, typename Query, typename Update> class SegmentTree {
	size_t size_{};
	vector<T> sums;
	SegmentTree(const size_t size_arg) : size_{bit_ceil(size_arg)}, sums(2 * size_) {}
	T query(const size_t l, const size_t r, const size_t idx, const size_t node_l,
		const size_t node_r) {
		/*! Returns the sum over the intersection of [query_l, query_r) with [node_l,
		 * node_r) */
		if (node_r <= l) {
			return {};
		}
		if (l <= node_l && node_r <= r) {
			return sums[idx];
		}
		const size_t mid = (l + r) / 2;
		return query(l, r, 2 * idx, node_l, mid) + query(l, r, 2 * idx, mid, node_r);
	}
	T query(const size_t l, const size_t r) { return query(l, r, 1, 0, size_); }
	void update(const size_t l, const size_t r, const T val) {
		// TODO
	}
};
