#pragma once
#include "core.hpp"
#include "utility.hpp"
/*! Binary indexed tree (also called Fenwick tree)
 * Value is the type of the value
 * MonoidOp is a Monoid on the Value type */
template <typename Value, typename MonoidOp = plus<>> class BIT {
	static constexpr Value identity{}; //!< The identity element
	vector<Value>
	    arr; //!< The array storing the BIT's internal values. Each element
		 //!< of this represents a range of elements.
	MonoidOp op{}; //!< The monoid operation functor
      public:
	//! Construct a BIT of size size_arg
	explicit BIT(const ll size_arg)
	    : arr(next_pow_of_2(size_arg) + 1, identity) {}
	Value query(ll r) const {
		/*! Returns sum of Monoid over elements in [0, r)*/
		auto sum = identity;
		for (; r; r -= get_len(r)) {
			sum = op(sum, arr[r]);
		}
		return sum;
	}
	void update(ll idx, const Value value) {
		/*! Update the value at idx by value. Note that this does _not_
		 * set the value to value*/
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
