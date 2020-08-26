#pragma once
#include "utility.hpp"
namespace utility::test {
void test_with() {
	ll var = 12;
	auto inner_func = [&] {
		with _w(23, var);
		assert(var == 23);
		var = 45;
	};
	inner_func();
	assert(var == 12);
}
void test_uniq() {
	assert((uniq(vector<ll>{2, -1, 3, -1, 2, 3}) == vector<ll>{-1, 2, 3}));
	assert((uniq<equal_to<>, greater<>>(vector<ll>{1, -3, 5}) == vector<ll>{5, 1, -3}));
}
void test_key_compare() {
	vector<ll> a{24, 25};
	assert(key_compare<greater<>>([&](ll i) { return a[i]; })(1, 0));
}
void test_bit_ceil() {
	assert(bit_ceil(0) == 1);
	assert(bit_ceil(1) == 1);
	assert(bit_ceil(2) == 2);
	assert(bit_ceil(3) == 4);
	assert(bit_ceil(4) == 4);
	assert(bit_ceil(5) == 8);
	assert(bit_ceil((1LL << 45) - 100) == 1LL << 45);
	assert(bit_ceil((1LL << 45)) == 1LL << 45);
}
void test_next_comb() {
	ll x = 0b111;
	x = next_comb(x);
	assert(x == 0b1011);
	x = next_comb(x);
	assert(x == 0b1101);
	x = next_comb(x);
	assert(x == 0b1110);
	x = 0b1;
	x = next_comb(x);
	assert(x == 0b10);
	x = next_comb(x);
	assert(x == 0b100);
}
void test_ar() {
	static_assert(is_same_v<ar_t<ll[2][3]>, array<array<ll, 3>, 2>>);
	static_assert(is_same_v<ar_t<array<ll, 200>[2][3]>, array<array<array<ll, 200>, 3>, 2>>);
}
void test_counting_sort() {
	// TODO test stability
	const vector<ll> vec{3, 1, 5, 1, 2, 3, 4};
	auto sorted_vec = vec;
	sort(al(sorted_vec));
	auto count_sorted_vec = vec;
	counting_sort(
	    al(count_sorted_vec), [](auto x) { return x; }, *max_element(al(vec)) + 1);
	assert(count_sorted_vec == sorted_vec);
}
void test_utility() {
	test_with();
	test_uniq();
	test_next_comb();
	test_ar();
	test_bit_ceil();
	test_key_compare();
	test_counting_sort();
}
} // namespace utility::test
using namespace utility::test;
