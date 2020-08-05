#pragma once
#include "queue.hpp"
namespace queue_tools::test {
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
} // namespace queue_tools::test
using namespace queue_tools::test;
