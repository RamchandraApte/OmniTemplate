#pragma once
#include "core/all.hpp"
#include "graph/all.hpp"
string graph_to_dot(const GraphAdj &graph, bool undirected = true) {
	ostringstream os;
	os << (undirected ? "graph" : "digraph");
	os << " G {" << endl;
	fo(u, graph.size()) {
		for (const auto v : graph[u]) {
			if (!undirected || u <= v) {
				os << "\t" << u << (undirected ? " -- " : " -> ") << v << endl;
			}
		}
	}
	os << "}";
	return os.str();
}
void show_dot(const string &dot) {
	ofstream("graph.dot") << dot;
	system("dot -Tpng graph.dot -o graph.png && xdg-open graph.png");
}
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
