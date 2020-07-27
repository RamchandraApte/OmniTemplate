#pragma once
#include "core/all.hpp"
/**
 * @brief Binary indexed tree (also called Fenwick tree)
 * @param Value is the type of the value
 * @param MonoidOp is a Monoid operating on the Value type
 */
template <typename Value, typename MonoidOp = plus<>> class BIT {
	//! The array storing the BIT's internal values. Each element of this represents a range of
	//! elements.
	vector<Value> arr;
	MonoidOp op{}; //!< The monoid operation functor
      public:
	//! Construct a BIT of size size_arg
	explicit BIT(const ll size_arg)
	    : arr(bit_ceil(size_arg) + 1, identity(MonoidOp{}, Value{})) {}
	Value query(ll r) const {
		/*! Returns sum of Monoid over elements in [0, r)*/
		auto sum = identity(MonoidOp{}, Value{});
		for (; r; r -= get_len(r)) {
			sum = op(sum, arr[r]);
		}
		return sum;
	}
	/**
     * @brief  Update the value at idx by value. Note that this does _not_ set the value to value.
     * @param idx the index of the element
     * @param value the value the element will be updated by
     */
	void update(ll idx, const Value value) {
		++idx;
		for (; idx < arr.size(); idx += get_len(idx)) {
			arr[idx] = op(arr[idx], value);
		}
	}
      private:
	static ll get_len(const ll idx) {
		/*! Returns the length of the range of elements idx is
		 * responsible for*/
		return idx & (-idx);
	}
};
void test_bit() {
	BIT<ll> bit(10);
	bit.update(3, 4);
	assert((bit.query(10) == 4));
	bit.update(2, 3);
	assert((bit.query(2) == 0));
	assert((bit.query(3) == 3));
	assert((bit.query(4) == 7));
	bit.update(0, 2);
	bit.update(9, 5);
	assert((bit.query(10) == 4 + 3 + 2 + 5));
	assert((bit.query(0) == 0));
	assert((bit.query(1) == 2));
}
