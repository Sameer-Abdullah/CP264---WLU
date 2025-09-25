/**
 * -------------------------------------
 * @project a10
 * @file graph.c
 * @author Sameer Abdullah
 * @version 2025-04-01
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_stack.h"
#include "graph.h"

GRAPH* new_graph(int order) {
	GRAPH *gp = malloc(sizeof(GRAPH));
	gp->nodes = malloc(order * sizeof(GNODE*));

	int i;
	for (i = 0; i < order; i++) {
		gp->nodes[i] = malloc(sizeof(GNODE));
		gp->nodes[i]->nid = i;
		strcpy(gp->nodes[i]->name, "null");
		gp->nodes[i]->neighbor = NULL;
	}

	gp->order = order;
	gp->size = 0;

	return gp;
}

void insert_edge_graph(GRAPH *g, int from, int to, int weight) {
	ADJNODE *new_node = malloc(sizeof(ADJNODE));
	new_node->nid = to;
	new_node->weight = weight;
	new_node->next = g->nodes[from]->neighbor;
	g->nodes[from]->neighbor = new_node;
	g->size++;
}

void delete_edge_graph(GRAPH *g, int from, int to) {
	ADJNODE *current = g->nodes[from]->neighbor;
	ADJNODE *prev = NULL;
	while (current != NULL) {
		if (current->nid == to) {
			if (prev == NULL) { // First neighbor
				g->nodes[from]->neighbor = current->next;
			} else {
				prev->next = current->next;
			}
			free(current);
			g->size--;
			return;
		}
		prev = current;
		current = current->next;
	}
}

int get_edge_weight(GRAPH *g, int from, int to) {
	ADJNODE *current = g->nodes[from]->neighbor;
	while (current != NULL) {
		if (current->nid == to) {
			return current->weight;
		}
		current = current->next;
	}
	return INFINITY;
}

void traverse_bforder(GRAPH *g, int nid) {
	int visited[g->order];
	for (int i = 0; i < g->order; i++) {
		visited[i] = 0;
	}
	QUEUE q = { NULL, NULL };
	enqueue(&q, &g->nodes[nid]);
	visited[nid] = 1;
	printf("BFS Order: ");
	while (q.front != NULL) {
		GNODE *current = dequeue(&q);
		printf("%d ", current->nid);
		ADJNODE *adj = current->neighbor;
		while (adj != NULL) {
			if (!visited[adj->nid]) {
				enqueue(&q, g->nodes[adj->nid]);
				visited[adj->nid] = 1;
			}
			adj = adj->next;
		}
	}
	printf("\n");
	clean_queue(&q);
}

// Use auxiliary stack data structure for the algorithm
void traverse_dforder(GRAPH *g, int nid) {
	int visited[g->order];
	for (int i = 0; i < g->order; i++) {
		visited[i] = 0;
	}
	STACK s = { NULL };
	push(&s, &g->nodes[nid]);
	printf("DFS Order: ");
	while (s.top != NULL) {
		GNODE *current = pop(&s);
		if (!visited[current->nid]) {
			printf("%d ", current->nid);
			visited[current->nid] = 1;
			ADJNODE *adj = current->neighbor;
			while (adj != NULL) {
				if (!visited[adj->nid]) {
					push(&s, g->nodes[adj->nid]);
				}
				adj = adj->next;
			}
		}
	}
	printf("\n");
	clean_stack(&s);
}

void clean_graph(GRAPH **gp) {
	int i;
	GRAPH *g = *gp;
	ADJNODE *temp, *ptr;
	for (i = 0; i < g->order; i++) {
		ptr = g->nodes[i]->neighbor;
		while (ptr != NULL) {
			temp = ptr;
			ptr = ptr->next;
			free(temp);
		}
		free(g->nodes[i]);
	}
	free(g->nodes);
	free(g);
	*gp = NULL;
}

void display_graph(GRAPH *g) {
	if (g) {
		printf("order %d ", g->order);
		printf("size %d ", g->size);
		printf("(from to weight) ");
		int i;
		ADJNODE *ptr;
		for (i = 0; i < g->order; i++) {
			//printf("\n%d:", g->nodes[i]->nid);
			ptr = g->nodes[i]->neighbor;
			while (ptr != NULL) {
				printf("(%d %d %d) ", i, ptr->nid, ptr->weight);
				ptr = ptr->next;
			}
		}
	}
}

