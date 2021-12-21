#include "polynomial.hpp"
namespace polynomial_ns::test {
void test_polynomial() {
	with _w{1e9 + 7, modulo::modulus};
	using poly = Polynomial<modulo>;
	poly p1{1, 2, 3};
	poly p2{2, -3};
	/*3x^2+2x+1
	-3x+2

	4x+1*/
	assert((p2 * p1 == p1 * p2 && p1 * p2 == poly{2, 1, 0, -9, 0, 0}));
	assert((p2 + p1 == p1 + p2 && p1 + p2 == poly{3, -1, 3, 0}));
	assert((p1 + p2 != poly{3, -1, 3, 1}));
	assert((poly{3} * p2 == poly{6, -9}));
	assert((p1 % p2 == poly{11_M / 3_M}));
	assert((p1 % poly{2} == poly{}));
	assert((p2 % p1 == p2));
	assert(poly{}.degree() == -inf);
	assert((poly{0, 2, 0}.degree() == 1));
}
}; // namespace polynomial_ns::test
using namespace polynomial_ns::test;
