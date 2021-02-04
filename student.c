#include <stdio.h>
#include <stdlib.h>

#include "bool.h"
#include "student.h"
#include "binTree.h"
#include "hash.h"

#define MAX_GRADE 100
#define MIN_GRADE 0

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

course_t* newCourse(unsigned int id, int grade) {
	// Can't have a course with a grade of 300 or -200 right ?
	if (grade <= MIN_GRADE && grade > MAX_GRADE) return NULL;

	course_t* c = malloc(sizeof(course_t));
	c->id = id;
	c->grade = grade;

	return c;
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



void addCourse(student_t* s, course_t* c) {
	// Assign a course to a student
	array_course* courses = s->courses;

	if(s->coursesNum < courses->totalSize) {
		int newSize = courses->totalSize * 2;
		courses->data = realloc(courses->data, newSize);
		courses->totalSize = newSize;
	}

	s->coursesNum++;
	courses->data[s->coursesNum] = c;
}

int changeGrade(unsigned long stID, course_t* c) {
	course_t* tmp;
	struct Student* st = getStudent(stID);
	int numOfCourses = st->coursesNum;

	for (int i = 0; i < numOfCourses; i++) {
		tmp = st->courses->data[i];
		if (tmp->id == c->id) {
			tmp->grade = c->grade;
			return true;
		}
	}

	return false;
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