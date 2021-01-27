#pragma once

struct Course {
	int id;
	int grade;
};

struct CourseArray {
	unsigned int totalSize;
	struct Course* data;
};

struct Student {
	unsigned long id;
	struct CourseArray* courses;
	int coursesNum;
	int heapPosition;
};

typedef struct Course course_t;
typedef struct CourseArray array_course;
typedef struct Student student_t;
