#include "template.h"
void test_matrix(){
	mat<ld> a{{2,3,5}, {3,6,10}, {5,9,16}};
	mat<ld> b{{1,2,3}, {4,5,6}, {9,7,8}};
	auto x = b/a;
	dbg(x);
	dbg(a*x);
	dbg(b);
	dbg(det(a));
}
void main2(){
	test_matrix();
}