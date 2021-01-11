#include "core/all.hpp"
#include "core/main.hpp"
#define GRAPH
#define MATRIX
#ifdef GRAPH
#include "graph/all.hpp"
#endif
#ifdef MATRIX
#include "algebra/linear_algebra.hpp"
#include "number_theory/number_theory.hpp"
#endif
bool multitest{};
void main2() {
#ifdef GRAPH
	GraphAdj g(10);
	g.add_edge(2, 3);
	cout << g << endl;
#endif
#ifdef MATRIX
	matrix<ll> hello{{1, 2, 3}, {2, 3, 4}, {4, 5, 6}};
	cout << power(hello, 100) << endl;
#endif
	ll a, b;
	cin >> a >> b;
	cout << a + b << endl;
}
