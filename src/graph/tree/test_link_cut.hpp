#include "link_cut.hpp"
namespace link_cut::test {
void test_link_cut_tree() {
	vector<Node *> nodes(10);
	generate(al(nodes), make_tree);
	link(nodes[1], nodes[2]);
	assert(find_root(nodes[2]) == nodes[1]);
	assert(find_root(nodes[1]) == nodes[1]);
	assert(lca(nodes[1], nodes[2]) == nodes[1]);
	link(nodes[0], nodes[1]);
	assert(lca(nodes[2], nodes[1]) == nodes[1]);
	assert(lca(nodes[0], nodes[2]) == nodes[0]);
	assert(lca(nodes[0], nodes[1]) == nodes[0]);
	assert(lca(nodes[1], nodes[1]) == nodes[1]);
	assert(lca(nodes[1], nodes[8]) == nullptr);
	assert(find_root(nodes[2]) == nodes[0]);
	assert(find_root(nodes[1]) == nodes[0]);
	assert(find_root(nodes[0]) == nodes[0]);
	link(nodes[3], nodes[4]);
	link(nodes[4], nodes[5]);
	assert(find_root(nodes[5]) == nodes[3]);
	link(nodes[0], nodes[3]);
	assert(lca(nodes[4], nodes[1]) == nodes[0]);
	assert(lca(nodes[4], nodes[4]) == nodes[4]);
	assert(lca(nodes[6], nodes[4]) == nullptr);
	link(nodes[6], nodes[7]);
	link(nodes[6], nodes[8]);
	link(nodes[8], nodes[9]);
	link(nodes[0], nodes[6]);
	assert(lca(nodes[6], nodes[4]) == nodes[0]);
	assert(find_root(nodes[3]) == nodes[0]);
	assert(find_root(nodes[2]) == nodes[0]);
	cut(nodes[1]);
	assert(find_root(nodes[2]) == nodes[1]);
	cut(nodes[3]);
	assert(find_root(nodes[3]) == nodes[3]);
	assert(find_root(nodes[4]) == nodes[3]);
	assert(find_root(nodes[5]) == nodes[3]);
	cut(nodes[4]);
	link(nodes[0], nodes[4]);
	assert(find_root(nodes[5]) == nodes[0]);
	assert(find_root(nodes[9]) == nodes[0]);
	assert(find_root(nodes[6]) == nodes[0]);
	cut(nodes[8]);
	assert(find_root(nodes[9]) == nodes[8]);
	assert(find_root(nodes[8]) == nodes[8]);
	assert(find_root(nodes[0]) == nodes[0]);
}
} // namespace link_cut::test
using namespace link_cut::test;
