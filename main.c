#include <stdio.h>
#include <stdlib.h>

const int STUDENT_MAP_SIZE = 17;

#include "binTree.h"
#include "hash.h"
#include "heap.h"
#include "student.h"

bnode_t *students[STUDENT_MAP_SIZE];

heap_t *avgHeap;

void insertStudent(struct Student *st) {
  unsigned long studentPosition = hash(st->id, STUDENT_MAP_SIZE);
  double calculatedAvg = getAverage(st);
  struct StudentAverage *stAvg = newStudentAverage(calculatedAvg, st->id);

  if (students[studentPosition] != NULL)
    insertIntoTree(students[studentPosition], st);
  else
    students[studentPosition] = newBNode(st);

  st->heapPosition = heapInsert(avgHeap, stAvg);
}

int main(void) {
  struct Student *s1 = newStudent(12345678);
  struct Course *csCoruse = newCourse(1234, 82);

  avgHeap = malloc(sizeof(heap_t));

  initHeap(avgHeap, STUDENT_MAP_SIZE);

  for (int i = 0; i < STUDENT_MAP_SIZE; i++)
    students[i] = NULL;

  printStudent(s1);

  insertStudent(s1);
  addCourse(s1, csCoruse);

  printStudent(s1);

  return 0;
}
