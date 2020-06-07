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
	vector<T> sums;
	SegmentTree(const size_t size_) : sums(2 * bit_ceil(size_)) {}
};
