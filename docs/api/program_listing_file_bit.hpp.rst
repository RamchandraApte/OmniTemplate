
.. _program_listing_file_bit.hpp:

Program Listing for File bit.hpp
================================

|exhale_lsh| :ref:`Return to documentation for file <file_bit.hpp>` (``bit.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "core.hpp"
   #include "utility.hpp"
   template <typename Value, typename MonoidOp = plus<>> class BIT {
       vector<Value> arr;
       MonoidOp op{}; 
         public:
       explicit BIT(const ll size_arg)
           : arr(bit_ceil(size_arg) + 1, identity(MonoidOp{}, Value{})) {}
       Value query(ll r) const {
           auto sum = identity(MonoidOp{}, Value{});
           for (; r; r -= get_len(r)) {
               sum = op(sum, arr[r]);
           }
           return sum;
       }
       void update(ll idx, const Value value) {
           ++idx;
           for (; idx < arr.size(); idx += get_len(idx)) {
               arr[idx] = op(arr[idx], value);
           }
       }
         private:
       static ll get_len(const ll idx) {
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
