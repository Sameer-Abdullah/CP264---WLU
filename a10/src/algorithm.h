/**
 * -------------------------------------
 * @project a10
 * @file algorithm.h
 * @author Sameer Abdullah
 * @version 2025-04-01
 * -------------------------------------
 */
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "edgelist.h"
#include "graph.h"

EDGELIST* mst_prim(GRAPH *g, int start);
EDGELIST* spt_dijkstra(GRAPH *g, int start);
EDGELIST* sp_dijkstra(GRAPH *g, int start, int end);

#endif
