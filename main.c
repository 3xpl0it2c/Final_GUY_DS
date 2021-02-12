#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int STUDENT_MAP_SIZE = 17;

#include "binTree.h"
#include "bool.h"
#include "hash.h"
#include "heap.h"
#include "student.h"

#define RANDOM_ID                                                              \
  abs((100000000 + 2 * 3 * 4 * 5 * 6 * 7 * rand()) % (1000000000))
#define MAX_COURSES_PER_STUDENT 8
#define AMOUNT_OF_STUDENTS_FOR_MILGA 5

#ifndef MAX_GRADE
#define MAX_GRADE 100
#endif

bnode_t *students[STUDENT_MAP_SIZE] = {NULL};

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

void addCoursesRandomly(student_t *st) {
  int randomAmountOfCourses = rand() % MAX_COURSES_PER_STUDENT;

  for (int i = 0; i < randomAmountOfCourses; i++) {
    struct Course *course = randomCourse();
    addCourse(st, course);
  }
}

void milga(void) {
  for (int i = 0; i < AMOUNT_OF_STUDENTS_FOR_MILGA; i++) {
    struct StudentAverage *stAvg = heapExtractMax(avgHeap);
    struct Student *st = getStudent(stAvg->id);
    st->heapPosition = -1;

    printStudent(st);
  }
}

int main(void) {
  srand(time(NULL));
  avgHeap = initHeap(avgHeap, STUDENT_MAP_SIZE);
  const char randomStudentIDMsg[] = "Chose random student with ID: %lu";
  const char scholarshipMsg[] = "Printing %d students for scholarship:\n";
  // Decrement 2 since the teacher told so.
  int randomStudentIndex = rand() % (STUDENT_MAP_SIZE - 2);
  student_t *randomStudent = NULL;

  // Decrement 2 since the teacher told so.
  for (int i = 0; i < (STUDENT_MAP_SIZE - 2); i++) {
    struct Student *st = newStudent(RANDOM_ID);
    addCoursesRandomly(st);
    insertStudent(st);
    printStudent(st);

    if (i == randomStudentIndex)
      randomStudent = st;
  }

  printHeap(avgHeap);

  printf(randomStudentIDMsg, randomStudent->id);

  int randomCourseIndex = rand() % randomStudent->coursesNum;
  struct Course *randomCourse = randomStudent->courses->data[randomCourseIndex];

  // In Question 21 the teacher instructed to
  // change the grade of some course to 0.
  changeGrade(randomStudent->id, randomCourse, 0);

  for (int i = 0; i < (STUDENT_MAP_SIZE - 2); i++) {
    printTree(students[i]);
  }

  printHeap(avgHeap);

  printf(scholarshipMsg, AMOUNT_OF_STUDENTS_FOR_MILGA);
  milga();

  printf(scholarshipMsg, AMOUNT_OF_STUDENTS_FOR_MILGA);
  milga();

  return 0;
}
