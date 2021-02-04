#include <stdio.h>
#include <stdlib.h>

const int STUDENT_MAP_SIZE = 17;

#include "student.h"
#include "binTree.h"
#include "hash.h"
#include "heap.h"

bnode_t* students[STUDENT_MAP_SIZE];

heap_t* avgHeap;

void insertStudent(struct Student* st) {
	unsigned long studentHash = hash(st->id, STUDENT_MAP_SIZE);
	double calculatedAvg = getAverage(st);
	struct BNode* treeInStudentPos = students[studentHash];
	struct StudentAverage* stAvg = newStudentAverage(calculatedAvg, st->id);

	st->heapPosition = heapInsert(avgHeap, stAvg);

	if (treeInStudentPos != NULL) insertIntoTree(treeInStudentPos, st);
	// treeInStudentPos only holds the value instead of pointing to that element of the array.
	else students[studentHash] = newBNode(st);
}

void updateStudent(struct Student* st) {
	double calculatedAvg = getAverage(st);
}

int main(void) {
	struct Student* s1 = newStudent(12345678);
	avgHeap = malloc(sizeof(heap_t));

	for (int i = 0; i < STUDENT_MAP_SIZE; i++)
		students[i] = NULL;

	printStudent(s1);

	return 0;
}
