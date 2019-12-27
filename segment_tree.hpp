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
tm() struct lazy_ptr {
	mutable T* ptr;
	_ operator->() co{
		if(!ptr){
			ptr = new T{};
		}
		return ptr;
	}
	lazy_ptr(): ptr{nullptr} {}
	_& operator*() co{
		return *(this.operator->());
	}
	operator bool() co{
		return ptr;
	}
};
tm() struct pers_ptr {
	mutable T* ptr;
	_ operator->() co {
		if(ptr){
			dbg("creatin");
			ptr = new T{*ptr};
		}
		else {
			dbg("null");
			ptr = new T{};
		}
		return ptr;
	}
	pers_ptr(): ptr{nullptr} {}
	_& operator*() co{
		return *(this.operator->());
	}
	operator bool() co{
		return ptr;
	}
};
_ up_inv($ s, $ i){
	s.v(i).a = s.op(s.v(gl(i)).a,s.v(gr(i)).a);
}
tm() struct no_v {
	T a,z;
	no_v(): a{}, z{} {};
};
template<typename T, template<typename> typename Ptr>
struct no_ptr_v {
	T v;
	Ptr<no_ptr_v> l_, r_;
	no_ptr_v(): v{}, l_{}, r_{} {}
	no_ptr_v(no_ptr_v co& oth): v{oth.v}, l_{}, r_{} {
		dbg("copying,,,");
		l_.ptr = oth.l_.ptr;
		r_.ptr = oth.r_.ptr;
	}
};
template<typename T>
using mypers = pers_ptr<no_ptr_v<T, pers_ptr>>;
template<typename T>
using mylazy = lazy_ptr<no_ptr_v<T, lazy_ptr>>;
_& gl($ ptr){
	return ptr->l_;
}
_& gr($ ptr){
	return ptr->r_;
}
tm() struct seg_base {
	_& v(T co& x) co{
		return x->v;
	}
	bool ok(T co& x) co{
		return true;
	}
	seg_base($ n, $ id){}
};
tm() struct no_impl {
	ll i;
	no_impl(ll i_ = 1): i(i_) {}
};
tm() no_impl<T> gl(no_impl<T> co& x) {return ll(x.i)<<ll(1);}
tm() no_impl<T> gr(no_impl<T> co& x) {return gl(x).i|ll(1);}
tm() struct seg_base<no_impl<T>> {
	mutable vc<T> v_;
	_& v(no_impl<T> x) co{
		return v_[x.i];
	}
	_ ok(no_impl<T> x) co{
		return x.i < v_.size();
	}
	seg_base($ n, $ id): v_(2*n){
		/*
		fo(i,n){
			v(n+i).a = d[i];
		}
		for(_ i:rev(ra{n})){
			up_inv(this, dbg(i));
		}*/
	}
};
ll identity(plus<ll>){
	return 0;
}
template<typename Op = plus<ll>, template<typename> typename No_T = mypers, typename T = tp(identity(Op{})), typename No = No_T<no_v<T>>>
struct seg2: seg_base<No> {
	Op op;
	T id;
	ll co n;
	No ro;
	vc<No> h;
	#define v this.v
	seg2(ll n_): seg_base<No>(nx2(n_), 0LL), n{nx2(n_)}, id{identity(op)}, ro{} {}
	co static _ def = -1LL;
	ll l, r;
	_ mid(ll nl, ll nr) co {
		return ll(nl+nr)>>ll(1);
	}
	_ dis(ll nl, ll nr) co {
		return r<=nl || nr<=l;
	}
	_ over(ll nl, ll nr) co {
		return l<=nl && nr<=r;
	}
	_ down(No co& i, bool d) co{
		v(i).a+=v(i).z;
		//for(_ x: initializer_list<reference_wrapper<No>>{gl(i), gr(i)}){
		#define do_lazy(x) if(d){v(x).a+=v(i).z;}
		do_lazy(gl(i));
		do_lazy(gr(i));
		v(i).z = 0;
	}
	#define sig No co& i, ll nl, ll nr
	T gt(sig) co {
		dbg(nl);dbg(nr);dbg(v(i).a);
		_ m = mid(nl, nr);
		down(i,nr-nl!=1);
		return dis(nl, nr)?id:over(nl, nr)?v(i).a:op(gt(gl(i), nl, m), gt(gr(i), m, nr));
	}
	_ gt(ll l_, ll r_){
		l = l_; r = r_;
		return gt(ro, 0, n);
	}
	_ gt(ll l){
		return gt(l, l+1);
	}
	_ up(T co& val, sig){
		//dbg(i.i);dbg(val);dbg(nl);dbg(nr);
		//cerr<<i.i<<" "<<val<<" "<<nl<<" "<<nr<<endl;
		_ m = mid(nl, nr);
		if(over(nl,nr)){
			dbg(nl);dbg(nr);
			v(i).z+=val;
		}
		down(i,nr-nl!=1);
		if(dis(nl,nr)||over(nl,nr)){
			return;
		}
		dbg("recursing...");
		up(val, gl(i), nl, m);
		up(val, gr(i), m, nr);
		up_inv(this, i);
		//cerr<<"exiting: "<<i.i<<endl;
	}
	_ up(_ val, ll l_, ll r_){
		l = l_; r = r_;
		h.pb(ro);
		up(val, ro, 0, n);
	}
	_ up(_ val, ll l){
		up(val, l, l+1);
	}
};
#undef v
struct mymax {
	_ operator()(ll x, ll y) co{
		return max(x,y);
	};
};
_ identity(mymax){
	return -inf;
}