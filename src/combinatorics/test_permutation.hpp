#pragma once
#include "permutation.hpp"
namespace permutation::test {
void test_ops() {
	using ::operator/;
	Permutation p1{0, 1, 3, 2};
	Permutation p2{0, 2, 3, 1};
	assert((p1 * p2 == Permutation{0, 3, 2, 1}));
	assert(((p1 / p2) * p2 == p1));
	assert(((p2 / p1) * p1 == p2));
}
void test_cycles_impl(const Permutation &perm) {
	assert(Permutation(perm.to_cycles(), perm.size()) == perm);
}
void test_cycles() {
	test_cycles_impl(Permutation{2, 1, 6, 4, 5, 3, 0});
	test_cycles_impl(Permutation{0, 1, 2, 3});
	test_cycles_impl(Permutation{0});
}
void test_power() {
	Permutation perm{2, 1, 6, 4, 5, 3, 0};
	assert(permutation::power(perm, 10) == modulo_namespace::power(perm, 10));
	assert(permutation::power(perm, -10) == modulo_namespace::power(perm, -10));
}
void test_permutation() {
	test_ops();
	test_cycles();
	test_power();
}
} // namespace permutation::test
using namespace permutation::test;
