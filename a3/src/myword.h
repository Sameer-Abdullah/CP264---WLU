/**
 * -------------------------------------
 * @project a3
 * @file	myword.h
 * @author Sameer Abdullah
 * @version 2025-01-29
 * -------------------------------------
 */
#include <stdio.h>
#ifndef MYWORD_H_
#define MYWORD_H_

/*
 * Define enumeration type BOOLEAN with value FALSE = 0 and TRUE 1.
 */
typedef enum {
	FALSE, TRUE
} BOOLEAN;

/*
 * Define structure type WORD consists of char word[20] to store a word, int count to hold frequency of the word.
 */
typedef struct {
	char word[20];
	int count;
} WORD;

/*
 * Define structure type WORDSTATS consisting of int line_count, int word_count, and int keyword_count to represent
 * to represent the number of lines, number of all words, and the number of different non-common-word in text data.
 */
typedef struct {
	int line_count;
	int word_count;
	int keyword_count;
} WORDSTATS;

/*
 * Load word data from file, and insert words a directory represented by char array.
 *
 * @param  FILE *fp -   file pointer to an opened text file
 * @param *dictionary - char pointer to a char array where dictionary words are stored.
 *                      It's up to your design on how to store words in the char array.
 * @return - the number of words added into the dictionary.
 */
int create_dictionary(FILE *fp, char *dictionnary);

/*
 * Determine if a given word is contained in the given dictionary.
 *
 * @param *dictionary -  char pointer to a char array of given dictionary.
 * @param *word  -  pointer to a given word.
 *
 * @return - TRUE if the word is in the dictionary, FALSE otherwise.
 */
BOOLEAN contain_word(char *dictionary, char *word);

/*
 * Process text data from a file for word statistic information of line count, word count, keyword count, and frequency of keyword.
 *
 * @param *fp -  FILE pointer of input text data file. .
 * @param *words  -  WORD array for keywords and their frequencies.
 * @param *dictionary  -  stop-word/common-word dictionary.
 *
 * @return - WORDSTATS value of processed word stats information.
 */
WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary);

#endif /* MYWORD_H_ */
