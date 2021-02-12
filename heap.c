#include "heap.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>

#define DOES_NOT_EXIST_IN_HEAP -1
#define heapRight(i) ((i * 2) + 2)
#define heapLeft(i) ((i * 2) + 1)
#define heapParent(i) ((i - 1) / 2)

void freeHeap(heap_t *h) {
  for (int i = 0; i < h->size; i++) {
    free(h->data[i]);
  }

  free(h->data);
  free(h);
}

heap_t *initHeap(heap_t *heap, int capacity) {
  if (!heap)
    heap = malloc(sizeof(struct Heap));

  heap->data = calloc(sizeof(stdavg_t *), capacity);
  heap->capacity = capacity;
  heap->size = 0;

  return heap;
}

// Including this function here and not inside main.c
// Or even inside student.c saves us from caring to update the heap manually.
// Therefore, although in theory this seems weird,
// We pay this price for better DX & less "Forgot to updateHeapPos() !" bugs.
void updateHeapPos(unsigned long id, int newHeapPos) {
  struct Student *s = getStudent(id);

  if (s)
    s->heapPosition = newHeapPos;
}

void updateAllHeapPositions(heap_t *heap) {
  for (int i = 0; i < heap->size; i++) {
    struct StudentAverage *stdAvg = heap->data[i];
    updateHeapPos(stdAvg->id, i);
  }
}

int maxStdAvgInIndex(stdavg_t *array[], int a, int b) {
  // Return the index of the bigger stdAvg inside the given array.
  struct StudentAverage *avgA = array[a];
  struct StudentAverage *avgB = array[b];

  return avgA->data > avgB->data ? a : b;
}

void swap(stdavg_t *array[], int a, int b) {
  unsigned long idStudentA = array[a]->id;
  unsigned long idStudentB = array[b]->id;

  updateHeapPos(idStudentA, b);
  updateHeapPos(idStudentB, a);

  struct StudentAverage *tmp = array[a];

  array[a] = array[b];
  array[b] = tmp;
}

void heapifyUp(heap_t *heap, int i) {
  if (i < 0)
    return updateAllHeapPositions(heap);

  struct StudentAverage *parent = heap->data[heapParent(i)];
  struct StudentAverage *currentIndex = heap->data[i];

  if (parent->data < currentIndex->data) {
    swap(heap->data, i, heapParent(i));
    return heapifyUp(heap, heapParent(i));
  }

  return updateAllHeapPositions(heap);
}

void heapifyDown(heap_t *heap, int i) {
  if (i >= (heap->size - 1))
    return updateAllHeapPositions(heap);

  int leftRightMax = maxStdAvgInIndex(heap->data, heapLeft(i), heapRight(i));
  int largest = maxStdAvgInIndex(heap->data, i, leftRightMax);

  if (i != largest) {
    swap(heap->data, i, largest);
    return heapifyDown(heap, i);
  }

  return updateAllHeapPositions(heap);
}

int heapInsert(heap_t *heap, stdavg_t *key) {
  if (heap->size == heap->capacity) {
    heap->capacity += 10;
    heap->data = realloc(heap->data, sizeof(stdavg_t *) * heap->capacity);
  }

  int i = heap->size;

  while (i >= 1 && heap->data[heapParent(i)]->data < key->data) {
    heap->data[i] = heap->data[heapParent(i)];
    i = heapParent(i);
  }

  heap->data[i] = key;
  heap->size++;

  updateAllHeapPositions(heap);

  return i;
}

stdavg_t *getByIndex(heap_t *heap, int position) {
  if (position == DOES_NOT_EXIST_IN_HEAP)
    return NULL;

  return heap->data[position];
}

void heapUpdate(heap_t *heap, student_t *student, double newValue) {
  // Change the average of certain student, reorganizes the heap.
  if (!heap)
    return;

  int studentAvgIndex = student->heapPosition;

  if (studentAvgIndex == DOES_NOT_EXIST_IN_HEAP)
    return;

  struct StudentAverage *currentAvg = heap->data[studentAvgIndex];

  double oldValue = currentAvg->data;

  currentAvg->data = newValue;

  if (newValue > oldValue)
    heapifyUp(heap, studentAvgIndex);
  else
    heapifyDown(heap, studentAvgIndex);
}

void printStdAvg(stdavg_t *avg) {
  printf("Average for student with id: %lu\n", avg->id);
  printf("Average: %lf\n", avg->data);
}

void printHeap(heap_t *heap) {
  printf("Printing Heap:\n");
  for (int i = 0; i < heap->size; i++) {
    printStdAvg(heap->data[i]);
  }
}
