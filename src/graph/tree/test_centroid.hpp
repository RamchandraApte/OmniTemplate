#pragma once
#include "centroid.hpp"
void test_centroid_decomp() {
	{
		GraphAdj graph(7);
		fo(i, graph.size() - 1) { graph.add_edge(i, i + 1); }
		assert((centroid_decomp(graph) ==
			vector<vector<ll>>{
			    {3, 1, 0}, {3, 1}, {3, 1, 2}, {3}, {3, 5, 4}, {3, 5}, {3, 5, 6}}));
	}
	{
		GraphAdj graph(1);
		assert((centroid_decomp(graph) == vector<vector<ll>>{{0}}));
	}
}
