/**
 * -------------------------------------
 * @project a10
 * @file main.c
 * @author Sameer Abdullah
 * @version 2025-04-01
 * -------------------------------------
 */

#include <stdio.h>
#include "edgelist.h"
#include "graph.h"
#include "algorithm.h"

void test_edgelist() {
	printf("\n===== Testing EdgeList =====\n");
	EDGELIST *elist = new_edgelist();

	insert_edge_end(elist, 0, 1, 10);
	insert_edge_end(elist, 1, 2, 20);
	insert_edge_start(elist, 2, 3, 30);

	display_edgelist(elist);
	printf("\nTotal weight: %d\n", weight_edgelist(elist));

	delete_edge(elist, 1, 2);
	printf("\nAfter deleting edge (1, 2):\n");
	display_edgelist(elist);

	clean_edgelist(&elist);
	if (elist == NULL)
		printf("\nEdgelist cleaned successfully.\n");
}

void test_graph() {
	printf("\n===== Testing Adjacency List Graph =====\n");
	GRAPH *graph = new_graph(5);

	insert_edge_graph(graph, 0, 1, 4);
	insert_edge_graph(graph, 0, 2, 2);
	insert_edge_graph(graph, 1, 2, 5);
	insert_edge_graph(graph, 1, 3, 10);
	insert_edge_graph(graph, 2, 4, 3);
	insert_edge_graph(graph, 4, 3, 4);
	insert_edge_graph(graph, 3, 4, 11);

	display_graph(graph);

	printf("\nBFS traversal from node 0:\n");
	traverse_bforder(graph, 0);

	printf("\nDFS traversal from node 0:\n");
	traverse_dforder(graph, 0);

	printf("\nWeight of edge (0, 2): %d\n", get_edge_weight(graph, 0, 2));
	printf("Deleting edge (1, 3)...\n");
	delete_edge_graph(graph, 1, 3);
	display_graph(graph);

	clean_graph(&graph);
	if (graph == NULL)
		printf("\nGraph cleaned successfully.\n");
}

void test_algorithms() {
	printf("\n===== Testing Graph Algorithms =====\n");
	GRAPH *graph = new_graph(5);

	insert_edge_graph(graph, 0, 1, 4);
	insert_edge_graph(graph, 0, 2, 2);
	insert_edge_graph(graph, 1, 2, 5);
	insert_edge_graph(graph, 1, 3, 10);
	insert_edge_graph(graph, 2, 4, 3);
	insert_edge_graph(graph, 4, 3, 4);
	insert_edge_graph(graph, 3, 4, 11);

	printf("\nOriginal Graph:\n");
	display_graph(graph);

	printf("\n--- PRIM's MST starting from node 0 ---\n");
	EDGELIST *mst = mst_prim(graph, 0);
	display_edgelist(mst);
	printf("\nTotal weight of MST: %d\n", weight_edgelist(mst));
	clean_edgelist(&mst);

	printf("\n--- Dijkstra's Shortest Path Tree from node 0 ---\n");
	EDGELIST *spt = spt_dijkstra(graph, 0);
	display_edgelist(spt);
	clean_edgelist(&spt);

	printf("\n--- Dijkstra's Single Source Shortest Path from 0 to 3 ---\n");
	EDGELIST *path = sp_dijkstra(graph, 0, 3);
	if (path) {
		display_edgelist(path);
		printf("\nTotal weight of path: %d\n", weight_edgelist(path));
		clean_edgelist(&path);
	} else {
		printf("No path found.\n");
	}

	clean_graph(&graph);
}

int main() {
	test_edgelist();
	test_graph();
	test_algorithms();
	return 0;
}
