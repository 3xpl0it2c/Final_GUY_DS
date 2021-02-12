#include <stdio.h>
#include <stdlib.h>

const int STUDENT_MAP_SIZE = 17;

#include "binTree.h"
#include "bool.h"
#include "hash.h"
#include "heap.h"
#include "student.h"

bnode_t *students[STUDENT_MAP_SIZE];

heap_t *avgHeap = NULL;

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

void addCourse(student_t *st, course_t *c) {
  // Assign a course to a student
  const int REALLOC_STEP = 10;
  array_course *courses = st->courses;

  if (st->coursesNum < (courses->totalSize - 1)) {
    int newSize = courses->totalSize + REALLOC_STEP;
    courses->data = realloc(courses->data, newSize);
    courses->totalSize = newSize;
  }

  courses->data[st->coursesNum] = c;
  st->coursesNum++;

  double newAverage = getAverage(st);

  heapUpdate(avgHeap, st, newAverage);
}

int changeGrade(unsigned long stID, course_t *c, int newGrade) {
  // Change the grade of a student in a certain course
  course_t *tmp;
  struct Student *st = getStudent(stID);
  int numOfCourses = st->coursesNum;

  for (int i = 0; i < numOfCourses; i++) {
    tmp = st->courses->data[i];
    if (tmp->id == c->id) {
      tmp->grade = newGrade;
      double newAverage = getAverage(st);

      heapUpdate(avgHeap, st, newAverage);
      return true;
    }
  }

  return false;
}

int main(void) {
  struct Student *s1 = newStudent(12345678);
  struct Course *csCoruse = newCourse(1234, 82);

  initHeap(avgHeap, STUDENT_MAP_SIZE);

  for (int i = 0; i < STUDENT_MAP_SIZE; i++)
    students[i] = NULL;

  printStudent(s1);

  insertStudent(s1);
  addCourse(s1, csCoruse);

  printStudent(s1);

  return 0;
}
