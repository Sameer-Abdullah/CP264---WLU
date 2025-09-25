/**
 * -------------------------------------
 * @file  bst_linked.c
 * Linked BST Source Code File
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@
 * @author Sameer Abdullah, 169065039, abdu5039@mylaurier.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "bst_linked.h"

// Macro for comparing node heights
#define MAX_HEIGHT(a,b) ((a) > (b) ? a : b)

//--------------------------------------------------------------------
// Local Functions

/**
 * Initializes a new BST node with a copy of item.
 *
 * @param source pointer to a BST source
 * @param item pointer to the item to assign to the node
 * @return a pointer to a new BST node
 */
static bst_node* bst_node_initialize(const data_ptr item) {
	// Base case: add a new node containing a copy of item.
	bst_node *node = malloc(sizeof *node);
	node->item = malloc(sizeof *node->item);
	data_copy(node->item, item);
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/**
 * Helper function to determine the height of node - handles empty node.
 * @param node The node to process.
 * @return The height of the current node.
 */
static int bst_node_height(const bst_node *node) {
	int height = 0;

	if (node != NULL) {
		height = node->height;
	}
	return height;
}

/**
 * Updates the height of a node. Its height is the max of the heights of its
 * child nodes, plus 1.
 * @param node The node to process.
 */
static void bst_update_height(bst_node *node) {
	int left_height = bst_node_height(node->left);
	int right_height = bst_node_height(node->right);

	node->height = MAX_HEIGHT(left_height, right_height) + 1;
	return;
}

/**
 * Inserts item into a BST. Insertion must preserve the BST definition.
 * item may appear only once in source.
 *
 * @param source - pointer to a BST
 * @param node - pointer to a node
 * @param item - the item to insert
 * @return - true if item inserted, false otherwise
 */
static bool bst_insert_aux(bst_linked *source, bst_node **node,
		const data_ptr item) {
	bool inserted = false;

	if (*node == NULL) {
		// Base case: add a new node containing the item.
		*node = bst_node_initialize(item);
		source->count += 1;
		inserted = true;
	} else {
		// Compare the node data_ptr against the new item.
		int comp = data_compare(item, (*node)->item);

		if (comp < 0) {
			// General case: check the left subsource.
			inserted = bst_insert_aux(source, &(*node)->left, item);
		} else if (comp > 0) {
			// General case: check the right subsource.
			inserted = bst_insert_aux(source, &(*node)->right, item);
		}
	}
	if (inserted) {
		// Update the node height if any of its children have been changed.
		bst_update_height(*node);
	}
	return inserted;
}

//--------------------------------------------------------------------
// Functions

// Initializes a BST.
bst_linked* bst_initialize() {
	bst_linked *source = malloc(sizeof *source);
	source->root = NULL;
	source->count = 0;
	return source;
}

// frees a BST.
void bst_free(bst_linked **source) {

	if (source == NULL || *source == NULL) { // BST is empty
		return;
	}

	bst_node *current = (*source)->root;
	bst_node *temp;

	while (current != NULL) {
		if (current->left != NULL) {
			temp = current->left;
			current->left = NULL;
			current = temp;
		} else if (current->right != NULL) {
			temp = current->right;
			current->right = NULL;
			current = temp;
		} else {
			data_free(&(current->item));
			temp = current;
			current = NULL;
			free(temp);
		}
	}
	free(*source);
	*source = NULL;

	return;
}

// Determines if a BST is empty.
bool bst_empty(const bst_linked *source) {

	if (source == NULL || source->root == NULL || source->count == 0) {
		return true;
	}
	return false;

}

// Determines if a BST is full.
bool bst_full(const bst_linked *source) {
	bst_node *temp = malloc(sizeof(bst_node));
	if (temp == NULL) {
		return true;  // System out of memory
	}
	free(temp);
	return false;
}

// Returns number of items in a BST.
int bst_count(const bst_linked *source) {

	if (source == NULL) {
		return 0;
	}

	return source->count;
}

// Copies the contents of a BST to an array in inorder.
void bst_inorder(const bst_linked *source, data_ptr *items) {

	if (source == NULL || source->root == NULL) {
		return;  // Empty tree, nothing to do
	}

	int index = 0;  // Keep track of position in the array
	bst_node *stack[100]; // Simulating recursion using a stack (assuming max 100 nodes)
	int top = -1;
	bst_node *current = source->root;

	while (current != NULL || top >= 0) {
		// Reach the leftmost node
		while (current != NULL) {
			stack[++top] = current;
			current = current->left;
		}

		// Pop from stack (process node)
		current = stack[top--];
		items[index++] = current->item;  // Store in array

		// Move to the right subtree
		current = current->right;
	}
}

// Copies the contents of a BST to an array in preorder.
void bst_preorder(const bst_linked *source, data_ptr *items) {

	if (source == NULL || source->root == NULL) {
		return;  // Empty tree, nothing to do
	}

	int index = 0;  // Keeps track of array position
	bst_node *stack[100];  // Simulating recursion (assuming max 100 nodes)
	int top = -1;
	bst_node *current = source->root;

	// Start by pushing the root onto the stack
	stack[++top] = current;

	while (top >= 0) {
		// Pop from stack
		current = stack[top--];

		// Process current node
		items[index++] = current->item;

		// Push right child first, so left child is processed first
		if (current->right != NULL) {
			stack[++top] = current->right;
		}
		if (current->left != NULL) {
			stack[++top] = current->left;
		}
	}
}

// Copies the contents of a BST to an array in postorder.
void bst_postorder(const bst_linked *source, data_ptr *items) {

	if (source == NULL || source->root == NULL) {
		return;  // Empty tree, nothing to do
	}

	int index = 0;
	bst_node *stack1[100], *stack2[100];  // Two stacks to store nodes
	int top1 = -1, top2 = -1;
	bst_node *current = source->root;

	// Push root onto stack1
	stack1[++top1] = current;

	// Process all nodes
	while (top1 >= 0) {
		current = stack1[top1--];
		stack2[++top2] = current;

		// Push left then right (right gets processed first)
		if (current->left != NULL) {
			stack1[++top1] = current->left;
		}
		if (current->right != NULL) {
			stack1[++top1] = current->right;
		}
	}

	// Store values in correct postorder from stack2
	while (top2 >= 0) {
		items[index++] = stack2[top2--]->item;
	}
}

// Inserts a copy of an item into a BST.
bool bst_insert(bst_linked *source, const data_ptr item) {
	return bst_insert_aux(source, &(source->root), item);
}

// Retrieves a copy of a value matching key in a BST.
bool bst_retrieve(bst_linked *source, const data_ptr key, data_ptr item) {

	if (source == NULL || source->root == NULL) {
		return false;  // BST is empty
	}

	bst_node *current = source->root;

	while (current != NULL) {
		int cmp = data_compare(key, current->item);

		if (cmp == 0) {
			data_copy(item, current->item);  // Copy data to item
			return true;
		} else if (cmp < 0) {
			current = current->left;  // Search left subtree
		} else {
			current = current->right;  // Search right subtree
		}
	}
	return false;  // Key not found
}

// Removes a value matching key in a BST.
bool bst_remove(bst_linked *source, const data_ptr key, data_ptr item) {

	if (source == NULL || source->root == NULL) {
		return false;  // Empty tree
	}

	bst_node *parent = NULL;
	bst_node *current = source->root;

	// Find the node
	while (current != NULL) {
		int cmp = data_compare(key, current->item);

		if (cmp == 0) {
			data_copy(item, current->item);  // Store the deleted value
			break;
		} else if (cmp < 0) {
			parent = current;
			current = current->left;
		} else {
			parent = current;
			current = current->right;
		}
	}

	if (current == NULL) {
		return false;  // Key not found
	}

	// Case 1: No children (leaf node)
	if (current->left == NULL && current->right == NULL) {
		if (parent == NULL) {
			source->root = NULL;
		} else if (parent->left == current) {
			parent->left = NULL;
		} else {
			parent->right = NULL;
		}
		free(current);
	}
	// Case 2: One child
	else if (current->left == NULL || current->right == NULL) {
		bst_node *child =
				(current->left != NULL) ? current->left : current->right;
		if (parent == NULL) {
			source->root = child;
		} else if (parent->left == current) {
			parent->left = child;
		} else {
			parent->right = child;
		}
		free(current);
	}
	// Case 3: Two children
	else {
		bst_node *successor = current->right;
		while (successor->left != NULL) {
			successor = successor->left;
		}
		data_copy(current->item, successor->item);
		bst_remove(source, successor->item, item);
	}

	source->count--;
	return true;
}

// Copies source to target.
void bst_copy(bst_linked **target, const bst_linked *source) {

	if (source == NULL || source->root == NULL) {
		*target = bst_initialize();  // Create an empty BST
		return;
	}

	// Initialize target BST
	*target = bst_initialize();

	// Stack for iterative copying (since no helper functions allowed)
	bst_node *stack[100];  // Assume max 100 nodes
	int top = -1;
	bst_node *current = source->root;

	// Start copying using an iterative preorder traversal
	while (current != NULL || top >= 0) {
		while (current != NULL) {
			// Copy data to new node
			data_ptr new_item = malloc(sizeof(int));
			data_copy(new_item, current->item);
			bst_insert(*target, new_item);  // Insert into target BST

			// Push current onto stack and go left
			stack[++top] = current;
			current = current->left;
		}

		// Pop from stack and visit right
		current = stack[top--];
		current = current->right;
	}
}

// Finds the maximum item in a BST.
bool bst_max(const bst_linked *source, data_ptr item) {

	if (source == NULL || source->root == NULL) {
		return false;
	}

	bst_node *current = source->root;
	while (current->right != NULL) {
		current = current->right;
	}

	data_copy(item, current->item);
	return true;
}

// Finds the minimum item in a BST.
bool bst_min(const bst_linked *source, data_ptr item) {

	if (source == NULL || source->root == NULL) {
		return false;
	}

	bst_node *current = source->root;
	while (current->left != NULL) {
		current = current->left;
	}

	data_copy(item, current->item);
	return true;
}

// Finds the number of leaf nodes in a tree.
int bst_leaf_count(const bst_linked *source) {

	if (source == NULL || source->root == NULL) {
		return 0;  // Empty tree, no leaves
	}

	int count = 0;
	bst_node *stack[100];  // Stack for traversal (max 100 nodes assumed)
	int top = -1;
	bst_node *current = source->root;

	stack[++top] = current;

	while (top >= 0) {
		current = stack[top--];

		// Leaf node condition (no left and right child)
		if (current->left == NULL && current->right == NULL) {
			count++;
		}

		// Push children to stack (right first so left is processed first)
		if (current->right != NULL) {
			stack[++top] = current->right;
		}
		if (current->left != NULL) {
			stack[++top] = current->left;
		}
	}

	return count;
}

// Finds the number of nodes with one child in a tree.
int bst_one_child_count(const bst_linked *source) {

	if (source == NULL || source->root == NULL)
		return 0;
	int count = 0;
	bst_node *stack[100];
	int top = -1;
	stack[++top] = source->root;
	while (top >= 0) {
		bst_node *node = stack[top--];
		if ((node->left == NULL && node->right != NULL)
				|| (node->left != NULL && node->right == NULL))
			count++;
		if (node->left != NULL)
			stack[++top] = node->left;
		if (node->right != NULL)
			stack[++top] = node->right;
	}
	return count;
}

// Finds the number of nodes with two children in a tree.
int bst_two_child_count(const bst_linked *source) {

	if (source == NULL || source->root == NULL)
		return 0;
	int count = 0;
	bst_node *stack[100];
	int top = -1;
	stack[++top] = source->root;
	while (top >= 0) {
		bst_node *node = stack[top--];
		if (node->left != NULL && node->right != NULL)
			count++;
		if (node->left != NULL)
			stack[++top] = node->left;
		if (node->right != NULL)
			stack[++top] = node->right;
	}
	return count;
}

// Determines the number of nodes with zero, one, and two children.
// (May not call bst_leaf_count, bst_one_child_count, or bst_two_child_count.)
void bst_node_counts(const bst_linked *source, int *zero, int *one, int *two) {

	if (zero == NULL || one == NULL || two == NULL)
		return;
	*zero = *one = *two = 0;
	if (source == NULL || source->root == NULL)
		return;
	bst_node *stack[100];
	int top = -1;
	stack[++top] = source->root;
	while (top >= 0) {
		bst_node *node = stack[top--];
		if (node->left == NULL && node->right == NULL)
			(*zero)++;
		else if ((node->left == NULL && node->right != NULL)
				|| (node->left != NULL && node->right == NULL))
			(*one)++;
		else if (node->left != NULL && node->right != NULL)
			(*two)++;
		if (node->left != NULL)
			stack[++top] = node->left;
		if (node->right != NULL)
			stack[++top] = node->right;
	}
}
// Determines whether or not a tree is a balanced tree.
bool bst_balanced(const bst_linked *source) {

	if (source == NULL || source->root == NULL) {
		return true;  // An empty tree is balanced
	}

	bst_node *stack[100];
	int top = -1;
	bst_node *current = source->root;

	stack[++top] = current;

	while (top >= 0) {
		current = stack[top--];

		int left_height = (current->left) ? current->left->height : 0;
		int right_height = (current->right) ? current->right->height : 0;

		if (abs(left_height - right_height) > 1) {
			return false;  // Not balanced
		}

		if (current->right != NULL) {
			stack[++top] = current->right;
		}
		if (current->left != NULL) {
			stack[++top] = current->left;
		}
	}

	return true;
}

// Determines whether or not a tree is a valid BST.
bool bst_valid(const bst_linked *source) {

	if (source == NULL || source->root == NULL) {
		return true;
	}

	bst_node *stack[100];
	int top = -1;
	bst_node *current = source->root;
	data_ptr prev = NULL;

	while (current != NULL || top >= 0) {
		while (current != NULL) {
			stack[++top] = current;
			current = current->left;
		}

		current = stack[top--];

		if (prev != NULL && data_compare(prev, current->item) >= 0) {
			return false;  // Not a valid BST
		}

		prev = current->item;
		current = current->right;
	}

	return true;
}

// Determines if two trees contain same data in same configuration.
bool bst_equals(const bst_linked *target, const bst_linked *source) {

	if (target == NULL && source == NULL) {
		return true;
	}

	// If one tree is NULL and the other is not, they are not equal.
	if (target == NULL || source == NULL) {
		return false;
	}

	// Start comparing from the root nodes.
	bst_node *stack1[100], *stack2[100];  // Two stacks for iterative traversal
	int top1 = -1, top2 = -1;
	bst_node *current1 = target->root;
	bst_node *current2 = source->root;

	while ((current1 != NULL || top1 >= 0) && (current2 != NULL || top2 >= 0)) {
		// Traverse left subtree for both trees.
		while (current1 != NULL && current2 != NULL) {
			stack1[++top1] = current1;
			stack2[++top2] = current2;
			current1 = current1->left;
			current2 = current2->left;
		}

		// If one tree reaches NULL before the other, they are not identical.
		if (current1 != NULL || current2 != NULL) {
			return false;
		}

		// Pop from stack to process nodes.
		current1 = stack1[top1--];
		current2 = stack2[top2--];

		// Compare node values.
		if (data_compare(current1->item, current2->item) != 0) {
			return false;
		}

		// Traverse right subtree for both trees.
		current1 = current1->right;
		current2 = current2->right;
	}

	// If both stacks are empty at the same time, trees are equal.
	return (current1 == NULL && current2 == NULL);
}

/**
 * Private helper function to print contents of BS in preorder.
 *
 * @param to_string - function to print data_ptr
 * @param node - pointer to bst_node
 */
static void bst_print_aux(bst_node *node) {
	char string[DATA_STRING_SIZE];

	if (node != NULL) {
		data_string(string, DATA_STRING_SIZE, node->item);
		printf("%s\n", string);
		bst_print_aux(node->left);
		bst_print_aux(node->right);
	}
	return;
}

// Prints the items in a BST in preorder.
void bst_print(const bst_linked *source) {
	printf("  count: %d, height: %d, items:\n", source->count,
			source->root->height);
	bst_print_aux(source->root);
	printf("\n");
	return;
}
