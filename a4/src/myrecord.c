/**
 * -------------------------------------
 * @project a4
 * @file	myrecord.c
 * @author Sameer Abdullah
 * @version 2025-02-06
 * -------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "myrecord.h"
#include "mysort.h"

GRADE grade(float score) {
	GRADE r = { "F" };

	if (score >= 90)
		strcpy(r.letter_grade, "A+");
	else if (score >= 85)
		strcpy(r.letter_grade, "A");
	else if (score >= 80)
		strcpy(r.letter_grade, "A-");
	else if (score >= 77)
		strcpy(r.letter_grade, "B+");
	else if (score >= 73)
		strcpy(r.letter_grade, "B");
	else if (score >= 70)
		strcpy(r.letter_grade, "B-");
	else if (score >= 67)
		strcpy(r.letter_grade, "C+");
	else if (score >= 63)
		strcpy(r.letter_grade, "C");
	else if (score >= 60)
		strcpy(r.letter_grade, "C-");
	else if (score >= 57)
		strcpy(r.letter_grade, "D+");
	else if (score >= 53)
		strcpy(r.letter_grade, "D");
	else if (score >= 50)
		strcpy(r.letter_grade, "D-");

	return r;
}

int compare_scores(const void *a, const void *b) {
	RECORD *recordA = (RECORD*) a;
	RECORD *recordB = (RECORD*) b;

	if (recordA->score < recordB->score) {
		return -1;
	} else if (recordA->score > recordB->score) {
		return 1;
	} else {
		return 0;
	}
}

int import_data(FILE *fp, RECORD *dataset) {
	int count = 0;
	while (fscanf(fp, "%19[^,],%f\n", dataset[count].name,
			&dataset[count].score) == 2) {
		count++;
	}
	return count;
}

STATS process_data(RECORD *dataset, int count) {
	STATS stats = { count, 0.0, 0.0, 0.0 };
	float sum = 0.0;
	float sum_squared_diff = 0.0;
	float median = 0.0;

	for (int i = 0; i < count; i++) {
		sum += dataset[i].score;
	}
	stats.mean = sum / count;

	for (int i = 0; i < count; i++) {
		sum_squared_diff += (dataset[i].score - stats.mean)
				* (dataset[i].score - stats.mean);
	}
	stats.stddev = sqrt(sum_squared_diff / count);

	my_sort((void**) dataset, 0, count - 1,
			(int (*)(void*, void*)) compare_scores);

	if (count % 2 == 0) {
		median = (dataset[count / 2 - 1].score + dataset[count / 2].score) / 2;
	} else {
		median = dataset[count / 2].score;
	}
	stats.median = median;

	return stats;
}

int report_data(FILE *fp, RECORD *dataset, STATS stats) {
	if (stats.count < 1)
		return 0;

	fprintf(fp, "Record count: %d\n", stats.count);
	fprintf(fp, "Average score: %.2f\n", stats.mean);
	fprintf(fp, "Standard deviation: %.2f\n", stats.stddev);
	fprintf(fp, "Median score: %.2f\n\n", stats.median);

	for (int i = 0; i < stats.count; i++) {
		GRADE g = grade(dataset[i].score);
		fprintf(fp, "Name: %-20s Score: %.2f Grade: %s\n", dataset[i].name,
				dataset[i].score, g.letter_grade);
	}

	return 1;
}

