#pragma once
#include "graph_draw.hpp"
namespace graph_draw::test {
void test_graph_draw() {
	GraphAdj graph(6);
	add_edge(graph, 1, 2);
	add_edge(graph, 0, 3);
	add_edge(graph, 4, 5);
	add_edge(graph, 0, 5);
	const auto dot = graph_to_dot(graph, false);
	cout << dot << endl;
	show_dot(dot);
}
} // namespace graph_draw::test
using namespace graph_draw::test;
