#pragma once
#include "core/all.hpp"
inline namespace queue_tools {
/**
 * @brief Queue adaptor, creates a queue using two Stacks left, right
 * If there are at least two elements, left and right are not empty.
 * If there is one element, it is in left.
 *
 */
template <typename Stack> class QueueAdaptor {
      public:
	using container_type = Stack;
	using value_type = typename Stack::value_type;
	using size_type = typename Stack::size_type;
	using reference = typename Stack::reference;
	using const_reference = typename Stack::const_reference;
	const_reference front() const { return (left.empty() ? right : left).top(); }
	reference front() {
		return const_cast<reference>(const_cast<const QueueAdaptor &>(*this).front());
	}
	const_reference back() const { return (right.empty() ? left : right).top(); }
	reference back() {
		return const_cast<reference>(const_cast<const QueueAdaptor &>(*this).back());
	}
	bool empty() const { return left.empty() && right.empty(); }
	size_type size() const { return left.size() + right.size(); }
	void push(const value_type &val) {
		(empty() ? left : right).push(val);
		check_invariant();
	}
	void pop() {
		left.pop();
		if (left.empty() && !right.empty()) {
			const auto last = right.top();
			bool b = size() > 1;
			if (b) {
				right.pop();
			}
			for (; !right.empty(); right.pop()) {
				left.push(right.top());
			}
			if (b) {
				right.push(last);
			}
		}
		check_invariant();
	}

      protected:
	const auto &get_left() { return left; }
	const auto &get_right() { return right; }

      private:
	Stack left, right;
	void check_invariant() const {
		if constexpr (false) {
			if (size() >= 2) {
				assert(!left.empty() && !right.empty());
			} else if (size() == 1) {
				assert(!left.empty());
				assert(front() == back());
			} else {
				assert(empty());
			}
		}
	}
};
template <typename T, typename Base = stack<pair<T, T>>> class MinStack : public Base {
      public:
	using container_type = T;
	using value_type = T;
	using size_type = ll;
	using reference = value_type &;
	using const_reference = const value_type &;
	void push(const T &val) { Base::push({val, std::min(val, min())}); }
	/*! Return the top of the stack*/
	const T &top() const { return Base::top().first; }
	/*! Return the minimum element of the stack */
	T min() const { return Base::empty() ? inf : Base::top().second; }
};
template <typename T> class MinQueue : public QueueAdaptor<MinStack<T>> {
      public:
	T min() { return std::min(this->get_left().min(), this->get_right().min()); }
};
} // namespace queue_tools
