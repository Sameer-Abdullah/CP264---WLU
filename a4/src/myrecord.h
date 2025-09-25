/**
 * -------------------------------------
 * @project a4
 * @file	myrecord.h
 * @author Sameer Abdullah
 * @version 2025-02-06
 * -------------------------------------
 */
#ifndef MYRECORD_H
#define MYRECORD_H
#include "mysort.h"

typedef struct {
	char name[20];
	float score;
} RECORD;

typedef struct {
	int count;
	float mean;
	float stddev;
	float median;
} STATS;

typedef struct {
	char letter_grade[3];
} GRADE;

GRADE grade(float score);

int import_data(FILE *fp, RECORD *dataset);

STATS process_data(RECORD *dataset, int count);

int report_data(FILE *fp, RECORD *dataset, STATS stats);

#endif

