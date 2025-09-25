/**
 * -------------------------------------
 * @project
 * @file main.c
 * @author Sameer Abdullah
 * @version 2025-03-14
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "set_avl.h"
#include "myrecord_avl.h"

int main() {
	AVLDS avldsA = { NULL, 0, 0.0, 0.0 };
	AVLDS avldsB = { NULL, 0, 0.0, 0.0 };

	RECORD rec;

	// Add test records to avldsA
	for (int i = 1; i <= 10; i++) {
		sprintf(rec.name, "A%02d", i);
		rec.score = i * 10.0;
		add_record(&avldsA, rec);
	}

	// Add test records to avldsB
	for (int i = 1; i <= 10; i++) {
		sprintf(rec.name, "B%02d", i);
		rec.score = i * 10.0;
		add_record(&avldsB, rec);
	}

	printf("Before merging:\n");
	printf("avldsA count: %d, mean: %.2f, stddev: %.2f\n", avldsA.count,
			avldsA.mean, avldsA.stddev);
	printf("avldsB count: %d, mean: %.2f, stddev: %.2f\n", avldsB.count,
			avldsB.mean, avldsB.stddev);

	avlds_merge(&avldsA, &avldsB);

	printf("After merging:\n");
	printf("avldsA count: %d, mean: %.2f, stddev: %.2f\n", avldsA.count,
			avldsA.mean, avldsA.stddev);
	printf("avldsB count: %d, mean: %.2f, stddev: %.2f\n", avldsB.count,
			avldsB.mean, avldsB.stddev);

	return 0;
}
