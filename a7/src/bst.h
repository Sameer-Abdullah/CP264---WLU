/**
 * -------------------------------------
 * @project a7
 * @file bst.h
 * @author Sameer Abdullah
 * @version 2025-03-07
 * -------------------------------------
 */
#ifndef BST_H
#define BST_H

typedef struct record {
	char name[20];
	float score;
} RECORD;

typedef struct bstnode BSTNODE;

struct bstnode {
	RECORD data;
	BSTNODE *left;
	BSTNODE *right;
};

BSTNODE* bst_node(RECORD data);

BSTNODE* bst_search(BSTNODE *root, char *key);

void bst_insert(BSTNODE **rootp, RECORD data);

void bst_delete(BSTNODE **rootp, char *key);

void bst_clean(BSTNODE **rootp);

BSTNODE* extract_smallest_node(BSTNODE **rootp);

#endif
