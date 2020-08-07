#pragma once
#include "core/all.hpp"
#include "modulo.hpp"
vl divs;
/** @brief Return whether integer n >= 2 is prime*/
auto prime(ll n) {
	assert(n >= 2);
	if (n < divs.size()) {
		return divs[n] == n;
	}
	with _m{n, modulo::modulus};
	ll tz = __builtin_ctz(n - 1);
	auto b = (n - 1) >> tz;
	auto prime_a = [&](modulo const &a) {
		if (a == 0) {
			return true;
		}
		auto p = power(a, b);
		if (p == 1) {
			return true;
		}
		fo(i, tz) {
			if (p == -1) {
				return true;
			}
			p *= p;
		}
		return false;
	};
	vl v{2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	return all_of(al(v), prime_a);
}
/*! @brief Return all divisors of x in sorted order*/
vl divisors(ll x) {
	assert(x >= 1);
	vl v;
	fo(d, 1, x + 1) if (!(x % d)) {
		ll y = x / d;
		if (y < d) {
			break;
		}
		v.push_back(d);
		if (d < y) {
			v.push_back(y);
		}
	}
	sort(al(v));
	return v;
}
/**
 * @brief Linear time prime sieve.
 * 
 * @param n Sieve numbers in [0,n)
 * @return a vector where ret[idx] is the smallest prime divisor of idx
 */
vector<ll> sieve(ll n) {
	vl d(n), ps;
	fo(i, 2, n) {
		if (d[i] == 0) {
			ps.push_back(d[i] = i);
		}
		for (auto p : ps) {
			if (!(p <= d[i] && p * i < n)) {
				break;
			}
			assert(d[p * i] == 0);
			d[p * i] = p;
		}
	}
	return d;
}

/** @brief Returns the factorization of n.
 * @return a map from the prime to the exponent
 */
um fac(ll n) {
	assert(n >= 1);
	if (n == 1) {
		return {};
	};
	ll g = n;
	if (n < divs.size()) {
		g = divs[n];
	} else if (!prime(n)) {
		with _m{n, modulo::modulus};
		for (modulo c = 0; g == n; ++c) {
			auto const f = [&](const auto &x) {
				return x * x + x + c;
			};
			for (modulo a = 0, b = a; a = f(a), b = f(f(b)),
				    (g = gcd(ll(a - b), n)) == 1;) {
			}
		}
	}
	if (g == n) {
		return {{n, 1}};
	}
	assert(1 < g && g < n && !(n % g));
	return fac(g) + fac(n / g);
}
/** @brief Sets x and y so that \f$x\cdot a + y\cdot b = \gcd(a,b)\f$*/
void egcd(const ll a, const ll b, ll &x, ll &y) {
	a ? egcd(mod(b, a), a, y, x), x -= b / a * y : (x = 0, y = 1);
}
/** @brief Returns the totient of the integer n
 * @pre n >= 1
 */
ll totient(ll n) {
    assert(n>=1);
	auto fact = fac(n);
	for (const auto &p : fact) {
		n -= n / p.first;
	}
	return n;
}
/** @brief Finds x such that a^x = b (mod M) using baby-step giant-step
 * algorithm.
 * @pre a and M must be coprime.*/
ll dlog(const modulo a, const modulo b) {
	assert(gcd(static_cast<ll>(a), modulo::modulus) == 1);
	auto check = [&](ll x) {
		assert(power(a, x) == b);
		return x;
	};
	ll sq = sqrt(static_cast<long long int>(modulo::modulus)) + 1;
	unordered_map<modulo, ll> powers;
	const auto a_sq = power(a, sq);
	modulo pw = 1;
	fo(i, sq + 1) {
		powers[pw] = i;
		pw *= a_sq;
	}
	auto x = b;
	for (ll cnt = 0;; ++cnt) {
		if (auto it = powers.find(x); it != end(powers)) {
			return check(mod(it->second * sq - cnt, totient(modulo::modulus)));
		}
		x *= a;
	}
}

/** @brief Returns a primitive root modulo M*/
modulo primitive_root() {
	if (modulo::modulus == 1) {
		return 0;
	}
	auto tot = totient(modulo::modulus);
	auto pfactor = fac(tot);
	fo(i, 1, modulo::modulus) {
		auto is_primitive_root = [&] {
			if (gcd(i, modulo::modulus) != 1) {
				return false;
			}
			for (auto p : pfactor) {
				if (power(modulo{i}, tot / p.first) == 1) {
					return false;
				}
			}
			return true;
		};
		if (is_primitive_root()) {
			return i;
		}
	}
	throw invalid_argument{"M has no primitive root!"};
}
