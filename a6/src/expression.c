/**
 * -------------------------------------
 * @project a6
 * @file expression.c
 * @author Sameer Abdullah
 * @version 2025-02-25
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression.h"

QUEUE infix_to_postfix(char *infixstr) {
	STACK operatorStack = { 0, NULL };
	QUEUE outputQueue = { 0, NULL, NULL };

	char *p = infixstr;

	while (*p) {
		int type = mytype(*p);

		if (type == 0) { // Operand
			int num = 0;
			while (*p >= '0' && *p <= '9') { // Capture full multi-digit number
				num = num * 10 + (*p - '0');
				p++;
			}
			enqueue(&outputQueue, new_node(num, type));
			p--; // Adjust pointer since the main loop also increments it
		} else if (type == 2) { // Left parenthesis
			push(&operatorStack, new_node(*p, type));
		} else if (type == 3) { // Right parenthesis
			while (operatorStack.top && operatorStack.top->type != 2) {
				enqueue(&outputQueue, pop(&operatorStack));
			}
			pop(&operatorStack); // Remove left parenthesis
		} else if (type == 1) { // Operator
			while (operatorStack.top
					&& priority(operatorStack.top->data) >= priority(*p)) {
				enqueue(&outputQueue, pop(&operatorStack));
			}
			push(&operatorStack, new_node(*p, type));
		}
		p++;
	}

	while (operatorStack.top) {
		enqueue(&outputQueue, pop(&operatorStack));
	}

	return outputQueue;
}

int evaluate_postfix(QUEUE queue) {
	STACK valueStack = { 0, NULL };

	while (queue.front) {
		NODE *node = dequeue(&queue);

		if (node->type == 0) { // Operand
			push(&valueStack, new_node(node->data, node->type));
		} else { // Operator
			int b = pop(&valueStack)->data;
			int a = pop(&valueStack)->data;
			int result = 0;

			switch (node->data) {
			case '+':
				result = a + b;
				break;
			case '-':
				result = a - b;
				break;
			case '*':
				result = a * b;
				break;
			case '/':
				result = a / b;
				break;
			}
			push(&valueStack, new_node(result, 0)); // Store result as integer
		}
		free(node);
	}

	int finalResult = pop(&valueStack)->data;
	return finalResult;
}

int evaluate_infix(char *infixstr) {
	QUEUE postfixQueue = infix_to_postfix(infixstr);
	return evaluate_postfix(postfixQueue);
}
