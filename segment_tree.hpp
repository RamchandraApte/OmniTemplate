#pragma once
#include "core.hpp"
// TODO non commutative monoids, specify the ordering
size_t base_ceil(const size_t x, const size_t base) {
	ll pw = 1;
	for (; pw < x; pw *= base)
		;
	return pw;
}
// TODO persistent dynamic multidimensional
/*! Generic implicit lazy based segment tree
 * T is the value type of the segment tree
 * Query is the monoid for queries
 * Update is the monoid for queries
 * Query must be an additive monoid of a semiring, and Update must be a
 * multiplicative monoid of a semiring
 * base is the segment tree base. Default is 2.
 */
template <typename T, typename Query, typename Update, size_t base = 2> class SegmentTree {
      public:
	SegmentTree(const size_t size_arg)
	    : size_{size_arg}, qsum(base * base_ceil(size_arg, base), identity(Query{}, T{})),
	      lazy(qsum.size(), identity(Update{}, T{})) {}
	void down(const size_t idx) {
		/*! Push lazy update down*/
		qsum[idx] = Update{}(qsum[idx], lazy[idx]);
		if (base * idx < lazy.size()) {
			fo(i, base) { lazy[base * idx + i] += lazy[idx]; }
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
		auto ret = identity(Query{}, T{});
		const auto mid = [&](size_t i) {
			return (node_l * (base - i) + node_r * i) / base;
		};
		fo(inc, base) {
			ret = Query{}(ret, query(l, r, base * idx + inc, mid(inc), mid(inc + 1)));
		}
		return ret;
	}
	T query(const size_t l, const size_t r) {
		if (!(0 <= l && l <= r && r <= size_)) {
			throw out_of_range{"Segment tree query out of bounds"};
		}
		return query(l, r, 1, 0, qsum.size() / base);
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
		const auto mid = [&](size_t i) {
			return (node_l * (base - i) + node_r * i) / base;
		};
		qsum[idx] = identity(Query{}, T{});
		fo(inc, base) {
			update(l, r, val, base * idx + inc, mid(inc), mid(inc + 1));
			qsum[idx] = Query{}(qsum[idx],
					    query(l, r, base * idx + inc, mid(inc), mid(inc + 1)));
		}
	}
	void update(const size_t l, const size_t r, const T val) {
		update(l, r, val, 1, 0, qsum.size() / base);
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
