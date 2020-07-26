#pragma once
#include "core.hpp"
#include "modulo.hpp"
/**
 * @brief Permutation namespace. Contains the Permutation class and tools related to permutations.
 * 
 */
namespace permutation {
/**
* @brief Permutation class
* 
*/
class Permutation : public vector<ll> {
      public:
	using vector<ll>::operator[];
	explicit Permutation(ll n) : vector<ll>(n) {
		iota(this.begin(), this.end(), 0LL);
	}
	explicit Permutation(const initializer_list<ll> &arr) : vector<ll>{arr} {}
    /**
    * @brief Returns the cycle decomposition of the permutation.
    * 
    * @return A vector containing a vector of the indices in the cycle.
    */
	[[nodiscard]] vector<vector<ll>> to_cycles() const {
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
	explicit Permutation(const vector<vector<ll>> &cycles, const ll n, const ll shift = 1) : Permutation(n) {
		for (const auto &cycle : cycles) {
			fo(i, cycle.size()) {
				with _m{ssize(cycle), modulo::modulus};
				this[cycle[i]] = cycle[static_cast<ll>(modulo{i} + shift)];
			}
		}
	}
};
Permutation identity(multiplies<>, const Permutation &perm) { return Permutation(ssize(perm)); }
/** @brief Returns the composition of permutations a and b, so that ret[i] = a[b[i]].
 * @return \f$ab\f$
 */
Permutation operator*(const Permutation &a, const Permutation &b) {
	assert(a.size() == b.size());
	Permutation c(a.size());
    fo(i, a.size()) { c[i] = a[b[i]]; }
	return c;
}

/**
 * @brief Inverts a permutation.
 * 
 * @param p Permutation.
 * @return Inverse of the permutation.
 */
Permutation invert(multiplies<>, const Permutation &p) {
	Permutation inv(p.size());
	fo(i, p.size()) { inv[p[i]] = i; }
	return inv;
}
/**
* @brief Returns in linear-time, perm^n using cycle-decomposition
* 
* @param perm A permutation.
* @param n The exponent. If negative, returns the power of the inverse permutation.
* @return \f$\left(perm\right)^n\f$
*/
Permutation power(const Permutation &perm, ll n) {
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
