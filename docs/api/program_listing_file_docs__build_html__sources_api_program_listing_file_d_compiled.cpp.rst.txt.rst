
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_d_compiled.cpp.rst.txt:

Program Listing for File program_listing_file_d_compiled.cpp.rst.txt
====================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_d_compiled.cpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_d_compiled.cpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_d_compiled.cpp:
   
   Program Listing for File d_compiled.cpp
   =======================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_d_compiled.cpp>` (``d_compiled.cpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      
      #ifndef PRE
      //#if defined(__GNUC__) && !defined(__clang__)
      #if 0
      #define REALGCC
      #endif
      #ifdef REALGCC
      #include <bits/extc++.h>
      #else
      #include <bits/stdc++.h>
      #endif
      #include <experimental/iterator>
      #include <experimental/source_location>
      #endif
      # 1 "d.cpp"
      # 1 "graph_theory.hpp" 1
             
      # 1 "core.hpp" 1
             
      # 26 "core.hpp"
      bool debug_mode = false;
      # 43 "core.hpp"
      using namespace std;
      vector<pair<string, string>> lets{{"__debug::", ""},
            {"const ", ""},
            {"__cxx11::basic_string<char>", "string"}};
      struct lets_add {
       lets_add(const string &a, const string &b) { lets.push_back({a, b}); }
      };
      
      
      
      
      using std::priority_queue;
      using namespace std; lets_add _l0{"std" "::", ""};;
      
      using experimental::make_ostream_joiner;
      using experimental::ostream_joiner;
      using experimental::source_location;
      using namespace chrono; lets_add _l1{"chrono" "::", ""};;
      using namespace literals; lets_add _l2{"literals" "::", ""};;
      using namespace placeholders; lets_add _l3{"placeholders" "::", ""}; using lli = long long; lets_add _l4{"long long", "lli"};;
      using ull = unsigned long long; lets_add _l5{"unsigned long long", "ull"};;
      using ll = long long; lets_add _l6{"long long", "ll"};;
      using vl = vector<ll>; lets_add _l7{"vector<ll>", "vl"};;
      using ld = long double; lets_add _l8{"long double", "ld"}; using pr = pair<ll, ll>; lets_add _l9{"pair<ll, ll>", "pr"};;
      using com = complex<double>; lets_add _l10{"complex<double>", "com"};;
      using point = complex<ll>; lets_add _l11{"complex<ll>", "point"};;
      using ull = unsigned long long; lets_add _l12{"unsigned long long", "ull"};;
      using bt = bitset<numeric_limits<ll>::digits>;
      template <typename T, typename Comp>
      using prio_queue_t = std::priority_queue<T, vector<T>, Comp>;
      using clock_ = high_resolution_clock; lets_add _l13{"high_resolution_clock", "clock_"};;
      using namespace this_thread; lets_add _l14{"this_thread" "::", ""};;
      using um = unordered_map<ll, ll>; lets_add _l15{"unordered_map<ll, ll>", "um"};;
      
      
      
      
      
      
      
      auto constexpr inf = ll(numeric_limits<ll>::max()) / 8;
      auto const delim = ", "s;
      auto constexpr tau = 2 * 3.1415926535897932384626433L;
      extern bool multitest;
      
      # 1 "io.hpp" 1
             
      # 1 "debug.hpp" 1
             
      # 1 "operations.hpp" 1
             
      # 1 "range.hpp" 1
             
      
      template <typename T> struct it_base {
       using value_type = T;
       using pointer = T *;
       using reference = T &;
       using difference_type = ll;
      };
      template <typename T> struct int_it : it_base<T> {
       using iterator_category = random_access_iterator_tag;
       T x, m;
       template <typename Integer>
       int_it(Integer x_, T m_ = 1) : x(x_), m(m_) {}
       int_it() {}
       auto &operator*() const {
        static T x_stat;
        return x_stat = x;
       }
       explicit operator auto() const { return x; }
       int_it operator+(ll y) const { return x + m * y; }
       int_it operator-(ll y) const { return x - m * y; }
       ll operator-(int_it<T> const &y) const { return (x - y.x) / m; }
       int_it operator++() { return x += m; }
       int_it operator--() { return x -= m; }
       int_it operator--(int) {
        auto ret = x;
        --x;
        return ret;
       }
       int_it operator++(int) {
        auto ret = x;
        ++x;
        return ret;
       }
      };
      
      
      template <typename T> auto operator ==(int_it<T> const &a, int_it<T> const &b) { return a.x == b.x; };
      template <typename T> auto operator <(int_it<T> const &a, int_it<T> const &b) { return a.x < b.x; };
      
      template <typename T> struct range {
       T bg, ed;
       explicit range(T ed_) : range(0LL, ed_) {}
       range(T const &bg_, T const &ed_)
           : bg(bg_), ed(max(bg, static_cast<T>(ed_))) {}
       auto begin() const { return bg; }
       auto end() const { return ed; }
       explicit operator ll() { return ed - bg; }
      };
      template <typename T> auto operator<(range<T> const &a, range<T> const &b) {
       return a.bg == b.bg ? a.ed > b.ed : a.bg < b.bg;
      }
      template <typename T> auto operator&(range<T> const &a, range<T> const &b) {
       return range<T>{max(a.bg, b.bg), min(a.ed, b.ed)};
      }
      template <typename Range> auto rev(const Range &r) {
       using rev_it = reverse_iterator<decltype(begin(r))>;
       return range{rev_it{end(r)}, rev_it{begin(r)}};
      }
      using ra = range<int_it<ll>>;
      template <typename T> int_it<T> operator+(int_it<T> const &a, int_it<T> const &b) {
       return a.x + b.x;
      }
      template <typename T> int_it<T> operator-(int_it<T> const &a) { return -a.x; }
      enum isect { null, dis, over, cont, eq };
      template <typename T1, typename T2> auto intersect(const T1 &a, const T2 &b) {
       if (a == b) {
        return isect::eq;
       }
       if (a[1] <= b[0]) {
        return isect::dis;
       }
       if (a[0] <= b[0] && b[1] <= a[1]) {
        return isect::cont;
       }
       if (a[0] <= b[0] && a[1] <= b[1]) {
        return isect::over;
       }
       return isect::null;
      }
      template <typename T> auto operator^(range<T> const &a, range<T> const &b) {
       return max(intersect(a, b), intersect(b, a));
      }
      auto filter(vector<ra> &v) {
       sort(begin(v), end(v));
       vector<ra> sg;
       for (const auto &p : v) {
        if (sg.empty() || sg.back().ed < p.ed) {
         sg.push_back(p);
        }
       }
      }
      # 3 "operations.hpp" 2
      
      
      
      
      
      
      template <typename T1, typename T2> auto operator +=(T1 &a, const T2 &b) { return a = a + b; };
      template <typename T1, typename T2> auto operator -=(T1 &a, const T2 &b) { return a = a - b; };
      template <typename T1, typename T2> auto operator *=(T1 &a, const T2 &b) { return a = a * b; };
      template <typename T1, typename T2> auto operator /=(T1 &a, const T2 &b) { return a = a / b; };
      template <typename T> enable_if_t<is_floating_point_v<T>, T> invert(multiplies<>, const T &x) { return 1 / x; }
      template <typename Group> Group operator/(Group const &a, Group const &b) { return a * invert(multiplies{}, b); }
      template <typename T1, typename T2>
      auto constexpr operator-(const T1 &a, const T2 &b) {
       return a + -b;
      }
      template <typename T1, typename T2>
      auto constexpr operator!=(const T1 &a, const T2 &b) {
       return !(a == b);
      }
      template <typename T1, typename T2> auto operator<=(const T1 &a, const T2 &b) {
       return !(b < a);
      }
      template <typename T1, typename T2> auto operator>=(const T1 &a, const T2 &b) {
       return b <= a;
      }
      template <typename T1, typename T2> auto operator>(const T1 &a, const T2 &b) {
       return b < a;
      }
      template <typename T> using uset = unordered_set<T>;
      um operator+(um a, um const &b) {
       for (const auto &p : b) {
        a[p.first] += p.second;
       }
       return a;
      }
      # 47 "operations.hpp"
      template <typename T> auto operator|(unordered_set<T> const &a, unordered_set<T> const &b) {
       const auto &[sm, bg] = minmax(a, b);
       auto ret = bg;
       ret.insert(begin(sm), end(sm));
       return ret;
      };
      template <typename T> auto operator&(unordered_set<T> const &a, unordered_set<T> const &b) {
       const auto &[sm, bg] = minmax(a, b);
       unordered_set<T> ret;
       for (const auto &x : sm) {
        if (bg.count(x)) {
         ret.insert(x);
        }
       }
       return ret;
      }
      template <typename T> auto sub_set(unordered_set<T> const &a, unordered_set<T> const &b,
          unordered_set<T> &ret) {
       for (const auto &x : a) {
        if (!b.count(x)) {
         ret.insert(x);
        }
       }
       return ret;
      }
      template <typename T> auto operator-(unordered_set<T> const &a, unordered_set<T> const &b) {
       unordered_set<T> ret;
       return sub_set(a, b, ret);
      }
      template <typename T> auto operator^(unordered_set<T> const &a, unordered_set<T> const &b) {
       unordered_set<T> ret = a - b;
       sub_set(b, a, ret);
       return ret;
      }
      template <typename T> auto operator*(vector<T> a, vector<T> b) {
       assert(a.size() == b.size());
       vector<T> c(a.size());
       for ([[maybe_unused]] const auto i : ra{a.size()}) { c[i] = a[i] * b[i]; }
       return c;
      }
      template <typename Iterator> auto operator+(Iterator it, enable_if_t<!is_same<typename iterator_traits<decltype(it)>::iterator_category, random_access_iterator_tag>::value, ll> n) {
       advance(it, n);
       return it;
      }
      template <typename T> using bin_op = T(*)(T, T);
      
      
      
      
      constexpr ll identity(bin_op<ll const &> const &f) {
       if (f == static_cast<decltype(f)>(max<ll>)) { return -inf; };
       if (f == static_cast<decltype(f)>(min<ll>)) { return inf; };
       abort();
      }
      constexpr ll identity(bin_op<ll> const &f) {
       if (f == static_cast<decltype(f)>(gcd<ll>)) { return 0; };
       abort();
      }
      ll identity(plus<>, ll) { return 0; }
      ll identity(multiplies<>, ll) { return 1; }
      struct Max {
       template <typename T> auto operator()(T a, T b) const { return max(a, b); }
      };
      ll identity(Max, ll) { return -inf; }
      struct Min {
       template <typename T> auto operator()(T a, T b) const { return min(a, b); }
      };
      ll identity(Min, ll) { return inf; }
      # 3 "debug.hpp" 2
      # 12 "debug.hpp"
      namespace debug_tools {
      template <typename T> auto type_name([[maybe_unused]] T const &v) {
      
       string s = __PRETTY_FUNCTION__, tar = "T = ";
       auto st = s.find(tar) + tar.size();
       return s.substr(st, s.find("]", st) - st);
      }
      auto replace(string s, const string &a, const string &b) {
      
      
       ll loc;
       while ((loc = s.find(a)) != string::npos) {
        s = s.substr(0, loc) + b + s.substr(loc + a.size());
       }
       return s;
      }
      template <typename T> auto simple_tp([[maybe_unused]] const T &v) {
      
       auto s = type_name(v);
       for (const auto &p : lets) {
        s = replace(s, p.first, p.second);
       }
       return s;
      }
      ll depth = -1;
      template <typename T>
      auto debug(const T &x, const string &name,
          source_location const &loc = source_location::current()) {
      
       if (debug_mode) {
        for ([[maybe_unused]] const auto i : ra{depth}) { cerr << "\t"; }
        cerr << loc.function_name() << ":" << loc.line() << " " << name
             << " = " << x << endl;
       }
       --depth;
       return x;
      }
      }
      using namespace debug_tools;
      # 3 "io.hpp" 2
      
      
      
      
      struct rin {
       istream &in;
       rin(istream &in_) : in(in_) {}
       auto &operator<<(const char *) { return (*this); }
       auto &operator<<(string const &s) {
        if (s.empty()) {
         in >> const_cast<string &>(s);
        }
        return (*this);
       }
       template <typename T> rin &operator>>(T &x) {
        (*this) << x;
        return (*this);
       }
      };
      template <typename R, typename T>
      auto operator<<(R &r, const T &x)
          -> decltype(r.in >> const_cast<T &>(x),
        declval<enable_if_t<is_same<R, rin>::value, rin &>>()) {
       r.in >> const_cast<T &>(x);
       return r;
      }
      template <typename Stream, typename T>
      enable_if_t<is_same<T, istream>::value, rin> operator>>(Stream &is, T &x) {
       rin r{is};
       return r >> x;
      }
      template <typename Stream, typename... T>
      auto &operator<<(Stream &os, tuple<T...> t) {
       apply(
           [&](auto &f, auto &... x) {
            os << f;
            ((os << delim << x), ...);
           },
           t);
       return os;
      }
      template <typename T1, typename... Ts>
      auto print(const T1 &arg1, const Ts &... args) {
      
       cout << arg1;
       ((cout << " " << args), ...);
       cout << endl;
      }
      namespace std {
      template <typename Stream, typename... T>
      auto &operator<<(Stream &os, pair<T...> const &p) {
       return os << simple_tp(p) << "{" << p.first << delim << p.second << "}";
      }
      template <typename Stream, typename Container>
      auto operator<<(Stream &os, const Container &v)
          -> decltype(begin(v), declval<decltype(os)>()) {
       auto ed = begin(v);
       auto big = v.size() > 20;
       if (big) {
        advance(ed, 20);
       } else {
        ed = end(v);
       }
       os << simple_tp(v) << "{";
       copy(begin(v), ed, make_ostream_joiner(os, delim));
       if (big) {
        os << delim << "...";
       }
       return os << "}";
      }
      template <typename T>
      auto operator<<(rin &os, const T &v)
          -> decltype(begin(v), declval<decltype(os)>()) {
       for (const auto &elem : v) {
        os << elem;
       }
       return os;
      }
      
      
      
      
      
      
      }
      # 89 "core.hpp" 2
      
      
      
      # 1 "utility.hpp" 1
             
      
      namespace utility {
      
      template <typename T> struct [[nodiscard]] with {
       T old;
       T &v;
       template <typename Tp> with(const Tp new_, T &v_) : old(v_), v(v_) { v = new_; }
       ~with() { v = old; }
      };
      void test_with() {
       ll var = 12;
       auto inner_func = [&] {
        with _w(23, var);
        assert(var == 23);
        var = 45;
       };
       inner_func();
       assert(var == 12);
      }
      
      
      template <typename Func> struct fix {
       Func func;
       fix(const Func &func_) : func(func_) {}
       template <typename... Args> decltype(auto) operator()(Args &&... args) const { return func((*this), forward<Args>(args)...); }
      };
      
      template <typename T> auto max_eq(T &x, const T &y) { x = max(x, y); }
      template <typename T> auto min_eq(T &x, const T &y) { x = min(x, y); }
      template <typename T> auto cache(const T &f) {
      
       T ch;
       return [=](const auto &arg) mutable {
        if (ch.find(arg) == end(ch)) {
         return ch[arg] = f(arg);
        }
        return ch[arg];
       };
      }
      
      
      template <typename Eq = equal_to<>, typename T = less<>, typename Cont>
      [[nodiscard]] auto uniq(Cont v, Eq const &up = Eq{}, T const &sp = T{}) {
       sort(begin(v), end(v), sp);
       v.resize(unique(begin(v), end(v), up) - begin(v));
       return v;
      }
      void test_uniq() {
       assert((uniq(vl{2, -1, 3, -1, 2, 3}) == vl{-1, 2, 3}));
       assert((uniq<equal_to<>, greater<>>(vl{1, -3, 5}) == vl{5, 1, -3}));
      }
      template <typename T = less<>, typename Func> auto key_compare(const Func &f, T g = T{}) {
       return [=](auto &&... args) -> decltype(auto) { return g(f(forward<decltype(args)>(args))...); };
      }
      void test_key_compare() {
       vl a{24, 25};
       assert(key_compare<greater<>>([&](ll i) { return a[i]; })(1, 0));
      }
      template <typename T> auto prev_less(const T &v) {
       ll n = v.size();
       vl l(n, -1);
       stack<ll> s;
       for ([[maybe_unused]] const auto i : ra{n}) {
        while (s.size() && !(s.top() < v[i])) {
         s.pop();
        }
        if (s.size()) {
         l[i] = s.top();
        }
        s.push(v[i]);
       }
       return l;
      }
      ll bit_ceil(ll x) {
      
       if (x <= 1) {
        return 1;
       }
       return 1LL << (sizeof(ll) * CHAR_BIT - __builtin_clzll(x - 1));
      }
      void test_bit_ceil() {
       assert(bit_ceil(0) == 1);
       assert(bit_ceil(1) == 1);
       assert(bit_ceil(2) == 2);
       assert(bit_ceil(3) == 4);
       assert(bit_ceil(4) == 4);
       assert(bit_ceil(5) == 8);
       assert(bit_ceil((1LL << 45) - 100) == 1LL << 45);
       assert(bit_ceil((1LL << 45)) == 1LL << 45);
      }
      ll power_ceil(const ll x, const ll base) {
       ll pw = 1;
       for (; pw < x; pw *= base)
        ;
       return pw;
      }
      ll log_ceil(const ll x, const ll base) {
       ll pw = 1, cnt = 0;
       for (; pw < x; pw *= base, ++cnt) {
       }
       return cnt;
      }
      [[nodiscard]] ll next_comb(ll x) {
      
      
       ll tz = __builtin_ctzll(x);
       ll y = x + (ll{1} << tz);
       const auto ret = y | (y ^ x) >> (2 + tz);
       assert(ret > x);
       assert(__builtin_popcountll(ret) == __builtin_popcountll(x));
       return ret;
      }
      void test_next_comb() {
       ll x = 0b111;
       x = next_comb(x);
       assert(x == 0b1011);
       x = next_comb(x);
       assert(x == 0b1101);
       x = next_comb(x);
       assert(x == 0b1110);
       x = 0b1;
       x = next_comb(x);
       assert(x == 0b10);
       x = next_comb(x);
       assert(x == 0b100);
      }
      template <typename T, typename Func> void swap2(T &a, T &b, const Func &func) {
      
       if (func(a) > func(b)) {
        swap(a, b);
       }
      }
      template <typename Cont> ll ssize(const Cont &cont) { return size(cont); }
      
      
      template <typename T> struct ar { using type = T; };
      template <typename T> using ar_t = typename ar<T>::type;
      template <typename T, ll n> struct ar<T[n]> { using type = array<ar_t<T>, n>; };
      void test_ar() {
       static_assert(is_same_v<ar_t<ll[2][3]>, array<array<ll, 3>, 2>>);
       static_assert(is_same_v<ar_t<array<ll, 200>[2][3]>,
          array<array<array<ll, 200>, 3>, 2>>);
      }
      struct random_device_patch {
      
      
       unsigned int operator()() { return clock_::now().time_since_epoch().count(); }
       double entropy() { return 0.0; }
      };
      struct Empty {};
      
      
      using random_device = random_device_patch;
      
      default_random_engine reng{random_device{}()};
      void test_utility() {
       test_with();
       test_uniq();
       test_next_comb();
       test_ar();
       test_bit_ceil();
       test_key_compare();
      }
      }
      using namespace utility;
      # 92 "core.hpp" 2
      # 3 "graph_theory.hpp" 2
      # 1 "dsu.hpp" 1
             
      
      namespace dsu_ds {
      
      struct dsu {
       mutable vl parent;
       vl size_;
      
       explicit dsu(const ll n) : parent(n), size_(n, 1) { iota(begin(parent), end(parent), 0); }
      
       ll find(ll x) const {
        return x == parent[x] ? x : parent[x] = (*this).find(parent[x]);
       }
      
      
      
      
       bool join(ll x, ll y) {
        x = (*this).find(x);
        y = (*this).find(y);
        if (x == y) {
         return false;
        }
        swap2(x, y, [&](auto idx) { return size_[idx]; });
        size_[y] += size_[x];
        parent[x] = y;
        return true;
       }
      };
      
      template <typename Stream> auto &operator<<(Stream &os, dsu const &d) {
       os << "dsu{";
       for ([[maybe_unused]] const auto i : ra{d.parent.size()}) {
        if (i) {
         os << delim;
        }
        os << d.find(i);
       }
       return os << "}";
      }
      void test_dsu() {
       dsu d{100};
       for ([[maybe_unused]] const auto i : ra{100}) { assert(d.find(i) == i); }
       assert(d.join(3, 4));
       assert(d.join(6, 10));
       assert(!d.join(6, 6));
       assert(d.join(10, 3));
       assert(!d.join(6, 3));
       vl idx{d.find(3), d.find(4), d.find(6), d.find(10)};
       assert(all_of(begin(idx), end(idx), [&](auto x) { return x == idx[0]; }));
       for ([[maybe_unused]] const auto i : ra{99}) { d.join(i, i + 1); }
       for ([[maybe_unused]] const auto i : ra{100}) { assert(d.find(i) == d.find(0)); }
      }
      }
      using namespace dsu_ds;
      # 4 "graph_theory.hpp" 2
      # 1 "linear_algebra.hpp" 1
             
      
      # 1 "modulo.hpp" 1
             
      
      namespace modulo_namespace {
      template <typename... Args> using invert_t = decltype(invert(std::declval<Args>()...));
      
      
      
      
      
      
      template <typename T> T power(T a, ll b) {
       if (b < 0) {
        if constexpr (experimental::is_detected_v<invert_t, multiplies<>, decltype(a)>) {
         a = invert(multiplies{}, a);
         b = -b;
        } else {
         assert(("b < 0 but unable to inverse a", false));
        }
       }
       T ret = identity(multiplies<>{}, a);
       for (; b; b >>= 1, a *= a) {
        if (b & 1) {
         ret *= a;
        }
       }
       return ret;
      }
      
      ll mod(ll a, const ll b) {
       a %= b;
       if (a < 0) {
        a += b;
       }
       return a;
      }
      
      ll mod_eq(ll &a, const ll b) { return a = mod(a, b); }
      
      struct no_mod {};
      struct modulo {
       inline static ll modulus =
           1e9 +
           7;
      
       ll x;
       modulo() : x{0LL} {}
       template <typename T, typename = enable_if_t<is_integral<T>::value, void>>
       modulo(T x_) : x(mod(x_, modulo::modulus)) {}
       modulo(ll x_, no_mod) : x(x_) {}
       explicit operator auto() const { return x; }
      };
      modulo identity(plus<>, modulo) { return 0; }
      modulo identity(multiplies<>, modulo) { return 1; }
      modulo operator+(modulo const &a, modulo const &b) {
       ll const sum = a.x + b.x;
       return {sum >= modulo::modulus ? sum - modulo::modulus : sum, no_mod{}};
      }
      modulo operator++(modulo &a) { return a += 1; }
      modulo operator-(modulo const &a) { return {modulo::modulus - a.x, no_mod{}}; }
      
      using ::operator-;
      auto operator ==(modulo const &a, modulo const &b) { return a.x == b.x; };
      modulo operator*(modulo const &a, modulo const &b) {
      
       const ull quot = ld(a.x) * ld(b.x) / ld(modulo::modulus);
      
       const ll rem = ull(a.x) * ull(b.x) - ull(modulo::modulus) * quot;
       if (rem < 0) {
        return {rem + modulo::modulus, no_mod{}};
       }
       if (rem >= modulo::modulus) {
        return {rem - modulo::modulus, no_mod{}};
       }
       return {rem, no_mod{}};
      }
      modulo invert(multiplies<>, modulo const &b) {
      
       assert(b != 0);
       return power(b, modulo::modulus - 2);
      }
      using ::operator/;
      template <typename Stream> auto &operator<<(Stream &os, modulo const &m) {
       return os << m.x;
      }
      void test_power() {
       assert(power(2, 3) == 8);
       assert(power(3, 10) == 59049);
       with _m{static_cast<ll>(1e9 + 7), modulo::modulus};
       assert(power(modulo{3}, 1000) == modulo{56888193});
       assert(power(modulo{3}, -1000) * power(modulo{3}, 1000) == 1);
       assert(power(modulo{1}, 0) == 1);
      }
      void test_md() {
       with _m{7, modulo::modulus};
       assert(modulo{34} / modulo{-2} == modulo{4});
       assert(modulo{2} - modulo{6} == modulo{3});
      }
      void test_modulo() {
       test_power();
       test_md();
      }
      }
      using namespace modulo_namespace;
      namespace std {
      template <> struct hash<modulo> {
       ll operator()(modulo const &x) const { return x.x; }
      };
      }
      # 4 "linear_algebra.hpp" 2
      # 1 "polynomial.hpp" 1
             
      
      
      
      
      
      template <typename T> class Polynomial : public vector<T> {
       using vector<T>::vector;
            public:
       void shrink() {
        while (!(*this).empty() && (*this).back() == 0) {
         (*this).pop_back();
        }
       }
      };
      template <typename T> Polynomial<T> operator+(const Polynomial<T> &a, const Polynomial<T> &b) {
       if (!(a.size() <= b.size())) {
        return b + a;
       }
       auto sum = b;
       for ([[maybe_unused]] const auto i : ra{a.size()}) { sum[i] += a[i]; }
       return sum;
      }
      template <typename T> Polynomial<T> operator*(const Polynomial<T> &a, const Polynomial<T> &b) {
       Polynomial<T> prod(a.size() - 1 + b.size() - 1 + 1);
       for ([[maybe_unused]] const auto i : ra{a.size()}) {
        for ([[maybe_unused]] const auto j : ra{b.size()}) { prod[i + j] += a[i] * b[j]; }
       }
       return prod;
      }
      template <typename T> bool operator==(const Polynomial<T> &a, const Polynomial<T> &b) {
      
       if (!(a.size() <= b.size())) {
        return b == a;
       }
       return equal(begin(a), end(a), b.begin(), b.begin() + a.size()) && all_of(b.begin() + a.size(), b.end(), [](T x) { return x == 0; });
      }
      void test_polynomial() {
       Polynomial<ll> p1{1, 2, 3};
       Polynomial<ll> p2{2, -3};
       assert((p2 * p1 == p1 * p2 && p1 * p2 == Polynomial<ll>{2, 1, 0, -9, 0, 0}));
       assert((p2 + p1 == p1 + p2 && p1 + p2 == Polynomial<ll>{3, -1, 3, 0}));
       assert((p1 + p2 != Polynomial<ll>{3, -1, 3, 1}));
      }
      # 5 "linear_algebra.hpp" 2
      
      
      namespace linear_algebra {
      template <typename T> struct matrix {
      
       ll rows_n, cols_n;
       vector<T> a;
       explicit matrix(ll r_, ll c_, remove_const_t<decltype(0LL)> v = 0LL)
           : rows_n(r_), cols_n(c_), a(rows_n * cols_n, v) {
        assert(rows_n >= 1 && cols_n >= 1);
       }
       explicit matrix(T d) : rows_n(1), cols_n(1), a{d} {}
       explicit matrix(vector<vector<pr>> const &g)
           : matrix(g.size(), g.size(), inf) {
        for ([[maybe_unused]] const auto i : ra{rows_n}) {
         for (const auto &p : g[i]) {
          auto [x, w] = p;
          (*this)[i][x] = w;
         }
        }
        for ([[maybe_unused]] const auto i : ra{rows_n}) { (*this)[i][i] = 0; }
       }
       explicit matrix(const initializer_list<initializer_list<ll>> &vals)
           : matrix(size(vals), size(begin(vals)[0])) {
        for ([[maybe_unused]] const auto i : ra{rows_n}) {
         assert(size(begin(vals)[i]) == cols_n);
         for ([[maybe_unused]] const auto j : ra{cols_n}) { (*this)[i][j] = begin(begin(vals)[i])[j]; }
        }
       }
       auto operator[](const ll i) {
        return const_cast<T *>(const_cast<matrix const &>((*this))[i]);
       }
       auto operator[](const ll i) const { return &a[i * cols_n]; }
      };
      template <typename T> auto identity(const plus<>, const matrix<T> &mat) {
       return matrix(mat.rows_n, mat.cols_n);
      }
      template <typename T> auto identity(const multiplies<>, const matrix<T> &mat) {
       assert(mat.rows_n == mat.cols_n);
       matrix<T> id(mat.rows_n, mat.cols_n);
       for ([[maybe_unused]] const auto i : ra{mat.rows_n}) { id[i][i] = 1; }
       return id;
      }
      template <typename... Ts>
      auto operator+(const matrix<Ts...> &a, const matrix<Ts...> &b) {
       assert(a.rows_n == b.rows_n && a.rows_n == b.rows_n);
       matrix c(a.rows_n, a.cols_n);
       for ([[maybe_unused]] const auto i : ra{a.rows_n}) {
        for ([[maybe_unused]] const auto j : ra{a.col_n}) { c[i][j] = a[i][j] + b[i][j]; }
       }
       return c;
      }
      template <typename... Ts> auto operator-(const matrix<Ts...> &a) {
       matrix c(a.rows_n, a.cols_n);
       for ([[maybe_unused]] const auto i : ra{a.rows_n}) {
        for ([[maybe_unused]] const auto j : ra{a.col_n}) { c[i][j] = -a[i][j]; }
       }
       return c;
      }
      template <typename ... T> bool operator==(matrix<T...> const &a, matrix<T...> const &b) {
       return a.rows_n == b.rows_n && a.cols_n == b.cols_n && a.a == b.a;
      }
      template <typename ... T> auto operator*(matrix<T...> const &a, matrix<T...> const &b) {
      
       assert(a.cols_n == b.rows_n);
       matrix<T...> c{a.rows_n, b.cols_n};
       for ([[maybe_unused]] const auto i : ra{c.rows_n}) {
        for ([[maybe_unused]] const auto j : ra{a.cols_n}) {
         for ([[maybe_unused]] const auto k : ra{c.cols_n}) { c[i][k] += a[i][j] * b[j][k]; }
        }
       }
       return c;
      }
      template <typename T> pair<matrix<T> &&, T> gauss(matrix<T> b, matrix<T> a) {
      
      
      
      
       assert(a.rows_n == a.cols_n);
       assert(a.rows_n == b.rows_n);
       T det{1};
       for ([[maybe_unused]] const auto i : ra{a.rows_n}) {
        const auto div = a[i][i];
        det *= div;
        for (auto &ar : {ref(a), ref(b)}) {
         for ([[maybe_unused]] const auto k : ra{ar.get().cols_n}) { ar.get()[i][k] /= div; }
        }
        for ([[maybe_unused]] const auto j : ra{a.rows_n}) {
         if (j == i) {
          continue;
         }
         const auto mul = a[j][i];
         for (auto &ar : {ref(a), ref(b)}) {
          for ([[maybe_unused]] const auto k : ra{ar.get().cols_n}) {
           ar.get()[j][k] -= ar.get()[i][k] * mul;
          }
         }
        }
       }
       return {move(b), det};
      }
      template <typename... Ts> matrix<Ts...> invert(const matrix<Ts...> &a) { return identity(multiplies<>{}, a) / a; }
      template <typename... Ts> void test_invert_impl(const matrix<Ts...> &a) {
       assert(invert(a) * a == identity(multiplies<>{}, a));
       assert(a * invert(a) == identity(multiplies<>{}, a));
      }
      void test_invert() {
       with _m{ll(1e9 + 7), modulo::modulus};
       matrix<modulo> a{{2, 3, 5}, {3, 6, 10}, {5, 9, 16}};
       matrix<modulo> b{{1, 2, 3}, {4, 5, 6}, {9, 7, 8}};
       test_invert_impl(a);
       test_invert_impl(b);
      }
      template <typename ... T> auto operator/(const matrix<T...> &b, const matrix<T...> &a) {
      
       return gauss(b, a).first;
      }
      template <typename T> T det(const matrix<T> &a) {
      
       return gauss(matrix<T>(a.rows_n, 1), a).second;
      }
      template <typename Stream, typename... T>
      auto &operator<<(Stream &os, matrix<T...> const &m) {
      
       os << simple_tp(m) << endl;
       for ([[maybe_unused]] const auto i : ra{m.rows_n}) {
        copy(m[i], m[i] + m.cols_n, make_ostream_joiner(os, delim));
        os << endl;
       }
       return os << "}";
      }
      void test_matrix() {
       with _m{ll(1e9 + 7), modulo::modulus};
       matrix<modulo> a{{2, 3, 5}, {3, 6, 10}, {5, 9, 16}};
       matrix<modulo> b{{1, 2, 3}, {4, 5, 6}, {9, 7, 8}};
       assert(a * (b / a) == b);
      }
      template <typename T> auto lin_recur(vector<T> const &c, const ll n) {
      
      
      
       matrix<T> m(size(c), size(c));
       copy(begin(c), end(c), m[0]);
       for ([[maybe_unused]] const auto i : ra{1, size(c)}) { m[i][i - 1] = 1; }
       return power(m, n)[0][0];
      }
      void test_lin_recur() {
       assert(lin_recur(vl{1, 2}, 5) == 21);
       assert(lin_recur(vl{2, 3, 1}, 4) == 65);
      }
      
      template <typename T> Polynomial<T> lin_recur_coef(vector<T> const &c) {}
      void test_linear_algebra() {
       test_matrix();
       test_lin_recur();
       test_invert();
      
      }
      }
      using namespace linear_algebra;
      # 5 "graph_theory.hpp" 2
      namespace graph_theory {
      
      struct edge {
       ll weight, a, b;
       auto to_tuple() const { return tuple{weight, a, b}; }
      };
      bool operator<(edge const &a, edge const &b) {
      
       return a.to_tuple() < b.to_tuple();
      }
      bool operator==(edge const &a, edge const &b) {
       return a.to_tuple() == b.to_tuple();
      }
      template <typename Stream> auto &operator<<(Stream &os, edge const &e) {
      
       return os << "edge{" << e.a << "-(" << e.weight << ")>" << e.b << "}";
      }
      auto add_edge(vector<vl> &graph, ll u, ll v) {
      
       graph[u].push_back(v);
       graph[v].push_back(u);
      }
      auto shortest_dist(vector<vector<pr>> graph, ll source) {
      
      
       vl d(graph.size(), inf), pv(graph.size(), -1);
       prio_queue_t<pr, greater<>> q;
       d[source] = 0;
       for ([[maybe_unused]] const auto i : ra{d.size()}) { q.push({d[i], i}); }
       while (q.size()) {
        const auto [di, a] = q.top();
        q.pop();
        if (di != d[a]) {
         continue;
        }
        for (const auto &edge : graph[a]) {
         const auto &[b, w] = edge;
         auto &x = d[b];
         auto nw = di + w;
         if (nw < x) {
          pv[b] = a;
          x = nw;
          q.push({x, b});
         }
        }
       }
       return array<vl, 2>{d, pv};
      }
      
      
      
      
      auto shortest_dist(matrix<ll> const &graph) {
       assert(graph.rows_n == graph.cols_n);
       auto n = graph.rows_n;
       auto d = graph;
       for ([[maybe_unused]] const auto k : ra{n}) {
        for ([[maybe_unused]] const auto i : ra{n}) {
         for ([[maybe_unused]] const auto j : ra{n}) {
          auto &x = d[i][j];
          x = min(x, d[i][k] + d[k][j]);
         }
        }
       }
       return d;
      }
      void test_shortest_dist() {
       matrix<ll> g{{7, 2, 5}, {2, 4, 1}, {3, 2, 5}};
       matrix<ll> short_dist{{4, 2, 3}, {2, 3, 1}, {3, 2, 3}};
       assert(shortest_dist(g) == short_dist);
       const auto n = g.rows_n;
       vector<vector<pr>> adj(n);
       for ([[maybe_unused]] const auto i : ra{0, n}) {
        for ([[maybe_unused]] const auto j : ra{0, n}) { adj[i].push_back({j, g[i][j]}); }
       }
       for ([[maybe_unused]] const auto s : ra{0, n}) {
      
        const auto dijkstra = shortest_dist(adj, s)[0];
        auto floyd = vl(short_dist[s], short_dist[s] + n);
        floyd[s] = 0;
        assert((dijkstra == floyd));
       }
      }
      
      auto mst(vector<edge> edges, const ll n) {
       sort(begin(edges), end(edges));
       dsu d{n};
       vector<edge> ret;
       for (const auto &e : edges) {
        if (!d.join(e.a, e.b)) {
         continue;
        }
        ret.push_back(e);
       }
       return ret;
      }
      void test_mst() {
       vector<edge> edges{{5, 0, 3}, {2, 1, 2}, {3, 1, 3}, {1, 3, 2}};
       auto ret = mst(edges, 6);
       sort(begin(ret), end(ret));
       assert((ret == vector<edge>{edges[3], edges[1], edges[0]}));
      }
      
      struct gsearch {
       vector<vl> const &graph;
       vector<char> visited;
       deque<ll> q;
       vl parent;
       vl distance;
       gsearch(const vector<vector<ll>> &g_)
           : graph(g_), visited(graph.size()), parent(graph.size(), -1),
             distance(graph.size(), inf) {}
       virtual void operator()(ll) = 0;
       void operator()() {
      
      
        for ([[maybe_unused]] const auto i : ra{graph.size()}) {
         if (!visited[i]) {
          (*this)(i);
         }
        }
       }
       void add(const ll child, const ll par) {
      
      
        distance[child] = distance[par] + 1;
        parent[child] = par;
       }
      };
      
      template <typename Searcher> vector<ll> get_size(const Searcher &search) {
       vector<ll> sz(search.parent.size(), 1);
       for (auto idx : rev(search.q)) {
        if (search.parent[idx] != -1) {
         sz[search.parent[idx]] += sz[idx];
        }
       }
       return sz;
      }
      
      struct dfs : public gsearch {
       using gsearch::operator(), gsearch::gsearch;
       void operator()(const ll source) {
        visited[source] = true;
        for (const auto &j : graph[source]) {
         if (visited[j]) {
          continue;
         }
         add(j, source);
         (*this)(j);
        }
        q.push_front(source);
       }
      };
      
      struct bfs : public gsearch {
       using gsearch::operator(), gsearch::gsearch;
       void operator()(ll source) {
        ll old_size = q.size();
        q.push_back(source);
        visited[source] = true;
        distance[source] = 0;
        for (ll idx = old_size; idx < q.size(); ++idx) {
         auto i = q[idx];
         for (const auto &j : graph[i]) {
          if (visited[j]) {
           continue;
          }
          q.push_back(j);
          visited[j] = true;
          add(j, i);
         }
        }
       }
      };
      void test_bfs() {
       vector<vl> g(4);
       add_edge(g, 0, 1);
       add_edge(g, 1, 2);
       add_edge(g, 1, 3);
       add_edge(g, 2, 3);
       bfs b{g};
       b(0);
       assert((b.parent == vl{-1, 0, 1, 1}));
       assert((b.distance == vl{0, 1, 2, 2}));
      }
      
      auto trans(const vector<vl> &graph) {
       ll n = size(graph);
       vector<vl> h(n);
       for ([[maybe_unused]] const auto i : ra{n}) {
        for (ll j : graph[i]) {
         h[j].push_back(i);
        }
       }
       return h;
      }
      void test_trans() {
       assert((trans(vector<vl>{{2, 3}, {2, 1}, {2}, {2, 3, 1}}) ==
        vector<vl>{{}, {1, 3}, {0, 1, 2, 3}, {0, 3}}));
       assert((trans(vector<vl>{}) == vector<vl>{}));
      }
      auto scc(const vector<vl> &graph) {
      
      
       auto h = trans(graph);
       vl cm(size(graph), -1);
       auto assign = fix{[&](const auto &assign, ll u, ll c) -> void {
        if (cm[u] != -1) {
         return;
        }
        cm[u] = c;
        for (ll v : h[u]) {
         assign(v, c);
        }
       }};
       dfs s{graph};
       s();
       for (ll i : s.q) {
        assign(i, i);
       }
       return cm;
      }
      void test_scc() {
       vector<vl> g(5);
       g[0].push_back(3);
       g[3].push_back(1);
       g[1].push_back(2);
       g[2].push_back(0);
       g[0].push_back(4);
       g[2].push_back(4);
       const auto cm = scc(g);
       vl v{cm[0], cm[1], cm[2], cm[3]};
      
       assert((all_of(begin(v), end(v), [&](auto x) { return x == v[0]; })));
       assert(cm[4] != cm[0]);
      }
      auto bipartite(const vector<vl> &graph) {
      
       bfs b{graph};
       b();
       auto n = size(graph);
       vl s(n);
       for (auto i : b.q) {
        if (const auto par = b.parent[i]; par != -1) {
         s[i] = !s[par];
        }
       }
       bool bi = true;
       for ([[maybe_unused]] const auto i : ra{n}) {
        for (const auto j : graph[i]) {
         bi &= s[i] != s[j];
        }
       }
       return bi ? optional{s} : nullopt;
      }
      void test_bipartite() {
       vector<vl> g(6);
      
      
       add_edge(g, 2, 5);
       add_edge(g, 4, 5);
       add_edge(g, 4, 3);
      
       add_edge(g, 1, 0);
       add_edge(g, 4, 0);
       const auto col = bipartite(g).value();
       for ([[maybe_unused]] const auto i : ra{0, g.size()}) {
        for (auto j : g[i]) {
         assert(col[i] ^ col[j]);
        }
       }
      }
      
      
      auto max_match(const vector<vl> &graph) {
       auto side = bipartite(graph).value();
       ll n = graph.size();
       vl match(n, -1);
       while (true) {
      
      
        vector<vl> aug_path(n + 2);
        const auto dummy_a = n;
        const auto dummy_b = n + 1;
        for ([[maybe_unused]] const auto i : ra{n}) {
         for (ll j : graph[i]) {
          if ((j == match[i]) == side[i]) {
           aug_path[i].push_back(j);
          }
         }
        }
        for ([[maybe_unused]] const auto i : ra{n}) {
         if (match[i] != -1) {
          continue;
         }
         if (side[i]) {
          aug_path[i].push_back(dummy_b);
         } else {
          aug_path[dummy_a].push_back(i);
         }
        }
        bfs b{aug_path};
        b(dummy_a);
        if (b.distance[dummy_b] == inf) {
         break;
        }
        vl vis(aug_path.size());
        auto path = fix{[&](const auto &path, ll i) -> bool {
         if (vis[i]) {
          return false;
         }
         vis[i] = true;
         if (i == dummy_b) {
          return true;
         }
         for (ll j : aug_path[i]) {
          if (b.distance[j] == b.distance[i] + 1) {
           if (path(j)) {
            if (i < n && j < n) {
             match[i] = j;
             match[j] = i;
            }
            return true;
           }
          }
         }
         return false;
        }};
        path(dummy_a);
       }
       return match;
      }
      
      
      
      ll matching_size(const vl &matching) {
       return count_if(begin(matching), end(matching), [&](const auto x) { return x != -1; });
      }
      void test_max_match() {
       {
        vector<vl> g(3);
      
        add_edge(g, 0, 1);
        add_edge(g, 2, 1);
        assert((matching_size(max_match(g)) == 2 * 1));
       }
       {
        vector<vl> g(4);
      
        add_edge(g, 0, 1);
        add_edge(g, 2, 1);
        add_edge(g, 2, 3);
        assert((matching_size(max_match(g)) == 2 * 2));
       }
       {
        vector<vl> g(6);
      
        add_edge(g, 0, 1);
        add_edge(g, 0, 3);
        add_edge(g, 2, 3);
        add_edge(g, 2, 5);
        add_edge(g, 4, 1);
        add_edge(g, 4, 5);
        const auto matching = max_match(g);
        assert((matching_size(max_match(g)) == 2 * 3));
       }
       {
        vector<vl> g(6);
      
        add_edge(g, 0, 1);
        add_edge(g, 0, 3);
        add_edge(g, 2, 1);
        add_edge(g, 2, 5);
        add_edge(g, 4, 1);
        add_edge(g, 4, 5);
        assert((matching_size(max_match(g)) == 2 * 3));
       }
       {
        vector<vl> g(6);
      
        add_edge(g, 0, 1);
        add_edge(g, 2, 1);
        add_edge(g, 2, 5);
        add_edge(g, 4, 1);
        add_edge(g, 4, 5);
        assert((matching_size(max_match(g)) == 2 * 2));
       }
       {
        vector<vl> g(10);
      
        for ([[maybe_unused]] const auto i : ra{0, g.size() / 2}) {
         if (2 * i - 1 >= 0) {
          add_edge(g, 2 * i, 2 * i - 1);
         }
         if (2 * i + 1 < g.size()) {
          add_edge(g, 2 * i, 2 * i + 1);
         }
        }
        assert((matching_size(max_match(g)) == 2 * g.size() / 2));
       }
      }
      void test_add_edge() {
       vector<vl> g(10);
       add_edge(g, 3, 4);
       add_edge(g, 6, 4);
       add_edge(g, 9, 2);
      
       for (auto &x : g) {
        sort(begin(x), end(x));
       }
       assert(
           (g == vector<vl>{{}, {}, {9}, {4}, {3, 6}, {}, {4}, {}, {}, {2}}));
      }
      auto graph_in(vector<vl> &g, ll m) {
      
       for ([[maybe_unused]] const auto i : ra{0, m}) {
        ll u; cin >> u;;
        ll v; cin >> v;;
        add_edge(g, --u, --v);
       }
      }
      
      
      
      
      pair<array<ll, 2>, ll> tree_diameter(const vector<vector<ll>> &g) {
      
       bfs b{g};
       b();
       const auto u = b.q.back();
       bfs b2{g};
       b2(u);
       const auto v = b2.q.back();
       auto c = v;
       for ([[maybe_unused]] const auto i : ra{b2.distance[v] / 2}) { c = b2.parent[c]; }
       return {{u, v}, c};
      }
      void test_tree_diameter() {
       {
        vector<vector<ll>> graph(5);
        add_edge(graph, 1, 3);
        add_edge(graph, 3, 2);
        add_edge(graph, 2, 0);
        add_edge(graph, 0, 4);
        auto ret = tree_diameter(graph);
        sort(begin(ret.first), end(ret.first));
        assert((ret.first == array<ll, 2>{1, 4}));
        assert(ret.second == 2);
       }
       {
        vector<vector<ll>> graph(5);
        add_edge(graph, 1, 3);
        add_edge(graph, 3, 2);
        add_edge(graph, 2, 0);
        add_edge(graph, 3, 4);
        auto ret = tree_diameter(graph).first;
        sort(begin(ret), end(ret));
        assert(ret[0] == 0);
       }
      }
      void test_graph_theory() {
       test_add_edge();
       test_trans();
       test_shortest_dist();
       test_mst();
       test_bfs();
       test_bipartite();
       test_scc();
       test_max_match();
       test_tree_diameter();
      }
      }
      using namespace graph_theory;
      # 2 "d.cpp" 2
      # 1 "main.hpp" 1
             
      
      # 1 "time.hpp" 1
             
      
      namespace time_tools {
      struct timer {
      
      
       decltype(clock_::now()) t1;
       timer() : t1(clock_::now()) {}
       ~timer() {
        cerr << "Time duration: "
             << duration<ld>(clock_::now() - t1).count() << " s"
             << endl;
       }
      };
      template <typename Func> void bench(Func a) {
       timer _t;
       decltype(a) ans = 0;
       for (decltype(a) i = 0; i < a; ++i) {
        for (decltype(a) j = 1; j < a; ++j) {
         ans += ((-i) % (j));
        }
       }
      
       const auto volatile _unused = ans;
      }
      }
      using namespace time_tools;
      # 4 "main.hpp" 2
      void main2();
      
      
      
      
      
      auto &in = cin;
      
      int main(int argc, char *argv[]) {
      
      
      
       for ([[maybe_unused]] const auto i : ra{argc}) {
        if (argv[i] == "-q"s) {
         debug_mode = false;
        }
       }
       ios::sync_with_stdio(false);
       if (!debug_mode) {
        cerr.rdbuf(nullptr);
       }
       for (ios &os :
            initializer_list<reference_wrapper<ios>>{in, cout, cerr, clog}) {
        fixed(os);
        if (os.rdbuf()) {
         os.exceptions(ios::failbit | ios::badbit | ios::eofbit);
        }
        os.precision(false ? numeric_limits<ld>::max_digits10 : 5);
       }
       cout.precision(numeric_limits<ld>::max_digits10);
       timer _t;
       ll t = 1;
       if (multitest) {
        cin >> t;
       }
       for ([[maybe_unused]] const auto i : ra{t}) { main2(); }
      }
      # 3 "d.cpp" 2
      bool multitest{};
      void main2() {
          ll n; cin >> n;;ll m; cin >> m;;
          vector<vl> g(n);
          vl u(m), v(m), col(m, 1);
          for ([[maybe_unused]] const auto i : ra{m}){
              cin>>u[i]>>v[i];
              --u[i];--v[i];
              g[u[i]].push_back(v[i]);
          }
          dfs d{g};
       d();
          vl pos(n);
          for ([[maybe_unused]] const auto i : ra{n}){
              pos[d.q[i]] = i;
          }
          for ([[maybe_unused]] const auto i : ra{m}){
              col[i] = 1+(pos[u[i]] > pos[v[i]]);
          }
          cout<<*max_element(begin(col), end(col))<<endl;;
          for(auto x:col){cout<<x<<" ";}
          cout<<endl;
      }
