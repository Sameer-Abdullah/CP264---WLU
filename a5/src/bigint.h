/**
 * -------------------------------------
 * @project a5
 * @file bigint.h
 * @author Sameer Abdullah
 * @version 2025-02-14
 * -------------------------------------
 */


/*
 * your program signature
 */ 
 
 #ifndef BIGINT_H
 #define BIGINT_H
 #include "dllist.h"
 
 typedef DLL BIGINT;
 BIGINT bigint(char *digitstr);
 BIGINT bigint_add(BIGINT oprand1, BIGINT oprand2);
 BIGINT bigint_fibonacci(int n);
 
 #endif