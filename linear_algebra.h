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
	mat(const initializer_list<initializer_list<ll>>& vals): mat(size(vals), size(begin(vals)[0])){
		fo(i,r){
			assert(size(begin(vals)[i]) == c);
			fo(j,c){
				this[i][j] = begin(begin(vals)[i])[j];
			}
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
		fo(j,a.c){
			fo(k,c.c){
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
template<typename T>
_ lin_recur(vc<T> co& c, ll n){
	mat<T> m{size(c), size(c)};
	copy(al(c), m[0]);
	fo(i,1,size(c)){
		m[i][i-1] = 1;
	}
	return power(m,n)[0][0];
}