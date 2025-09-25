/**
 * -------------------------------------
 * @project a3
 * @file myword.c
 * @author Sameer Abdullah
 * @version 2025-01-29
 * -------------------------------------
 */
#include "myword.h"

#include <string.h>

int create_dictionary(FILE *fp, char *dictionary) {
	int count = 0;
	char word[20];
	while (fscanf(fp, "%s", word) != EOF) {
		strcat(dictionary, word);
		strcat(dictionary, " ");
		count++;
	}
	return count;
}

BOOLEAN contain_word(char *dictionary, char *word) {
	return strstr(dictionary, word) ? TRUE : FALSE;
}

WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary) {
	WORDSTATS stats = { 0, 0, 0 };
	char line[256], *token;

	while (fgets(line, sizeof(line), fp)) {
		stats.line_count++;
		token = strtok(line, " ,.\t\n");

		while (token) {
			stats.word_count++;
			str_lower(token);
			str_trim(token);

			if (!contain_word(dictionary, token)) {
				int found = FALSE;
				for (int i = 0; i < stats.keyword_count; i++) {
					if (strcmp(words[i].word, token) == 0) {
						words[i].count++;
						found = TRUE;
						break;
					}
				}
				if (!found) {
					strcpy(words[stats.keyword_count].word, token);
					words[stats.keyword_count].count = 1;
					stats.keyword_count++;
				}
			}
			token = strtok(NULL, " ,.\t\n");
		}
	}
	return stats;
}

