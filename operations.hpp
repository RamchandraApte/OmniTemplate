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
tm() using uset = unordered_set<T>;
um operator+(um a, um const& b){
	for($ p:b){
		a[p.first]+=p.second;
	}
	return a;
}
tm() _ operator|(uset<T> const& a, uset<T> const& b){
	$ [sm, bg] = minmax(a, b);
	_ ret = bg;
	ret.insert(al(sm));
	return ret;
};
tm() _ operator&(uset<T> const& a, uset<T> const& b){
	$ [sm, bg] = minmax(a, b);
	uset<T> ret;
	for($ x: sm){
		if(bg.count(x)){
			ret.insert(x);
		}
	}
	return ret;
}
tm() _ sub_set(uset<T> const& a, uset<T> const& b, uset<T>& ret){
	for($ x: a){
		if(!b.count(x)){
			ret.insert(x);
		}
	}
	return ret;
}
tm() _ operator-(uset<T> const& a, uset<T> const& b){	
	uset<T> ret;
	return sub_set(a,b,ret);
}
tm() _ operator^(uset<T> const& a, uset<T> const& b){
	uset<T> ret = a-b;
	sub_set(b, a, ret);
	return ret;
}
tm() _ operator*(vc<T> a, vc<T> b){
	assert(a.size() == b.size());
	vc<T> c(a.size());
	fo(i,a.size()){
		c[i] = a[i]*b[i];
	}
	return c;
}
_ operator+(_ it, enable_if_t<!is_same<typename iterator_traits<tp(it)>::iterator_category, random_access_iterator_tag>::value, size_t> n){
	advance(it, n);
	return it;
}