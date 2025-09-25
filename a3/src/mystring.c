/**
 * -------------------------------------
 * @project a3
 * @file mystring.c
 * @author Sameer Abdullah
 * @version 2025-01-27
 * -------------------------------------
 */
#include "mystring.h"

int str_words(char *s) {
	int count = 0;
	int in_word = 0;
	while (*s) {
		if ((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z')) {
			if (!in_word) {
				count++;
				in_word = 1;
			}
		} else if (*s == ' ' || *s == '\t' || *s == ',' || *s == '.') {
			in_word = 0;
		}
		s++;
	}
	return count;
}

int str_lower(char *s) {
	int flips = 0;
	while (*s) {
		if (*s >= 'A' && *s <= 'Z') {
			*s += ('a' - 'A');
			flips++;
		}
		s++;
	}
	return flips;
}

void str_trim(char *s) {
	char *d = s;
	int space_found = 0;

	while (*s) {
		if (*s == ' ' || *s == '\t') {
			if (!space_found && d != s) {
				*d++ = ' ';
				space_found = 1;
			}
		} else {
			*d++ = *s;
			space_found = 0;
		}
		s++;
	}
	*d = '\0';
}

int main() {
	return 0;
}
