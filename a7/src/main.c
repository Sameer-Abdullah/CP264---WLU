/**
 * -------------------------------------
 * @project
 * @file
 * @author Sameer Abdullah
 * @version 2025-03-07
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "tree.h"
#include "bst.h"

void test_binary_tree() {
	TNODE *root = NULL;
	insert_tree(&root, 'A');
	insert_tree(&root, 'B');
	insert_tree(&root, 'C');
	insert_tree(&root, 'D');
	insert_tree(&root, 'E');
	insert_tree(&root, 'F');
	insert_tree(&root, 'G');

	printf("\nBinary Tree Test:\n");
	printf("Preorder traversal: ");
	preorder(root);
	printf("\n");

	printf("Inorder traversal: ");
	inorder(root);
	printf("\n");

	printf("Postorder traversal: ");
	postorder(root);
	printf("\n");

	printf("Breadth-first traversal: ");
	bforder(root);
	printf("\n");

	char searchKey = 'E';
	TNODE *bfsResult = bfs(root, searchKey);
	printf("BFS search result for %c: %s\n", searchKey,
			bfsResult ? "Found" : "Not Found");

	TNODE *dfsResult = dfs(root, searchKey);
	printf("DFS search result for %c: %s\n", searchKey,
			dfsResult ? "Found" : "Not Found");

	TPROPS props = tree_property(root);
	printf("Tree properties - Order: %d, Height: %d\n", props.order,
			props.height);

	clean_tree(&root);
}

void test_bst() {
	BSTNODE *bstRoot = NULL;
	RECORD records[] = { { "Alice", 85.5 }, { "Bob", 90.0 },
			{ "Charlie", 78.2 }, { "David", 92.3 }, { "Eve", 88.8 } };

	for (int i = 0; i < 5; i++) {
		bst_insert(&bstRoot, records[i]);
	}

	printf("\nBinary Search Tree Test:\n");

	char *searchKey = "Charlie";
	BSTNODE *searchResult = bst_search(bstRoot, searchKey);
	printf("BST search result for %s: %s\n", searchKey,
			searchResult ? "Found" : "Not Found");

	printf("Deleting Bob from BST...\n");
	bst_delete(&bstRoot, "Bob");

	searchResult = bst_search(bstRoot, "Bob");
	printf("BST search result for Bob: %s\n",
			searchResult ? "Found" : "Not Found");

	bst_clean(&bstRoot);
}

int main() {
	test_binary_tree();
	test_bst();
	return 0;
}
