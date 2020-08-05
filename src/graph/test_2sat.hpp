#pragma once
#include "2sat.hpp"
namespace sat2::test {
void test_sat2() {
	const auto ret1 = sat2({{2, 1}, {-2, 3}}, 3).value();
	assert(ret1[1] || ret1[2]);
	assert(!ret1[2] || ret1[3]);
	const auto ret2 = sat2({{2, 1}, {3, 2}, {-2, -1}}, 3).value();
	assert(ret2[1] || ret2[2]);
	assert(ret2[2] || ret2[3]);
	assert(!ret2[2] || !ret2[1]);
	const auto ret3 = sat2({{1, 1}, {-1, -1}}, 1);
	assert(!ret3);
	const auto ret4 = sat2({{1, 2}, {3, 2}, {-1, -1}, {-2, -2}}, 3);
	assert(!ret4);
}
} // namespace sat2::test
using namespace sat2::test;
