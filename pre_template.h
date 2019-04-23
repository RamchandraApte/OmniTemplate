#ifndef LOCAL
#define NDEBUG
#endif
#include <bits/extc++.h>
#include <experimental/source_location>
#include <experimental/iterator>
#define fo(i,...) for([[maybe_unused]] _ i: ra{__VA_ARGS__})
#define _ auto
#define tp decltype
#define tm(...) template<typename __VA_ARGS__ T>
#define this (*this)
#define al(v) begin(v),end(v)
#define I(x) ll x;in>>x;
#define co const
#define $ _ co&
#define pb push_back
#define vc vector
bool debug_mode = false;
//#define rel_assert(msg) if constexpr(debug_mode){static_assert(false, msg);}
#define rel_assert(...)
#define WARN(msg) [[deprecated(msg)]] _ warn = [](){rel_assert(msg);}; warn();
//#define TODO(msg) WARN("TODO: " msg)
#define TODO(msg)
#define dbg(x) (++depth, debug(x, #x##s))
#define paste2(x,y) x##y
#define paste(x, y) paste2(x,y)
#define lets_count lets_add paste(_l, __COUNTER__)
#define let(a, ...) using a = __VA_ARGS__; lets_count{#__VA_ARGS__, #a};
#define import(a) using namespace a; lets_count{#a "::", ""};
#define df(x, v) remove_const_t<tp(v)> x = v
using namespace std;
#define ostream auto
vector<pair<string, string>> lets{{"__debug::", ""}, {"const ", ""}, {"__cxx11::basic_string<char>", "string"}};
struct lets_add {
	lets_add($ a, $ b){
		lets.pb({a,b});
	}
};
import(__gnu_pbds);
using std::priority_queue;
using __gnu_cxx::power;
import(std);
import(experimental);
import(chrono);
import(literals);
import(placeholders)
let(lli,long long int);
let(ull, unsigned long long);
_ constexpr operator-($ a, $ b){
	return a + -b;
}
_ constexpr operator!=($ a, $ b){
	return !(a==b);
}
_ operator<=($ a, $ b){
	return !(b < a);
}
_ operator>=($ a, $ b){
	return b <= a;
}
_ operator>($ a, $ b){
	return b < a;
}
#define aug(op) _ operator op##=(_& a, $ b){return a = a op b;}
struct ll {
	lli x;
	constexpr ll(long long int x_ = 0): x(x_) {}
	constexpr operator _&(){return x;}
	constexpr operator _() co {return x;}
	template<typename T, typename = enable_if_t<is_integral<T>::value, void>>
	constexpr operator T() co{return x;}
	/*operator bool() co{return x;}
	operator size_t() co {return x;}
	operator int128() co {return x;}*/
	constexpr ll operator-() co{return -x;}
	ll operator--(){--x; return this;}
	ll operator++(){++x; return this;}
	ll operator+=(ll b){return x += b.x;}
};
#ifdef __SIZEOF_INT128__
using int128 = __int128;
using uint128 = __uint128_t;
#endif
aug(+); aug(-); aug(*); aug(/);
let(vl,vector<ll>);
let(ld,long double)
let(pr,pair<ll, ll>);
let(com, complex<double>);
let(pt, complex<ll>);
template<typename T = less<>>
_ map_args($ f, T g = T{}){
	return [&]($... args){return g(f(args)...);};
}
#ifdef __SIZEOF_INT128__
#define MIX128(op, T1) mix(op, T1, int128)
#else
#define MIX128(...)
#endif
#define mix1(op, T1, T2) constexpr _ operator op(T1 a, T2 b){return static_cast<ll>(a) op static_cast<ll>(b);}
#define mix(op, T1, T2) mix1(op, T1, T2) mix1(op, T2, T1)
#define mixll(op) mix(op, ll, int) mix(op, ll, lli) MIX128(op, ll) mix(op, ll, size_t) mix(op, ll, double)
#define bill(op) constexpr ll operator op(ll co& a, ll co& b){return lli(a) op lli(b);}
bill(+) bill(*) bill(|) bill(&) bill(^) bill(<<) bill(>>)
constexpr ll operator/(ll co& a, ll co& b){
   lli x = lli(a)/lli(b), r = lli(a)%lli(b);
   return x-((x < 0) && r);
}
constexpr _ operator<(ll a, ll b){return lli(a) < lli(b);}
constexpr _ operator==(ll a, ll b){return lli(a) == lli(b);}
constexpr ll operator%(ll a, ll b){
	lli x = lli(a)%lli(b);
	if(lli(x) < 0){x+=lli(b);}
	return x;
}
mixll(+) mixll(/) mixll(*) mixll(<) mixll(==) mixll(%) mixll(&)
_& operator<<(ostream& os, ll co& a){
	return os<<a.x;
}
namespace std {
#define inh(cls) template<> struct cls<ll> : cls<lli>
inh(hash){using hash<lli>::hash;};
inh(is_integral){}; inh(is_unsigned){}; inh(is_signed){}; inh(numeric_limits){};
_ operator+(_ a, ll b){return a+lli(b);}
tm() _& operator<<(ostream& os, optional<T> co& opt){
	return opt?(os<<*opt):(os<<"nullopt");
}
_ operator<(pt co& a, pt co& b){
	return map_args([](_ x){return tuple{real(x), imag(x)};})(a,b);
}
}
struct edge {
	ll w, a, b;
	_ to_tuple() co{
		return tuple{w,a,b};
	}
};
using bt = bitset<numeric_limits<ll>::digits>;
operator<(edge co& a, edge co& b){
	return a.to_tuple() < b.to_tuple();
}
tm() using pq = std::priority_queue<T, vector<T>, greater<>>;
let(clock_, high_resolution_clock);
import(this_thread);
let(um,unordered_map<ll, ll>);
tm() _ type_name([[maybe_unused]] T co& v){
	string s = __PRETTY_FUNCTION__, tar = "T = ";
	_ st = s.find(tar)+tar.size();
	return s.substr(st, s.find("]", st)-st);
}
_ replace(_ s, $ a, $ b){
	ll loc;
	while((loc = s.find(a)) !=string::npos){
		s = s.substr(0, loc) + b + s.substr(loc+a.size());
	}
	return s;
}
_ simple_tp([[maybe_unused]] $ v){
	_ s = type_name(v);
	for($ p: lets){
		s = replace(s, p.first, p.second);
	}
	return s;
}
_ constexpr inf = ll(numeric_limits<ll>::max())/8;
_ co delim = ", "s;
_ constexpr tau = 2*3.1415926535897932384626433L;
struct rin {
	istream& in;
	rin(istream& in_): in(in_) {}
	_& operator<<(const char*){
		return this;
	}
	_& operator<<(string co& s){
		if(s.empty()){
			in>>const_cast<string&>(s);
		}
		return this;
	}
	rin& operator>>(_& x){
		this << x;
		return this;
	}
};
template<typename R, typename T>
_ operator<<(R& r, const T& x) -> decltype(r.in>>const_cast<T&>(x), declval<enable_if_t<is_same<R, rin>::value, rin&>>()) {
	r.in>>const_cast<T&>(x);
	return r;
}
tm() enable_if_t<is_same<T, istream>::value, rin> operator>>(T& is, _& x){
	rin r{is};
	return r>>x;
}
namespace std {
	tm(...) _& operator<<(ostream& os, pair<T...> co& p){
		return os<<simple_tp(p)<<"{"<<p.first<<delim<<p.second<<"}";
	}
	_ operator<<(ostream& os, $ v) -> decltype(begin(v), declval<tp(os)>()){
		_ ed = begin(v);
		_ big = v.size()>20;
		if(big){
			advance(ed, 20);
		}
		else {
			ed = end(v);
		}
		os<<simple_tp(v)<<"{";
		copy(begin(v), ed, make_ostream_joiner(os, delim));
		if(big){
			os<<delim<<"...";
		}
		return os<<"}";
	}
	_ operator<<(rin& os, $ v) -> decltype(begin(v), declval<tp(os)>()){
		for($ elem:v){
			os<<elem;
		}
		return os;
	}
}
_& operator<<(ostream& os, edge co& e){
	return os<<"edge{"<<e.a<<"-"<<e.w<<"->"<<e.b<<"}";
}
tm(...) _& operator<<(ostream& os, tuple<T...> t){
	apply([&](_& f, _& ... x){
		os<<f;
		((os<<delim<<x), ...);
		}, t);
	return os;
}
tm() struct it_base {
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using difference_type = ll;
};
tm() struct int_it: it_base<T>{
	using iterator_category = random_access_iterator_tag;
	T x, m;
	int_it(_ x_, _ m_ = 1):x(x_), m(m_) {}
	int_it(_ x_):int_it(x_, 1){}
	int_it(){}
	_& operator *() co {
		static T x_stat;
		return x_stat = x;
	}
	explicit operator _() co {return x;}
	int_it operator+(ll y) co{return x+m*y;}
	int_it operator-(ll y) co{return x-m*y;}
	ll operator-(int_it<T> co& y) co{return (x-y.x)/m;}
	int_it operator ++(){return x+=m;}
	int_it operator --(){return x-=m;}
	int_it operator--(int){
		_ ret = x;
		--x;
		return ret;
	}
	int_it operator++(int){
		_ ret = x;
		++x;
		return ret;
	}
};
#define bin(op, Tp) _ operator op(Tp co& a, Tp co& b) {return a.x op b.x;}
tm() bin(==, int_it<T>);
tm() bin(<, int_it<T>);
tm() struct range {
	T bg, ed;
	range(_ ed_):range(0LL, ed_){}
	range(T co& bg_, T co& ed_):bg(bg_),ed(max(bg,static_cast<T>(ed_))) {}
	_ begin() co{return bg;}
	_ end() co{return ed;}
	explicit operator ll(){return ed-bg;}
};
tm()
_ operator<(range<T> co& a, range<T> co& b){
	return a.bg==b.bg?a.ed>b.ed:a.bg<b.bg;
}
tm()
_ operator&(range<T> co& a, range<T> co& b){
return range<T>{max(a.bg, b.bg),min(a.ed, b.ed)};
}
_ rev($ r){
	using rev_it = reverse_iterator<tp(begin(r))>;
	return range{rev_it{end(r)}, rev_it{begin(r)}};
}
using ra = range<int_it<ll>>;
ll depth = -1;
_ debug($ x, $ name, source_location co& loc = source_location::current()){
	if(debug_mode){
		fo(i,depth){cerr<<"\t";}
		cerr<<loc.function_name()<<":"<<loc.line()<<" "<<name<<" = "<<x<<endl;
	}
	--depth;
	return x;
}
tm() struct mat {
	ll r,c;
	vc<T> a;
	mat(_ r_, _ c_, df(v, 0LL)): r(r_), c(c_), a(r*c, v) {assert(r>=1 && c>=1);}
	mat(_ d):r(1),c(1),a{d}{}
	mat(vc<vc<pr>> co& g):mat(g.size(),g.size(),inf) {
		fo(i,r){
			for($ p:g[i]){
				_ [x,w] = p;
				this[i][x] = w;
			}
		}
		fo(i,r){
			this[i][i]=0;
		}
	}
	_ operator[](_ i){
		return const_cast<T*>(const_cast<mat co&>(this)[i]);
	}
	_ operator[](_ i) co{
		return &a[i*c];
	}
	_ id() co{
		return this.r==1 && this.c==1 && this[0][0]==1;
	}
};
tm(...) _ operator*(mat<T...> co& a, mat<T...> co& b){
	if(a.id()){return b;}
	if(b.id()){return a;}
	assert(a.c == b.r);
	mat<T...> c{a.r, b.c};
	fo(i,c.r){
		fo(k,c.c){
			fo(j,a.c){
				c[i][k]+=a[i][j]*b[j][k];
			}
		}
	}
	return c;
}
tm(...) _& operator<<(ostream& os, mat<T...> co& m){
	os<<"mat{"<<endl;
	fo(i,m.r){
		copy(m[i], m[i]+m.c, make_ostream_joiner(os, delim));
		os<<endl;
	}
	return os<<"}";
}
struct dsu {
	mutable vl p;
	vl s;
	explicit dsu(_ n): p(n), s(n,1) {iota(al(p),0);}
	ll operator[](ll x) co {return x==p[x]?x:p[x]=this[p[x]];}
	_ operator()(_ x, _ y){
		x = this[x]; y = this[y];
		if(x == y){return false;}
		if(s[x] > s[y]){swap(x,y);}
		s[y]+=s[x];
		p[x] = y;
		return true;
	}
};
_& operator<<(ostream& os, dsu co& d){
	os<<"dsu{";
	fo(i,d.p.size()){
		if(i){os<<delim;}
		os<<d[i];
	}
	return os<<"}";
}
ll M;
struct with {
	ll old;
	ll& v;
	with(ll new_, ll& v_ = M):old(v_), v(v_){v = new_;}
	~with(){v = old;}
};
struct small_mod {};	
struct no_mod {};
struct md {
	ll x;
	md():x{0LL}{}
	template<typename T, typename = enable_if_t<is_integral<T>::value, void>>
	md(T x_):x(ll(x_)%M){}
	md(ll x_, small_mod):x(x_>=M?x_-M:x_){}
	md(ll x_, no_mod): x(x_) {}
	explicit operator _(){return x;}
};
md operator+(md co& a, md co& b){
	return {a.x+b.x, small_mod{}};
}
md operator++(md& a){
	return a+=1;
}
md operator-(md co& a){
	return {M-a.x, no_mod{}};
}
bin(==, md);
tm() int_it<T> operator +(int_it<T> co& a, int_it<T> co& b){return a.x + b.x;}
tm() int_it<T> operator -(int_it<T> co& a){return -a.x;}
md operator*(md co& a, md co& b){
	#if 0
	ll ret = ull(a.x)*ull(b.x)-ull(M)*ull(ld(a.x)*ld(b.x)/ld(M));
	if(ret < 0){return {ret+M, no_mod{}};}
	if(ret >= M){return {ret-M, no_mod{}};}
	return {ret, no_mod{}};
	#endif
	return a.x*b.x;
}
struct id {};
md operator/(id, md co& b){
	assert(b != 0);
	return power(b, M-2);
}
_ operator/(md co& a, md co& b) {
	return a*(id{}/b);
}
_& operator<<(ostream& os, md co& m){return os<<m.x;}
vl divs;
_ prime(_ n){
	assert(n>=2);
	if(n < divs.size()){
		return divs[n] == n;
	}
	with _m{n};
	ll tz = __builtin_ctz(n-1);
	_ b = (n-1)>>tz;
	dbg(b);
	_ prime_a = [&](md co& a){
		dbg(a);
		if(a==0){return true;}
		_ p = power(a,b);
		if(p==1){return true;}
		fo(i,tz){
			if(p == -1){return true;}
			p*=p;
		}
		return false;
	};
	vl v{2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	return all_of(al(v), prime_a);
}
um operator+(um a, um co& b){
	for($ p:b){
		a[p.first]+=p.second;
	}
	return a;
}
um fac(ll n){
	assert(n>=1);
	if(n==1){return {};};
	ll g = n;
	if(n < divs.size()){
		g = divs[n];
	}
	else if(!prime(n)) {
		with _m{n};
		for(md c = 0;g == n;++c){
			_ co f = [&]($ x){return x*x+x+c;};
			for(md a = 0, b = a; a = f(a), b = f(f(b)), (g = gcd(ll(a-b),n)) == 1;){}
		}
	}
	if(g == n){
		return {{n,1}};
	}
	assert(1 < g && g < n && !(n%g));
	return fac(g) + fac(n/g);
}
tm() struct ar {using type = T;};
tm() using ar_t = typename ar<T>::type;
template<typename T, size_t n>
struct ar<T[n]>{using type = array<ar_t<T>,n>;};
_ perm(_ a, _ b){
	using T = tp(a);
	return accumulate(int_it<T>{a+1-b}, int_it<T>{a+1}, 1LL, multiplies<>{});
}
_ fact(_ n){
	return perm(n, n);
}
_ choose(_ a, _ b){
	return perm(a, b)/fact(b);
}
_ sieve(ll n){
	vl d(n), ps;
	fo(i,2,n){
		if(d[i] == 0){ps.pb(d[i] = i);}
		for(_ p: ps){
			if(!(p<=d[i] && p*i < n)){break;}
			assert(d[p*i] == 0);
			d[p*i] = p;
		}
	}
	return d;
}
_ dist(_ g, _ s){
	vl d(g.size(),inf), pv(g.size(),-1);
	pq<pr> q;
	d[s] = 0;
	fo(i,d.size()){
		q.push({d[i], i});
	}
	while(q.size()){
		$ [di, a] = q.top();
		q.pop();
		if(di != d[a]){continue;}
		for($ pb: g[a]){
			$ [b,w] = pb;
			_& x = d[b];
			_ nw = di+w;
			if(nw < x){
				pv[b] = a;
				x = nw;
				q.push({x,b});
			}
		}
	}
	return array<vl,2>{d,pv};
}
_ dist(mat<ll> co& g){
	assert(g.r == g.c);
	_ n = g.r;
	_ d = g;
	fo(k,n){
		fo(i,n){
			fo(j,n){
				_& x = d[i][j];
				x = min(x, d[i][k]+d[k][j]);
			}
		}
	}
	return d;
}
_ mst(_ es){
	sort(al(es));
	_ mi = -inf;
	for($ e: es){
		mi = max(mi,max(e.a,e.b));
	}
	dsu d{mi+1};
	tp(es) ret;
	for($ e: es){
		if(d(e.a,e.b)){continue;}
		ret.pb(e);
	}
	return ret;
}
tm() using bin_op = T(*)(T,T);
#define ret(x, id) if(f == static_cast<tp(f)>(x)){return id;}
constexpr ll identity(bin_op<ll co&> co& f){
	ret(max<ll>, -inf);
	ret(min<ll>, inf);
	abort();
}
constexpr ll identity(bin_op<ll> co& f){
	ret(gcd<ll>, 0);
	abort();
}
_ nx2(_ x){
	return ll(1LL)<<ll(ceil(log2(lli(x))));
}
template<_ op, lli id_ = identity(op)>
struct seg {
	using T = tp(identity(op));
	static constexpr T id = id_;
	ll co n;
	mutable vc<T> a, z;
	seg(_ v): n(nx2(v.size())), a(2*n, id), z(2*n){
		copy(al(v), begin(a)+n);
		for(_ i:rev(ra{n})){
			dbg(i);
			a[i] = op(a[2*i],a[2*i+1]);
		}
	}
	co static _ def = -1LL;
	_ fix(_ l, _& r, _ nl, _& nr) co{
		if(r == def){r = l+1;}
		if(nr == def){nr = n;}
		return make_tuple((nl+nr)/2, r<=nl || nr<=l, l<=nl && nr<=r);
	}
	_ down(_ i) co{
		a[i]+=z[i];
		if(i<n){
			fo(j,2){z[2*i+j]+=z[i];}
		}
		z[i] = 0;
	}
	#define sig _ l, df(r, def), df(i, 1LL), df(nl, 0LL), df(nr, def)
	T gt(sig) co {
		$ [m, dis, over] = fix(l, r, nl, nr);
		down(i);
		return dis?id:over?a[i]:op(gt(l, r, 2*i, nl, m), gt(l, r, 2*i+1, m, nr));
	}
	_ up(_ v, sig){
		$ [m, dis, over] = fix(l, r, nl, nr);
		if(dis||over){
			if(over){
				z[i]+=v;
			}
			down(i);
			return;
		}
		up(v, l, r, 2*i, nl, m);
		up(v, l, r, 2*i+1, m, nr);
		a[i] = op(a[2*i], a[2*i+1]);
	}
};
template<_... args>
 _& operator<<(ostream& os, seg<args...> co& sg){
	os<<"seg{vl{";
	fo(i,sg.n){
		if(i){os<<delim;}
		os<<sg.gt(i);
	}
	return os<<"}}";
}
struct first_cmp {
	operator()(_ a, _ b) co{
		return a.first < b.first;
	}
};
_ tim = 0LL;
tm()
struct pers {
	using event = pair<ll, T>;
	set<event, first_cmp> s;
	_ operator =($ v){
		event e{tim,v};
		s.erase(e);
		s.insert(e);
	}
	operator _() co{
		return (*--s.upper_bound({tim, T{}})).second;
	}
};
tm() _& operator<<(ostream& os, pers<T> co& p){
	return os<<static_cast<T>(p);
}
//_ cnt = 0LL;
#if 0
 _ fft(_& v, df(d, 1LL),  df(s, 0LL)){
	 if(v.size() == d){return;}
	_ n = nx2(v.size());
	v.resize(n);
	fft(v, 2*d, s);
	fft(v, 2*d, s+d);
	_ e = exp(com{-double{tau}*1.0i/(n/d)});
	_ p = com{1};
	_ i = s;
	vc<com> out(n/d);
	fo(j,n/(2*d)){
		_ od = p*v[i+d];
		out[j] = v[i]+od;
		out[j+n/(2*d)] = v[i]-od;
		p*=e;
		i+=2*d;
	}
	i = s;
	for($ x:out){
		v[i] = x;
		i+=d;
	}
}
_ ifft(_& v){
	reverse(begin(v)+1, end(v));
	fft(v);
	for(_& x: v){
		x/=com(v.size());
	}
}
#endif
#if 1
_ fft(_ v){
	_ n = nx2(v.size());
	if(n == 1){return v;}
	v.resize(n);
	vc<vc<com>> vs(2, vc<com>(n/2));
	fo(i,n){
		vs[i%2][i/2] = v[i];
	}
	for(_& x: vs){
		x = fft(x);
	}
	vc<com> f(n);
	fo(i2,n){
		_ i = i2%(n/2);
		f[i2] = vs[0][i]+exp(-com{0, double{tau}*i2/n})*vs[1][i];
		//++cnt;
	}
	return f;
}
_ ifft(_ v){
	reverse(begin(v)+1, end(v));
	_ r = fft(v);
	for(_& x: r){
		x/=com{v.size()};
	}
	return r;
}
#endif
enum isect {
	null, dis, over, cont, eq
};
_ intersect($ a, $ b){
	if(a == b){return isect::eq;}
	if(a[1] <= b[0]){return isect::dis;}
	if(a[0]<=b[0] && b[1] <= a[1]){return isect::cont;}
	if(a[0]<=b[0] && a[1] <= b[1]){return isect::over;}
	return isect::null;
}
tm() _ operator^(range<T> co& a, range<T> co& b){
	return max(intersect(a,b), intersect(b,a));
}
_ filter(vc<ra>& v){
	sort(al(v));
	vc<ra> sg;
	for($ p: v){
		if(sg.empty() || sg.back().ed < p.ed){
			sg.pb(p);
		}
	}
}
struct timer {
	tp(clock_::now()) t1;
	timer(): t1(clock_::now()){}
	~timer(){
		cerr<<"Time duration: "<<duration<ld>(clock_::now()-t1).count()<<" s"<<endl;
	}
};
_ bench(_ a){
	timer _t;
	dbg(ll(-5)/ll(3));
	dbg(tp(a)(-5)/tp(a)(3));
	dbg(tp(a)(-6)/tp(a)(3));
	tp(a) ans = 0;
	for(tp(a) i = 0; i < a; ++i){
		for(tp(a) j = 1; j < a; ++j){
			ans+=((-i)%(j));
		}
	}
	dbg(ans);
}
tm() _ operator*(vc<T> a, vc<T> b){
	assert(a.size() == b.size());
	vc<T> c(a.size());
	fo(i,a.size()){
		c[i] = a[i]*b[i];
	}
	return c;
}
_ conv($ a, $ b){
	return ifft(fft(a)*fft(b));
}
struct bigint {
	vc<ull> v;
	explicit bigint($ v_): v(v_) {}
	_ operator[](size_t i) co{
		return i<v.size()?v[i]:0;
	}
};
_& operator<<(ostream& os, bigint co& a){
	return os<<a.v;
}
#if 0
_ operator+(bigint co& a, bigint co& b){
	#define addo __builtin_add_overflow
	initializer_list xs{a,b};
	ull sm = 0;
	for($ x: xs){sm+=x.v.size();}
	bigint c(sm+1);
	fo(i,sm){
		for($ x: xs){
			dbg(i);
			c.v[i+1] |= dbg(addo(c.v[i], x[i], c.v.data()+i));
		}
	}
	return c;
}
#endif
#define lambda(f) [&](_... args){return f(args...);}
struct gsearch {
	vc<vl> co& g;
	ll n;
	vl v;
	deque<ll> q;
	vl p, d;
	gsearch($ g_): g(g_), n(size(g)), v(n), p(n,-1), d(n) {}
	virtual void operator()(ll) = 0;
	void operator()(){
		fo(i,n){if(!v[i]){this(i);}}
	}
	_ add(ll j, ll i){
		d[j] = d[i]+1;
		p[j] = i;
	}
};
#define searcher public gsearch {using gsearch::operator(), gsearch::gsearch; void operator()(ll s)
struct dfs: searcher {
	v[s] = true;
	for($ j: g[s]){
		if(v[j]){continue;}
		add(j, s);
		this(j);
	}
	q.push_front(s);
}
};
struct bfs: searcher {
	q.pb(s);
	for(ll idx = 0; idx < q.size(); ++idx){
		_ i = q[idx];
		if(v[i]){continue;}
		v[i]=true;
		for($ j: g[i]){
			q.pb(j);
			add(j, i);
		}
	}
}
};
_ trans($ g){
	ll n = size(g);
	vc<vl> h(n);
	fo(i,n){
		for(ll j:g[i]){
			h[j].pb(i);
		}
	}
	return h;
}
_ fix($ func){
	return [=](_... args) {return func(fix(func), args...);};
}
_ scc($ g){
	_ h = trans(g);
	dbg(h);
	vl cm(size(g), -1);
	_ assign = fix([&]($ assign, ll u, ll c) -> void {
			dbg(u);
			if(cm[u]!=-1){return;}
			cm[u] = c;
			for(ll v: h[u]){
				assign(v,c);
			}
		});
	dfs s{g};
	s();
	dbg(s.q);
	for(ll i:s.q){
		assign(i, i);
	}
	return cm;
}
_ bipartite($ g){
	bfs b{g};
	b();
	_ n = size(g);
	vl s(n);
	for(_ i:b.q){
		if(_ x = b.p[i]; x!=-1){s[i] = !s[x];}
	}
	bool bi = true;
	fo(i,n){
		for(_ j:g[i]){
			bi &= s[i] != s[j];
		}
	}
	return bi?optional{s}:nullopt;
}
_ max_match($ g){
	_ s = bipartite(g).value();
	ll n = g.size();
	vl m(n,-1);
	for(ll md = -1; md != inf;){
		vl v(n);
		vc<vl> h(n);
		fo(i,n){
			for(ll j:g[i]){
				if((j == m[i]) == s[i]){
					h[i].pb(j);
				}
			}
		}
		bfs b{h};
		b();
		md = inf;
		fo(i,n){
			if(s[i]==1 && m[i] == -1){
				md = min(md, b.d[i]);
			}
		}
		dbg(md);
		dbg(b.d);
		dbg(m);
		dbg(s);
		auto path = fix([&]($ path, ll i) -> bool{
			dbg(i);
			if(v[i]){return false;}
			v[i] = true;
			if(s[i] == 1 && m[i] == -1 && b.d[i] == md){return true;}
			for(ll j: g[i]){
				if(b.d[j] = b.d[i]+1){
					if(dbg(path(j))){
						dbg(j);
						if(s[i] == 0){
							m[i] = j;
							m[j] = i;
						}
						return true;
					}
				}
			}
			return false;
		});
		fo(i,n){
			if(s[i]==0 && m[i] == -1){
				path(i);
			}
		}
	}
	return m;
}
ll co sz = 30;
tm() struct no {
	vector<no*> p;
	T v;
	no(T co& v_, no* pa = nullptr): p(sz), v(v_){
		if(!pa){pa = &this;}
		fo(i,sz){
			p[i] = pa;
			pa = pa->p[i];
		}
	}
	_ gt(ll h){
		bt b(h);
		_ x = &this;
		fo(i,sz){
			if(b[i]){
				x = x->p[i];
			}
		}
		return x;
	}
	operator bool(){
		return p[0] != &this;
	}
	_ dp(){
		bt b;
		_ x = this;
		for($ i:rev(ra{sz})){
			if(*x.p[i]){
				x = *x.p[i];
				b[i] = 1;
			}
		}
		return ll(b.to_ullong())+1;
	}
};
tm() _ lca(no<T>* a, no<T>* b){
	ll da = a->dp(), db = b->dp();
	if(da > db){swap(a,b);}
	b = b->gt(db-da);
	if(a == b){return a;}
	for($ i:rev(ra{sz})){
		if(a->p[i] != b->p[i]){
			a = a->p[i];
			b = b->p[i];
		}
	}
	dbg(a->v); dbg(b->v);
	assert(a->p[0] == b->p[0]);
	return a->p[0];
}
vl prefix(string co& s){
	ll n = s.size();
	vl p(n);	
	fo(i,1,n){
		for(ll j = p[i-1]; ; j = p[j-1]){
			if(s[j] == s[i]){p[i] = j+1;break;}
			if(!j){break;}
		}
	}
	dbg(p);
	return p;
}
_ search_all(string co& t, string co& s){
	_ p = prefix(s+'\0'+t);
	vl v;
	fo(i,t.size()){
		if(p[s.size()+1+i] == s.size()){
			v.pb(i);
		}
	}
	return v;
}
string empstr = "";
struct search_it: it_base<ll> {
	using iterator_category = input_iterator_tag;
	string co& t, s;
	const ll n, ed;
	vl p;
	ll i=0, o=0;
	search_it(string co& t_, string co& s_): t(t_), s(s_), n(s.size()), ed(n+1+t.size()), p(n) {++this;}
	explicit search_it():search_it(empstr, empstr){}
	_ operator*(){
		assert(n);
		return i-(n+1);
	}
	void operator++(){
		for(++i;i < ed;++i){
			_ cur = i <= n?s.c_str()[i]:t[*this];
		 	for(ll j = o; ; j = p[j-1]){
				if(s[j] == cur){o = j+1; break;}
				if(!j){o = 0;break;}
			}
			if(i<n){
				p[i] = o;
			}
			dbg(i);dbg(o);
			if(o == n){
				break;
			}
		}
	}
};
_ operator==(search_it co& a, search_it co& b){
	bool sa = a.n, sb = b.n;
	if(sa ^ sb){return a.i == b.i;}
	if(sa){return a.i == a.ed;}
	if(sb){return b.ed == b.i;}
}
_ operator<(search_it co& a, search_it co& b){
	bool sa = a.n, sb = b.n;
	if(sa ^ sb){return a.i < b.i;}
	if(sa){return a.i < a.ed;}
	if(sb){return b.ed < b.i;}
}
_ search_ra($... args){
	return range{search_it(args...), search_it()};
}
_ prev_less($ v){
	ll n = v.size();
	vl l(n,-1);
	stack<ll> s;
	fo(i,n){
		while(s.size() && !(s.top() < v[i])){
			s.pop();
		}
		if(s.size()){
			l[i] = s.top();
		}
		s.push(v[i]);
	}
	return l;
}
#define CO_SWITCH
#ifdef CO_SWITCH
#define cobegin static lli pos = 0; switch(pos){case 0:
#define coend throw out_of_range("Coroutine reached end.");}
#define coreturn(x) pos=__LINE__; return x; case __LINE__:;
#endif
#ifdef CO_JMP
#define cobegin static bool first = true; static jmp_buf env; if(!first){longjmp(env, true);} first = false;
#define coreturn if(!setjmp(env)) return 
#define coend throw out_of_range("Coroutine reached end.");
#endif
ll coro(ll a){
	cobegin
	coreturn(404);
	for(static ll i=0;i<a;i++){
		coreturn(i*i);
	}
	coreturn(-1);
	coend
}
_ dot(pt co& a, pt co& b){
	return real(conj(a)*b);
}
_ wedge(pt co& a, pt co& b){
	return imag(conj(a)*b);
}
_ area(_ a, _ b, _ c){
	return wedge(b-a, c-a);
}
_ ccw(pt a, pt b, pt c){
	ll w = area(a,b,c);
	if(!(a == b || a == c || b == c || w)){
		throw invalid_argument{"Points are collinear."};
	}
	return w > 0;
}
_ hull(_& v, df(do_sort, true)){
	if(do_sort){
		_ p = *min_element(al(v), map_args([](pt a){return tuple{imag(a), real(a)};}));
		sort(al(v), bind(ccw, p, _1, _2));
	}
	vc<pt> h;
	for(_ x:v){
		while(h.size()>=2 && !ccw(h[h.size()-2], h.back(), x)){
			h.pop_back();
		}
		h.push_back(x);
	}
	return h;
}
template<typename T = less<>>
_ uniq(_& v, $ up, T co& sp = T{}){
	sort(al(v), sp);
	v.resize(unique(al(v), up)-begin(v));
	return v;
}

_ convex_min($ r, $ f){
	return *partition_point(al(r), [&](_ i){return !(f(i) < f(i+1));});
}
struct cht {
	vc<pt> h;
	cht(_& v){
		uniq(v, map_args(lambda(imag), equal_to{}),map_args(lambda(conj)));
		h = dbg(hull(v, false));
	}
	_ min($ x){
		_ co eval = [&]($ i){return real(h[i])*x+imag(h[i]);};
		return eval(convex_min(ra{size(h)-1}, eval));
	}
};
using ull = unsigned long long ;
struct hash_str {
	static _ constexpr lcg_mod = (1ULL<<62)-57;
	const char* st;
	vc<md> h, p;
	explicit hash_str($ s): st(s.data()), h(s.size()+1), p(s.size()) {
		with _w{lcg_mod};
		md g = 1;
		fo(i,0,s.size()){
			g*=md{0x51a3e995948c0deULL};
			//dbg(A);
			//dbg(B);
			//dbg(lli((int128(A.x)*int128(B.x))%int128(M)));
			h[i+1] = md{s[i]}*g;
		}
		//dbg(h);
		partial_sum(al(h), begin(h));		
		_ co inv = md{1}/md{0x51a3e995948c0deULL};
		md x = 1;
		fo(i,0,p.size()){
			p[i] = x;
			x*=md{inv};
		}
	}
	size_t operator()(string_view co& v){
		with _w{lcg_mod};
		ll l = v.data()-st;
		//dbg(l);
		//dbg(v.size());
		//dbg(md{10}-md{100});
		//dbg(h[l+v.size()]-h[l]);
		//dbg(p[l]);
		return ll((h[l+v.size()]-h[l]) * p[l]);
	}
};
void main2();
#if 0
string s = __FILE__;
ifstream input{s.substr(0,s.size()-string{"cpp"}.size())+"in"};
_& in = input?input:cin;
#else
_& in = cin;
#endif
int main(int argc, char *argv[]){
	#ifdef LOCAL
	debug_mode = true;
	#endif
	fo(i,argc){
		if(argv[i] == "-q"s){
			debug_mode = false;
		}
	}
	ios::sync_with_stdio(false);
	if(!debug_mode){cerr.rdbuf(nullptr);}
	for(ios& os: initializer_list<reference_wrapper<ios>>{in, cout, cerr, clog}){
		fixed(os);
		if(os.rdbuf()){os.exceptions(ios::failbit | ios::badbit | ios::eofbit);}
		os.precision(false?numeric_limits<ld>::max_digits10:5);
	}
	cout.precision(numeric_limits<ld>::max_digits10);
	{
	timer _t;
	ll t = 1;
	if(false){in>>t;}
	fo(i,t){
		main2();
	}
	}
}
_ print($ arg1, $... args){
	cout<<arg1;
	(void)((cout<<" "<<args),...);
	cout<<endl;
}
tm() using uset = unordered_set<T>;
tm() _ operator|(uset<T> co& a, uset<T> co& b){
	$ [sm, bg] = minmax(a, b);
	_ ret = bg;
	ret.insert(al(sm));
	return ret;
};
tm() _ operator&(uset<T> co& a, uset<T> co& b){
	$ [sm, bg] = minmax(a, b);
	uset<T> ret;
	for($ x: sm){
		if(bg.count(x)){
			ret.insert(x);
		}
	}
	return ret;
}
tm() _ sub_set(uset<T> co& a, uset<T> co& b, uset<T>& ret){
	for($ x: a){
		if(!b.count(x)){
			ret.insert(x);
		}
	}
	return ret;
}
tm() _ operator-(uset<T> co& a, uset<T> co& b){	
	uset<T> ret;
	return sub_set(a,b,ret);
}
tm() _ operator^(uset<T> co& a, uset<T> co& b){
	uset<T> ret = a-b;
	sub_set(b, a, ret);
	return ret;
}
_ add_edge(vc<vl>& g, ll u, ll v){
	g[u].pb(v);
	g[v].pb(u);
}
_ graph_in(vc<vl>& g, ll m){
	fo(i,0,m){
		I(u);I(v);
		add_edge(g, --u, --v);
	}
}
_ ceil_div(ll x, ll y){
	return (x+y-1)/y;
}
void egcd($ a, $ b, _& x, _& y){a?egcd(b%a, a, y, x),x-=b/a*y:(x=0,y=1);}
template<typename T, typename V = null_type>
using omap = tree<T, V, less<>, rb_tree_tag, tree_order_statistics_node_update>;
_ operator+(_ it, enable_if_t<!is_same<typename iterator_traits<tp(it)>::iterator_category, random_access_iterator_tag>::value, size_t> n){
	advance(it, n);
	return it;
}