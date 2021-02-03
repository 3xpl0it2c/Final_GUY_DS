#include <stdlib.h>
#include "heap.h"
#include "student.h"

#define heapRight(i) ((i * 2) + 2)
#define heapLeft(i) ((i * 2) + 1)
#define heapParent(i) ((i - 1) / 2)

void freeHeap(heap_t* h) {
	for (int i = 0; i < h->size; i++) {
		free(h->data[i]);
	}

	free(h->data);
	free(h);
}

void initHeap(heap_t* h, int capacity) {
	h->data = calloc(sizeof(stdavg_t*), capacity);
	h->capacity = capacity;
	h->size = 0;
}

void updateHeapPos(unsigned long id, int newHeapPos) {
	struct Student* s = getStudent(id);
	s->heapPosition = newHeapPos;
}

int maxByIndex(stdavg_t* array[], int a, int b) {
	struct StudentAverage* avgA = array[a];
	struct StudentAverage* avgB = array[b];

	return avgA->data > avgB->data ? a : b;
}

void swap(stdavg_t* array[], int a, int b) {
	unsigned long idStudentA = array[a]->id;
	unsigned long idStudentB = array[b]->id;

	updateHeapPos(idStudentA, b);
	updateHeapPos(idStudentB, a);

	struct StudentAverage* tmp = array[a];

	array[a] = array[b];
	array[b] = tmp;
}

void heapifyUp(heap_t* heap, int i) {
	if (i < 0) return;

	struct StudentAverage* parent = heap->data[heapParent(i)];
	struct StudentAverage* currentIndex = heap->data[i];

	if (parent->data < currentIndex->data) {
		swap(heap->data, i, heapParent(i));
		return heapifyUp(heap, heapParent(i));
	}

	return;
}

void heapifyDown(heap_t* heap, int i) {
	if (i > heap->size) return;

	int leftRightMax = maxByIndex(heap->data, heapLeft(i), heapRight(i));
	int largest = maxByIndex(heap->data, i, leftRightMax);

	if (i != largest) {
		swap(heap->data, i, largest);
		return heapifyDown(heap, i);
	}

	return;
}

int heapInsert(heap_t* h, stdavg_t* key) {
	if(h->size == h->capacity) {
		h->capacity += 10;
		h->data = realloc(h->data, sizeof(int) * h->capacity);
	}

	int i = h->size;

	while (i>=1 && h->data[heapParent(i)]->data < key->data) {
		h->data[i] = h->data[heapParent(i)];
		i = heapParent(i);
	}

	h->data[i] = key;
	h->size++;

	return i;
}
