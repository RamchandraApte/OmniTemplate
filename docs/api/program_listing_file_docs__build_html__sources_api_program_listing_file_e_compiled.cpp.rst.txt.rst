
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_e_compiled.cpp.rst.txt:

Program Listing for File program_listing_file_e_compiled.cpp.rst.txt
====================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_e_compiled.cpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_e_compiled.cpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_e_compiled.cpp:
   
   Program Listing for File e_compiled.cpp
   =======================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_e_compiled.cpp>` (``e_compiled.cpp``)
   
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
      # 1 "e.cpp"
      # 1 "segment_tree.hpp" 1
             
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
      # 3 "segment_tree.hpp" 2
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
      # 4 "segment_tree.hpp" 2
      # 14 "segment_tree.hpp"
      template <typename T, typename Query, typename Update, bool has_lazy = true, bool has_ptr = true, bool has_pers = true, ll base = 2> class SegmentTree {
            public:
       SegmentTree(const ll size_arg) : size_{size_arg}, ceil_size{power_ceil(size_arg, base)}, nodes(!has_ptr ? base * ceil_size : 0) {
        if constexpr (has_ptr) {
         root = new NodeExp{};
        } else {
         root = 1;
        }
       }
       SegmentTree(const vector<T>& arr): SegmentTree(arr.size()) {
              build(arr);
          }
       static_assert(!has_pers || has_ptr, "Pointers required for persistency");
       static_assert(base > 1, "Base must be at least 1");
       struct LazyPart {
        T lazy{identity(Update{}, T{})};
       };
       struct NodeCore : public conditional_t<has_lazy, LazyPart, Empty> {
        T qsum{identity(Query{}, T{})};
       };
       struct NodeExp : public NodeCore {
        array<NodeExp *, base> child{};
       };
       using Node = conditional_t<has_ptr, NodeExp *, ll>;
      
       auto &get_core(NodeExp *const &obj) { return *obj; }
       auto &get_core(const ll idx) { return nodes[idx]; }
       auto &get_child(NodeExp *const &obj, const ll i) { return obj->child[i]; }
       auto get_child(const ll idx, const ll i) { return base * idx + i; }
       static ll mid(const ll node_l, const ll node_r, const ll i) {
        const auto df = (node_r - node_l) / base;
        return node_l + df * i;
       };
          void build(const vector<T>& arr){
              build(arr, root, 0, ceil_size);
          }
          void build(const vector<T>& arr, const Node idx, const ll node_l, const ll node_r){
              if(node_r-node_l == 1){
                  get_core(idx).qsum = node_l < arr.size() ? arr[node_l]: identity(Query{}, T{});
                  return;
              }
              auto ret = identity(Query{}, T{});
              for ([[maybe_unused]] const auto inc : ra{base}){
                  build(arr, get_child(idx, inc), mid(node_l, node_r, inc), mid(node_l, node_r, inc+1));
                  ret = Query{}(ret, get_core(get_child(idx, inc)).qsum);
              }
              get_core(idx).qsum = ret;
          }
      
       void down(const Node idx, const ll node_l, const ll node_r) {
        const bool leaf = node_r - node_l == 1;
        if constexpr (has_ptr) {
         if (!leaf) {
          for (auto &ptr : idx->child) {
           if (!ptr) {
            ptr = new NodeExp{};
           }
          }
         }
        }
        if constexpr (has_lazy) {
      
         get_core(idx).qsum = Update{}(get_core(idx).qsum, get_core(idx).lazy);
         if (!leaf) {
          for ([[maybe_unused]] const auto i : ra{base}) { get_core(get_child(idx, i)).lazy += get_core(idx).lazy; }
         }
         get_core(idx).lazy = identity(Update{}, get_core(idx).lazy);
        }
       }
       T query(const ll l, const ll r, const Node idx, const ll node_l, const ll node_r) {
      
      
        if (node_r <= l || r <= node_l) {
         return identity(Query{}, T{});
        }
        down(idx, node_l, node_r);
        if (l <= node_l && node_r <= r) {
         return get_core(idx).qsum;
        }
      
        auto ret = identity(Query{}, T{});
        for ([[maybe_unused]] const auto inc : ra{base}) { ret = Query{}(ret, query(l, r, get_child(idx, inc), mid(node_l, node_r, inc), mid(node_l, node_r, inc + 1))); }
        return ret;
       }
       T query(const ll l, const ll r, const Node custom_root) {
        if (!(0 <= l && l <= r && r <= size_)) {
         throw out_of_range{"Segment tree query out of bounds"};
        }
        return query(l, r, custom_root, 0, ceil_size);
       }
       T query(const ll l, const ll r) { return query(l, r, root); }
       Node update(const ll l, const ll r, const T val, Node idx, const ll node_l, const ll node_r) {
      
      
      
        if (node_r <= l || r <= node_l) {
         return idx;
        }
        down(idx, node_l, node_r);
        if constexpr (has_pers) {
         idx = new NodeExp{*idx};
        }
        if (l <= node_l && node_r <= r) {
         if constexpr (has_lazy) {
          get_core(idx).lazy = Update{}(get_core(idx).lazy, val);
          down(idx, node_l, node_r);
         } else {
          get_core(idx).qsum = Update{}(get_core(idx).qsum, val);
         }
         return idx;
        }
        for ([[maybe_unused]] const auto inc : ra{base}) {
         auto get_update = [&] { return update(l, r, val, get_child(idx, inc), mid(node_l, node_r, inc), mid(node_l, node_r, inc + 1)); };
         if constexpr (has_pers) {
          get_child(idx, inc) = get_update();
         } else {
          get_update();
         }
        }
        get_core(idx).qsum = identity(Query{}, T{});
        for ([[maybe_unused]] const auto inc : ra{base}) { get_core(idx).qsum = Query{}(get_core(idx).qsum, get_core(get_child(idx, inc)).qsum); }
        return idx;
       }
       Node update(const ll l, const ll r, const T val) {
        if constexpr (!has_lazy) {
         assert(l + 1 == r);
        }
        return root = update(l, r, val, root, 0, ceil_size);
       }
       void destroy(Node node) {
      
        if constexpr (has_ptr && !has_pers) {
         if (!node) {
          return;
         }
         for ([[maybe_unused]] const auto inc : ra{base}) { destroy(get_child(node, inc)); }
         delete node;
        }
       }
       ~SegmentTree() {
      
        if constexpr (has_ptr && !has_pers) {
         destroy(root);
        }
       }
      
            private:
       ll size_;
       ll ceil_size;
       Node root;
       vector<NodeCore> nodes;
      };
      template <bool has_lazy, bool has_ptr, bool has_pers, ll base> void test_segment_tree_impl() {
       SegmentTree<ll, Max, plus<>, has_lazy, has_ptr, has_pers, base> seg{1000};
       assert(seg.query(1, 3) == -inf);
       assert(seg.query(7, 9) == -inf);
       for ([[maybe_unused]] const auto i : ra{0, 10}) { seg.update(i, i + 1, inf); }
       auto upd_old = [&] { return seg.update(0, 1, 0); };
       using NodePtr = typename decltype(seg)::NodeExp *;
       NodePtr old;
       if constexpr (has_pers) {
        old = upd_old();
       } else {
        upd_old();
       }
       assert(seg.query(0, 10) == 0);
       assert(seg.query(3, 4) == 0);
       seg.update(2, 3, 2);
       auto old2 = seg.update(4, 5, 3);
       if constexpr (has_pers) {
        assert(seg.query(0, 10, old) == 0);
       }
       assert(seg.query(0, 10) == 3);
       assert(seg.query(3, 4) == 0);
       assert(seg.query(2, 4) == 2);
       if constexpr (has_pers) {
        assert(seg.query(2, 4, old2) == 2);
       }
       seg.update(2, 3, -2);
       seg.update(4, 5, -3);
       assert(seg.query(2, 4) == 0);
       assert(seg.query(0, 10) == 0);
       if constexpr (has_pers) {
        assert(seg.query(0, 10, old) == 0);
        assert(seg.query(2, 4, old2) == 2);
       }
       for ([[maybe_unused]] const auto i : ra{0, 10}) { seg.update(i, i + 1, -inf); }
       if constexpr (has_lazy) {
        seg.update(0, 10, inf);
        auto upd1 = [&] { return seg.update(3, 4, 10); };
        NodePtr old_lazy;
        if constexpr (has_pers) {
         old_lazy = upd1();
        } else {
         upd1();
        }
        assert(seg.query(0, 10) == 10);
        if constexpr (has_pers) {
         assert(seg.query(0, 10, old_lazy) == 10);
        }
        seg.update(2, 4, 20);
        assert(seg.query(3, 4) == 30);
        assert(seg.query(2, 4) == 30);
        assert(seg.query(2, 3) == 20);
        assert(seg.query(1, 10) == 30);
        seg.update(0, 2, 10);
        assert(seg.query(1, 10) == 30);
        if constexpr (has_pers) {
         assert(seg.query(0, 10, old) == 0);
         assert(seg.query(2, 4, old2) == 2);
         assert(seg.query(0, 10, old_lazy) == 10);
        }
       }
      }
      void test_segment_tree() {
       test_segment_tree_impl<false, false, false, 2>();
      
       test_segment_tree_impl<false, false, false, 3>();
      
       test_segment_tree_impl<true, false, false, 2>();
      
       test_segment_tree_impl<false, true, false, 2>();
      
       test_segment_tree_impl<false, true, false, 2>();
      
       test_segment_tree_impl<false, true, true, 2>();
      
       test_segment_tree_impl<true, true, true, 2>();
      }
      # 2 "e.cpp" 2
      # 1 "main.hpp" 1
             
      
      
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
      # 3 "e.cpp" 2
      namespace std{
      pr operator+(pr a, const pr& b){
          a.first = b.first;
          a.second = min(a.second, b.second);
          return a;
      }
      }
      pr identity(const Min&, const pr&){
          return {inf, inf};
      }
      bool multitest{};
      void main2() {
          ll n; cin >> n;;ll m; cin >> m;;
          vl a(n);
          for(auto& x:a){cin>>x;}
          const ll sz = 9;
          using st = SegmentTree<pr, Min, plus<>, false, false, false>;
          vector<st> s(sz, st(2));
          vector arr(sz, vector<pr>(n));
          for ([[maybe_unused]] const auto i : ra{0,n}){
              ll x = a[i];
              for ([[maybe_unused]] const auto j : ra{0,sz}){
                  arr[j][i] = {x%10?a[i]:inf, i};
                  x/=10;
              }
          }
          for ([[maybe_unused]] const auto j : ra{0,sz}){
              s[j] = st(arr[j]);
          }
          auto q1 = [&](ll idx, const ll orig){
              --idx;
              ll val = orig;
              for ([[maybe_unused]] const auto i : ra{0,sz}){
                  auto& tree = s[i];
                  tree.update(idx, idx+1, {(val%10?orig:inf), idx});
                  val/=10;
              }
          };
          auto q2 = [&](ll l, ll r){
              --l;
              ll ans = inf;
              for ([[maybe_unused]] const auto i : ra{0,sz}){
                  auto m1 = s[i].query(l, r);
                  if(m1.first == inf){continue;}
                  auto m2 = min(s[i].query(l, m1.second), s[i].query(m1.second+1, r));
                  if(m2.first == inf){continue;}
                  ans = min(ans, m1.first+m2.first);
              }
              if(ans == inf){ans = -1;}
              cout<<ans<<endl;
          };
          for ([[maybe_unused]] const auto i : ra{0,m}){
              ll tp; cin >> tp;;ll qa; cin >> qa;;ll qb; cin >> qb;;
              if(tp == 1){
                  q1(qa, qb);
              }
              if(tp == 2){
                  q2(qa, qb);
              }
          }
      }
