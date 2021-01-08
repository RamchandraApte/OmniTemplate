#pragma once
#include "core/all.hpp"
inline namespace string_tools {
template <ll start = 'a', ll alphabet_size = 26> struct Trie {
	/*! Whether this node is a leaf node*/
	bool leaf{};
	/*! The string for this leaf node*/
	string str;
	/*! Parent of this node*/
	Trie *parent{};
	/*! Character for the edge to the parent*/
	char edge_char{};
	/*! @brief Returns the child corresponding to the character c*/
	Trie *&next(const char c) { return next_storage[c - start]; }
	auto &next(const char c) const {
		return const_cast<Trie *const &>(const_cast<Trie *>(this)->next(c));
	}
	/*! @brief Returns the child corresponding to the character c. A new child is created if no
	 * such child exists.*/
	Trie *next_default(const char c) {
		auto &vert = next(c);
		if (!vert) {
			vert = new Trie{};
			vert->parent = this;
			vert->edge_char = c;
		}
		return vert;
	};
	/*! @brief inserts str into the trie*/
	void insert(const string &str) {
		auto cur = this;
		for (const auto c : str) {
			auto old = cur;
			cur = cur->next_default(c);
		}
		cur->leaf = true;
		cur->str = str;
	}
	/*! @brief Return the leaf node for str, or nullptr if none exists.*/
	Trie *find_leaf(const string &str) {
		const auto node = find_node(str);
		return node && node->leaf ? node : nullptr;
	}
	/*! @brief Returns node corresponding to str (including non-leaf nodes), otherwise nullptr*/
	Trie *find_node(const string &str) {
		auto cur = this;
		for (const auto c : str) {
			cur = cur->next(c);
			if (!cur) {
				return {};
			}
		}
		return cur;
	}
	/*! @brief returns the suffix link*/
	Trie *link() {
		if (!suffix_link_cache) {
			auto get = [&] {
				if (!parent) {
					return this;
				}
				if (!parent->parent) {
					return parent;
				}
				return parent->link()->go(edge_char);
			};
			suffix_link_cache = get();
		}
		return suffix_link_cache;
	}
	/*! @brief Goes to the node for the largest suffix of the current string plus c*/
	Trie *go(const char c) {
		auto &go_val = go_cache[c - start];
		if (!go_val) {
			auto get = [&] {
				if (const auto next_c = next(c)) {
					return next_c;
				}
				return parent ? link()->go(c) : this;
			};
			go_val = get();
		}
		return go_val;
	}
	/*! @brief Returns the exit link, the next leaf suffix*/
	Trie *exit_link() {
		if (!exit_link_cache) {
			if (!parent) {
				exit_link_cache = nullptr;
			} else {
				auto suffix = link();
				exit_link_cache = suffix->leaf ? suffix : suffix->exit_link();
			}
		}
		return exit_link_cache;
	}
	/*! @brief Searches for the patterns in text.
	 * @returns a vector of ((left, right), node) pairs for each match where [left, right) is
	 * the range of the match, and node is the node corresponding to the match. character of the
	 * match
	 */
	auto search(const string &text) {
		vector<pair<array<ll, 2>, Trie *>> matches;
		auto cur = this;
		fo(idx, text.size()) {
			cur = cur->go(text[idx]);
			for (auto exit = cur; exit; exit = exit->exit_link()) {
				if (exit->leaf) {
					const ll j = idx + 1;
					matches.push_back({{j - ssize(exit->str), j}, exit});
				}
			}
		}
		return matches;
	}

      private:
	array<Trie *, alphabet_size> next_storage{};
	array<Trie *, alphabet_size> go_cache{};
	Trie *suffix_link_cache{};
	Trie *exit_link_cache{};
};
} // namespace string_tools
