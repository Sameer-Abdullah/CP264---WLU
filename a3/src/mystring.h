/**
 * -------------------------------------
 * @project a3
 * @file mystring.h
 * @author Sameer Abdullah
 * @version 2025-01-27
 * -------------------------------------
 */
#include <stdio.h>
#ifndef MYSTRING_H_
#define MYSTRING_H_

/**
 * Count the number words of given simple string. A word starts with an English character end with a character of space, tab, comma,  or period
 *
 * @param s - char pointer to a string
 * @return - return the number of words.
 */
int str_words(char *s);

/**
 * Change every upper case English letter to its lower case of string passed by s
 *
 * @param s - char pointer to a string
 * @return - return the number of actual flips.
 */
int str_lower(char *s);

/**
 * Remove unnecessary space characters in a simple string passed by `s`
 *
 * @param s - char pointer to a string
 */
void str_trim(char *s);

#endif /* MYSTRING_H_ */
