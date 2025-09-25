/**
 * -------------------------------------
 * @file  functions.c
 * Lab 2 Functions Source Code File
 * -------------------------------------
 * @author Sameer Abdullah, 169065039, abdu5039@mylaurier.ca
 *
 * @version 2025-01-26
 * -------------------------------------
 */
#include "functions.h"

int sum_three_integers(void) {

	int num1, num2, num3;
	char input[100];
	int result;

	while (1) {
		printf("Enter three comma-separated integers: ");
		fgets(input, sizeof(input), stdin);

		result = sscanf(input, "%d,%d,%d", &num1, &num2, &num3);

		if (result == 3) {
			return num1 + num2 + num3;
		} else {
			printf("The integers were not properly entered.\n");
		}

	}
}

