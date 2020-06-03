#include "template.hpp"
void test_all() {
	test_matrix();
	test_sat2();
	test_number_theory();
	test_modulo();
	test_queue();
	test_splay_tree();
	test_geometry();
	test_utility();
	test_combinatorics();
	test_dsu();
	test_graph_theory();
	test_string();
	test_coroutine();
	test_linear_algebra();
	cout << "\e[0;32mAccepted\e[0m" << endl;
}
void main2() { test_all(); }
