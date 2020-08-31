#pragma once
#include "big_integer.hpp"
namespace bigint::test {
void test_bigint() {
	const auto int_max = numeric_limits<unsigned int>::max();
	BigInt x{vector<unsigned int>{int_max, int_max}};
	const auto sum = x + x;
	assert((sum == BigInt{vector<unsigned int>{4294967294, 4294967295, 1}}));
}
} // namespace bigint::test
using namespace bigint::test;
