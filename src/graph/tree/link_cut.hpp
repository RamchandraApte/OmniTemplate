#pragma once
#include "core/all.hpp"
#include "ds/splay_tree.hpp"
namespace link_cut {
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
} // namespace link_cut
using namespace link_cut;
