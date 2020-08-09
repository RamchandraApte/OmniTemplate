#pragma once
#include "core/all.hpp"
namespace splay_tree {
/** @brief Implements a splay tree*/
template<typename Node>
struct PathParent {
	Node* path_parent{};
};
template<typename T, bool has_link_cut = false>
struct SplayNode : public conditional_t<has_link_cut, PathParent<SplayNode<T, has_link_cut>>, Empty> {
		public:
	SplayNode(){}
	SplayNode(T value_arg): value{value_arg} {}
	T value{}; //!< Value associated with node
	array<SplayNode *, 2> child{}; //!< Left and right children
	SplayNode *parent{}; //!< Pointer to parent
	bool side() const {
		/*! Returns true if child is on the right, and false otherwise*/
		return parent->child[1] == &this;
	}
	void rotate() {
		/*! Rotate node x around its parent */
		const auto p = parent;
		const bool i = side();

		if (p->parent) {
			p->parent->attach(p->side(), &this);
		} else {
			parent = nullptr;
		}
		p->attach(i, child[!i]);
		attach(!i, p);
		if constexpr(has_link_cut){this.path_parent = p->path_parent;}
	}
	void splay() {
		/*! Splay node x. x will become the root of the tree*/
		for(;parent;rotate()) {
			if (parent->parent) {
			  (side() == parent->side() ? parent: &this)->rotate();
			}
		}
	}
	array<SplayNode *, 2> split() {
		splay();
		// TODO use detach function
		const auto right = child[1];
		if (right) {
			right->parent = nullptr;
		}
		this->right = nullptr;
		return {&this, right};
	}
	void attach(bool side, SplayNode *const new_) {
		/*! Attach node new_ as the node's side children*/
		if (new_) {
			new_->parent = &this;
		}
		child[side] = new_;
	}
};
template <typename T> struct SplayTree {
      public:
	using Node = SplayNode<T>;
	/** @brief Splay tree node */
	/*! Splay tree iterator */
	struct iterator : public it_base<T> {
		using iterator_category = bidirectional_iterator_tag;

	      public:
		void operator--() { advance<false>(); }
		void operator++() { advance<true>(); }
		const T &operator*() { return node->value; }
		Node *node;
		iterator(Node *node_arg) : node(node_arg) {}
		bool operator==(const iterator oth) const { return node == oth.node; }

	      private:
		template <bool dir> void advance() {
			if (node->child[1]) {
				node = extremum<!dir>(node->child[1]);
				return;
			}
			for (; node->parent && node->side() == dir; node = node->parent)
				;
			node = node->parent;
		}
	};
	Node *root{}; /*!< Root node */
	ll size_{};   /*!< Size of the splay tree*/
	SplayTree() {}
	~SplayTree() { destroy(root); }
	static void destroy(Node *const node) {
		/*! Destroy the subtree node */
		if (!node) {
			return;
		}
		for (Node *const child : node->child) {
			destroy(child);
		}
		delete node;
	}
	void insert(Node *const x) {
		/*! Insert node x into the splay tree*/
		++size_;
		if (!root) {
			root = x;
			return;
		}
		auto y = root;
		while (true) {
			auto &nw = y->child[x->value > y->value];
			if (!nw) {
				nw = x;
				nw->parent = y;
				root = nw;
				nw->splay();
				return;
			}
			y = nw;
		}
		return;
	}
	void insert(const T &key) {
		/*! Insert key key into the splay tree*/
		insert(new SplayNode{key});
	}
	void erase(Node *const x) {
		/*! Erase node x from the splay tree*/
		assert(x);
		x->splay();
		root = join(x->child[0], x->child[1]);
		delete x;
		--size_;
	}
	/** @brief Erases the node with key key from the splay tree */
	void erase(const T &key) { erase(find(key)); }
	template <bool i> static Node *extremum(Node * x) {
		/*! Return the extremum of the subtree x. Minimum if i is false,
		 * maximum if i is true.*/
		assert(x);
		for(; x->child[i]; x = x->child[i]);
		return x;
	}
	static Node *join(Node *const a, Node *const b) {
		if (!a) {
			b->parent = nullptr;
			return b;
		}
		Node *const mx = extremum<true>(a);
		mx->splay();
		assert(mx->child[1] == nullptr);
		mx->child[1] = b;
		mx->parent = nullptr;
		return mx;
	}
    /*! Returns node with key key*/
	Node *find(const T &key) {
		auto x = root;
		for (; x && key != x->value; x = x->child[key > x->value])
			;
		return x;
	}
	/**
     * @brief Returns the number of nodes in the splay tree.
     */
    ll size() const { return size_; }
	bool empty() const { return size() == 0; }
	iterator begin() { return iterator{extremum<false>(root)}; }
	iterator end() { return iterator{nullptr}; }
};
} // namespace splay_tree
using namespace splay_tree;
