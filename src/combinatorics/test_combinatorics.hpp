#pragma once
#include "combinatorics.hpp"
namespace combinatorics::test {
void test_perm() {
	assert(perm(4, 2) == 4 * 3);
	assert(perm(4, 4) == 4 * 3 * 2 * 1);
	assert(perm(4, 0) == 1);
	assert(perm(0, 0) == 1);
	assert(perm(1, 0) == 1);
	assert(perm(1, 1) == 1);
}
void test_fact() {
	assert(fact(4) == 4 * 3 * 2 * 1);
	assert(fact(0) == 1);
	assert(fact(1) == 1);
	assert(fact(8) == 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1);
}
void test_choose() {
	assert(binom(5, 2) == 10);
	assert(binom(5, 3) == 10);
	assert(binom(5, 0) == 1);
	assert(binom(5, 5) == 1);
	assert(binom(0, 0) == 1);
	assert(binom(1, 0) == 1);
	assert(binom(1, 1) == 1);
	assert(binom(6, 3) == 20);
}
void test_combinatorics() {
	test_perm();
	test_fact();
	test_choose();
}
} // namespace combinatorics::test
using namespace combinatorics::test;
