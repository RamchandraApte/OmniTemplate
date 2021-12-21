#pragma once
#include "core/all.hpp"
// TODO this code needs tests
namespace tree {
template <typename T, size_t sz_arg = 30> struct no {
	static const size_t sz = sz_arg;
	vector<no *> p;
	T v;
	no(T const &v_, no *pa = nullptr) : p(sz), v(v_) {
		if (!pa) {
			pa = this;
		}
		fo(i, sz) {
			p[i] = pa;
			pa = pa->p[i];
		}
	}
	auto gt(ll h) {
		bt b(h);
		auto x = this;
		fo(i, sz) {
			if (b[i]) {
				x = x->p[i];
			}
		}
		return x;
	}
	operator bool() { return p[0] != &this; }
	auto dp() {
		bt b;
		auto x = this;
		for (const auto &i : rev(ra{sz})) {
			if (*x.p[i]) {
				x = *x.p[i];
				b[i] = 1;
			}
		}
		return ll(b.to_ullong()) + 1;
	}
};
template <typename Node> auto lca(Node *a, Node *b) {
	ll da = a->dp(), db = b->dp();
	if (da > db) {
		swap(a, b);
	}
	b = b->gt(db - da);
	if (a == b) {
		return a;
	}
	for (const auto &i : rev(ra{Node::sz})) {
		if (a->p[i] != b->p[i]) {
			a = a->p[i];
			b = b->p[i];
		}
	}
	assert(a->p[0] == b->p[0]);
	return a->p[0];
}
} // namespace tree
using namespace tree;
