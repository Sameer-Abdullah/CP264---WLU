/**
 * -------------------------------------
 * @project a6
 * @file queue.h
 * @author Sameer Abdullah
 * @version 2025-02-25
 * ---------------- ---------------------
 */

#ifndef QUEUE_H
#define QUEUE_H
#include "common.h"

typedef struct queue {
	int length;
	NODE *front;
	NODE *rear;
} QUEUE;

void enqueue(QUEUE *qp, NODE *np);
NODE* dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);

#endif
