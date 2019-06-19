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
void test_sat2(){
	for(char c:*sat2({{1,2},{-2, 3}})){
		dbg((ll)c);
	}
};
void test_totient(){
	assert(totient(1) == 1 && totient(2) == 1 && totient(6) == 2 && totient(84) == 24 && totient(127) == 126);
}
void main2(){
	test_matrix();
	test_sat2();
	test_totient();
}