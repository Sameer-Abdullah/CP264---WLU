/**
 * -------------------------------------
 * @file  int_array_read.c
 * Lab 3 Source Code File
 * -------------------------------------
 * @author Sameer Abdullah, 169065039, abdu5039@mylaurier.ca
 *
 * @version 2025-01-26
 * -------------------------------------
 */
#include "functions.h"

void int_array_read(int *array, int size) {

	char input[100];
	int value, result;

	printf("Enter %d values for an array of int.\n", size);

	for (int i = 0; i < size; i++) {
		while (1) {
			printf("Value for index %d: ", i);
			if (fgets(input, sizeof(input), stdin) == NULL) {
				printf("Not a valid integer\n");
				continue;
			}

			result = sscanf(input, "%d", &value);
			if (result == 1) {
				array[i] = value;
				break;
			} else {
				printf("Not a valid integer\n");
			}
		}
	}
}
