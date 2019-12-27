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