/**
 * -------------------------------------
 * @project a6
 * @file stack.c
 * @author Sameer Abdullah
 * @version 2025-02-25
 * -------------------------------------
 */
#include <stdio.h>
#include "stack.h"

void push(STACK *sp, NODE *np) {
	np->next = sp->top;
	sp->top = np;
	sp->length++;
}

NODE* pop(STACK *sp) {
	if (sp->top == NULL) {
		return NULL;
	}
	NODE *removedNode = sp->top;
	sp->top = sp->top->next;
	removedNode->next = NULL;
	sp->length--;

	return removedNode;
}

void clean_stack(STACK *sp) {
	clean(&(sp->top));
	sp->top = NULL;
	sp->length = 0;
}
