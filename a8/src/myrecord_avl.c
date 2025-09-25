/**
 * -------------------------------------
 * @project a7
 * @file myrecord_avl.c
 * @author Sameer Abdullah
 * @version 2025-03-14
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "avl.h"
#include "myrecord_avl.h"

void avl_merge(AVLNODE **dest_rootp, AVLNODE **source_rootp) {
	if (*source_rootp == NULL)
		return;

	RECORD temp = (*source_rootp)->data;

	avl_merge(dest_rootp, &(*source_rootp)->left);
	avl_merge(dest_rootp, &(*source_rootp)->right);

	avl_delete(source_rootp, temp.name);

	avl_insert(dest_rootp, temp);
}

void avlds_merge(AVLDS *dest, AVLDS *source) {
	if (source->count == 0)
		return;

	int new_count = dest->count + source->count;

	float new_mean = ((dest->mean * dest->count)
			+ (source->mean * source->count)) / new_count;

	float new_variance = (((dest->stddev * dest->stddev
			+ dest->mean * dest->mean) * dest->count
			+ (source->stddev * source->stddev + source->mean * source->mean)
					* source->count) / new_count) - (new_mean * new_mean);

	dest->mean = new_mean;
	dest->stddev = sqrt(new_variance > 0 ? new_variance : 0);
	dest->count = new_count;

	avl_merge(&dest->root, &source->root);

	avlds_clean(source);
}

void avlds_clean(AVLDS *ds) {
	avl_clean(&ds->root);
	ds->count = 0;
	ds->mean = 0;
	ds->stddev = 0;
}

void add_record(AVLDS *tree, RECORD data) {
	if (avl_search(tree->root, data.name) == NULL) {
		avl_insert(&(tree->root), data);
		int count = tree->count;
		float mean = tree->mean;
		float stddev = tree->stddev;
		tree->count = count + 1;
		tree->mean = (mean * count + data.score) / (count + 1.0);
		tree->stddev = sqrt(
				data.score * data.score / (count + 1.0)
						+ (stddev * stddev + mean * mean)
								* (count / (count + 1.0))
						- tree->mean * tree->mean);
	} else {
		printf("record exits");
	}
}

void remove_record(AVLDS *tree, char *name) {
	AVLNODE *np = NULL;
	if ((np = avl_search(tree->root, name)) != NULL) {
		float score = np->data.score;
		avl_delete(&(tree->root), name);
		float count = tree->count;
		float mean = tree->mean;
		float stddev = tree->stddev;
		tree->count = count - 1;
		if (count >= 3) {
			tree->mean = (mean * count - score) / (count - 1.0);
			tree->stddev = sqrt(
					(stddev * stddev + mean * mean) * (count / (count - 1.0))
							- score * score / (count - 1.0)
							- tree->mean * tree->mean);
		} else if (count == 2) {
			tree->mean = mean * count - score;
			tree->stddev = 0;
		} else {
			tree->mean = 0;
			tree->stddev = 0;
		}
	} else {
		printf("record does not exit");
	}
}
