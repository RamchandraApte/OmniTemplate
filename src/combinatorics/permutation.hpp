#pragma once
#include "core/all.hpp"
#include "number_theory/modulo.hpp"
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
	explicit Permutation(ll n) : vector<ll>(n) { iota(begin(), end(), 0LL); }
	explicit Permutation(const initializer_list<ll> &arr) : vector<ll>{arr} {}
	/**
	 * @brief Returns the cycle decomposition of the permutation.
	 *
	 * @return A vector containing a vector of the indices in the cycle.
	 */
	[[nodiscard]] vector<vector<ll>> to_cycles() const {
		vector<ll> vis(size());
		vector<vector<ll>> cycles;
		fo(i, size()) {
			if (vis[i] != 0) {
				continue;
			}
			vector<ll> cycle;
			ll x = i;
			do {
				cycle.push_back(x);
				x = (*this)[x];
			} while (x != i);
			cycles.push_back(cycle);
		}
		return cycles;
	}
	explicit Permutation(const vector<vector<ll>> &cycles, const ll n, const ll shift = 1)
	    : Permutation(n) {
		for (const auto &cycle : cycles) {
			fo(i, cycle.size()) {
				with _m{ssize(cycle), modulo::modulus};
				(*this)[cycle[i]] = cycle[static_cast<ll>(modulo{i} + shift)];
			}
		}
	}
};
/** @brief Returns the identity permutation
 */
Permutation identity_elt(multiplies<>, const Permutation &perm) { return Permutation(ssize(perm)); }
/** @brief Returns the composition of permutations a and b, so that ret[i] = a[b[i]].
 * @return \f$a\cdot b\f$
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
} // namespace permutation
using namespace permutation;
