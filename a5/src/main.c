#include "bigint.h"
#include <stdio.h>

/*
 * Prints a BIGINT (Doubly Linked List) as a number.
 */
void print_bigint(BIGINT big) {
    NODE *current = big.start;
    while (current != NULL) {
        printf("%d", current->data);
        current = current->next;
    }
}

/*
 * Main function to match the expected test output.
 */
int main() {
    printf("\n------------------\nTest: bigint\n\n");

    BIGINT num1 = bigint("111");
    printf("bigint(111): ");
    print_bigint(num1);
    printf("\n");

    BIGINT num2 = bigint("2222");
    printf("bigint(2222): ");
    print_bigint(num2);
    printf("\n");

    BIGINT num3 = bigint("666666666666");
    printf("bigint(666666666666): ");
    print_bigint(num3);
    printf("\n");

    BIGINT num4 = bigint("1111111111111111111");
    printf("bigint(1111111111111111111): ");
    print_bigint(num4);
    printf("\n");

    printf("\n------------------\nTest: bigint_add\n\n");

    BIGINT sum1 = bigint_add(bigint("111"), bigint("222"));
    printf("111+222: ");
    print_bigint(sum1);
    printf("\n");

    BIGINT sum2 = bigint_add(bigint("2222"), bigint("3333"));
    printf("2222+3333: ");
    print_bigint(sum2);
    printf("\n");

    BIGINT sum3 = bigint_add(bigint("666666666666"), bigint("333333333334"));
    printf("666666666666+333333333334: ");
    print_bigint(sum3);
    printf("\n");

    BIGINT sum4 = bigint_add(bigint("1111111111111111111"), bigint("8888888888888888889"));
    printf("1111111111111111111+8888888888888888889: ");
    print_bigint(sum4);
    printf("\n");

    printf("\n------------------\nTest: big_fibonacci\n\n");

    BIGINT fib1 = bigint_fibonacci(1);
    printf("bigint_fibonacci(1): ");
    print_bigint(fib1);
    printf("\n");

    BIGINT fib2 = bigint_fibonacci(2);
    printf("bigint_fibonacci(2): ");
    print_bigint(fib2);
    printf("\n");

    BIGINT fib3 = bigint_fibonacci(3);
    printf("bigint_fibonacci(3): ");
    print_bigint(fib3);
    printf("\n");

    BIGINT fib10 = bigint_fibonacci(10);
    printf("bigint_fibonacci(10): ");
    print_bigint(fib10);
    printf("\n");

    BIGINT fib40 = bigint_fibonacci(40);
    printf("bigint_fibonacci(40): ");
    print_bigint(fib40);
    printf("\n");

    BIGINT fib100 = bigint_fibonacci(100);
    printf("bigint_fibonacci(100): ");
    print_bigint(fib100);
    printf("\n");

    return 0;
}
