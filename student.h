#pragma once

struct Course {
  int id;
  int grade;
};

struct CourseArray {
  unsigned int totalSize;
  struct Course **data;
};

struct Student {
  unsigned long id;
  struct CourseArray *courses;
  int coursesNum;
  int heapPosition;
};

struct StudentAverage {
  double data;
  unsigned long id;
};

typedef struct Course course_t;
typedef struct CourseArray array_course;
typedef struct Student student_t;
typedef struct StudentAverage stdavg_t;

student_t *newStudent(unsigned long);
student_t *getStudent(unsigned long id);
course_t *newCourse(unsigned int, int);
stdavg_t *newStudentAverage(double, unsigned long);

double calcAverage(student_t *);
void printStudent(student_t *);
