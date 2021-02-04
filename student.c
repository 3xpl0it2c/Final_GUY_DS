#include <stdlib.h>
#include "binTree.h"
#include "student.h"
#include "hash.h"

extern int STUDENT_MAP_SIZE;
extern bnode_t* students[];

student_t* newStudent(unsigned long studentID) {
	// Allocate memory for a new student.
	student_t* student = malloc(sizeof(struct Student));

	student->id = studentID;
	student->courses = NULL;
	student->heapPosition = -1;
	student->coursesNum = 0;

	return student;
}

stdavg_t* newStudentAverage(double average, unsigned long id) {
	struct StudentAverage* sa = malloc(sizeof(stdavg_t));

	sa->data = average;
	sa->id = id;

	return sa;
}

student_t* getStudent(unsigned long id) {
	int studentPos = hash(id, STUDENT_MAP_SIZE);
	bnode_t* studentBNode = students[studentPos];

	if(!studentBNode) return NULL;

	return studentBNode->key;
}

double getAverage(student_t* st) {
	double gradesSummary = 0;
	double amountOfCourses = (double)st->coursesNum;
	course_t* courses = st->courses->data;

	for(int i = 0; i < amountOfCourses; i++) {
		course_t tmp = courses[i];
		gradesSummary += tmp.grade;
	}

	return gradesSummary / amountOfCourses;
}

