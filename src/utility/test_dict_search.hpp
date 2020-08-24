#include "dict_search.hpp"
namespace string_tools::test {
template <typename Trie_Type> void test_dict_search_impl() {
	auto trie = new Trie_Type{};
	const vector<string> good_words{"hello", "world", "hell", "water", "wo",  "lop",
					"l",	 "er",	  "y",	  "yyy",   "yyyy"};
	const vector<string> bad_words{"help", "think", "codeforces", "mike",	   "wor",
				       "worl", "w",	"hel",	      "helloworld"};
	for (const auto &word : good_words) {
		trie->insert(word);
	}
	for (const auto &word : good_words) {
		assert(trie->find_leaf(word));
	}
	for (const auto &word : bad_words) {
		assert(!trie->find_leaf(word));
	}
	auto hello = trie->find_node("hello");
	assert(hello->go('p') == trie->find_node("lop"));
	assert(hello->go('c') == trie);
	assert(trie->find_node("lop")->exit_link() == nullptr);
	assert(trie->find_node("lo")->exit_link() == nullptr);
	assert(trie->find_node("water")->exit_link() == trie->find_node("er"));
	const string str = "zhelloperzzasdfnpokncopdeforcesofoajcodeforcessyyyyyyyyyzzz";
	vector<pair<ll, Trie_Type *>> expected;
	fo(j, str.size()) {
		fo(i, j) {
			for (const auto &word : good_words) {
				if (str.substr(i, j - i) == word) {
					expected.push_back({j - 1, trie->find_leaf(word)});
				}
			}
		}
	}
	assert(trie->search(str) == expected);
}
void test_dict_search() {
	test_dict_search_impl<Trie<>>();
	test_dict_search_impl<Trie<'\0', 256>>();
}
} // namespace string_tools::test
using namespace string_tools::test;
