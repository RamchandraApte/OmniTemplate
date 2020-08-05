#pragma once
#include "bit.hpp"
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
