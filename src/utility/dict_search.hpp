#pragma once
#include "core/all.hpp"
namespace string_tools {
template <ll start = 'a', ll alphabet_size = 26> struct Trie {
	bool leaf{};
	Trie *parent{};
	char edge_char{};
	/*! @brief Returns the child corresponding to the character c*/
	Trie *&next(const char c) { return next_storage[c - start]; }
	auto &next(const char c) const {
		return const_cast<Trie *const &>(const_cast<Trie *>(&this)->next(c));
	}
	/*! @brief Returns the child corresponding to the character c. A new child is created if no
	 * such child exists.*/
	Trie *next_default(const char c) {
		auto &vert = next(c);
		if (!vert) {
			vert = new Trie{};
			vert->parent = &this;
			vert->edge_char = c;
		}
		return vert;
	};
	/*! @brief inserts str into the trie*/
	void insert(const string &str) {
		auto cur = &this;
		for (const auto c : str) {
			auto old = cur;
			cur = cur->next_default(c);
		}
		cur->leaf = true;
	}
	Trie *find_leaf(const string &str) {
		const auto node = find_node(str);
		return node && node->leaf ? node : nullptr;
	}
	/*! @brief Returns node corresponding to str (including non-leaf nodes), otherwise nullptr*/
	Trie *find_node(const string &str) {
		auto cur = &this;
		for (const auto c : str) {
			cur = cur->next(c);
			if (!cur) {
				return {};
			}
		}
		return cur;
	}
	Trie *link() {
		if (!link_storage) {
			auto get = [&] {
				if (!parent) {
					return &this;
				}
				if (!parent->parent) {
					return parent;
				}
				return parent->link()->go(edge_char);
			};
			link_storage = get();
		}
		return link_storage;
	}

	Trie *go(const char c) {
		auto &go_cache = go_storage[c - start];
		if (!go_cache) {
			auto get = [&] {
				if (const auto next_c = next(c)) {
					return next_c;
				}
				return parent ? link()->go(c) : &this;
			};
			go_cache = get();
		}
		return go_cache;
	}

      private:
	array<Trie *, alphabet_size> next_storage{};
	array<Trie *, alphabet_size> go_storage{};
	Trie *link_storage{};
};
} // namespace string_tools
