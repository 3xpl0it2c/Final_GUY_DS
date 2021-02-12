#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int STUDENT_MAP_SIZE = 17;

#include "binTree.h"
#include "bool.h"
#include "hash.h"
#include "heap.h"
#include "student.h"

#define RANDOM_ID ((100000000 + 2 * 3 * 4 * 5 * 6 * 7 * rand()) % (1000000000))
#define MAX_COURSES_PER_STUDENT 8

#ifndef MAX_GRADE
#define MAX_GRADE 100
#endif

bnode_t *students[STUDENT_MAP_SIZE];

heap_t *avgHeap = NULL;

void insertStudent(struct Student *st) {
  unsigned long studentPosition = hash(st->id, STUDENT_MAP_SIZE);
  double calculatedAvg = calcAverage(st);
  struct StudentAverage *stAvg = newStudentAverage(calculatedAvg, st->id);

  if (students[studentPosition] != NULL)
    insertIntoTree(students[studentPosition], st);
  else
    students[studentPosition] = newBNode(st);

  st->heapPosition = heapInsert(avgHeap, stAvg);
}

course_t *randomCourse(void) {
  int randomGrade = rand() % MAX_GRADE;
  return newCourse(RANDOM_ID, randomGrade);
}

int main(void) {
  srand(time(NULL));
  avgHeap = initHeap(avgHeap, STUDENT_MAP_SIZE);

  for (int i = 0; i < STUDENT_MAP_SIZE; i++)
    students[i] = NULL;

  return 0;
}
