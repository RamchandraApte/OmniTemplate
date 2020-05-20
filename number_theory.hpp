vl divs;
auto prime(auto n) {
  assert(n >= 2);
  if (n < divs.size()) {
    return divs[n] == n;
  }
  with _m{n, M};
  ll tz = __builtin_ctz(n - 1);
  auto b = (n - 1) >> tz;
  dbg(b);
  auto prime_a = [&](md const &a) {
    dbg(a);
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
vl divisors(ll x) {
  vl v;
  fo(d, 1, ll{ceil(sqrt(ld{x}))} + 1) {
    if (!(x % d)) {
      v.pb(d);
      if (ll y = x / d; d != y) {
        v.pb(y);
      }
    }
  }
  return v;
}
auto sieve(ll n) {
  vl d(n), ps;
  fo(i, 2, n) {
    if (d[i] == 0) {
      ps.pb(d[i] = i);
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
um fac(ll n) {
  // Returns the factorization of n as a mapping from the prime to the
  // exponent.
  assert(n >= 1);
  if (n == 1) {
    return {};
  };
  ll g = n;
  if (n < divs.size()) {
    g = divs[n];
  } else if (!prime(n)) {
    with _m{n, M};
    for (md c = 0; g == n; ++c) {
      auto const f = [&](const auto &x) { return x * x + x + c; };
      for (md a = 0, b = a;
           a = f(a), b = f(f(b)), (g = gcd(ll(a - b), n)) == 1;) {
      }
    }
  }
  if (g == n) {
    return {{n, 1}};
  }
  assert(1 < g && g < n && !(n % g));
  return fac(g) + fac(n / g);
}
void egcd(const auto &a, const auto &b, auto &x, auto &y) {
  a ? egcd(b % a, a, y, x), x -= b / a * y : (x = 0, y = 1);
}
ll totient(ll n) {
  auto fact = fac(n);
  for (const auto &p : fact) {
    n -= n / p.first;
  }
  return n;
}
void test_totient() {
  assert(totient(1) == 1 && totient(2) == 1 && totient(6) == 2 &&
         totient(84) == 24 && totient(127) == 126);
}
ll dlog(const md a, md b) {
  /* Finds x such that a^x = b (mod M) using baby-step giant-step algorithm.
          M must be prime
  */
  assert(prime(M));
  auto check = [&](ll x) {
    assert(power(a, x) == b);
    return x;
  };
  ll sq = sqrt(static_cast<long long int>(M)) + 1;
  unordered_map<md, ll> powers;
  const auto a_sq = power(a, sq);
  md pw = 1;
  fo(i, sq + 1) {
    powers[pw] = i;
    pw *= a_sq;
  }
  for (ll cnt = 0;; ++cnt) {
    if (auto it = powers.find(b); it != end(powers)) {
      return check((it->second * sq - cnt) % (M - 1));
    }
    b *= a;
  }
}
void test_dlog() {
  auto check = [](ll a2, ll b, ll m) {
    with _m{m, M};
    md a{a2};
    auto x = power(a, b);
  };
  check(2, 10, 1025);
  check(7, 1, 30);
  check(1, 1, 1);
  check(23, 47, 153);
  check(15, 100, 45);
}
md primitive_root() {
  if (M == 1) {
    return 0;
  }
  auto tot = totient(M);
  auto pfactor = fac(tot);
  fo(i, 1, M) {
    auto is_primitive_root = [&]() {
      if (gcd(i, M) != 1) {
        return false;
      }
      for (auto p : pfactor) {
        if (power(md{i}, tot / p.first) == 1) {
          return false;
        }
      }
      return true;
    };
    if (is_primitive_root()) {
      return i;
    }
  }
}
void test_primitive_root() {
  auto check = [&](ll m, ll x) {
    with _m{m, M};
    assert(primitive_root() == x);
  };
  check(1, 0);
  check(3, 2);
  check(6, 5);
  check(7, 3);
}