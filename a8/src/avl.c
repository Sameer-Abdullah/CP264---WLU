/**
 * -------------------------------------
 * @project a7
 * @file avl.c
 * @author Sameer Abdullah
 * @version 2025-03-14
 * -------------------------------------
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"

AVLNODE* avl_node(RECORD data) {
	AVLNODE *np = (AVLNODE*) malloc(sizeof(AVLNODE));
	if (np) {
		np->data = data;
		np->height = 1;
		np->left = NULL;
		np->right = NULL;
	}
	return np;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(AVLNODE *np) {
	return np ? np->height : 0;
}

int balance_factor(AVLNODE *np) {
	return np ? height(np->left) - height(np->right) : 0;
}

AVLNODE* rotate_left(AVLNODE *np) {
	AVLNODE *new_root = np->right;
	np->right = new_root->left;
	new_root->left = np;
	np->height = max(height(np->left), height(np->right)) + 1;
	new_root->height = max(height(new_root->left), height(new_root->right)) + 1;
	return new_root;
}

AVLNODE* rotate_right(AVLNODE *root) {
	AVLNODE *new_root = root->left;
	root->left = new_root->right;
	new_root->right = root;
	root->height = max(height(root->left), height(root->right)) + 1;
	new_root->height = max(height(new_root->left), height(new_root->right)) + 1;
	return new_root;
}

AVLNODE* extract_smallest_node(AVLNODE **rootp) {
	AVLNODE *p = *rootp, *parent = NULL;
	if (p) {
		while (p->left) {
			parent = p;
			p = p->left;
		}
		if (parent == NULL)
			*rootp = p->right;
		else
			parent->left = p->right;

		p->left = NULL;
		p->right = NULL;
	}
	return p;
}

void avl_insert(AVLNODE **rootp, RECORD data) {
	if (*rootp == NULL) {
		*rootp = avl_node(data);
		return;
	}

	if (strcmp(data.name, (*rootp)->data.name) < 0)
		avl_insert(&(*rootp)->left, data);
	else if (strcmp(data.name, (*rootp)->data.name) > 0)
		avl_insert(&(*rootp)->right, data);
	else
		return;

	(*rootp)->height = max(height((*rootp)->left), height((*rootp)->right)) + 1;
	int balance = balance_factor(*rootp);

	if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) < 0)
		*rootp = rotate_right(*rootp);
	else if (balance < -1 && strcmp(data.name, (*rootp)->right->data.name) > 0)
		*rootp = rotate_left(*rootp);
	else if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) > 0) {
		(*rootp)->left = rotate_left((*rootp)->left);
		*rootp = rotate_right(*rootp);
	} else if (balance < -1
			&& strcmp(data.name, (*rootp)->right->data.name) < 0) {
		(*rootp)->right = rotate_right((*rootp)->right);
		*rootp = rotate_left(*rootp);
	}
}

void avl_delete(AVLNODE **rootp, char *name) {
	if (*rootp == NULL)
		return;

	if (strcmp(name, (*rootp)->data.name) < 0)
		avl_delete(&(*rootp)->left, name);
	else if (strcmp(name, (*rootp)->data.name) > 0)
		avl_delete(&(*rootp)->right, name);
	else {
		AVLNODE *temp;
		if ((*rootp)->left == NULL || (*rootp)->right == NULL) {
			temp = (*rootp)->left ? (*rootp)->left : (*rootp)->right;
			if (temp == NULL) {
				temp = *rootp;
				*rootp = NULL;
			} else
				**rootp = *temp;
			free(temp);
		} else {
			AVLNODE *succParent = *rootp, *succ = (*rootp)->right;
			while (succ->left) {
				succParent = succ;
				succ = succ->left;
			}
			(*rootp)->data = succ->data;
			if (succParent->left == succ)
				succParent->left = succ->right;
			else
				succParent->right = succ->right;
			free(succ);
		}
	}
	if (*rootp == NULL)
		return;
	(*rootp)->height = max(height((*rootp)->left), height((*rootp)->right)) + 1;
	int balance = balance_factor(*rootp);
	if (balance > 1 && balance_factor((*rootp)->left) >= 0)
		*rootp = rotate_right(*rootp);
	else if (balance > 1 && balance_factor((*rootp)->left) < 0) {
		(*rootp)->left = rotate_left((*rootp)->left);
		*rootp = rotate_right(*rootp);
	} else if (balance < -1 && balance_factor((*rootp)->right) <= 0)
		*rootp = rotate_left(*rootp);
	else if (balance < -1 && balance_factor((*rootp)->right) > 0) {
		(*rootp)->right = rotate_right((*rootp)->right);
		*rootp = rotate_left(*rootp);
	}
}

AVLNODE* avl_search(AVLNODE *root, char *name) {
	if (!root || strcmp(root->data.name, name) == 0) {
		return root;
	}

	if (strcmp(name, root->data.name) < 0) {
		return avl_search(root->left, name);
	}
	return avl_search(root->right, name);
}

void avl_clean(AVLNODE **rootp) {
	AVLNODE *root = *rootp;
	if (root) {
		if (root->left)
			avl_clean(&root->left);
		if (root->right)
			avl_clean(&root->right);
		free(root);
	}
	*rootp = NULL;
}

