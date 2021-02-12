#pragma once
#include "student.h"

struct Heap {
  int size;
  int capacity;
  stdavg_t **data;
} typedef heap_t;

void heapifyUp(heap_t *, int);
void heapifyDown(heap_t *, int);
int heapInsert(heap_t *, stdavg_t *);
void heapUpdate(heap_t *, student_t *, double);
stdavg_t *getByIndex(heap_t *, int);
void updateHeapPos(unsigned long, int);
heap_t *initHeap(heap_t *, int);
void printStdAvg(stdavg_t *);
void printHeap(heap_t *);
