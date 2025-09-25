/**
 * -------------------------------------
 * @project a7
 * @file set_avl.c
 * @author Sameer Abdullah
 * @version 2025-03-14
 * -------------------------------------
 */

#include "string.h"
#include "avl.h"
#include "set_avl.h"

int set_size(SET *s) {
	return s ? s->size : 0;
}

int set_contain(SET *s, char *e) {
	return avl_search(s->root, e) != NULL;
}

void set_add(SET *s, char *e) {
	if (!set_contain(s, e)) {
		RECORD rec;
		strcpy(rec.name, e);
		rec.score = 0;
		avl_insert(&s->root, rec);
		s->size++;
	}
}

void set_remove(SET *s, char *e) {
	if (set_contain(s, e)) {
		avl_delete(&s->root, e);
		s->size--;
	}
}

void set_clean(SET *s) {
	avl_clean(&s->root);
	s->size = 0;
}

