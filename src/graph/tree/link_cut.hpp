#pragma once
#include "core/all.hpp"
#include "ds/splay_tree.hpp"
using Node = SplayNode<ll, true>;
Node *make_tree() {
	/*! Make a new tree */
	return new Node{};
}
void detach_child(Node* node){
	/*! Converts node's preferred child edge to a path parent edge*/
	if(node->child[1]){
		node->child[1]->path_parent = node;
		node->child[1]->parent = nullptr;
	}
}
Node *access(Node *node) {
	/*! Moves node to the root of the auxillary tree containing the root node of the tree. Returns last path-parent of node as it moves up the tree*/
	node->splay();
	detach_child(node);
	node->child[1] = nullptr;
	Node *par = node;
	while (node->path_parent) {
		par = node->path_parent;
		par->splay();
		detach_child(par);
		par->attach(1, node);
		node->path_parent = nullptr;
		node->splay();
	}
	return par;
}
Node *find_root(Node *node) {
	/** Finds the root of the tree containing node*/
	access(node);
	for (; node->child[0]; node = node->child[0])
		;
	access(node);
	return node;
}
void cut(Node *node) {
	/*! Detaches the subtree of node from the tree of node's parent*/
	access(node);
	node->child[0]->parent = nullptr;
	node->child[0] = nullptr;
}
void link(Node *par, Node *child) {
	/*! Makes child the child of par*/
	access(child);
	access(par);
	child->attach(0, par);
}
Node *lca(Node *u, Node *v) {
	/*! Returns lowest common ancestor of nodes u and v or nullptr if u and v are in different trees*/
	if (find_root(u) != find_root(v)) {
		return nullptr;
	}
	access(u);
	return access(v);
}
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
