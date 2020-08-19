#include "algebra/test_linear_algebra.hpp"
#include "algebra/test_polynomial.hpp"
#include "combinatorics/test_combinatorics.hpp"
#include "combinatorics/test_permutation.hpp"
#include "core/template.hpp"
#include "core/test_utility.hpp"
#include "ds/test_bit.hpp"
#include "ds/test_cht.hpp"
#include "ds/test_dsu.hpp"
#include "ds/test_queue.hpp"
#include "ds/test_segment_tree.hpp"
#include "ds/test_sparse_table.hpp"
#include "ds/test_splay_tree.hpp"
#include "graph/test_2sat.hpp"
#include "graph/test_all.hpp"
#include "graph/test_biconnected.hpp"
#include "graph/test_bipartite.hpp"
#include "graph/tree/test_hld.hpp"
#include "graph/tree/test_link_cut.hpp"
#include "number_theory/test_modulo.hpp"
#include "number_theory/test_number_theory.hpp"
#include "utility/test_coroutine.hpp"
#include "utility/test_dict_search.hpp"
#include "utility/test_graph_draw.hpp"
#include "utility/test_string.hpp"
bool multitest{};
void test_all() {
	test_dict_search();
	test_utility();
	test_graph_theory();
	test_dsu();
	test_sat2();
	test_modulo();
	test_number_theory();
	test_queue();
	test_splay_tree();
	test_geometry();
	test_combinatorics();
	test_string();
	test_coroutine();
	test_linear_algebra();
	test_permutation();
	test_bit();
	test_segment_tree();
	test_polynomial();
	test_sparse_table();
	test_hld();
	test_link_cut_tree();
	if (false) {
		test_graph_draw();
	}
	clog << "\e[0;32mAccepted\e[0m" << endl;
}
void main2() { test_all(); }
