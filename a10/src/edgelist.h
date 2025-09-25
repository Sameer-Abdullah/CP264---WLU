/**
 * -------------------------------------
 * @project a10
 * @file edgelist.h
 * @author Sameer Abdullah
 * @version 2025-04-01
 * -------------------------------------
 */

#ifndef EDGELIST_H
#define EDGELIST_H

typedef struct edgenode {
	int from;
	int to;
	int weight;
	struct edgenode *next;
} EDGENODE;

typedef struct edgelist {
	int size;
	EDGENODE *start;
	EDGENODE *end;
} EDGELIST;

EDGELIST* new_edgelist();

void insert_edge_start(EDGELIST *g, int from, int to, int weight);

void insert_edge_end(EDGELIST *g, int from, int to, int weight);

void delete_edge(EDGELIST *g, int from, int to);

int weight_edgelist(EDGELIST *g);

void clean_edgelist(EDGELIST **gp);

void display_edgelist(EDGELIST *g);

#endif
