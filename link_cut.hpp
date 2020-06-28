#pragma once
#include "core.hpp"
#include "splay_tree.hpp"
using Node = SplayTree<ll>::Node;
Node *make_tree() { return new Node{}; }
void access(Node *node) {
	// Moves node to the root of the auxillary tree containing the root node of the tree
	node->splay();
	if (node->child[1]) {
		node->child[1]->path_parent = node;
		node->child[1]->parent = nullptr;
		node->child[1] = nullptr;
	}
	while (node->path_parent) {
		auto par = node->path_parent;
		par->splay();
		if (par->child[1]) {
			par->child[1]->path_parent = par;
			par->child[1]->parent = nullptr;
		}
		par->child[1] = node;
		node->parent = par;
		node->path_parent = nullptr;
		// node = par;
		node->splay();
	}
	node->splay();
}
Node *find_root(Node *node) {
	// Finds the root of the tree containing node
	access(node);
	for (; node->child[0]; node = node->child[0])
		;
	access(node);
	return node;
}
void cut(Node *node) {
	// Detaches the subtree of node from the tree of node's parent
	access(node);
	node->child[0]->parent = nullptr;
	node->child[0] = nullptr;
}
void link(Node *par, Node *child) {
	// Makes child the child of par
	access(child);
	access(par);
	child->child[0] = par;
	par->parent = child;
}
void test_link_cut_tree() {
	vector<Node *> nodes(10);
	generate(al(nodes), make_tree);
	link(nodes[1], nodes[2]);
	assert(find_root(nodes[2]) == nodes[1]);
	assert(find_root(nodes[1]) == nodes[1]);
	link(nodes[0], nodes[1]);
	assert(find_root(nodes[2]) == nodes[0]);
	assert(find_root(nodes[1]) == nodes[0]);
	assert(find_root(nodes[0]) == nodes[0]);
	link(nodes[3], nodes[4]);
	link(nodes[4], nodes[5]);
	assert(find_root(nodes[5]) == nodes[3]);
	link(nodes[0], nodes[3]);
	assert(find_root(nodes[3]) == nodes[0]);
	assert(find_root(nodes[2]) == nodes[0]);
	cut(nodes[1]);
	assert(find_root(nodes[2]) == nodes[1]);
	cut(nodes[3]);
	assert(find_root(nodes[3]) == nodes[3]);
	assert(find_root(nodes[4]) == nodes[3]);
	assert(find_root(nodes[5]) == nodes[3]);
}
