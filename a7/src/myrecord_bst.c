/**
 * -------------------------------------
 * @project a7
 * @file myrecord_bst.c
 * @author Sameer Abdullah
 * @version 2025-03-07
 * -------------------------------------
 */
#include <stdio.h>
#include <math.h>
#include "bst.h"
#include "myrecord_bst.h"

void add_record(BSTDS *ds, RECORD record) {
	float old_mean = ds->mean;
	float old_stddev = ds->stddev;

	bst_insert(&(ds->root), record);
	ds->count++;

	ds->mean = ((old_mean * (ds->count - 1)) + record.score) / ds->count;

	if (ds->count > 1) {
		ds->stddev = sqrt(
				((old_stddev * old_stddev * (ds->count - 1))
						+ (record.score - ds->mean) * (record.score - old_mean))
						/ ds->count);
	} else {
		ds->stddev = 0;
	}
}

void remove_record(BSTDS *ds, char *name) {
	BSTNODE *target = bst_search(ds->root, name);
	if (target) {
		float old_mean = ds->mean;
		float old_stddev = ds->stddev;
		float removed_score = target->data.score;

		bst_delete(&(ds->root), name);
		ds->count--;

		if (ds->count > 0) {
			ds->mean = ((old_mean * (ds->count + 1)) - removed_score)
					/ ds->count;
			ds->stddev = sqrt(
					((old_stddev * old_stddev * (ds->count + 1))
							- (removed_score - ds->mean)
									* (removed_score - old_mean)) / ds->count);
		} else {
			ds->mean = 0;
			ds->stddev = 0;
		}
	}
}

void bstds_clean(BSTDS *ds) {
	bst_clean(&ds->root);
	ds->count = 0;
	ds->mean = 0;
	ds->stddev = 0;
}

