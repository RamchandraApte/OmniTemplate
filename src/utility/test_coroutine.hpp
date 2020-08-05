#pragma once
#include "coroutine.hpp"
namespace coroutine::test {
void test_coroutine() {
	const ll a = 4;
	vl v;
	try {
		while (true) {
			v.push_back(coro(a));
		}
	} catch (out_of_range &) {
	}
	assert((v == vl{404, 0 * 0, 1 * 1, 2 * 2, 3 * 3, 505}));
}
} // namespace coroutine::test
using namespace coroutine::test;
