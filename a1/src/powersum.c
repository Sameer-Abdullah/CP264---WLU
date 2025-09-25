/**
 * -------------------------------------
 * @project a1
 * @file   powersum.c
 * @author Sameer Abdullah
 * @version 2025-01-15
 * -------------------------------------
 */
#include "powersum.h"

/**
 * Depect if overflow in power computing of b to power of n
 *
 * @param b - the base
 * @param n - the exponent
 * @return - if overflow happens, 0 otherwise.
 */
int power_overflow(int b, int n) {

	int result = 1;
	int INT_MAX = 2147483647;

	for (int i = 0; i < n; i++) {
		if (result > INT_MAX / b) {
			return 1;
		}
		result *= b;
	}
	return 0;
}

/**
 * Compute and return b to the power of n
 *
 * @param b - the base
 * @param n - the exponent
 * @return - b to the power of n if no overflow happens, 0 otherwise
 */
int mypower(int b, int n) {

	int result = 1;
	if (power_overflow(b, n)) {
		return 0;
	} else {
		for (int i = 0; i < n; i++) {
			result *= b;
		}
		return result;
	}

}

/**
 * Compute and return the sum of powers
 *
 * @param b - the base
 * @param n - the exponent
 * @return - the sum of powers if no overflow happens, 0 otherwise
 */

int powersum(int b, int n) {
	if (power_overflow(b, n)) {
		return 0;
	}

	int sum = 1;
	for (int i = 1; i <= n; i++) {
		sum += mypower(b, i);
		if (sum < 0) {
			return 0;
		}
	}
	return sum;

}

