namespace std {
_ operator<(pt co& a, pt co& b){
	return map_args([](_ x){return tuple{real(x), imag(x)};})(a,b);
}
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