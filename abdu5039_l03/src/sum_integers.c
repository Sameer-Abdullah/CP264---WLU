/**
 * -------------------------------------
 * @file  sum_integers.c
 * Lab 3 Source Code File
 * -------------------------------------
 * @author Sameer Abdullah, 169065039, abdu5039@mylaurier.ca
 *
 * @version 2025-01-26
 *
 * -------------------------------------
 */
#include "functions.h"

int sum_integers(void) {

	int sum = 0;
	int number;
	char input[100];

	printf("Enter integers, one per line:\n");

	while (fgets(input, sizeof(input), stdin)) {
		if (sscanf(input, "%d", &number) == 1) {
			sum += number;
		} else {
			break;
		}
	}

	return sum;

}
