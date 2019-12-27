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
tm() int_it<T> operator +(int_it<T> co& a, int_it<T> co& b){return a.x + b.x;}
tm() int_it<T> operator -(int_it<T> co& a){return -a.x;}
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