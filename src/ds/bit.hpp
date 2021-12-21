#pragma once
#include "core/all.hpp"
/**
 * @brief Binary indexed tree (also called Fenwick tree)
 * @tparam Value value type
 * @tparam MonoidOp monoid operating on the Value type
 */
template <typename Value, typename MonoidOp = plus<>> class BIT {
	//! The array storing the BIT's internal values. Each element of this represents a range of
	//! elements.
	vector<Value> arr;
	MonoidOp op{}; //!< The monoid operation functor
      public:
	//! Construct a BIT of size size_arg
	explicit BIT(const ll size_arg)
	    : arr(bit_ceil(size_arg) + 1, identity_elt(MonoidOp{}, Value{})) {}
	/*! @brief Returns sum of Monoid over elements in [0, r)*/
	Value query(ll r) const {
		auto sum = identity_elt(MonoidOp{}, Value{});
		for (; r; r -= get_len(r)) {
			sum = op(sum, arr[r]);
		}
		return sum;
	}
	/**
	 * @brief  Update the value at idx by value. Note that this does _not_ set the value to
	 * value.
	 * @param idx the index of the element
	 * @param value the value the element will be updated by
	 */
	void update(ll idx, const Value value) {
		for (++idx; idx < arr.size(); idx += get_len(idx)) {
			arr[idx] = op(arr[idx], value);
		}
	}

      private:
	/*! @brief Returns the length of the range of elements idx is
	 * responsible for*/
	static ll get_len(const ll idx) { return idx & (-idx); }
};
