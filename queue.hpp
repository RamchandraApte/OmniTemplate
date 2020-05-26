#pragma once
#include "core.hpp"
/* Queue adaptor, creates a queue using two Stacks left, right
 * If there are at least two elements, left and right are not empty.
 * If there is one element, it is in left.
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
    return const_cast<reference>(
        const_cast<const QueueAdaptor &>(this).front());
  }
  const_reference back() const { return (right.empty() ? left : right).top(); }
  reference back() {
    return const_cast<reference>(const_cast<const QueueAdaptor &>(this).back());
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
    if (size() >= 2) {
      assert(!left.empty() && !right.empty());
    } else if (size() == 1) {
      assert(!left.empty());
      assert(front() == back());
    } else {
      assert(empty());
    }
  }
};
void test_queueadaptor() {
  QueueAdaptor<stack<ll>> q;
  q.push(4);
  q.push(5);
  q.pop();
  q.push(6);
  q.push(7);
  q.push(8);
  assert(q.size() == 4);
  assert(!q.empty());
  assert(q.front() == 5);
  dbg(q.back());
  assert(q.back() == 8);
  q.pop();
  q.pop();
  assert(q.front() == 7);
  assert(q.back() == 8);
  q.pop();
  assert(q.front() == 8);
  assert(q.back() == 8);
  q.pop();
  assert(q.size() == 0 && q.empty());
  q.push(4);
  assert(q.front() == 4);
  assert(q.back() == 4);
}
template <typename T, typename Base = stack<pair<T, T>>>
class MinStack : public Base {
public:
  using container_type = T;
  using value_type = T;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  void push(const T &val) { Base::push({val, ::min(val, min())}); }
  const T &top() const { return Base::top().first; }
  T min() const { return Base::empty() ? inf : Base::top().second; }
};
void test_minstack() {
  MinStack<ll> ms;
  ms.push(2);
  ms.push(5);
  assert(ms.min() == 2);
  ms.pop();
  ms.push(1);
  assert(ms.min() == 1);
  ms.pop();
  assert(ms.min() == 2);
}
template <typename T> class MinQueue : public QueueAdaptor<MinStack<T>> {
public:
  T min() { return ::min(this.get_left().min(), this.get_right().min()); }
};
void test_minqueue() {
  MinQueue<ll> mq;
  assert(mq.min() == inf);
  mq.push(3);
  mq.push(5);
  assert(mq.min() == 3);
  mq.pop();
  assert(mq.min() == 5);
  mq.push(4);
  assert(mq.min() == 4);
  mq.pop();
  assert(mq.min() == 4);
  mq.pop();
  assert(mq.min() == inf);
}
void test_queue() {
  test_minstack();
  test_queueadaptor();
  test_minqueue();
}