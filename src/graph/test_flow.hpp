#include "flow.hpp"
template <typename Func> void test_flow_algo(const Func &algo) {
	matrix<ll> flow(3, 3);
	flow[0][1] = 2;
	flow[1][2] = 3;
	flow[0][2] = 1;
	assert(total_flow(algo(flow)) == 3);

	{
		matrix<ll> flow(4, 4);
		flow[0][1] = 2;
		flow[0][2] = 3;
		flow[1][2] = 2;
		flow[2][3] = 7;
		assert(total_flow(algo(flow)) == 5);
	}
}
void test_flow() { test_flow_algo(edmond_karp); }
