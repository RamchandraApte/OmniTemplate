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
      public:
	SegmentTree(const size_t size_arg)
	    : size_{size_arg}, qsum(2 * bit_ceil(size_arg), identity(Query{}, T{})),
	      lazy(2 * bit_ceil(size_arg), identity(Update{}, T{})) {}
	void down(const size_t idx) {
		/*! Push lazy update down*/
		qsum[idx] = Update{}(qsum[idx], lazy[idx]);
		if (2 * idx < lazy.size()) {
			fo(i, 2) { lazy[2 * idx + i] += lazy[idx]; }
		}
		lazy[idx] = identity(Update{}, lazy[idx]);
	}
	T query(const size_t l, const size_t r, const size_t idx, const size_t node_l,
		const size_t node_r) {
		/*! Returns the sum over the intersection of [query_l, query_r) with [node_l,
		 * node_r) */
		down(idx);
		if (node_r <= l || r <= node_l) {
			return 0;
		}
		if (l <= node_l && node_r <= r) {
			return qsum[idx];
		}
		const size_t mid = (node_l + node_r) / 2;
		return Query{}(query(l, r, 2 * idx, node_l, mid),
			       query(l, r, 2 * idx + 1, mid, node_r));
	}
	T query(const size_t l, const size_t r) {
		if (!(0 <= l && l <= r && r <= size_)) {
			throw out_of_range{"Segment tree query out of bounds"};
		}
		return query(l, r, 1, 0, qsum.size() / 2);
	}
	void update(const size_t l, const size_t r, const T val, const size_t idx,
		    const size_t node_l, const size_t node_r) {
		/*! Update the range l to r with the update val*/
		down(idx);
		if (node_r <= l || r <= node_l) {
			return;
		}
		if (l <= node_l && node_r <= r) {
			lazy[idx] += val;
			down(idx);
			return;
		}
		const size_t mid = (node_l + node_r) / 2;
		update(l, r, val, 2 * idx, node_l, mid);
		update(l, r, val, 2 * idx + 1, mid, node_r);
		qsum[idx] = Query{}(qsum[2 * idx], qsum[2 * idx + 1]);
	}
	void update(const size_t l, const size_t r, const T val) {
		update(l, r, val, 1, 0, qsum.size() / 2);
	}

      private:
	size_t size_;
	vector<T> qsum;
	vector<T> lazy;
};
void test_segment_tree() {
	SegmentTree<ll, Max, plus<>> seg{10};
	seg.update(0, 10, inf);
	assert(seg.query(0, 10) == 0);
	assert(seg.query(3, 4) == 0);
	seg.update(3, 4, 10);
	seg.update(2, 4, 20);
	assert(seg.query(3, 4) == 30);
	assert(seg.query(2, 4) == 30);
	assert(seg.query(2, 3) == 20);
	assert(seg.query(1, 10) == 30);
	seg.update(0, 2, 10);
	assert(seg.query(1, 10) == 30);
}
