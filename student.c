#include "student.h"
#include "binTree.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

extern int STUDENT_MAP_SIZE;
extern bnode_t *students[];

student_t *newStudent(unsigned long studentID) {
  // Allocate memory for a new student.
  struct Student *student = malloc(sizeof(struct Student));

  student->id = studentID;
  student->courses = malloc(sizeof(struct CourseArray));
  student->courses->data = NULL;
  student->courses->totalSize = 0;
  student->heapPosition = -1;
  student->coursesNum = 0;

  return student;
}

stdavg_t *newStudentAverage(double average, unsigned long id) {
  struct StudentAverage *sa = malloc(sizeof(stdavg_t));

  sa->data = average;
  sa->id = id;

  return sa;
}

student_t *getStudent(unsigned long id) {
  int studentPos = hash(id, STUDENT_MAP_SIZE);
  bnode_t *studentBNode = students[studentPos];

  if (!studentBNode)
    return NULL;

  return studentBNode->key;
}

double getAverage(student_t *st) {
  double gradesSummary = 0;
  double amountOfCourses = (double)st->coursesNum;
  course_t **courses = st->courses->data;

  for (int i = 0; i < amountOfCourses; i++) {
    course_t *tmp = courses[i];
    gradesSummary += tmp->grade;
  }

  return gradesSummary / amountOfCourses;
}

void printCourse(course_t *c) {
  printf("Course ID: %d\n", c->id);
  printf("Course Grade: %d\n", c->grade);
}

void printStudent(student_t *st) {
  printf("Student ID: %lu\n", st->id);
  printf("Heap Position: %d\n", st->heapPosition);

  printf("Courses:\n");
  if (st->courses->totalSize == 0) {
    printf("No Courses !\n");
  } else {
    for (int i = 0; i < st->courses->totalSize; i++) {
      printCourse(st->courses->data[i]);
    }
  }
}