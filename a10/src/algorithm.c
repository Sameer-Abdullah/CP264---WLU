/**
 * -------------------------------------
 * @project a10
 * @file algorithm.c
 * @author Sameer Abdullah
 * @version 2025-04-01
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "algorithm.h"

EDGELIST* mst_prim(GRAPH *g, int start) {
	int visited[g->order];
	for (int i = 0; i < g->order; i++)
		visited[i] = 0;

	EDGELIST *mst = new_edgelist();
	HEAP *heap = new_heap(g->order);
	visited[start] = 1;

	ADJNODE *ptr = g->nodes[start]->neighbor;
	while (ptr) {
		HEAPDATA d = { ptr->weight, (start << 16) | ptr->nid };
		heap_insert(heap, d);
		ptr = ptr->next;
	}

	while (heap->size > 0) {
		HEAPDATA min = heap_extract_min(heap);
		int from = min.value >> 16;
		int to = min.value & 0xFFFF;
		if (visited[to])
			continue;
		insert_edge_end(mst, from, to, min.key);
		visited[to] = 1;

		ptr = g->nodes[to]->neighbor;
		while (ptr) {
			if (!visited[ptr->nid]) {
				HEAPDATA d = { ptr->weight, (to << 16) | ptr->nid };
				heap_insert(heap, d);
			}
			ptr = ptr->next;
		}
	}

	heap_clean(&heap);
	return mst;
}

EDGELIST* spt_dijkstra(GRAPH *g, int start) {
	int visited[g->order];
	int dist[g->order];
	int prev[g->order];

	for (int i = 0; i < g->order; i++) {
		visited[i] = 0;
		dist[i] = INFINITY;
		prev[i] = -1;
	}
	dist[start] = 0;

	HEAP *heap = new_heap(g->order);
	heap_insert(heap, (HEAPDATA ) { 0, start });

	while (heap->size > 0) {
		HEAPDATA min = heap_extract_min(heap);
		int u = min.value;
		if (visited[u])
			continue;
		visited[u] = 1;

		ADJNODE *ptr = g->nodes[u]->neighbor;
		while (ptr) {
			int v = ptr->nid;
			if (!visited[v] && dist[u] + ptr->weight < dist[v]) {
				dist[v] = dist[u] + ptr->weight;
				prev[v] = u;
				heap_insert(heap, (HEAPDATA ) { dist[v], v });
			}
			ptr = ptr->next;
		}
	}

	EDGELIST *spt = new_edgelist();
	for (int i = 0; i < g->order; i++) {
		if (i != start && prev[i] != -1) {
			insert_edge_end(spt, prev[i], i, dist[i] - dist[prev[i]]);
		}
	}

	heap_clean(&heap);
	return spt;
}

EDGELIST* sp_dijkstra(GRAPH *g, int start, int end) {
	int visited[g->order];
	int dist[g->order];
	int prev[g->order];

	for (int i = 0; i < g->order; i++) {
		visited[i] = 0;
		dist[i] = INFINITY;
		prev[i] = -1;
	}
	dist[start] = 0;

	HEAP *heap = new_heap(g->order);
	heap_insert(heap, (HEAPDATA ) { 0, start });

	while (heap->size > 0) {
		HEAPDATA min = heap_extract_min(heap);
		int u = min.value;
		if (visited[u])
			continue;
		visited[u] = 1;
		if (u == end)
			break;

		ADJNODE *ptr = g->nodes[u]->neighbor;
		while (ptr) {
			int v = ptr->nid;
			if (!visited[v] && dist[u] + ptr->weight < dist[v]) {
				dist[v] = dist[u] + ptr->weight;
				prev[v] = u;
				heap_insert(heap, (HEAPDATA ) { dist[v], v });
			}
			ptr = ptr->next;
		}
	}

	EDGELIST *path = new_edgelist();
	int current = end;
	while (prev[current] != -1) {
		insert_edge_start(path, prev[current], current,
				get_edge_weight(g, prev[current], current));
		current = prev[current];
	}

	if (current != start) { // No path
		clean_edgelist(&path);
		path = NULL;
	}

	heap_clean(&heap);
	return path;
}
