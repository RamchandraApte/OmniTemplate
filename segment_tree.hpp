#pragma once
#include "core.hpp"
// TODO non commutative monoids, specify the ordering
size_t base_ceil(const size_t x, const size_t base) {
	ll pw = 1;
	for (; pw < x; pw *= base)
		;
	return pw;
}
// TODO persistent multidimensional
/*! Generic explicit/implicit lazy based segment tree
 * T is the value type of the segment tree
 * Query is the monoid for queries
 * Update is the monoid for queries
 * Query must be an additive monoid of a semiring, and Update must be a
 * multiplicative monoid of a semiring
 * base is the segment tree base. Default is 2.
 */
template <typename T, typename Query, typename Update, bool has_lazy = true, bool has_ptr = true,
	  size_t base = 2>
class SegmentTree {
      public:
	SegmentTree(const size_t size_arg)
	    : size_{size_arg}, ceil_size{base_ceil(size_arg, base)},
	      qsum(!has_ptr ? base * ceil_size : 0, identity(Query{}, T{})),
	      lazy(!has_ptr && has_lazy ? qsum.size() : 0, identity(Update{}, T{})) {
		if constexpr (!has_ptr) {
			root = 1;
		} else {
			root = new NodeObj{};
		}
	}
	struct NodeObj {
		T qsum{identity(Query{}, T{})};
		T lazy{identity(Update{}, T{})};
		array<NodeObj *, base> child{};
	};
	using Node = conditional_t<has_ptr, NodeObj *, size_t>;
	auto &get_lazy(NodeObj *const &obj) { return obj->lazy; }
	auto get_child(NodeObj *const &obj, const size_t i) { return obj->child[i]; }
	auto &get_qsum(NodeObj *const &obj) { return obj->qsum; }
	auto &get_lazy(const size_t idx) { return lazy[idx]; }
	auto get_child(const size_t idx, const size_t i) { return base * idx + i; }
	auto &get_qsum(const size_t idx) { return qsum[idx]; }
	void down(const Node idx, const size_t node_l, const size_t node_r) {
		if constexpr (has_lazy) {
			/*! Push lazy update down*/
			get_qsum(idx) = Update{}(get_qsum(idx), get_lazy(idx));
			// if (base * idx < lazy.size()) {
			if (node_r - node_l > 1) {
				if constexpr (has_ptr) {
					for (auto &ptr : idx->child) {
						if (!ptr) {
							ptr = new NodeObj{};
						}
					}
				}
				fo(i, base) { get_lazy(get_child(idx, i)) += get_lazy(idx); }
			}
			get_lazy(idx) = identity(Update{}, get_lazy(idx));
		}
	}
	T query(const size_t l, const size_t r, const Node idx, const size_t node_l,
		const size_t node_r) {
		/*! Returns the sum over the intersection of [query_l, query_r) with [node_l,
		 * node_r) */
		if (node_r <= l || r <= node_l) {
			return identity(Query{}, T{});
		}
		down(idx, node_l, node_r);
		if (l <= node_l && node_r <= r) {
			return get_qsum(idx);
		}
		auto ret = identity(Query{}, T{});
		const auto mid = [&](size_t i) {
			return (node_l * (base - i) + node_r * i) / base;
		};
		fo(inc, base) {
			ret =
			    Query{}(ret, query(l, r, get_child(idx, inc), mid(inc), mid(inc + 1)));
		}
		return ret;
	}
	T query(const size_t l, const size_t r) {
		if (!(0 <= l && l <= r && r <= size_)) {
			throw out_of_range{"Segment tree query out of bounds"};
		}
		return query(l, r, root, 0, ceil_size);
	}
	void update(const size_t l, const size_t r, const T val, const Node idx,
		    const size_t node_l, const size_t node_r) {
		/*! Update the range l to r with the update val*/
		if (node_r <= l || r <= node_l) {
			return;
		}
		down(idx, node_l, node_r);
		if (l <= node_l && node_r <= r) {
			if constexpr (has_lazy) {
				get_lazy(idx) = Update{}(get_lazy(idx), val);
				down(idx, node_l, node_r);
			} else {
				get_qsum(idx) = Update{}(get_qsum(idx), val);
			}
			return;
		}
		const auto mid = [&](size_t i) {
			return (node_l * (base - i) + node_r * i) / base;
		};
		get_qsum(idx) = identity(Query{}, T{});
		fo(inc, base) {
			update(l, r, val, get_child(idx, inc), mid(inc), mid(inc + 1));
			get_qsum(idx) = Query{}(get_qsum(idx), query(l, r, get_child(idx, inc),
								     mid(inc), mid(inc + 1)));
		}
	}
	void update(const size_t l, const size_t r, const T val) {
		if constexpr (!has_lazy) {
			assert(l + 1 == r);
		}
		update(l, r, val, root, 0, ceil_size);
	}

      private:
	size_t size_;
	size_t ceil_size;
	Node root;
	vector<T> qsum;
	vector<T> lazy;
};
void test_segment_tree() {
	constexpr bool has_lazy = true;
	SegmentTree<ll, Max, plus<>, has_lazy> seg{1000};
	assert(seg.query(1, 3) == -inf);
	assert(seg.query(7, 9) == -inf);
	fo(i, 0, 10) { seg.update(i, i + 1, inf); }
	assert(seg.query(0, 10) == 0);
	assert(seg.query(3, 4) == 0);
	seg.update(2, 3, 2);
	seg.update(4, 5, 3);
	assert(seg.query(0, 10) == 3);
	assert(seg.query(3, 4) == 0);
	assert(seg.query(2, 4) == 2);
	seg.update(2, 3, -2);
	seg.update(4, 5, -3);
	assert(seg.query(2, 4) == 0);
	assert(seg.query(0, 10) == 0);
	fo(i, 0, 10) { seg.update(i, i + 1, -inf); }
	if constexpr (has_lazy) {
		seg.update(0, 10, inf);
		seg.update(3, 4, 10);
		seg.update(2, 4, 20);
		assert(seg.query(3, 4) == 30);
		assert(seg.query(2, 4) == 30);
		assert(seg.query(2, 3) == 20);
		assert(seg.query(1, 10) == 30);
		seg.update(0, 2, 10);
		assert(seg.query(1, 10) == 30);
	}
}
