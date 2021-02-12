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
void updateHeapPos(unsigned long, int);
void initHeap(heap_t *, int);
void printStdAvg(stdavg_t *);
void heapUpdate(heap_t *, student_t *, double);
void printHeap(heap_t *);
