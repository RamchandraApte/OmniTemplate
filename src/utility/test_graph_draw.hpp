#pragma once
#include "graph_draw.hpp"
namespace graph_draw::test {
void test_graph_draw() {
	GraphAdj graph(6);
	graph.add_edge(1, 2);
	graph.add_edge(0, 3);
	graph.add_edge(4, 5);
	graph.add_edge(0, 5);
	const auto dot = graph_to_dot(graph, false);
	cout << dot << endl;
	show_dot(dot);
}
} // namespace graph_draw::test
using namespace graph_draw::test;
