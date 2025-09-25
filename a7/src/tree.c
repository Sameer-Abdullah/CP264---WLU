/**
 * -------------------------------------
 * @project a7
 * @file tree.c
 * @author Sameer Abdullah
 * @version 2025-03-07
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "tree.h"

TPROPS tree_property(TNODE *root) {
	TPROPS props = { 0, 0 };
	if (!root)
		return props;

	QUEUE queue = { 0 };
	enqueue(&queue, root);
	int height = 0, count = 0;

	while (queue.front) {
		int levelSize = 0;
		QUEUE tempQueue = { 0 };
		while (queue.front) {
			TNODE *node = dequeue(&queue);
			count++;
			if (node->left)
				enqueue(&tempQueue, node->left);
			if (node->right)
				enqueue(&tempQueue, node->right);
		}
		queue = tempQueue;
		height++;
	}
	props.order = count;
	props.height = height;
	return props;
}

void preorder(TNODE *root) {
	if (root) {
		printf("%c ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(TNODE *root) {
	if (root) {
		inorder(root->left);
		printf("%c ", root->data);
		inorder(root->right);
	}
}

void postorder(TNODE *root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%c ", root->data);
	}
}

void bforder(TNODE *root) {
	if (!root)
		return;
	QUEUE queue = { 0 };
	enqueue(&queue, root);
	while (queue.front) {
		TNODE *node = dequeue(&queue);
		printf("%c ", node->data);
		if (node->left)
			enqueue(&queue, node->left);
		if (node->right)
			enqueue(&queue, node->right);
	}
}

TNODE* bfs(TNODE *root, char val) {
	if (!root)
		return NULL;
	QUEUE queue = { 0 };
	enqueue(&queue, root);
	while (queue.front) {
		TNODE *node = dequeue(&queue);
		if (node->data == val)
			return node;
		if (node->left)
			enqueue(&queue, node->left);
		if (node->right)
			enqueue(&queue, node->right);
	}
	return NULL;
}

TNODE* dfs(TNODE *root, char val) {
	if (!root)
		return NULL;
	STACK stack = { 0 };
	push(&stack, root);
	while (stack.top) {
		TNODE *node = pop(&stack);
		if (node->data == val)
			return node;
		if (node->right)
			push(&stack, node->right);
		if (node->left)
			push(&stack, node->left);
	}
	return NULL;
}

// the following functions are given, need to add to your program.

TNODE* tree_node(char val) {
	TNODE *np = (TNODE*) malloc(sizeof(TNODE));
	if (np != NULL) {
		np->data = val;
		np->left = NULL;
		np->right = NULL;
	}
	return np;
}

void clean_tree(TNODE **rootp) {
	TNODE *p = *rootp;
	if (p) {
		if (p->left)
			clean_tree(&p->left);
		if (p->right)
			clean_tree(&p->right);
		free(p);
	}
	*rootp = NULL;
}

void insert_tree(TNODE **rootp, char val) {
	if (*rootp == NULL) {
		*rootp = tree_node(val);
	} else {
		QUEUE queue = { 0 };
		TNODE *p;
		enqueue(&queue, *rootp);
		while (queue.front) {
			p = dequeue(&queue);
			if (p->left == NULL) {
				p->left = tree_node(val);
				break;
			} else {
				enqueue(&queue, p->left);
			}

			if (p->right == NULL) {
				p->right = tree_node(val);
				break;
			} else {
				enqueue(&queue, p->right);
			}
		}
	}
}

