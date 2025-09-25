/**
 * -------------------------------------
 * @project a7
 * @file tree.h
 * @author Sameer Abdullah
 * @version 2025-03-07
 * -------------------------------------
 */

#ifndef TREE_H
#define TREE_H

typedef struct tnode {
	char data;
	struct tnode *left;
	struct tnode *right;
} TNODE;

typedef struct tree_props {
	int order;
	int height;
} TPROPS;

TPROPS tree_property(TNODE *root);

void preorder(TNODE *root);

void inorder(TNODE *root);

void postorder(TNODE *root);

void bforder(TNODE *root);

TNODE* bfs(TNODE *root, char key);

TNODE* dfs(TNODE *root, char key);

TNODE* tree_node(char val);
void clean_tree(TNODE **rootp);
void insert_tree(TNODE **rootp, char val);

#endif
