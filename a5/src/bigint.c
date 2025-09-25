/**
 * -------------------------------------
 * @project a5
 * @file bigint.c
 * @author Sameer Abdullah
 * @version 2025-02-14
 * -------------------------------------
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "bigint.h"
 
 /*
  * Converts a digit string to a BIGINT object (Doubly Linked List representation).
  */
 BIGINT bigint(char *p) {
     BIGINT bn = {0};
     if (p == NULL) 
         return bn;
     else if (!(*p >= '0' && *p <= '9')) {  // Not a valid digit
         return bn;
     }
     else if (*p == '0' && *(p+1) == '\0') {  // "0" special case
         dll_insert_end(&bn, dll_node(*p - '0'));
         return bn;
     }  
     else { 
         while (*p) {
             if (*p >= '0' && *p <= '9') {
                 dll_insert_end(&bn, dll_node(*p - '0'));
             } else {
                 dll_clean(&bn);
                 break;
             }
             p++;
         }
         return bn;
     }
 }
 
 /*
  * Adds two BIGINT operands and returns the sum as a BIGINT.
  */
 BIGINT bigint_add(BIGINT op1, BIGINT op2) {
     BIGINT sum = {0, NULL, NULL};  // Initialize empty BIGINT
     NODE *ptr1 = op1.end;
     NODE *ptr2 = op2.end;
     int carry = 0;
 
     while (ptr1 != NULL || ptr2 != NULL || carry) {
         int digit1 = (ptr1 != NULL) ? ptr1->data : 0;
         int digit2 = (ptr2 != NULL) ? ptr2->data : 0;
         int digit_sum = digit1 + digit2 + carry;
 
         carry = digit_sum / 10;  // Extract carry
         int new_digit = digit_sum % 10;
 
         dll_insert_start(&sum, dll_node(new_digit));  // Insert at the start
 
         if (ptr1) ptr1 = ptr1->prev;
         if (ptr2) ptr2 = ptr2->prev;
     }
 
     return sum;
 }
 
 /*
  * Computes the Fibonacci sequence up to n and returns Fibonacci(n) as a BIGINT.
  */
 BIGINT bigint_fibonacci(int n) {
     if (n == 0) return bigint("0");
     if (n == 1) return bigint("1");
 
     BIGINT a = bigint("0");
     BIGINT b = bigint("1");
 
     for (int i = 2; i <= n; i++) {
         BIGINT temp = bigint_add(a, b);
         dll_clean(&a);  // Free the previous "a"
         a = b;          // Move "b" to "a"
         b = temp;       // Assign the new Fibonacci value to "b"
     }
 
     dll_clean(&a);  // Free the last unused variable
     return b;
 }
 