#pragma once
#include "core.hpp"
#include "modulo.hpp"
namespace permutation {
// TODO(ram): lazily computed permutation
class Permutation : public vector<ll> {
      public:
	using vector<ll>::vector;
	using vector<ll>::operator[];
	explicit Permutation(size_t n) : vector<ll>(n) { iota(this.begin(), this.end(), 0LL); }
	[[nodiscard]] vector<vector<ll>> to_cycles() const {
		/*! Returns vector of cycles*/
		vector<ll> vis(this.size());
		vector<vector<ll>> cycles;
		fo(i, this.size()) {
			if (vis[i] != 0) {
				continue;
			}
			vl cycle;
			ll x = i;
			do {
				cycle.push_back(x);
				x = this[x];
			} while (x != i);
			cycles.push_back(cycle);
		}
		return cycles;
	}
	explicit Permutation(const vector<vector<ll>> &cycles, const size_t n, const ll shift = 1) : Permutation(n) {
		for (const auto &cycle : cycles) {
			fo(i, cycle.size()) {
				with _m{static_cast<ll>(cycle.size()), modulo::modulus};
				this[cycle[i]] = cycle[static_cast<ll>(modulo{i} + shift)];
			}
		}
	}
};
Permutation identity(multiplies<> /*unused*/, const Permutation &perm) { return Permutation(perm.size()); }
Permutation operator*(const Permutation &a, const Permutation &b) {
	/*! Returns the composition of permutations a and b.*/
	assert(a.size() == b.size());
	Permutation c(a.size());
	fo(i, a.size()) { c[i] = a[b[i]]; }
	return c;
}
Permutation invert(const Permutation &p) {
	Permutation inv(p.size());
	fo(i, p.size()) { inv[p[i]] = i; }
	return inv;
}
Permutation power(const Permutation &perm, size_t n) {
	/*! Returns in linear-time, perm^n using cycle-decomposition */
	return Permutation(perm.to_cycles(), perm.size(), n);
}
void test_ops() {
	using ::operator/;
	Permutation p1{0, 1, 3, 2};
	Permutation p2{0, 2, 3, 1};
	assert((p1 * p2 == Permutation{0, 3, 2, 1}));
	assert(((p1 / p2) * p2 == p1));
	assert(((p2 / p1) * p1 == p2));
}
void test_cycles_impl(const Permutation &perm) { assert(Permutation(perm.to_cycles(), perm.size()) == perm); }
void test_cycles() {
	test_cycles_impl(Permutation{2, 1, 6, 4, 5, 3, 0});
	test_cycles_impl(Permutation{0, 1, 2, 3});
	test_cycles_impl(Permutation{0});
}
void test_power() {
	Permutation perm{2, 1, 6, 4, 5, 3, 0};
	assert(permutation::power(perm, 10) == modulo_namespace::power(perm, 10));
	assert(permutation::power(perm, -10) == modulo_namespace::power(perm, -10));
}
void test_permutation() {
	test_ops();
	test_cycles();
	test_power();
}
} // namespace permutation
using namespace permutation;
