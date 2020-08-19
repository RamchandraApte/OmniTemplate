#include "dict_search.hpp"
namespace string_tools::test {
template <typename Trie_Type> void test_dict_search_impl() {
	Trie_Type trie{};
	const vector<string> good_words{"hello", "world", "hell", "water", "wo"};
	const vector<string> bad_words{"help", "think", "codeforces", "mike",	   "wor",
				       "worl", "w",	"hel",	      "helloworld"};
	for (const auto &word : good_words) {
		trie.insert(word);
	}
	for (const auto &word : good_words) {
		assert(trie.find(word));
	}
	for (const auto &word : bad_words) {
		assert(!trie.find(word));
	}
}
void test_dict_search() {
	test_dict_search_impl<Trie<>>();
	test_dict_search_impl<Trie<'\0', 256>>();
}
} // namespace string_tools::test
using namespace string_tools::test;
