/**
 * -------------------------------------
 * @project a6
 * @file queue.c
 * @author Sameer Abdullah
 * @version 2025-02-25
 * -------------------------------------
 */

#include <stdio.h>
#include "queue.h"

void enqueue(QUEUE *qp, NODE *np) {
	if (qp->rear == NULL) {
		qp->front = qp->rear = np;
	} else {
		qp->rear->next = np;
		qp->rear = np;
	}
	np->next = NULL;
	qp->length++;
}

NODE* dequeue(QUEUE *qp) {
	if (qp->front == NULL) {
		return NULL;
	}

	NODE *removedNode = qp->front;
	qp->front = qp->front->next;

	if (qp->front == NULL) {
		qp->rear = NULL;
	}

	removedNode->next = NULL;
	qp->length--;
	return removedNode;
}

void clean_queue(QUEUE *qp) {
	clean(&(qp->front));
	qp->front = NULL;
	qp->rear = NULL;
	qp->length = 0;
}

