#include "flow.hpp"
namespace flow::test {
template <typename Func> void test_flow_algo(const Func &algo) {
	{
		matrix<ll> flow(3, 3);
		flow[0][1] = 2;
		flow[1][2] = 3;
		flow[0][2] = 1;
		assert(total_flow(algo(flow)) == 3);
	}
	{
		matrix<ll> flow(4, 4);
		flow[0][1] = 2;
		flow[0][2] = 3;
		flow[1][2] = 2;
		flow[2][3] = 7;
		assert(total_flow(algo(flow)) == 5);
	}
	{
		matrix<ll> flow(4, 4);
		flow[0][1] = 3;
		flow[1][3] = 6;
		flow[0][2] = 6;
		flow[2][3] = 1;
		flow[2][1] = 4;
		assert(total_flow(algo(flow)) == 7);
	}
}
matrix<ll> random_flow() {
	const ll n = 2 + (reng() % 30);
	matrix<ll> flow(n, n);
	fo(i2, n) {
		fo(j2, i2 + 1, n) {
			ll i = i2, j = j2;
			if (reng() % 2 == 0) {
				swap(i, j);
			}
			flow[i][j] = 1 + (reng() % 30);
		}
	}
	return flow;
}
template <typename Func1, typename Func2> void test_compare_flow(const Func1 &algo1, const Func2 &algo2, ll n_it = 100) {
	fo(i, n_it) {
		const auto flow = random_flow();
		// FIXME generated flow diff?
		assert(total_flow(algo1(flow)) == total_flow(algo2(flow)));
	}
}
void test_flow() {
	test_flow_algo(edmond_karp);
	test_flow_algo(dinic);
	test_compare_flow(edmond_karp, dinic);
}
} // namespace flow::test
using namespace flow::test;
