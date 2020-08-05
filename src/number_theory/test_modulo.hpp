#include "modulo.hpp"
namespace modulo_namespace::test {
void test_power() {
	assert(power(2, 3) == 8);
	assert(power(3, 10) == 59049);
	with _m{static_cast<ll>(1e9 + 7), modulo::modulus};
	assert(power(modulo{3}, 1000) == modulo{56888193});
	assert(power(modulo{3}, -1000) * power(modulo{3}, 1000) == 1);
	assert(power(modulo{1}, 0) == 1);
}
void test_md() {
	with _m{7, modulo::modulus};
	assert(modulo{34} / modulo{-2} == modulo{4});
	assert(modulo{2} - modulo{6} == modulo{3});
}
void test_modulo() {
	test_power();
	test_md();
}
} // namespace modulo_namespace::test
using namespace modulo_namespace::test;
