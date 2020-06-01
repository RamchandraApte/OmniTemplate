#pragma once
#include "core.hpp"
template <auto op, lli id_ = identity(op)> struct seg {
	using T = decltype(identity(op));
	static constexpr T id = id_;
	ll const n; /*!< Number of nodes of teh segment tree. Does not need to
		       be a power of two.*/
	mutable vector<T> a, z;
	template <typename Cont>
	seg(const Cont &v)
	    : n(next_pow_of_2(v.size())), a(2 * n, id), z(2 * n) {
		copy(al(v), begin(a) + n);
		for (auto i : rev(ra{n})) {
			dbg(i);
			a[i] = op(a[2 * i], a[2 * i + 1]);
		}
	}
	const static auto def = -1LL;
	auto fix(ll l, ll &r, ll nl, ll &nr) const {
		if (r == def) {
			r = l + 1;
		}
		if (nr == def) {
			nr = n;
		}
		return make_tuple((nl + nr) / 2, r <= nl || nr <= l,
				  l <= nl && nr <= r);
	}
	auto down(ll i) const {
		a[i] += z[i];
		if (i < n) {
			fo(j, 2) { z[2 * i + j] += z[i]; }
		}
		z[i] = 0;
	}
#define sig ll l, df(r, def), df(i, 1LL), df(nl, 0LL), df(nr, def)
	T gt(sig) const {
		const auto &[m, dis, over] = fix(l, r, nl, nr);
		down(i);
		return dis ? id
			   : over ? a[i]
				  : op(gt(l, r, 2 * i, nl, m),
				       gt(l, r, 2 * i + 1, m, nr));
	}
	auto up(T v, sig) {
		const auto &[m, dis, over] = fix(l, r, nl, nr);
		if (dis || over) {
			if (over) {
				z[i] += v;
			}
			down(i);
			return;
		}
		up(v, l, r, 2 * i, nl, m);
		up(v, l, r, 2 * i + 1, m, nr);
		a[i] = op(a[2 * i], a[2 * i + 1]);
	}
};
template <typename Stream, auto... args>
auto &operator<<(Stream &os, seg<args...> const &sg) {
	os << "seg{vl{";
	fo(i, sg.n) {
		if (i) {
			os << delim;
		}
		os << sg.gt(i);
	}
	return os << "}}";
}
tm() struct lazy_ptr {
	mutable T *ptr;
	auto operator->() const {
		if (!ptr) {
			ptr = new T{};
		}
		return ptr;
	}
	lazy_ptr() : ptr{nullptr} {}
	auto &operator*() const { return *(this.operator->()); }
	operator bool() const { return ptr; }
};
tm() struct pers_ptr {
	mutable T *ptr;
	auto operator->() const {
		if (ptr) {
			dbg("creatin");
			ptr = new T{*ptr};
		} else {
			dbg("null");
			ptr = new T{};
		}
		return ptr;
	}
	pers_ptr() : ptr{nullptr} {}
	auto &operator*() const { return *(this.operator->()); }
	operator bool() const { return ptr; }
};
template <typename T1, typename T2> auto up_inv(const T1 &s, const T2 &i) {
	s.v(i).a = s.op(s.v(gl(i)).a, s.v(gr(i)).a);
}
tm() struct no_v {
	T a, z;
	no_v() : a{}, z{} {};
};
template <typename T, template <typename> typename Ptr> struct no_ptr_v {
	T v;
	Ptr<no_ptr_v> l_, r_;
	no_ptr_v() : v{}, l_{}, r_{} {}
	no_ptr_v(no_ptr_v const &oth) : v{oth.v}, l_{}, r_{} {
		dbg("copying,,,");
		l_.ptr = oth.l_.ptr;
		r_.ptr = oth.r_.ptr;
	}
};
template <typename T> using mypers = pers_ptr<no_ptr_v<T, pers_ptr>>;
template <typename T> using mylazy = lazy_ptr<no_ptr_v<T, lazy_ptr>>;
template <typename T> auto &gl(const T &ptr) { return ptr->l_; }
template <typename T> auto &gr(const T &ptr) { return ptr->r_; }
tm() struct seg_base {
	auto &v(T const &x) const { return x->v; }
	bool ok(T const &x) const { return true; }
	seg_base(const ll &n, const T &id) {}
};
tm() struct no_impl {
	ll i;
	no_impl(ll i_ = 1) : i(i_) {}
};
tm() no_impl<T> gl(no_impl<T> const &x) { return ll(x.i) << ll(1); }
tm() no_impl<T> gr(no_impl<T> const &x) { return gl(x).i | ll(1); }
tm() struct seg_base<no_impl<T>> {
	mutable vector<T> v_;
	auto &v(no_impl<T> x) const { return v_[x.i]; }
	auto ok(no_impl<T> x) const { return x.i < v_.size(); }
	seg_base(const ll n, const T &id) : v_(2 * n) {
		/*
		fo(i,n){
			v(n+i).a = d[i];
		}
		for(auto i:rev(ra{n})){
			up_inv(this, dbg(i));
		}*/
	}
};
ll identity(plus<ll>) { return 0; }
template <typename Op = plus<ll>, template <typename> typename No_T = mypers,
	  typename T = decltype(identity(Op{})), typename No = No_T<no_v<T>>>
struct seg2 : seg_base<No> {
	Op op;
	T id;
	ll const n;
	No ro;
	vector<No> h;
#define v this.v
	seg2(ll n_)
	    : seg_base<No>(next_pow_of_2(n_), 0LL), n{next_pow_of_2(n_)},
	      id{identity(op)}, ro{} {}
	const static auto def = -1LL;
	ll l, r;
	auto mid(ll nl, ll nr) const { return ll(nl + nr) >> ll(1); }
	auto dis(ll nl, ll nr) const { return r <= nl || nr <= l; }
	auto over(ll nl, ll nr) const { return l <= nl && nr <= r; }
	auto down(No const &i, bool d) const {
		v(i).a += v(i).z;
// for(auto x: initializer_list<reference_wrapper<No>>{gl(i), gr(i)}){
#define do_lazy(x)                                                             \
	if (d) {                                                               \
		v(x).a += v(i).z;                                              \
	}
		do_lazy(gl(i));
		do_lazy(gr(i));
		v(i).z = 0;
	}
#define sig No const &i, ll nl, ll nr
	T gt(sig) const {
		dbg(nl);
		dbg(nr);
		dbg(v(i).a);
		auto m = mid(nl, nr);
		down(i, nr - nl != 1);
		return dis(nl, nr)
			   ? id
			   : over(nl, nr)
				 ? v(i).a
				 : op(gt(gl(i), nl, m), gt(gr(i), m, nr));
	}
	auto gt(ll l_, ll r_) {
		l = l_;
		r = r_;
		return gt(ro, 0, n);
	}
	auto gt(ll l) { return gt(l, l + 1); }
	auto up(T const &val, sig) {
		// dbg(i.i);dbg(val);dbg(nl);dbg(nr);
		// cerr<<i.i<<" "<<val<<" "<<nl<<" "<<nr<<endl;
		auto m = mid(nl, nr);
		if (over(nl, nr)) {
			dbg(nl);
			dbg(nr);
			v(i).z += val;
		}
		down(i, nr - nl != 1);
		if (dis(nl, nr) || over(nl, nr)) {
			return;
		}
		dbg("recursing...");
		up(val, gl(i), nl, m);
		up(val, gr(i), m, nr);
		up_inv(this, i);
		// cerr<<"exiting: "<<i.i<<endl;
	}
	auto up(const T &val, ll l_, ll r_) {
		l = l_;
		r = r_;
		h.push_back(ro);
		up(val, ro, 0, n);
	}
	auto up(T val, ll l) { up(val, l, l + 1); }
};
#undef v
struct mymax {
	auto operator()(ll x, ll y) const { return max(x, y); };
};
auto identity(mymax) { return -inf; }
