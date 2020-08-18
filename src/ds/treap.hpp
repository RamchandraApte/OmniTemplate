#pragma once
#include "core/all.hpp"
template <typename Key, typename Data> struct treap {
	/*! Treap class */
	treap *l{}, *r{}; //!< left and right nodes
	ll pri{};	  //!< random heap priority
	Key key{};	  //!< binary search tree key
	Data data{};	  //!< Data for the node
	bool rev{};	  //!< Whether to reverse the subtree of the node
	treap(Key const &key_) : pri(reng()), key{key_} { update_data(&this); }
};
template <typename Key, template <typename> typename Data_Temp>
using treap_t = treap<Key, Data_Temp<Key>>;
template <typename Key> struct size_data { ll size{}; };
template <typename Key>
/*! Returns the data for a node given the data for the children.*/
size_data<Key> operator+(size_data<Key> const &l, size_data<Key> const &r) {
	return size_data<Key>{l.size + r.size + 1};
}
/*! Print size data*/
template <typename Stream, typename Key>
ostream &operator<<(Stream &os, size_data<Key> const &data) {
	return os << "size = " << data.size << endl;
}
/*! Get data associated with the treap node*/
template <typename Key, typename Data> Data get_data(treap<Key, Data> *trp) {
	return trp ? trp->data : Data{};
}
template <typename Trp> void update_data(Trp *trp) {
	if (!trp) {
		return;
	}
	trp->data = get_data(trp->l) + get_data(trp->r);
}
/*! Splits the treap by key*/
template <typename Key, typename Data, typename Trp = treap<Key, Data>>
void split(treap<Key, Data> *trp, const Key &key, Trp *&l, Trp *&r) {
	if (!trp) {
		l = r = nullptr;
	} else if (key < trp->key) {
		split(trp->l, key, l, trp->l);
		r = trp;
	} else {
		split(trp->r, key, trp->r, r);
		l = trp;
	}
	update_data(trp);
}
/**
 * @brief Joins treap l and treap r.
 * @pre All the keys in l must be less than the keys in r.
 * @tparam Trp A treap type.
 * @param l The left half
 * @param r The right half
 * @return Trp*: The union of l and r.
 */
template <typename Trp>[[nodiscard]] Trp *join(Trp *l, Trp *r) {
	down(l);
	down(r);
	auto ret = [&] {
		if (!l) {
			return r;
		} else if (!r) {
			return l;
		} else if (l->pri < r->pri) {
			r->l = join(l, r->l);
			return r;
		} else {
			l->r = join(l->r, r);
			return l;
		}
	}();
	update_data(ret);
	return ret;
}
/*! @brief inserts Node x into treap
 * \param x the new node to be inserted
 * \param trp the treap the node is inserted into
 */
template <typename Trp> void insert(Trp *&trp, Trp *x) {
	/*! Insert node x into treap trp */
	if (!trp) {
		trp = x;
	} else if (trp->pri < x->pri) {
		split(trp, x->key, x->l, x->r), trp = x;
	} else {
		insert(x->key < trp->key ? trp->l : trp->r, x);
	}
	update_data(trp);
}
/*! @brief insert a node with key \param key into \param trp*/
template <typename Key, typename Data, typename Trp = treap<Key, Data>>
auto insert(treap<Key, Data> *&trp, const Key &key) {
	/*! Insert key into treap trp*/
	return insert(trp, new Trp{key});
}
/*! @brief erase the node with key \param key from the treap \param trp*/
template <typename Key, typename Data, typename Trp = treap<Key, Data>>
void erase(treap<Key, Data> *&trp, const Key &key) {
	/*! Erase key from treap */
	if (trp->key == key) {
		trp = join(trp->l, trp->r);
	} else {
		erase(key < trp->key ? trp->l : trp->r, key);
	}
	update_data(trp);
}
// Implicit treaps
template <typename Trp> void down(Trp *trp) {
	/*! Push updates down one level of the treap */
	if (!(trp && trp->rev)) {
		return;
	}
	swap(trp->l, trp->r);
#define flip(x)                                                                                    \
	if (trp->x) {                                                                              \
		trp->x->rev ^= 1;                                                                  \
	}
	flip(l) flip(r)
#undef flip
	    trp->rev = 0;
}
template <typename Trp> void split_imp(Trp *trp, ll pos, Trp *&l, Trp *&r, ll sum = 0) {
	/*! Splits the treap by pos*/
	if (!trp) {
		l = r = nullptr;
		return;
	}
	down(trp);
	ll cur = sum + get_data(trp->l).size;
	if (pos <= cur) {
		split_imp(trp->l, pos, l, trp->l, sum);
		r = trp;
	} else {
		split_imp(trp->r, pos, trp->r, r, cur + 1);
		l = trp;
	}
	update_data(trp);
}
/*! Insert a node x at position \param pos*/
template <typename Trp> void insert_imp(Trp *&trp, Trp *x, ll pos) {
	Trp *l, *r;
	split_imp(trp, pos, l, r);
	l = join(l, x);
	trp = join(l, r);
}
/*! Erase the node at position \param pos*/
template <typename Trp> void erase_imp(Trp *&trp, ll pos) {
	Trp *l, *r, *x, *nr;
	split_imp(trp, pos, l, r);
	split_imp(r, 1, x, nr);
	trp = join(l, nr);
}
/*! Get the node at positions \param pos*/
template <typename Trp> auto get_imp(Trp *&trp, ll pos) {
	Trp *l, *r, *x, *nr;
	split_imp(trp, pos, l, r);
	split_imp(r, 1, x, nr);
	trp = join(join(l, x), nr);
	return x->key;
}
/*! Insert the node with \param key at position \param pos into \param trp*/
template <typename Key, typename Data, typename Trp = treap<Key, Data>>
auto insert_imp(treap<Key, Data> *&trp, Key const &key, ll pos) {
	return insert_imp(trp, new Trp{key}, pos);
}
/*! Debug print the treap*/
template <typename Stream, typename... Ts> auto &operator<<(Stream &os, treap<Ts...> *trp) {
	static ll lvl = -1;
	with _w{lvl + 1, lvl};
	string tab(lvl, ' ');
	if (trp) {
		os << tab << "key = " << trp->key << " "
		   << "priority = " << trp->pri << " " << trp->data << endl;
		os << tab << "Left" << endl << trp->l << tab << "Right" << endl << trp->r;
	} else {
		os << tab << "null" << endl;
	}
	return os;
}
/*! Insert the elements of trp in-order into \param out*/
template <typename Key, typename Data> void to_array(treap<Key, Data> *trp, vector<Key> &out) {
	if (!trp) {
		return;
	}
	to_array(trp->l, out);
	out.push_back(trp->key);
	to_array(trp->r, out);
}
template <typename Key, typename Data> vector<Key> to_array(treap<Key, Data> *trp) {
	/*! Returns the array of keys for an implicit treap.*/
	vector<Key> out;
	to_array(trp, out);
	return out;
}
