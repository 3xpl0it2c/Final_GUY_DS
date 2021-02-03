#include <stdlib.h>

const int STUDENT_MAP_SIZE = 17;

#include "student.h"
#include "binTree.h"
#include "hash.h"
#include "heap.h"

bnode_t* students[STUDENT_MAP_SIZE];

heap_t* avgHeap;

void insertStudent(struct Student* st) {
	double calculatedAvg = getAverage(st);
	struct StudentAverage* stAvg = newStudentAverage(calculatedAvg, st->id);

	st->heapPosition = heapInsert(avgHeap, stAvg);
}

int main(void) {
	avgHeap = malloc(sizeof(heap_t));

	for (int i = 0; i < STUDENT_MAP_SIZE; i++)
		students[i] = NULL;

	return 0;
}
