#pragma once
#include "core/all.hpp"
#include "graph/all.hpp"
inline namespace graph_draw {
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
} // namespace graph_draw
