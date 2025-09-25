/**
 * -------------------------------------
 * @project a1
 * @file   quadratic.c
 * @author Sameer Abdullah
 * @version 2025-01-16
 * -------------------------------------
 */
#include "quadratic.h"
#include <math.h>

/**
 * Compute and return solution type of given quadratic equation ax*x + bx + c = 0
 *
 * @param a - quadratic coefficient
 * @param b -Linear coefficient
 * @param c - constant coefficient
 * @return - 0 if not quadratic equation, i.e. a = 0
 * 			 1 for one unique real solution;
 * 			 2 for two distinct real solutions;
 * 			 3 for two complex solutions;
 */
int solution_type(float a, float b, float c) {
	if (a == 0) {
		return 0;
	}

	float root1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	float root2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

	if (root1 == root2) {
		return 1;
	} else if (isnan(root1) || isnan(root2)) {
		return 3;
	} else {
		return 2;
	}
}

/**
 * Compute and return unique or bigger real roots of given quadratic equation ax*x + bx + c = 0 of types 1 and 2
 *
 * @param a - quadratic coefficient
 * @param b - linear coefficient
 * @param c - constant coefficient
 * @return - the unique real root or the bigger real root if the quadratic equation has two distinct real roots
 * 			 otherwise return 0
 */
float real_root_bit(float a, float b, float c) {
	int sol_type = solution_type(a, b, c);
	if (sol_type == 1) {
		return (-b) / (2 * a);
	} else if (sol_type == 2) {
		float root1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		float root2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		return (root1 > root2) ? root1 : root2;
	} else {
		return 0;
	}
}

/**
 * Compute and return unique or smaller real roots of given quadratic equation ax*x + bx + c = 0 of types 1 and 2.
 * @param a  - quadratic coefficient
 * @param b  - linear coefficient
 * @param c - constant coefficient
 * @return - 0 if not a == 0
 *  	 	 1 if having two complex solutions
 *	 	 	 2 if the unique real root or the smaller real root if the quadratic equation has two distinct real roots
 * 			 otherwise, return 0.
 */
float real_root_small(float a, float b, float c) {
	int sol_type = solution_type(a, b, c);
	if (sol_type == 1) {
		return (-b) / (2 * a);
	} else if (sol_type == 2) {
		float root1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		float root2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		return (root1 < root2) ? root1 : root2;
	} else {
		return 0;
	}
}

