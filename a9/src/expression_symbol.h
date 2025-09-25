/**
 * -------------------------------------
 * @project a9
 * @file expression_symbol.h
 * @author Sameer Abdullah
 * @version 2025-03-20
 * -------------------------------------
 */

#ifndef EXPRESSION_SYMBOL_H
#define EXPRESSION_SYMBOL_H

#include "common_queue_stack.h"
#include "hash.h"

QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr);

int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr);

int evaluate_postfix(QUEUE queue);

DATA evaluate_statement(HASHTABLE *ht, char *statement);

#endif
