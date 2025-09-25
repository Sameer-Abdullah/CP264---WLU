/**
 * -------------------------------------
 * @project a2
 * @file fibonacci.c
 * @author Sameer Abdullah
 * @version 2025-01-23
 * -------------------------------------
 */
#include "fibonacci.h"

/**
 * Compute and return the nth Fibonacci number F(n) using iterative algorithm,
 *  namely using a for or while loop.
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number
 */
int iterative_fibonacci(int n) {
	if (n <= 1) {
		return n;
	}
	int a = 0, b = 1, result = 0;

	for (int i = 2; i <= n; i++) {
		result = a + b;
		a = b;
		b = result;
	}
	return result;
}

/**
 * Cmpute and return the nth Fibonacci number F(n) using recurisve algorithm,
 *  namely using recursion function.
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number
 */
int recursive_fibonacci(int n) {
	if (n <= 1) {
		return n;
	}
	return (recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2));
}

/**
 * Cmpute and return the nth Fibonacci number F(n) using recurisve algorithm,
 *  namely using recursion function.
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number
 */
int dpbu_fibonacci(int *f, int n) {
	f[0] = 0;
	if (n > 0) {
		f[1] = 1;
	}
	for (int i = 2; i <= n; i++) {
		f[i] = f[i - 1] + f[i - 2];
	}
	return f[n];
}

/**
 * Cmpute and return the nth Fibonacci number F(n) using dynamic programming
 * top-down method with external array f[n+1] of initial value -1 for all elements.
 * Namely it fills up f[n+1] by recursion function call. Specifically it returns
 * f[n] if f[n]>0 else sets f[n] = dptd_fibonacci(f, n-2) + dptd_fibonacci(f, n-1)
 * and then returns f[n]
 *
 * @param n - the n for F(n)
 * @return - the nth Fibonacci number F(n).
 */
int dptd_fibonacci(int *f, int n) {
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	}
	if (f[n] != -1) {
		return f[n];
	}
	f[n] = dptd_fibonacci(f, n - 1) + dptd_fibonacci(f, n - 2);
	return f[n];
}

int main() {
	return 0;
}
