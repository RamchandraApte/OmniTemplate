template<typename Key, typename Data>
struct treap {
	treap *l{}, *r{}; // left and right nodes
	ll pri; // random heap priority
	Key key; // binary search tree key
	Data data;
	treap(Key co& key_): pri{reng()}, key{key_} {
		update_data(&this);
	}
};
template<typename Key, template<typename> typename Data_Temp>
using treap_t = treap<Key, Data_Temp<Key>>;
template<typename Key>
struct size_data {
	ll size{};
};
template<typename Key>
size_data<Key> operator+(size_data<Key> co& l, size_data<Key> co& r){
	// Returns the data for a node given the data for the children.
	return size_data<Key>{l.size+r.size+1};
}
template<typename Key>
ostream& operator<<(ostream& os, size_data<Key> co& data){
	return os<<"size = "<<data.size<<endl;
}
template<typename Key, typename Data>
Data get_data(treap<Key, Data>* trp){
	return trp?trp->data:Data{};
}
void update_data(_* trp){
	if(!trp){return;}
	trp->data = get_data(trp->l)+get_data(trp->r);
}
void split(_* trp, _ co& key, _*& l, _*& r){
	// Splits the treap by key
	if(!trp){l=r=nullptr;}
	else if(key < trp->key){
		split(trp->l, key, l, trp->l);
		r = trp;
	}
	else {
		split(trp->r, key, trp->r, r);
		l = trp;
	}
	update_data(trp);
}
template<typename Trp>
[[nodiscard]] Trp* join(Trp* l, Trp* r){
	// All the keys in l are less than the keys in r
	_ ret = [&](){
		if(!l){return r;}
		else if(!r){return l;}
		else if(l->pri < r->pri){
			r->l = join(l, r->l);
			return r;
		}
		else {
			l->r = join(l->r, r);
			return l;
		}
	}();
	update_data(ret);
	return ret;
}
template<typename Trp>
void insert(Trp*& trp, Trp* x){
	if(!trp){trp=x;}
	else if (trp->pri < x->pri){
		split(trp, x->key, x->l, x->r), trp = x;
	}
	else{
		insert(x->key<trp->key ?trp->l :trp->r, x);
	}
	update_data(trp);
}
template<typename Trp>
_ insert(Trp*& trp, _ co& key){
	return insert(trp, new Trp{key});
}
void erase(_*& trp, const _& key){
	if(trp->key == key){
		trp = join(trp->l, trp->r);
	}
	else {
		erase(key < trp->key ?trp->l :trp->r, key);
	}
	update_data(trp);
}
// Implicit treaps
void split_imp(_* trp, ll pos, _*& l, _*& r, ll sum = 0){
	// Splits the treap by key
	if(!trp){l=r=nullptr;}
	ll cur = sum + get_data(trp->l).size;
	if(pos <= sum){
		split(trp->l, pos, l, trp->l, sum);
		r = trp;
	}
	else {
		split(trp->r, pos, trp->r, r, cur+1);
		l = trp;
	}
	update_data(trp);
}
template<typename Trp>
void insert_imp(Trp*& trp, Trp* x, ll pos){
	if(!trp){trp=x;}
	else if (trp->pri < x->pri){
		split(trp, pos, x->l, x->r), trp = x;
	}
	else{
		insert(x->key<trp->key ?trp->l :trp->r, x);
	}
	update_data(trp);
}
template<typename Trp>
_ insert_imp(Trp*& trp, _ co& key, ll pos){
	return insert_imp(trp, new Trp{key}, pos);
}
template<typename T, typename... Ts>
T& operator<<(T& os, treap<Ts...>* trp){
	static ll lvl = -1;
	with _w{lvl+1, lvl};
	string tab(lvl, ' ');
	if(trp){
	os<<tab<<"key = "<<trp->key<<" "<<"priority = "<<trp->pri<<" "<<trp->data<<endl;
	os<<tab<<"Left"<<endl<<trp->l<<tab<<"Right"<<endl<<trp->r;
	}
	else{
		os<<tab<<"null"<<endl;
	}
	return os;	
}