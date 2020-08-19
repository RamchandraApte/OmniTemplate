#pragma once
#include "core/all.hpp"
namespace string_tools {
template <ll start = 'a', ll alphabet_size = 26> struct Trie {
	bool leaf{};
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
	/*! @brief Returns whether or not the trie contains str*/
	bool find(const string &str) const {
		auto cur = &this;
		for (const auto c : str) {
			cur = cur->next(c);
			if (!cur) {
				return false;
			}
		}
		return cur->leaf;
	}

      private:
	array<Trie *, alphabet_size> next_storage{};
};
} // namespace string_tools
